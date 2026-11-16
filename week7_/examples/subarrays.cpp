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