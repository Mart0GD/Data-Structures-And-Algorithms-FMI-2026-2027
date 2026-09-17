#include <iostream>

size_t gcd(size_t a, size_t b)
{
    size_t swap;
    while (b > 0) {
        swap = b;
        b = a % b;
        a = swap;
    }

    return a;
}

size_t gcd_rec(size_t a, size_t b)
{
    return b == 0 ? a : gcd_rec(b, a % b);
}

int main(void)
{
    std::cout << gcd_rec(8,18) << '\n';
}
 