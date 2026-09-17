#include <iostream>

void print(const int* arr, const int size)
{
    std::cout << "{ ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i];
        if(i + 1 < size) std::cout << ", ";
    }
    std::cout << " }\n";
}

void permute_multiset(const int* set, int*& result, int*& used, int u_cnt, int size)
{
    if(u_cnt == size)
    {
        print(result, size);
        return;
    }

    // Допълнители променливи, които следят кой е последния сменен елемент на това ниво от рекурсията
    bool swapped = false;
    int swapped_el = -1;

    for (int i = 0; i < size; i++)
    {
        // Само ако не е използвано и елементите, които разменяме са различни 
        if(used[i] == 0 && (!swapped || swapped_el != set[i]))
        {
            used[i] = 1;
            result[u_cnt++] = set[i];

            swapped = true;
            swapped_el = set[i];

            permute_multiset(set, result, used, u_cnt, size);

            // Връщаме назад, като отмаркираме данните
            used[i] = 0;
            u_cnt--;

        }
    }
    
}

void permute_multiset(const int* set, int size)
{
    int* res = new int[size];
    int* used = new(std::nothrow) int[size];
    if(!used)
    {
        delete[] res;
        std::cerr << "Error: cannot allocate memory!";
        return;
    }

    permute_multiset(set, res, used, 0, size);
    delete[] res;
    delete[] used;
}

void permute(int*& result, int*& used, int u_cnt, int n)
{
    if(u_cnt == n)
    {
        print(result, n);
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        // Само ако не е използвано
        if(used[i - 1] == 0)
        {
            used[i - 1] = 1;
            result[u_cnt++] = i;

            permute(result, used, u_cnt, n);

            // Връщаме назад, като отмаркираме данните
            used[i - 1] = 0;
            u_cnt--;

        }
    }
    
}

void permute(int n)
{
    int* res = new int[n]{};
    int* used = new(std::nothrow) int[n]{};
    if(!used)
    {
        delete[] res;
        std::cerr << "Error: cannot allocate memory!";
        return;
    }

    permute(res, used, 0, n);
    delete[] res;
    delete[] used;
}

void variate(const int* set, int*& res, int u_cnt, int n, int k)
{
    if(u_cnt >= k)
    {
        print(res, u_cnt);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        res[u_cnt] = set[i];
        variate(set, res, u_cnt + 1, n, k);
    }
}

void variate(const int* set, int n, int k)
{
    int* res = new int[k]{};

    variate(set, res, 0, n, k);
    delete[] res;
}

void variate_unique(const int* set, int*& res, int*& used, int u_cnt, int n, int k)
{
    if(u_cnt >= k)
    {
        print(res, u_cnt);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if(used[i] == 0)
        {
            used[i] = 1;

            res[u_cnt] = set[i];
            variate_unique(set, res, used, u_cnt + 1, n, k);

            used[i] = 0;
        }
    }
}

void variate_unique(const int* set, int n, int k)
{
    if(k > n)
    {
        std::cerr << "Invalid data, k cannot be bigger than n!";
        return;
    }

    int* res = new int[k]{};
    int* used = new(std::nothrow) int[k]{};
    if(!used)
    {
        delete[] res;
        std::cerr << "Error: cannot allocate memory!";
        return;
    }


    variate_unique(set, res, used, 0, n, k);

    delete[] res;
    delete[] used;
}

void comb_unique(const int* set, int*& res, int after, int pos, int n, int k)
{
    if(pos == k)
    {
        print(res, k);
        return;
    }

    for (int i = after; i < n; i++)
    {
        res[pos] = set[i];
        comb_unique(set, res, i + 1, pos + 1, n , k);
    }
}

void comb_unique(const int* set, int n, int k)
{
    int* res = new int[k]{};

    comb_unique(set, res, 0, 0, n, k);
    delete[] res;
}

void comb(const int* set, int*& res, int after, int pos, int n, int k)
{
    if(pos == k)
    {
        print(res, k);
        return;
    }

    for (int i = after; i < n; i++)
    {
        res[pos] = set[i];
        comb(set, res, i, pos + 1, n , k);
    }
}

void comb(const int* set, int n, int k)
{
    int* res = new int[k]{};

    comb(set, res, 0, 0, n, k);
    delete[] res;
}

int main(void)
{
    int set[5] = {1,2,3,4,5};
    comb(set, 5, 3);

    return 0;
}