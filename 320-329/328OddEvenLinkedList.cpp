/*
328. Odd Even Linked List
Given a singly linked list, group all odd nodes together followed by the even
nodes. Please note here we are talking about the node number and not the value
in the nodes.

You should try to do it in place. The program should run in O(1) space
complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was
in the input. The first node is considered odd, the second node even and so on
...
/*
    Submission Date: 2018-05-02
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* oddEvenList(ListNode* head) {
    ListNode *first_odd, *first_even;
    first_odd = first_even = NULL;
    vector<ListNode*> arr{NULL, NULL};

    int index = 0;
    while (head) {
      ListNode* temp = head;
      head = head->next;
      temp->next = NULL;

      if (index == 0 && first_odd == NULL) {
        first_odd = temp;
      } else if (index == 1 && first_even == NULL) {
        first_even = temp;
      }

      if (arr[index] == NULL)
        arr[index] = temp;
      else {
        arr[index]->next = temp;
        arr[index] = temp;
      }

      index ^= 1;
    }

    if (arr[0]) {
      arr[0]->next = first_even;
    }
    return first_odd;
  }
};

int main() { return 0; }