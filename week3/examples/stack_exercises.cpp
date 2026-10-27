#include <stack>
#include <string>
#include <vector>
// Leetcode -> 20. Valid Parentheses

class Solution1 {
public:

    static bool matching(char symb, char top)
    {
        return 
        (symb == '}' && top == '{') ||
        (symb == ')' && top == '(') ||
        (symb == ']' && top == '[');
    }

    static bool isValid(std::string s) {
        std::stack<char> check;

        for(char symb: s)
        {
            if(symb == '{' || symb == '(' || symb == '[')  check.push(symb);
            else if(!check.empty() && matching(symb, check.top())) check.pop();
            else return false;
        }

        return check.empty();
    }
};


// Leetcode -> 496. Next Greater Element I

class Solution2 {
public:
    static std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::stack<int> s;
        std::vector<int> nexts(nums2.size());

        for(int i = nums2.size() - 1; i >= 0; --i)
        {
            while(!s.empty() && s.top() <= nums2[i])
            {
                s.pop();
            }

            nexts[i] = s.empty() ? -1 : s.top();
            s.push(nums2[i]);
        }

        std::vector<int> res;
        for(int num : nums1)
        {
            for(int i = 0; i < nums2.size(); ++i)
            {
                if(num == nums2[i])
                {
                    res.push_back(nexts[i]);
                }
            }
        }

        return res;
    }
};


// Leetcode --> 844. Backspace String Compare

class Solution3 {
public:
    static bool backspaceCompare(const std::string& s, const std::string& t) {
        std::stack<char> symbs1;
        std::stack<char> symbs2;


        for(char c : s)
        {
            if(c == '#')
	    {
		if(!symbs1.empty()) symbs1.pop();
	    }
	    else  symbs1.push(c);
        }

        for(char c : t)
        {
            if(c == '#')
	    {		
		if(!symbs2.empty()) symbs2.pop();
	    }
            else                            symbs2.push(c);
        }

        bool equal = symbs1.size() == symbs2.size();

        while(equal)
        {
            if(symbs1.empty()) break;
            if(symbs1.top() != symbs2.top())
            {
                equal = false;
                break;
            }

            symbs1.pop();
            symbs2.pop();
        }

        return equal;
    }

};


// Leetocde --> 1021. Remove Outermost Parentheses

class Solution4 {
public:
    string removeOuterParentheses(string s) {
        if(s.empty()) return "";

        std::stack<char> st;
        std::string result;

        for(char c: s)
        {
            if(c == '(')
            {
                if(!st.empty()) result += c;
                st.push(c); 
            }
            else
            {
                if(st.size() > 1) result += c;
                st.pop();
            }
        }

        return result;
    }
};


// Leetcode --> 1047. Remove All Adjacent Duplicates In String

class Solution {
public:
    string removeDuplicates(string s) {
        std::stack<char> st;

        for(char c : s)
        {
            if(!st.empty() && st.top() == c) st.pop();
            else
            {
                st.push(c);
            }
        }

        std::stack<char> rev;
        while(!st.empty()) 
        {
            rev.push(st.top());
            st.pop();
        }
        
        std::string result;
        while(!rev.empty())
        {
            result += rev.top();
            rev.pop();
        }

        return result;
    }
};


// Leetcode --> 2000. Reverse Prefix of Word

class Solution {
public:
    string reversePrefix(string word, char ch) {
        std::string result;
        std::stack<char>  st;

        int i = 0;
        for(; i < word.size(); ++i)
        {
            st.push(word[i]);
            if(word[i] == ch) break;
        }
        if(i == word.size()) return word;

        while(!st.empty())
        {
            result += st.top();
            st.pop();
        }

        for(i = i + 1; i < word.size(); ++i) result += word[i];
        return result;
    }
};



int main()
{

    Solution3::backspaceCompare("y#fo##f", "y#f#o##f");
    return 0;
}
