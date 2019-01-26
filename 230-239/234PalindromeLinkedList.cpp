/*
234. Palindrome Linked List
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

/*
    Submission Date: 2017-08-06
    Runtime: 28 ms
    Difficulty: EASY
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
  ListNode* reverse(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    ListNode* next = curr->next;

    while (curr) {
      curr->next = prev;
      prev = curr;
      curr = next;
      if (next != NULL) next = curr->next;
    }

    return prev;
  }

  bool isEqual(ListNode* a, ListNode* b) {
    while (a && b) {
      if (a->val != b->val) return false;
      a = a->next;
      b = b->next;
    }
    return a == NULL && b == NULL;
  }

  bool isPalindrome(ListNode* head) {
    ListNode *slow, *fast, *last_slow;
    last_slow = NULL;
    slow = fast = head;

    while (fast && fast->next) {
      fast = fast->next->next;
      last_slow = slow;
      slow = slow->next;
    }

    if (slow == head) return true;

    last_slow->next = NULL;

    bool is_even_length = fast == NULL;
    // marker is where to start reversing if even and it's next is where to
    // start reversing if odd e.g marker is 1 in 0 -> 1 -> 2 -> 3 and marker is
    // 2 in 0 -> 1 -> 2 -> 3 -> 4
    ListNode* marker = slow;

    ListNode* rev_head = is_even_length
                             ? reverse(marker)
                             : reverse(marker->next);  // reverse last half
    bool res = isEqual(
        head,
        rev_head);  // check if first half and reversed second half is the same
    ListNode* rev_tail = reverse(rev_head);  // undo the reverse
    if (is_even_length) {
      last_slow->next = rev_tail;
    } else {
      last_slow->next = marker;  // place the marker back in between the first
                                 // half and second half for odd length
      marker->next = rev_tail;
    }

    return res;
  }
};

int main() { return 0; }