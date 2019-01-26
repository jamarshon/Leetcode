/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

/*
    Submission Date: 2017-01-14
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (m == n) return head;

    ListNode* begin = head;
    bool reverseIncludeHead = m == 1;

    for (int i = 0; i < m - 2; i++) {
      begin = begin->next;
    }

    ListNode* end = begin->next;
    ListNode* A = reverseIncludeHead ? head : end;
    ListNode* B = A->next;
    ListNode* C = B == NULL ? NULL : B->next;

    for (int i = 0; i < n - m; i++) {
      B->next = A;
      A = B;
      B = C;
      if (C != NULL) C = C->next;
    }

    if (reverseIncludeHead) {
      head->next = B;
      head = A;
    } else {
      begin->next = A;
      end->next = B;
    }

    return head;
  }
};

int main() { return 0; }