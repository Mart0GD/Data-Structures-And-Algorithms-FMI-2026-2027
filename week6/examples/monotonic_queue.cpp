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