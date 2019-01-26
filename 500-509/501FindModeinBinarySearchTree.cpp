/*
501. Find Mode in Binary Search Tree
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most
frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to
the node's key. The right subtree of a node contains only nodes with keys
greater than or equal to the node's key. Both the left and right subtrees must
also be binary search trees. For example: Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the
implicit stack space incurred due to recursion does not count).
/*
    Submission Date: 2018-06-09
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <iostream>
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
  typedef pair<int, int> pii;

  /*
  inorder traversal where if the current element is the same as the last then
  increase the frequency else reset it. if the frequency is greater than res
  frequency, then change res else if the frequency is the same than push back
  to res
  */
  void help(TreeNode* node, pii& curr, vector<pii>& res) {
    if (node == NULL) return;
    help(node->left, curr, res);

    if (curr.first == -1 || curr.second != node->val) {
      curr = {1, node->val};
    } else {
      curr.first++;
    }

    if (curr.first > res[0].first) {
      res = {curr};
    } else if (curr.first == res[0].first) {
      res.push_back(curr);
    }

    help(node->right, curr, res);
  }

  vector<int> findMode(TreeNode* root) {
    if (root == NULL) return {};

    vector<pii> res = {{0, INT_MIN}};
    pii curr = {-1, INT_MIN};
    help(root, curr, res);

    vector<int> v_i;
    v_i.reserve(res.size());
    for (const auto& p : res) v_i.push_back(p.second);
    return v_i;
  }
};
int main() { return 0; }