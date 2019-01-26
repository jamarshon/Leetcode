/*
143. Reorder List
Given a singly linked list L: L0?L1?…?Ln-1?Ln,
reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

/*
    Submission Date: 2017-07-18
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  void reorderList(ListNode* head) {
    // find midpoint
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* last_slow = slow;
    while (fast && fast->next) {
      last_slow = slow;
      slow = slow->next;
      fast = fast->next->next;
    }

    if (slow == fast) return;

    last_slow->next = NULL;

    // reverse the second half
    ListNode* prev = NULL;
    ListNode* curr = slow;
    ListNode* new_curr = curr->next;
    while (curr) {
      curr->next = prev;
      prev = curr;
      curr = new_curr;
      if (new_curr) new_curr = new_curr->next;
    }

    // merge first half and second half
    curr = prev;
    ListNode* new_head = NULL;
    new_curr = NULL;
    while (head) {
      new_head = head->next;
      new_curr = curr->next;

      head->next = curr;
      if (new_head) {
        curr->next = new_head;
      } else if (new_curr) {
        curr->next = new_curr;
      }

      head = new_head;
      curr = new_curr;
    }
  }
};

int main() { return 0; }