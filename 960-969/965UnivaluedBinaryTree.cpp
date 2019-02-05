/*
965. Univalued Binary Tree
A binary tree is univalued if every node in the tree has the same value.

Return true if and only if the given tree is univalued.

Example 1:

Input: [1,1,1,1,1,null,1]
Output: true

Example 2:

Input: [2,2,2,5,2]
Output: false

Note:

  The number of nodes in the given tree will be in the range [1, 100].
  Each node's value will be an integer in the range [0, 99].
/*
  Submission Date: 2019-02-04
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool isUnivalTree(TreeNode *root) {
    return (root == nullptr) ||
           ((root->left == nullptr || root->left->val == root->val) &&
            (root->right == nullptr || root->right->val == root->val)) &&
               isUnivalTree(root->left) && isUnivalTree(root->right);
  }
};

int main() { return 0; }
