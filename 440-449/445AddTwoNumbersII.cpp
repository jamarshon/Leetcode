/*
445. Add Two Numbers II
You are given two non-empty linked lists representing two non-negative integers.
The most significant digit comes first and each of their nodes contain a single
digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists
is not allowed.



Example:
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

/*
    Submission Date: 2018-07-10
    Runtime: 28 ms
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
  int GetLength(ListNode* node) {
    int res = 0;
    while (node) {
      node = node->next;
      res++;
    }
    return res;
  }

  /*
  create list where head is lsb by traversing the nodes and adding up
  corresponding l1, l2 nodes. the list may have numbers >= 10. traverse the list
  from lsb to msb and move the carry through the list and at the same time
  reverse it.
  */
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int N = GetLength(l1);
    int M = GetLength(l2);

    ListNode* res = NULL;
    // assuming N > 0 && M > 0 initially, then they will both hit 0 at the same
    // time as the longer one keeps getting trimmed
    while (N > 0 && M > 0) {
      int sum = 0;
      // if N == M, both if will execute moving both pointers and adding both
      // sums if N > M, just the first will execute if N < M, just the second
      // will execute both these last condition will ensure the longer is
      // trimmed
      if (N >= M) {
        sum += l1->val;
        l1 = l1->next;
        N--;
      }

      if (N < M) {
        sum += l2->val;
        l2 = l2->next;
        M--;
      }

      ListNode* head = new ListNode(sum);
      head->next = res;
      res = head;
    }

    // need to reverse the list and do carry through
    int carry = 0;
    ListNode* prev = NULL;
    ListNode* temp;
    while (res) {
      res->val += carry;
      carry = res->val / 10;
      res->val %= 10;

      temp = res->next;
      res->next = prev;
      prev = res;
      res = temp;
    }

    if (carry) {
      ListNode* head = new ListNode(carry);
      head->next = prev;
      prev = head;
    }

    return prev;
  }
};

int main() { return 0; }
