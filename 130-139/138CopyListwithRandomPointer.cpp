/*
138. Copy List with Random Pointer
A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.

/*
    Submission Date: 2017-07-16
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
 public:
  RandomListNode* copyRandomList(RandomListNode* head) {
    if (head == NULL) return NULL;

    RandomListNode* curr = head;

    // create duplicate node after the original one
    while (curr) {
      RandomListNode* next = curr->next;
      curr->next = new RandomListNode(curr->label);
      curr->next->next = next;
      curr = next;
    }

    // set all the random ones as the original node's random is adjacent
    // to the duplicate random node
    curr = head;
    while (curr) {
      RandomListNode* random = curr->random;
      curr->next->random = (random == NULL) ? NULL : random->next;
      curr = curr->next->next;
    }

    // remove originals
    RandomListNode* original_head = new RandomListNode(INT_MIN);
    RandomListNode* original_cur = original_head;

    RandomListNode* copy_head = new RandomListNode(INT_MIN);
    RandomListNode* copy_curr = copy_head;

    curr = head;
    while (curr) {
      original_cur->next = curr;
      original_cur = original_cur->next;

      copy_curr->next = curr->next;
      copy_curr = copy_curr->next;

      curr = curr->next->next;
    }

    original_cur->next = NULL;
    head = original_head->next;
    delete original_head;

    copy_curr->next = NULL;
    RandomListNode* root = copy_head->next;
    delete copy_head;

    return root;
  }
};

int main() { return 0; }