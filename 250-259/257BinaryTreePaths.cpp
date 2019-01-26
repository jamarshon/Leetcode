/*
257. Binary Tree Paths
Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
/*
    Submission Date: 2017-08-23
    Runtime: 79 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode *root) {
    if (root == NULL) return {};

    string curr = to_string(root->val);
    vector<string> res;

    vector<string> left = binaryTreePaths(root->left);
    for (auto str : left) res.push_back(curr + "->" + str);

    vector<string> right = binaryTreePaths(root->right);
    for (auto str : right) res.push_back(curr + "->" + str);

    if (left.empty() && right.empty()) res.push_back(curr);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}