/*
114. Flatten Binary Tree to Linked List
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
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

Hints:
If you notice carefully in the flattened tree, each node's right child points to
the next node of a pre-order traversal.

/*
    Submission Date: 2017-07-04
    Runtime: 6 ms
    Difficulty: MEDIUM
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
  void flatten(TreeNode* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) return;
    flatten(root->left);
    flatten(root->right);
    if (root->left) {
      TreeNode* right = root->right;
      root->right = root->left;
      TreeNode* temp = root->right;
      while (temp->right) {
        temp = temp->right;
      }
      temp->right = right;
      root->left = NULL;
    }
  }
};

int main() {
  Solution s;
  return 0;
}