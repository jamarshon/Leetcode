/*
572. Subtree of Another Tree
Given two non-empty binary trees s and t, check whether tree t has exactly the
same structure and node values with a subtree of s. A subtree of s is a tree
consists of a node in s and all of this node's descendants. The tree s could
also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of
s. Example 2: Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
/*
    Submission Date: 2018-06-09
    Runtime: 29 ms
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
  void serialize(TreeNode* node, string& res) {
    if (node == NULL) {
      res += "null,";
    } else {
      res += to_string(node->val) + ",";
      serialize(node->left, res);
      serialize(node->right, res);
    }
  }

  // check if s == t or s contains a subtree t
  bool isSubtree(TreeNode* s, TreeNode* t) {
    string s1 = "", s2 = "";
    serialize(s, s1);
    serialize(t, s2);
    return s1 == s2 || s1.find("," + s2) != string::npos;
  }
};

int main() { return 0; }