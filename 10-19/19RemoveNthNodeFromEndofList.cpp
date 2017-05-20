/*
19. Remove Nth Node From End of List
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.

/*
    Submission Date: 2017-05-20
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* current = head;
        ListNode* forward = head;
        for(int i = 0; i < n + 1; i++) {
            // Delete head
            if(forward == NULL) {
                ListNode* new_head = head -> next;
                delete head;
                return new_head;
            }
            forward = forward -> next;
        }
        
        // We assume deleted node is not the head
        while(forward != NULL) {
            current = current -> next;
            forward = forward -> next;
        }
        
        
        // Delete node at current
        ListNode* next_next_node = current -> next -> next;
        delete current -> next;
        current -> next = next_next_node;
        return head;
    }
};

int main(){
    return 0;
}