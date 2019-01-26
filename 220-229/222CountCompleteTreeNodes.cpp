/*
222. Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely
filled, and all nodes in the last level are as far left as possible. It can have
between 1 and 2h nodes inclusive at the last level h.

/*
    Submission Date: 2017-08-03
    Runtime: 72 ms
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
  int countNodes(TreeNode* root) {
    if (root == NULL) return 0;

    TreeNode* curr = root;
    int l_depth = 0, r_depth = 0;
    while (curr) {
      curr = curr->left;
      l_depth++;
    }

    curr = root;
    while (curr) {
      curr = curr->right;
      r_depth++;
    }

    if (l_depth == r_depth) {  // filled tree
      return (1 << l_depth) - 1;
    } else {  // not completely filled get the count of left and right with this
              // node
      return 1 + countNodes(root->left) + countNodes(root->right);
    }
  }
};

int main() { return 0; }