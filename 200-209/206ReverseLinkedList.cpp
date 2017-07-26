/*
206. Reverse Linked List
Reverse a singly linked list.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: EASY
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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = head -> next;

        while(curr != NULL) {
            curr -> next = prev;
            prev = curr;
            curr = next;
            if(next != NULL) next = next -> next;
        }

        return prev;
    }
};

int main() {
    Solution s;
    return 0;
}