/*
701. Insert into a Binary Search Tree
Given the root node of a binary search tree (BST) and a value to be inserted
into the tree, insert the value into the BST. Return the root node of the BST
after the insertion. It is guaranteed that the new value does not exist in the
original BST.

Note that there may exist multiple valid ways for the insertion, as long as the
tree remains a BST after insertion. You can return any of them.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3
And the value to insert: 5


You can return this binary search tree:

         4
       /   \
      2     7
     / \   /
    1   3 5


This tree is also valid:

         5
       /   \
      2     7
     / \
    1   3
         \
          4
/*
  Submission Date: 2019-01-25
  Runtime: 108 ms
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
  TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) {
      return new TreeNode(val);
    }

    if (root->val < val) {
      root->right = insert(root->right, val);
    } else {
      root->left = insert(root->left, val);
    }

    return root;
  }

  TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == NULL) return new TreeNode(val);
    insert(root, val);
    return root;
  }
};

int main() { return 0; }
