#ifndef SORTED_ARRAY_HPP_INCLUDED
#define SORTED_ARRAY_HPP_INCLUDED

#include <cstdint>
#include <stdexcept>
#include <utility>

// Масив, който винаги държи елементите си сортирани във възходящ ред.
// Изисквания към T: конструктор по подразбиране, присвояване и operator<.
template <typename T>
class SortedArray
{
public:
    class Proxy; // връща се от неконстантния operator[]

    SortedArray();
    SortedArray(const SortedArray& other);
    SortedArray(SortedArray&& other) noexcept;
    SortedArray& operator=(SortedArray other) noexcept; // copy-and-swap: покрива и copy, и move
    ~SortedArray();

    // Modify operations
    void insert(const T& el);
    void remove(uint32_t index);

    // Lookup
    bool find(const T& el) const;

    Proxy    operator[](uint32_t index);
    const T& operator[](uint32_t index) const;

    uint32_t size()  const { return size_; }
    bool     empty() const { return size_ == 0; }

private:
    void     ensure_capacity(uint32_t min_cap);
    void     resize(uint32_t new_cap);
    void     check_index(uint32_t index) const;

    static constexpr uint32_t INITIAL_CAP = 4;

    T*       data_;
    uint32_t size_;
    uint32_t cap_;
};

// ---------------------------------------------------------------------------
// Proxy: позволява arr[i] = x, като след присвояването масивът остава сортиран.
// Вложен клас -> има достъп до private членовете на SortedArray.
// ---------------------------------------------------------------------------
template <typename T>
class SortedArray<T>::Proxy
{
public:
  
    // arr[i] = el: заменя елемента на позиция i и го премества на правилното място.
    // Внимание: след това стойността може вече да не е на позиция i.
    Proxy& operator=(const T& el)
    {
        // Копие първо: el може да е референция към елемент от същия масив
        // (напр. arr[0] = arr[3]), а долу местим елементи.
        T value = el;

        T*       data = owner_->data_;
        uint32_t pos  = index_;

        if (value < data[pos])
        {
            // новата стойност е по-малка -> плъзгаме по-големите съседи надясно
            while (pos > 0 && value < data[pos - 1])
            {
                data[pos] = std::move(data[pos - 1]);
                --pos;
            }
        }
        else
        {
            // новата стойност е по-голяма или равна -> плъзгаме по-малките съседи наляво
            while (pos + 1 < owner_->size_ && data[pos + 1] < value)
            {
                data[pos] = std::move(data[pos + 1]);
                ++pos;
            }
        }

        data[pos] = std::move(value);
        return *this;
    }

    // arr[i] = arr[j]: без това щеше да се копира самото proxy (owner_ и index_),
    // а не стойността.
    Proxy& operator=(const Proxy& other)
    {
        return *this = static_cast<const T&>(other);
    }

    // четене: T x = arr[i]; std::cout << arr[i];
    operator const T&() const { return owner_->data_[index_]; }

private:
    friend class SortedArray<T>; // само SortedArray може да създава Proxy

    Proxy(SortedArray* owner, uint32_t index)
        : owner_(owner), index_(index) {}

    SortedArray* owner_;
    uint32_t     index_;
};

// ---------------------------------------------------------------------------
// Big 5
// ---------------------------------------------------------------------------
template <typename T>
SortedArray<T>::SortedArray()
    : data_(new T[INITIAL_CAP]), size_(0), cap_(INITIAL_CAP) {}

template <typename T>
SortedArray<T>::SortedArray(const SortedArray& other)
    : data_(new T[other.cap_]), size_(other.size_), cap_(other.cap_)
{
    try
    {
        for (uint32_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }
    catch (...)
    {
        delete[] data_;
        throw;
    }
}

template <typename T>
SortedArray<T>::SortedArray(SortedArray&& other) noexcept
    : data_(other.data_), size_(other.size_), cap_(other.cap_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_  = 0;
}

template <typename T>
SortedArray<T>& SortedArray<T>::operator=(SortedArray other) noexcept
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_,  other.cap_);
    return *this;
}

template <typename T>
SortedArray<T>::~SortedArray()
{
    delete[] data_;
}

// ---------------------------------------------------------------------------
// Modify operations
// ---------------------------------------------------------------------------
template <typename T>
void SortedArray<T>::insert(const T& el)
{
    ensure_capacity(size_ + 1);

    // започваме от края и плъзгаме по-големите елементи с една позиция надясно
    uint32_t pos = size_;
    while (pos > 0 && el < data_[pos - 1])
    {
        data_[pos] = std::move(data_[pos - 1]);
        --pos;
    }
    data_[pos] = el;
    ++size_;
}

template <typename T>
void SortedArray<T>::remove(uint32_t index)
{
    check_index(index);

    // i + 1 < size_, за да не четем data_[size_]
    for (uint32_t i = index; i + 1 < size_; ++i)
        data_[i] = std::move(data_[i + 1]);

    --size_;
}

// ---------------------------------------------------------------------------
// Lookup
// ---------------------------------------------------------------------------
template <typename T>
bool SortedArray<T>::find(const T& el) const
{
    // Двоично търсене в полуотворен интервал [l, r).
    // r = size_ (а не size_ - 1), затова няма проблем с празен масив и unsigned.
    uint32_t l = 0, r = size_;
    while (l < r)
    {
        uint32_t middle = l + (r - l) / 2;

        if (data_[middle] < el)
            l = middle + 1;   // el е вдясно
        else if (el < data_[middle])
            r = middle;       // el е вляво; middle вече е изключен от [l, r)
        else
            return true;      // нито <, нито > -> равни
    }
    return false;
}

template <typename T>
typename SortedArray<T>::Proxy SortedArray<T>::operator[](uint32_t index)
{
    check_index(index);
    return Proxy(this, index);
}

template <typename T>
const T& SortedArray<T>::operator[](uint32_t index) const
{
    check_index(index);
    return data_[index];
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------
template <typename T>
void SortedArray<T>::check_index(uint32_t index) const
{
    if (index >= size_)
        throw std::out_of_range("SortedArray: invalid index");
}

template <typename T>
void SortedArray<T>::ensure_capacity(uint32_t min_cap)
{
    if (min_cap <= cap_)
        return;

    uint32_t new_cap = cap_ ? cap_ : INITIAL_CAP; // cap_ е 0 след move
    while (new_cap < min_cap)
        new_cap *= 2;

    resize(new_cap);
}

template <typename T>
void SortedArray<T>::resize(uint32_t new_cap)
{
    T* tmp = new T[new_cap];
    try
    {
        // move_if_noexcept: ако преместването може да хвърли, копираме,
        // така старите данни остават непокътнати при изключение.
        for (uint32_t i = 0; i < size_; ++i)
            tmp[i] = std::move_if_noexcept(data_[i]);
    }
    catch (...)
    {
        delete[] tmp;  // масивът си остава какъвто беше
        throw;
    }

    delete[] data_;
    data_ = tmp;
    cap_  = new_cap;
}

#endif
