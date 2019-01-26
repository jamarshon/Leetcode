/*
25. Reverse Nodes in k-Group
Given a linked list, reverse the nodes of a linked list k at a time and return
its modified list.

k is a positive integer and is less than or equal to the length of the linked
list. If the number of nodes is not a multiple of k then left-out nodes in the
end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

/*
    Submission Date: 2017-01-08
    Runtime: 22 ms
    Difficulty: HARD
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
  void incrementalReverse(ListNode*& A, ListNode*& B, ListNode*& C) {
    B->next = A;
    A = B;
    B = C;
    if (C != NULL) {
      C = C->next;
    }
  }

  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k < 0 || head == NULL) return NULL;
    if (k == 1) return head;

    ListNode* newHead = NULL;
    ListNode* A = NULL;
    ListNode* B = head;
    ListNode* C = head->next;
    ListNode* lastInterval = head;
    ListNode* nextInterval = head;

    int i = k;

    while (i--) {
      if (nextInterval == NULL) {
        return head;
      }
      nextInterval = nextInterval->next;
    }

    while (true) {
      while (B != nextInterval) incrementalReverse(A, B, C);
      if (newHead == NULL) newHead = A;

      A = nextInterval;
      B = (A == NULL) ? NULL : A->next;
      C = (B == NULL) ? NULL : B->next;

      i = k;
      while (i--) {
        if (nextInterval == NULL) {
          lastInterval->next = A;
          return newHead;
        } else {
          if (i == 0) lastInterval->next = nextInterval;
          nextInterval = nextInterval->next;
        }
      }

      lastInterval = A;
      lastInterval->next = NULL;
    }
  }
};

int main() { return 0; }