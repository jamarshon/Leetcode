/*
148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

/*
    Submission Date: 2017-07-21
    Runtime: 52 ms
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
  ListNode* sortList(ListNode* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;

    ListNode *slow, *fast, *last;
    slow = fast = head;
    while (fast && fast->next) {
      last = slow;
      slow = slow->next;
      fast = fast->next->next;
    }

    ListNode* head1 = head;
    ListNode* head2 = last->next;
    last->next = NULL;

    ListNode* curr1 = sortList(head1);
    ListNode* curr2 = sortList(head2);

    ListNode* merged = new ListNode(INT_MIN);
    ListNode* merged_head = merged;

    while (curr1 && curr2) {
      if (curr1->val < curr2->val) {
        merged->next = curr1;
        merged = merged->next;
        curr1 = curr1->next;
      } else {
        merged->next = curr2;
        merged = merged->next;
        curr2 = curr2->next;
      }
    }

    while (curr1) {
      merged->next = curr1;
      merged = merged->next;
      curr1 = curr1->next;
    }

    while (curr2) {
      merged->next = curr2;
      merged = merged->next;
      curr2 = curr2->next;
    }

    merged->next = NULL;
    merged = merged_head;
    merged_head = merged_head->next;
    delete merged;

    return merged_head;
  }
};

int main() {
  Solution s;
  return 0;
}