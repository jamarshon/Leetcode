/*
82. Remove Duplicates from Sorted List II
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only 
distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

/*
    Submission Date: 2017-06-22
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* dummy = new ListNode(-1);

        dummy -> next = head;

        ListNode* prev = dummy;

        ListNode* current = head;
        ListNode* write_node = head;
        while(current) {
            while(current && current -> val == write_node -> val) {
                current = current -> next;
            }

            if(write_node -> next == current) {
                prev = write_node;
                write_node = write_node -> next;
            } else {
                ListNode* temp;
                while(write_node != current) {
                    temp = write_node;
                    write_node = write_node -> next;
                    delete temp;
                }

                prev -> next = current;
            }
        }

        ListNode* new_head = dummy -> next;
        delete dummy;
        return new_head;
    }
};

int main() {
    return 0;
}