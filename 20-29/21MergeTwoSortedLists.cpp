/*
21. Merge Two Sorted Lists
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* tail = head;
        while(l1 != NULL && l2 != NULL) {
            if(l1 -> val > l2 -> val) {
                tail -> next = l2;
                l2 = l2 -> next;
            } else {
                tail -> next = l1;
                l1 = l1 -> next;
            }
            tail = tail -> next;
        }
        
        tail -> next = (l1 != NULL) ? l1 : l2;
        
        return head -> next;
    }
};

int main() {
	return 0;
}