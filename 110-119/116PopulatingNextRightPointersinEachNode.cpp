/*
116. Populating Next Right Pointers in Each Node
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every 
parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

/*
    Submission Date: 2017-07-18
    Runtime: 22 ms
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
        TreeLinkNode* curr = root;
        TreeLinkNode* next_level_start = NULL;
        while(curr) {
            next_level_start = curr -> left;

            while(curr) {
                if(curr->left) {
                    curr -> left -> next = curr -> right;
                }
                if(curr -> right) {
                    if(curr -> next) {
                        curr -> right -> next = curr -> next -> left;
                    } else {
                        curr -> right -> next = NULL;
                    }
                }
                curr = curr -> next;
            }

            curr = next_level_start;
        }
    }
};

int main() {
    return 0;
}