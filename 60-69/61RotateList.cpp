/*
61. Rotate List
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

/*
    Submission Date: 2017-01-19
    Runtime: 9 ms
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
  ListNode* rotateRight(ListNode* head, int k) {
    if (k == 0 || head == NULL) return head;

    ListNode* current = head;
    ListNode* lastNode;
    int len = 0;
    while (current != NULL) {
      len++;
      lastNode = current;
      current = current->next;
    }

    k %= len;
    if (k == 0) return head;

    int target = len - k;
    ListNode* kLast = head;
    while (--target) {
      kLast = kLast->next;
    }

    ListNode* newHead = kLast->next;
    kLast->next = NULL;
    lastNode->next = head;

    return newHead;
  }
};

int main() { return 0; }