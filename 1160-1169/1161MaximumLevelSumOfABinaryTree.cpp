/*
1161. Maximum Level Sum of a Binary Tree
Given the root of a binary tree, the level of its root is 1, the level of its
children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at
level X is maximal.

Example 1:

Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Note:

  The number of nodes in the given tree is between 1 and 10^4.
  -10^5 <= node.val <= 10^5
/*
  Submission Date: 2019-09-21
  Runtime: 208 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int maxLevelSum(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int max_level = -1;
    int max_sum = INT_MIN;
    int level = 1;
    while (!q.empty()) {
      int sum = 0;
      for (int i = 0, N = q.size(); i < N; i++) {
        TreeNode* curr = q.front();
        sum += curr->val;
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
      if (max_level == -1 || sum > max_sum) {
        max_level = level;
        max_sum = sum;
      }
      level++;
    }
    return max_level;
  }
};

int main() { return 0; }
