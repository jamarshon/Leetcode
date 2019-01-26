/*
129. Sum Root to Leaf Numbers
Given a binary tree containing digits from 0-9 only, each root-to-leaf path
could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

/*
    Submission Date: 2017-07-14
    Runtime: 3 ms
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
  int sumNumbers(TreeNode* root, int current_path) {
    if (root == NULL) {
      return 0;
    }

    int curr_sum = current_path * 10 + root->val;

    if (root->left == NULL && root->right == NULL) {
      return curr_sum;
    }

    int left = sumNumbers(root->left, curr_sum);
    int right = sumNumbers(root->right, curr_sum);
    return left + right;
  }

  int sumNumbers(TreeNode* root) { return sumNumbers(root, 0); }
};

int main() { return 0; }