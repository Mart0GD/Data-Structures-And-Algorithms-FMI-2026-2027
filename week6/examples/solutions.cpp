#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <iostream>

using std::string;
using std::vector;
using std::queue;
using std::stack;

// 21. Merge Two Sorted Lists

class Solution1 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode  sentinel;
        ListNode* itt = &sentinel;

        while(list1 && list2)
        {
            if(list1->val < list2->val)
            {
                itt->next = list1;
                list1 = list1->next;
            }
            else
            {
                itt->next = list2;
                list2 = list2->next; 
            }

            itt = itt->next;
        }

        if(list1) itt->next = list1;
        else      itt->next = list2;

        return sentinel.next;
    }
};

// 83. Remove Duplicates from Sorted List

class Solution2 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return nullptr;

        ListNode* new_head = head;
        while(head->next)
        {
            if(head->next->val == head->val)
            {
                head->next = head->next->next;
                continue;
            }

            head = head->next;
        }

        return new_head;
    }
};

// 141. Linked List Cycle

class Solution3 {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;

        ListNode* slow = head;
        ListNode* fast = head;

        while(slow && fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) return true;
        }

        return false;
    }
};

// 160. Intersection of Two Linked Lists

class Solution4 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA;
        ListNode *q = headB;

        while(p != q)
        {
            p = p ? p->next : headB;
            q = q ? q->next : headA;
        }

        return p;
    }   
};

// 287. Find the Duplicate Number

class Solution5 {
public:

    // Алгоритъм на флойд 
    int findDuplicate(vector<int>& nums) {
        
        int slow = nums[0];
        int fast = nums[0];

        while(true)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];

            // старт на цикъла
            if(slow == fast)
            {
                slow = nums[0];
                while(slow != fast)
                {
                    slow = nums[slow];
                    fast = nums[fast];
                }
                return slow;
            }
        }
    }
};


// 203. Remove Linked List Elements

class Solution6 {
public:
    
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return nullptr;
        while(head && head->val == val) head = head->next;

        ListNode* new_head = head;
        while(head && head->next)
        {
            if(head->next->val == val)
            {
                head->next = head->next->next;
                continue;
            }
            head = head->next;
        }

        return new_head;
    }
};


// 206. Reverse Linked List

class Solution7 {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return nullptr;

        ListNode sentinel;

        while(head)
        {
            ListNode* tmp = sentinel.next;

            sentinel.next = head;
            head = head->next;
            
            sentinel.next->next = tmp;
        }

        return sentinel.next;
    }
};

// 234. Palindrome Linked List

class Solution8 {
public:
    bool isPalindrome(ListNode* head) {
        if(!head) return true;

        ListNode* rev = reverse(head);

        while(rev && head)
        {
            if(rev->val != head->val) return false;

            rev = rev->next;
            head = head->next;
        }

        return true;
    }

    ListNode* reverse(const ListNode* head)
    {
        ListNode sentinel;

        while(head)
        {
            sentinel.next = new ListNode(head->val, sentinel.next);
            head = head->next;
        }

        return sentinel.next;
    }

};

// 876. Middle of the Linked List

class Solution9 {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }
};

// 1290. Convert Binary Number in a Linked List to Integer

class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int number = 0;

        while(head)
        {
            number |= head->val;

            if(head->next) number <<= 1;
            head = head->next;
        }

        return number;
    }
};
