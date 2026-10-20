#include <iostream>
#include <cstdint>
#include <memory>
#include <string>

#include <vector>

class melon
{  
    int seeds;
    float sweetness;

public:

    melon(int seeds = 100, float sweetness = 3.2)
    : seeds(seeds), sweetness(sweetness)
    {
        std::cout << "Construction!\n";
    };

    ~melon()
    {
        std::cout << "Destructor!\n";
    };


    void print()
    {
        std::cout << "Seeds: " << seeds << '\n';
    }
};


void variables()
{
    uint8_t bytes[12]; 

    // алокираме int върху блок стекова памет
    int *iPtr = new(bytes) int(10);

    // алокираме double върху същия блок стекова памет
    double* dPtr = new(bytes + sizeof(int)) double(3.14f);

    // Какво очакваме?
    std::cout << *iPtr  << '\n';
    std::cout << *dPtr << '\n';    
}    


void classes(void)
{
    char* buffer = new char[100];

    // Един обект заделен върху heap-а
    melon *m1Ptr = new melon(100, 10);

    // Масив от класове заделен върху heap-a 
    melon *mArr = new melon[2];

    // Обект заделен върху буфера
    melon *m2Ptr = new(buffer) melon(10000, 10);

    // Как изтриваме?

    delete m1Ptr;  // извиква се деструктора на обекта и се освобождава паметта

    delete[] mArr; // извиква се деструктора на 2 обекта и се освобождава паметта 


    /*
    *    Обект заделен с placement new се освобождава ръчно с деструктор.
    *    Тъй като е на сурова памет за него не важи RAII и няма да се извика деструктор на delete.
    */
    
    m2Ptr->~melon(); 
    delete[] buffer;
}    


void allocator()
{
    std::allocator<melon> alloc;

    melon *melons = alloc.allocate(3);

    std::construct_at(melons, 1,2);
    std::construct_at(melons + 1, 1,3);

    melons[0].print();
    melons[1].print();

    // Защо това извиква само 1 деструктор?
    std::destroy(melons, melons + 1);
    alloc.deallocate(melons, 3);
}

int main(void)
{
  variables();
  // classes();
  // allocator();
}
