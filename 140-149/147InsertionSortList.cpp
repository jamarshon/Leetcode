/*
147. Insertion Sort List
Sort a linked list using insertion sort.

/*
    Submission Date: 2017-07-14
    Runtime: 59 ms
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummy = new ListNode(INT_MIN);

        ListNode* curr = head;
        ListNode* insert = NULL;
        while(curr) {
            insert = dummy;
            while(insert -> next && insert -> next -> val < curr -> val) {
                insert = insert -> next;
            }
            
            ListNode* new_curr = curr -> next;
            ListNode* next = insert -> next;
            insert -> next = curr;
            curr -> next = next;
            curr = new_curr;
        }

        head = dummy -> next;
        dummy -> next = NULL;
        delete dummy;
        return head;

    }
};

int main() {
    return 0;
}