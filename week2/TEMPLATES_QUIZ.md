## Нека видим какво сме разбрали за шаблоните

### Въпрос 1

Какъв ще бъде изхода от този код:

```.cpp
#include <iostream>
using namespace std;

template <typename T>
T max(T x, T y)
{
    return (x > y)? x : y;
}
int main()
{
    cout << max(3, 7) << std::endl;
    cout << max(3.0, 7.0) << std::endl;
    cout << max(3, 7.0) << std::endl;
    return 0;
}
```

<details>
<summary> Отговор </summary>
    Кодът няма да се компилира, тъй като последното извикване има разнородни по тип аргументи 
</details>


### Въпрос 2

Какъв ще бъде изхода от този код:

```.cpp

#include <iostream>
using namespace std;

template <typename T>
void fun(const T& x) {
    static int count = 0;
    cout << count << " ";
    count++;
}

int main() {
    fun<int>(1);
    fun<int>(2);
    fun<double>(3.5);
}

<details>
<summary> Отговор </summary>
    0 1 0 -> това е така, защото всяка инстанция на функцията си има собствена статична променлива 
</details>


### Въпрос 3

Колко очаквате, че ще бъде размера на двете инстанции, ако предположим, че размерът на int е 4 байта, а този на double 8?

```.cpp
#include<iostream>
#include<stdlib.h>
using namespace std;

template<class T, class U, class V=double>
class A  {
    T x;
    U y;
    V z;
    static int count;
};

int main()
{
   A<int, int> a;
   A<double, double> b;
   cout << sizeof(a) << endl;
   cout << sizeof(b) << endl;
   return 0;
}
```

<details>
<summary> Отговор </summary>
    Размерът на A ще бъде `16`, а този на B `24`, тъй като статичната променлива не влиза в размера на типа и имаме типизиран параметър по подразбиране! 
</details>

### Въпрос 4

Какъв е изходът от програмата?

```.cpp
#include <iostream>
using namespace std;

template <int i>
void fun()
{
   i = 20;
   cout << i;
}

int main()
{
   fun<10>();
   return 0;
}
```

<details>
<summary> Отговор </summary>
    Компилационна грешка, шаблонните параметри са константни и не могат да се променят! 
</details>


### Въпрос 5

Коя от двете функции ще се изпълни?

```.cpp
#include <iostream>
using namespace std;

template <class T>
T max (T &a, T &b)
{
    return (a > b)? a : b;
}

template <>
int max <int> (int &a, int &b)
{
    cout << "Called ";
    return (a > b)? a : b;
}

int main ()
{
    int a = 10, b = 20;
    cout << max <int> (a, b);
}
```

<details>
<summary> Отговор </summary>
    Тук имаме пример на шаблонна специализация. При всяка шаблонна функция първо се проверява дали не съществува специализация за конкретното повикване, преди да се създаде изцяло.
</details>

### Въпрос 6

Кодът компилира ли се и ако да какъв е изходът на програмата?

```.cpp
#include <iostream>
using namespace std;
 
template<int n> struct funStruct
{
    static const int val = 2*funStruct<n-1>::val;
};
 
template<> struct funStruct<0>
{
    static const int val = 1 ;
};
 
int main()
{
    cout << funStruct<10>::val << endl;
    return 0;
}
```

<details>
<summary> Отговор </summary>
    Това се нарича метапрограмиране и можем да постигнем функционално поведение изцяло по време на компилация. Тези две структури служат да пресметнат стойността на `2^n`.
</details>


### Въпрос 7

Коя функция ще се извика?

```.cpp
template<class T> void f(T);          // (a)
template<class T> void f(T*);         // (b)
template<>        void f<int*>(int*); // (c)
(...)
int* p; f(p);
```

<details>
<summary> Отговор </summary>
    Отговорът тук е `c`, тъй като тя специализира функцията `b`. Обаче ако `c` е дефинирана преди `b`, то тя ще специализира `a` и ще се извика `b`. Трябва да се внимава с реда на дефиниране! 
</details>
