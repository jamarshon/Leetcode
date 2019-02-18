/*
993. Cousins in Binary Tree
In a binary tree, the root node is at depth 0, and children of each depth k node
are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have
different parents.

We are given the root of a binary tree with unique values, and the values x and
y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are
cousins.

Example 1:

Input: root = [1,2,3,4], x = 4, y = 3
Output: false

Example 2:

Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true

Example 3:

Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false

Note:

  The number of nodes in the tree will be between 2 and 100.
  Each node has a unique integer value from 1 to 100.
/*
  Submission Date: 2019-02-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool isCousins(TreeNode* root, int x, int y) {
    if (!root || root->val == x || root->val == y) return false;
    queue<TreeNode*> q;
    q.push(root);
    vector<TreeNode*> v;
    while (!q.empty()) {
      for (int i = 0, size = q.size(); i < size; i++) {
        TreeNode* curr = q.front();
        q.pop();
        if (curr->left) {
          q.push(curr->left);
          if (q.back()->val == x || q.back()->val == y) {
            v.push_back(curr);
          }
        }

        if (curr->right) {
          q.push(curr->right);
          if (q.back()->val == x || q.back()->val == y) {
            v.push_back(curr);
          }
        }
      }

      if (!v.empty()) {
        if (v.size() != 2) return false;
        return v[0] != v[1];
      }
    }

    return false;
  }
};

int main() { return 0; }
