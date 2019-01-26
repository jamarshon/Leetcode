/*
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's
key. The right subtree of a node contains only nodes with keys greater than the
node's key. Both the left and right subtrees must also be binary search trees.

    2
   / \
  1   3

Binary tree [2,1,3], return true.

    1
   / \
  2   3

Binary tree [1,2,3], return false.

/*
    Submission Date: 2017-01-27
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool isValidBSTHelper(TreeNode* root, int* min, int* max) {
    if (root == NULL) return true;

    int rootVal = root->val;
    int* rootValPtr = &rootVal;

    if ((min && rootVal <= *min) || (max && rootVal >= *max)) return false;

    bool validLeftSubTree = isValidBSTHelper(root->left, min, rootValPtr);
    bool validRightSubTree = isValidBSTHelper(root->right, rootValPtr, max);

    return validLeftSubTree && validRightSubTree;
  }

  bool isValidBST(TreeNode* root) { return isValidBSTHelper(root, NULL, NULL); }
};

int main() { return 0; }
