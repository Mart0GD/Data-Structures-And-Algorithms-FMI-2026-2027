#include <iostream>

void print(const int* number, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << number[i];
        if(i + 1 < size) std::cout << " + ";
    }
    std::cout << '\n';
}

void divide_number(int n, int* res, int pos)
{
    if(n == 0)
    {
        print(res, pos);
    }
    else
    {
        for (int i = n; i > 0; i--)
        {
            res[pos] = i;

            if(pos == 0 || res[pos] <= res[pos - 1])  divide_number(n - i, res, pos + 1);
        }
    }
}

void divide_number(int n)
{
    int* res = new int[n];

    divide_number(n, res, 0);
    delete[] res;
}

int main()
{

    divide_number(5);
}