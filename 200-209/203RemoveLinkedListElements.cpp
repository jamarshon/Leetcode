/*
203. Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

/*
    Submission Date: 2017-07-26
    Runtime: 26 ms
    Difficulty: EASY
*/

#include <iostream>
#include <climits>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy_head = new ListNode(INT_MIN);
        dummy_head -> next = head;

        ListNode* curr = dummy_head;
        while(curr) {
            ListNode* next = curr -> next;
            while(next && next -> val == val) {
                ListNode* to_delete = next;
                next = next -> next;
                delete to_delete;
            }

            curr -> next = next;
            curr = next;
        }

        ListNode* to_delete = dummy_head;
        head = dummy_head -> next;
        delete to_delete;
        return head;
    }
};

int main() {
    return 0;
}