#include "seminar_13_10_2026.hpp"
#include "week2/examples/DynamicArray.hpp"
#include <vector>
#include <iostream>

struct no_default_ctor
{
    no_default_ctor();
    private:
};

int main()
{
    // Пример за "генерация на код" - name mangling 
    template_example<int> examp;
    // int val = examp.getVal();
    // examp.someFoo(1);

    sdp::DynamicArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(1);
    arr.pushBack(1);
    arr.pushBack(1);

    // Разгърнат пример на foreach цикъл

    sdp::DynamicArray<int>::ForwardIterator begin = arr.begin();
    sdp::DynamicArray<int>::ForwardIterator end = arr.end();

    for(; begin != end; ++begin)
    {
        std::cout << *begin << std::endl;
    }


    // Същото като горното ама е синтактична захар!

    for(int el : arr)
    {
        std::cout << el << std::endl;
    }

    return 0;
}
