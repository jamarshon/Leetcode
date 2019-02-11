/*
979. Distribute Coins in Binary Tree
Given the root of a binary tree with N nodes, each node in the tree has node.val
coins, and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to
another.  (The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

Example 1:

Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and
one coin to its right child.

Example 2:

Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root
[taking two moves].  Then, we move one coin from the root of the tree to the
right child.

Example 3:

Input: [1,0,2]
Output: 2

Example 4:

Input: [1,0,0,null,3]
Output: 4

Note:

  1<= N <= 100
  0 <= node.val <= N
/*
  Submission Date: 2019-02-09
  Runtime: 12 ms
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
  int ans;

  /*
  dfs returns the number of extra coins there are in this subtree.
  if it is positive then we can move coins up else if it is negative
  we move coins down from parent.
  at the node, the total moves would be the absolute value of the left and right
  subtree's number of extra coins.
  the number of excess coins is the number of coins in the root plus the excess
  amount of the left and right minus one for the root node requiring one.
  */
  int dfs(TreeNode* root) {
    if (root == nullptr) return 0;
    int L = dfs(root->left);
    int R = dfs(root->right);
    ans += abs(L) + abs(R);
    return root->val + L + R - 1;
  }

  int distributeCoins(TreeNode* root) {
    ans = 0;
    dfs(root);
    return ans;
  }
};

int main() { return 0; }
