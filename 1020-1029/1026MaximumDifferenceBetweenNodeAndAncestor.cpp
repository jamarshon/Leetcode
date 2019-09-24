/*
1026. Maximum Difference Between Node and Ancestor
Given the root of a binary tree, find the maximum value V for which there exists
different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.

(A node A is an ancestor of B if either: any child of A is equal to B, or any
child of A is an ancestor of B.)

Example 1:

Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| =
7.

Note:

  The number of nodes in the tree is between 2 and 5000.
  Each node will have value between 0 and 100000.
/*
  Submission Date: 2019-09-23
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <functional>
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
  int res = 0;

 public:
  void update(int x, pair<int, int> p) {
    if (p.first != -1) res = max(res, abs(x - p.first));
    if (p.second != -1) res = max(res, abs(x - p.second));
  }

  int get(vector<int> v, function<int(int, int)> compare) {
    int res = v[0];
    for (int i = 1; i < v.size(); i++) {
      if (v[i] != -1) res = compare(res, v[i]);
    }
    return res;
  }

  pair<int, int> solve(TreeNode* root) {
    if (!root) return {-1, -1};
    auto left = solve(root->left);
    auto right = solve(root->right);
    int x = root->val;
    update(x, left);
    update(x, right);
    int smallest = get(vector<int>{x, left.first, right.first},
                       [](int a, int b) { return min(a, b); });
    int largest = get(vector<int>{x, left.second, right.second},
                      [](int a, int b) { return max(a, b); });
    return {smallest, largest};
  }

  int maxAncestorDiff(TreeNode* root) {
    // compute the smallest and largest in the subtrees
    // then update and return the smalles/largest
    // see if abs(curr - smallest) || abs(curr - largest) is
    // greater than res
    solve(root);
    return res;
  }
};

int main() { return 0; }
