# Циклична опашка (Дек)

Dequeue или Double-Ended-Queue е абстрактна структура от данни, която в най-простия си вид позволява добавянето и премахването на елементи в двата края на буфера. Самата идея наподобява имплементация на двусвързан списък с два указателя за достъп - head и tail. Самото име е заблуждаващо, защото структурата прилича както на опашка така и на стек (можете да си я представите като два стека с гръб един за друг).


## Имплементация

**Двусвързан списък**

Можем да напишем дек и чрез едносвързан списък, но няма да е коректен спрямо абстрактната си дефиниция, тъй като няма да можем да поддържаме премахване в края. Поради това за имплементация е най-подходящо да се подходи, именно с двусвързан списък.

**Своиства**

* **Добавяне в началото/края** - приблизително $O(1)$ ако няма алокация на памет.
* **Премахване в началото/края** - $O(1)$.  
* **Достъп до произволен елемент** - $О(n)$.
* **Премахване на произволен елемент** - $O(1)$.

**Масив (Цикличен буфер)**

Друга имеплементация на дек е чрез масив. Идеята наподобява опашка, в това че данните са разположени циклично в буфера на масива. Използват се модулни операции както при добавяне в началото така и в края на масива, за да се възползва структурата максимално от свободното място.

**Как добавяме?**

* **push_front()** -> `data[(head - 1 + cap) % cap] = val`
* **push_back()** -> `data[(head + size) % cap] = val`

Това се прави с цел да се избегнат отрицателните индекси при добавяне в началото!

**Своиства**

* **Добавяне в началото/края** - амортизирано $O(1)$ след достатъчно реалокации.
* **Премахване в началото/края** - $O(1)$.  
* **Достъп до произволен елемент** - $О(1)$.
* **Премахване на произволен елемент** - $O(n)$.

---

## Задачи с циклична опашка (Sliding Window)

**Задача 1**

Даден е масив с големина $n$ и число $k$, което символизира големината на плъзгащ се прозорец. Напишете програма, която в линейно време $O(n)$ да намира най-големите стойности от всички прозорци с големина $k$ в масива. Резултатът върнете в нов масив, с ред на стойностите от ляво на дясно.

~~~.cpp
Пример:
масив = [1,3,-1,-3,5,3,6,7] и k = 3

прозорците са:
[1  3  -1] -3  5  3  6  7   --> 3
 1 [3  -1  -3] 5  3  6  7   --> 3
 1  3 [-1  -3  5] 3  6  7   --> 5
 1  3  -1 [-3  5  3] 6  7   --> 5
 1  3  -1  -3 [5  3  6] 7   --> 6
 1  3  -1  -3  5 [3  6  7]  --> 7
~~~

<details>
  <summary>Решение</summary>

  ~~~.cpp
    #include <vector>
    #include <deque>
    #include <utility>
    
    void push(std::deque<std::pair<int,int>>& queue, int i , std::vector<int>& nums)
    {
        while(!queue.empty() && queue.back().first < nums[i])
        {
            queue.pop_back();
        }
    
        queue.push_back(std::pair<int,int>(nums[i], i));
    }
    
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) 
    {
        std::deque<std::pair<int,int>> monotonic_queue;
        std::vector<int> res;
        
        int itt = 0;
        for(; itt < nums.size(); ++itt)
        {
            // Check if the largest element is outside the window
            if(!monotonic_queue.empty() && monotonic_queue.front().second <= itt - k)
                monotonic_queue.pop_front();
    
            // push current number
            push(monotonic_queue, itt, nums);
    
            // Wait for the for the first window to fill
            if(itt >= k - 1) res.push_back(monotonic_queue.front().first);
        }
    
        return res;
    }
  ~~~
</details>

**Задача 2**

Даден е масив $A$ от цели числа с дължина $n$.За един подмасив $A[i \dots j]$ ($0 \le i \le j < n$) казваме, че е валиден, ако за всеки два негови елемента $A[x]$ и $A[y]$ ($i \le x, y \le j$) е изпълнено условието: 

$$\vert{}A[x] - A[y]\vert{} \le 2$$

Напишете програма, която намира броя на всички валидни подмасива в дадения масив $A$.

~~~
Пример:
масив = [5,4,2,4]

масиви с големина 1: [5], [4], [2], [4]
масиви с големина 2: [5,4], [4,2], [2,4]
масиви с големина 3: [4,2,4]
Общо 8 подмасива
~~~

<details>
  <summary>Решение</summary>

~~~.cpp
    #include <vector>
    #include <deque>
    
    long long continuousSubarrays(std::vector<int>& nums) {
    
        long long res = 0;
        std::deque<int> min, max;
        int left = 0, right = 0;
    
        for(; right < nums.size(); ++right)
        {
            while(!max.empty() && nums[max.back()] <= nums[right])
                max.pop_back();
    
            max.push_back(right);
    
            while(!min.empty() && nums[min.back()] >= nums[right])
                min.pop_back();
            
            min.push_back(right);
            
            while(nums[max.front()] - nums[min.front()] > 2)
            {
                left++;
                if(max.front() < left) max.pop_front();
                if(min.front() < left) min.pop_front();
            }
    
            res += right - left + 1;
        }
    
        return res;
    }
~~~
</details>

**За упражнение**

**Задача 1 - [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/description/?envType=problem-list-v2&envId=monotonic-queue)**

**Задача 2 - [Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/?envType=problem-list-v2&envId=monotonic-queue)**

**Задача 3 - [Count Partitions With Max-Min Difference at Most K](https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/description/?envType=problem-list-v2&envId=monotonic-queue)**
