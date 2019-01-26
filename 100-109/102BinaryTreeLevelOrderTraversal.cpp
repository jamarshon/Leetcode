/*
102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
    Difficulty: MEDIUM
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
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      int level_size = q.size();
      vector<int> temp;
      for (int i = 0; i < level_size; i++) {
        TreeNode* curr = q.front();
        if (curr) {
          temp.push_back(curr->val);
          q.push(curr->left);
          q.push(curr->right);
        }
        q.pop();
      }
      if (!temp.empty()) res.push_back(temp);
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}