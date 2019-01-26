/*
543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two
nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges
between them.
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
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
  /*
  returns the height of a node so height(root) = 1 + max(height(left),
  height(right)) res can be updated to 2 + height(left) + height(right) as the
  longest path in the left and right go through this node.
  */
  int help(TreeNode* root, int& res) {
    if (root == NULL) return -1;
    int left = help(root->left, res);
    int right = help(root->right, res);
    res = max(res, 2 + left + right);
    return 1 + max(left, right);
  }

  int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    help(root, res);
    return res;
  }
};

int main() { return 0; }