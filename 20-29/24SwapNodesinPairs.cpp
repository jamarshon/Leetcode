/*
24. Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only 
nodes itself can be changed.

/*
    Submission Date: 2017-07-21
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* a = head;
        ListNode* b;
        ListNode* newHead = new ListNode(-1);
        ListNode* prev = newHead;
        prev -> next = a;
        
        while(a != NULL && a -> next != NULL){
            b = a -> next;
            prev -> next = b;
            prev = a;
            a -> next = b -> next;
            b -> next = a;
            a = a -> next;
        }
        
        return newHead -> next;
    }
};

int main() {
    Solution s;
    return 0;
}