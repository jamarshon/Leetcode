/*
515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

Example:
Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]

/*
    Submission Date: 2018-06-29
    Runtime: 15 ms
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
  vector<int> largestValues(TreeNode* root) {
    if (root == NULL) return {};
    vector<int> res;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      int n = q.size();
      int max_level = q.front()->val;
      for (int i = 0; i < n; i++) {
        TreeNode* curr = q.front();
        q.pop();
        max_level = max(max_level, curr->val);
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
      res.push_back(max_level);
    }

    return res;
  }
};

int main() { return 0; }