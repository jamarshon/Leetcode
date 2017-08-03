/*
117. Populating Next Right Pointers in Each Node II
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL

/*
    Submission Date: 2017-08-02
    Runtime: 26 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode* next_level_head, *next_level_curr;
        TreeLinkNode* curr = root;
        while(curr) {
            next_level_head = next_level_curr = NULL;
            while(curr) {
                if(curr -> left) {
                    if(next_level_head == NULL) next_level_head = curr -> left;
                    if(next_level_curr == NULL) {
                        next_level_curr = curr -> left;
                    } else {
                        next_level_curr -> next = curr -> left;
                        next_level_curr = next_level_curr -> next;
                    }
                }

                if(curr -> right) {
                    if(next_level_head == NULL) next_level_head = curr -> right;
                    if(next_level_curr == NULL) {
                        next_level_curr = curr -> right;
                    } else {
                        next_level_curr -> next = curr -> right;
                        next_level_curr = next_level_curr -> next;
                    }
                }

                curr = curr -> next;
            }
            
            curr = next_level_head;
        }
    }
};

int main() {
    return 0;
}