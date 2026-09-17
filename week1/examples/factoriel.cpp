#include <iostream>

size_t fact_itt(size_t n)
{
    size_t res = 1;
    for (size_t i = 2; i <= n; ++i)
    {
        res *= i;
    }
    
    return res;
}

size_t fact_rec(size_t n)
{
    if(n < 2) return 1;
    return n * fact_rec(n - 1);
}

int main(void)
{

    std::cout << fact_rec(6) << '\n';
    return 0;
}