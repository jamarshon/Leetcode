/*
1110. Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest
(a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the
result in any order.

Example 1:

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Constraints:

  The number of nodes in the given tree is at most 1000.
  Each node has a distinct value between 1 and 1000.
  to_delete.length <= 1000
  to_delete contains distinct values between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 20 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  vector<TreeNode*> res;

 public:
  /*
  return the tree without the deleted nodes
  when a node is deleted, put the pruned left/right (if non null) into the
  forest also add the root if it is not deleted
  */
  TreeNode* helper(TreeNode* root, const unordered_set<int>& delete_set) {
    if (!root) return nullptr;
    auto left = helper(root->left, delete_set);
    auto right = helper(root->right, delete_set);
    if (delete_set.count(root->val)) {
      if (left) res.push_back(left);
      if (right) res.push_back(right);
      return nullptr;
    } else {
      root->left = left;
      root->right = right;
      return root;
    }
  }

  vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    unordered_set<int> delete_set(to_delete.begin(), to_delete.end());
    if (!delete_set.count(root->val)) res.push_back(root);
    helper(root, delete_set);
    return res;
  }
};

int main() { return 0; }
