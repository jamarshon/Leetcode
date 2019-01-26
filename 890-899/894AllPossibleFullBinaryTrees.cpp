/*
894. All Possible Full Binary Trees
A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.  Each element of
the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.

You may return the final list of trees in any order.

 

Example 1:

Input: 7
Output:
[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:



 

Note:


  1 <= N <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 68 ms
  Difficulty: MEDIUM
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
  vector<TreeNode*> allPossibleFBT(int N) {
    if (N == 0) return {};

    vector<vector<TreeNode*>> dp(N + 1);
    dp[1] = {new TreeNode(0)};

    for (int i = 1; i <= N; i += 2) {
      for (int j = 1; j < i; j += 2) {
        for (const auto& l : dp[j]) {
          for (const auto& r : dp[i - 1 - j]) {
            TreeNode* node = new TreeNode(0);
            node->left = l;
            node->right = r;
            dp[i].push_back(node);
          }
        }
      }
    }

    return dp[N];
  }
};

int main() { return 0; }
