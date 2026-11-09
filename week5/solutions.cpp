#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <iostream>
#include <cassert>

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


typedef struct player
{
    int index;
    int save_cards;
} player; 

unsigned int kittens(const std::string& cards, unsigned int players)
{
    const char BOMB = 'B';
    const char SAVE = 'S';
    const char NTH  = 'O';
    
    std::queue<player> game;
    std::queue<char>   deck;

    for(int i = 0; i < players; ++i) game.push({i + 1,0});
    for(char c : cards)              deck.push(c);


    while(game.size() != 1)
    {
        player player_on_turn = game.front(); game.pop();
	char   card           = deck.front(); deck.pop();

	switch(card)
	{
            case NTH:  // do nothing...
	        game.push(player_on_turn);
	    	std::cout << "Player " << player_on_turn.index << " drew an ordinary card!\n"; 
	    break;

	    case SAVE: // add a save card
                player_on_turn.save_cards++;
                game.push(player_on_turn);

		std::cout << "Player " << player_on_turn.index << " gained a SAVE card!\n"; 
	    break;

	    case BOMB: // try to kill player
                player_on_turn.save_cards--;
	    
	        if(player_on_turn.save_cards >= 0)
		{
		    std::cout << "Player " << player_on_turn.index << " used a SAVE card!\n";
		    game.push(player_on_turn);
		    deck.push(BOMB);
		}
		else std::cout << "Player " << player_on_turn.index << " has been killed!\n";

	    break;
	}

    }
    
    return game.front().index;
}    

int main(void)
{
    std::cout << "Game 1:\n ------------------ \n";
    assert(kittens("BB", 3) == 3);

    std::cout << "Game 2:\n ------------------ \n";
    assert(kittens("SSBB", 3) == 2);

    std::cout << "Game 3:\n ------------------ \n";
    kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5);

    std::cout << "Game 4:\n ------------------ \n";
    kittens("SOOSBBOOOOSOOOSBOSOOBOSOSOOBOSOSOOB", 7); 
    return 0;
}    
