/*
86. Partition List
Given a linked list and a value x, partition it such that all nodes less than x come before nodes 
greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
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
    ListNode* partition(ListNode* head, int x) {
        ListNode less_head(-1);
        ListNode great_eq_head(-1);
        
        ListNode* less_curr = &less_head;
        ListNode* great_eq_curr = &great_eq_head;
        
        ListNode* curr = head;
        while(curr) {
            if(curr -> val < x) {
                less_curr -> next = curr;
                less_curr = less_curr -> next;
            } else {
                great_eq_curr -> next = curr;
                great_eq_curr = great_eq_curr -> next;
            }
            curr = curr -> next;
        }
        
        great_eq_curr -> next = NULL;
        less_curr -> next = great_eq_head.next;
        return less_head.next;
    }
};

int main() {
    return 0;
}