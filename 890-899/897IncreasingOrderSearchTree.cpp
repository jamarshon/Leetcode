/*
897. Increasing Order Search Tree
Given a tree, rearrange the tree in in-order so that the leftmost node in the
tree is now the root of the tree, and every node has no left child and only 1
right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9

Note:

  The number of nodes in the given tree will be between 1 and 100.
  Each node will have a unique integer value from 0 to 1000.
/*
  Submission Date: 2019-01-26
  Runtime: 72 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  void inorder(TreeNode* curr, TreeNode** last, TreeNode** res) {
    if (curr) {
      inorder(curr->left, last, res);
      if (*last) {
        (*last)->right = curr;
      }

      *last = curr;
      if (*res == NULL) {
        *res = curr;
      }

      curr->left = NULL;
      inorder(curr->right, last, res);
    }
  }
  TreeNode* increasingBST(TreeNode* root) {
    TreeNode *res = NULL, *last = NULL;
    inorder(root, &last, &res);
    return res;
  }
};

int main() { return 0; }
