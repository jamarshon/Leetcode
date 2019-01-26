/*
671. Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative
value, where each node in this tree has exactly two or zero sub-node. If the
node has two sub-nodes, then this node's value is the smaller value among its
two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set
made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
/*
    Submission Date: 2018-06-08
    Runtime: 3 ms
    Difficulty: EASY
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
  /*
  bfs that once reaches a different node->val than root->val will stop putting
  that node's children. result is the minimum of all these first encountered
  different node-> val
  */
  int findSecondMinimumValue(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = INT_MAX;
    bool seen_others = false;

    while (!q.empty()) {
      TreeNode* node = q.front();
      q.pop();
      if (node->val == root->val) {
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      } else {
        // found node that does not equal root->val, no need to go deeper as
        // they will be >= node->val
        res = min(res, node->val);
        seen_others = true;
      }
    }

    return seen_others ? res : -1;
  }
};

int main() { return 0; }