/*
958. Check Completeness of a Binary Tree
Given a binary tree, determine if it is a complete binary tree.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely
filled, and all nodes in the last level are as far left as possible. It can have
between 1 and 2h nodes inclusive at the last level h.

Example 1:

Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values
{1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as
possible.

Example 2:

Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.

Note:

  The tree will have between 1 and 100 nodes.
/*
  Submission Date: 2019-02-21
  Runtime: 12 ms
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
  struct NodeInfo {
    int height;
    bool perfect;
  };
  /*
  perfect means every node other than the leaves has two children and all leaves
  are at the same level (e.g tree of height h should have 2^(h+1)-1 children)
  height == -1 when subtree isn't complete else it is 1 + max(height(left,
  right))

  if the left height equals the right height then the left should be perfect
  because there are nodes in the right subtree. For nodes to be furthest left
  then nodes in right subtree indicates all the nodes are filled in the left.
       x
    z     x
  z   z  y

  z should be perfect

  if the left height == right height + 1, then the right should be prefect
  because there are nodes in the left subtree at right height + 1 but none in
  the right subtree at that same level.
       x
    x     z
  y

  z should be perfect

  a node is perfect if the heights of left and right are equal and both left and
  right are perfect
  */
  NodeInfo helper(TreeNode* root) {
    if (!root) return {0, true};
    const auto& left = helper(root->left);
    const auto& right = helper(root->right);
    if (left.height == -1 || right.height == -1) return {-1, false};

    const int& diff = left.height - right.height;
    if ((diff == 0 && left.perfect) || (diff == 1 && right.perfect)) {
      return {1 + max(left.height, right.height),
              diff == 0 && left.perfect && right.perfect};
    } else {
      return {-1, false};
    }
  }

 public:
  bool isCompleteTree(TreeNode* root) { return helper(root).height != -1; }
};

class Solution2 {
 public:
  /* level order search
  expect that depth d should have 2^d nodes except the last one
  if a node has a right child it must have a left child
  if a null node is encounted in a level, all the rest of the nodes should be
  null.
  */
  bool isCompleteTree(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q{{root}};
    int expected_size = 2;
    bool found_not_equal = false;
    while (!q.empty()) {
      bool seen_null = false;
      for (int i = 0, q_size = q.size(); i < q_size; i++) {
        TreeNode* curr = q.front();
        q.pop();
        if ((seen_null && (curr->left || curr->right)) ||
            (curr->right && !curr->left))
          return false;
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
        seen_null = curr->left == nullptr || curr->right == nullptr;
      }

      if (found_not_equal) return q.empty();
      found_not_equal = expected_size != q.size();
      expected_size *= 2;
    }
    return true;
  }
};

int main() { return 0; }
