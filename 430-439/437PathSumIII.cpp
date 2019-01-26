/*
437. Path Sum III
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go
downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000
to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
/*
    Submission Date: 2018-06-09
    Runtime: 28 ms
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
  /*
  returns path sums from this root down (not necessarily reach leaf)
  this is {root->val,
          root->val + l for all l from f(root->left),
          root->val + r for all r from f(root->left),
          }
  first one meets terminate the path here, second one means this extends a left
  path and the last one extends a right path check if any of the new paths equal
  sum to increase res
  */
  vector<int> help(TreeNode* root, int sum, int& res) {
    if (root == NULL) return {};
    vector<int> left = help(root->left, sum, res);
    vector<int> right = help(root->right, sum, res);

    if (root->val == sum) res++;

    vector<int> paths;
    paths.reserve(1 + left.size() + right.size());
    paths.push_back(root->val);

    for (const auto& l : left) {
      paths.push_back(root->val + l);
      if (paths.back() == sum) res++;
    }

    for (const auto& r : right) {
      paths.push_back(root->val + r);
      if (paths.back() == sum) res++;
    }

    return paths;
  }

  int pathSum(TreeNode* root, int sum) {
    int res = 0;
    help(root, sum, res);
    return res;
  }
};

int main() { return 0; }