#include <chrono>
#include <iostream>

int main(void)
{
    std::chrono::microseconds avg = std::chrono::microseconds(0);

    for(int trial = 0; trial < 100; trial++)
    {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        int n = 100;
        int sum = 0;

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                sum++;

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        avg += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

    std::cout << avg / 100;
}
    