#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <iostream>

using std::string;
using std::vector;
using std::queue;
using std::stack;

// 1700. Number of Students Unable to Eat Lunch

class Solution1 {
public:
    int countStudents(vector<int>& students, vector<int>& sandwithces) 
    {
        std::queue<int> student_queue;
        for(int s : students) student_queue.push(s);

        int iterations = 0;
        while(!student_queue.empty() && iterations <= student_queue.size())
        {
            int sandwitch_type = student_queue.front();
            student_queue.pop();

            if(sandwitch_type == sandwithces[0])
            {
                iterations = 0;
                sandwithces.erase(std::begin(sandwithces));                
            }
            else 
            {
                student_queue.push(sandwitch_type);
                iterations++;
            }

        }

        return student_queue.size();
    }
};


// 2073. Time Needed to Buy Tickets

class Solution2 {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) 
    {
        std::queue<int> cinema_queue;
        for(int person: tickets) cinema_queue.push(person);

        int seconds = 0;
        int kth_person = tickets[k];

        while(kth_person > 0)
        {
            int current = cinema_queue.front(); cinema_queue.pop();

            current--;
            if(current > 0) cinema_queue.push(current);

            if(k == 0)
            {
                kth_person--;
                k = cinema_queue.size();
            }

            ++seconds;
            --k;
        }

        return seconds;
    }
};


// 649. Dota2 Senate

class Solution3 {
public:
    string predictPartyVictory(string senate) {
        std::queue<char> bans;
        std::queue<char> order;

        for(char c: senate) order.push(c);

        while(true)
        {
            char curr = order.front();
            order.pop();

            if(!bans.empty() && bans.front() == curr) {
                bans.pop();
                continue;
            }

            if(curr == 'D') bans.push('R');
            else bans.push('D');

            order.push(curr);
            if(bans.size() == order.size()) break;
        }

        return order.front() == 'D' ? "Dire" : "Radiant";
    }
};

// 933. Number of Recent Calls

class RecentCounter {
public:
    RecentCounter() = default;
    
    int ping(int t) {
        int min_time = t - MAX_INTERVAL;

        while(!requests.empty() && requests.front() < min_time)
        {
            requests.pop();
        } 

        requests.push(t);
        return requests.size();
    }

private:
    static const int MAX_INTERVAL = 3000;

    std::queue<int> requests;
};
