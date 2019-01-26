/*
110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in
which the depth of the two subtrees of every node never differ by more than 1.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
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
  int computeHeight(TreeNode* root) {
    if (root == NULL) return -1;

    int left_height = computeHeight(root->left);
    if (left_height == INT_MIN) return INT_MIN;
    int right_height = computeHeight(root->right);
    if (right_height == INT_MIN) return INT_MIN;

    if (abs(left_height - right_height) > 1) return INT_MIN;
    return max(left_height, right_height) + 1;
  }

  bool isBalanced(TreeNode* root) { return computeHeight(root) != INT_MIN; }
};

int main() {
  Solution s;
  return 0;
}