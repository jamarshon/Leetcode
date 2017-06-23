/*
83. Remove Duplicates from Sorted List
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

/*
    Submission Date: 2017-06-22
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* new_head = head;
        ListNode* current = head;
        ListNode* write_node = head;
        while(current) {
            while(current && current -> val == write_node -> val) {
                current = current -> next;
            }

            if(current == NULL) {
                // delete remaining
                ListNode* to_delete = write_node -> next;
                write_node -> next = NULL;
                ListNode* temp;
                while(to_delete) {
                    temp = to_delete;
                    to_delete = to_delete -> next;
                    delete temp;
                }
            } else {
                write_node = write_node -> next;
                write_node -> val = current -> val;
            }
        }

        return new_head;
    }
};

int main() {
    return 0;
}