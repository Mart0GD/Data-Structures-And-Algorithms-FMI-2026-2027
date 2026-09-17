#include <iostream>

size_t fib_rec(size_t n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;

    return fib_rec(n - 1) + fib_rec(n - 2);
}

size_t cache[100]{};        // size_t не може да побере повече от 100
size_t fib_memo(size_t n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;

    // Проверка в изчислениете (никога няма да е нула, защото горе я улавяме)
    size_t result = cache[n] == 0 
    ? fib_memo(n - 1) + fib_memo(n - 2)
    : cache[n];

    cache[n] = result;  // Запазваме в кеша

    return result;
}

size_t fib_itt(size_t n)
{
    size_t f1 = 1, f2 = 0;
    size_t tmp;
    while (n--)
    {
        tmp = f1;

        f1 = f1 + f2;
        f2 = tmp;
    }

    return f2;
}

int main(void)
{

    std::cout << fib_memo(50) << '\n';
    return 0;
}