/*
1123. Lowest Common Ancestor of Deepest Leaves
Given a rooted binary tree, return the lowest common ancestor of its deepest
leaves.

Recall that:

  The node of a binary tree is a leaf if and only if it has no children
  The depth of the root of the tree is 0, and if the depth of a node is d, the
depth of each of its children is d+1.
  The lowest common ancestor of a set S of nodes is the node A with the largest
depth such that every node in S is in the subtree with root A.

Example 1:

Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization
"[1,2,3]".

Example 2:

Input: root = [1,2,3,4]
Output: [4]

Example 3:

Input: root = [1,2,3,4,5]
Output: [2,4,5]

Constraints:

  The given tree will have between 1 and 1000 nodes.
  Each node of the tree will have a distinct value between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
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
 public:
  // return lca, depth
  pair<TreeNode*, int> helper(TreeNode* curr) {
    if (!curr) return {nullptr, 0};
    auto left = helper(curr->left);
    auto right = helper(curr->right);
    // same depth means this is the lca
    if (left.second == right.second) return {curr, left.second + 1};
    // the left lca is the lca of all the deepest leaves so
    // return that upward
    else if (left.second > right.second)
      return {left.first, left.second + 1};
    // same as before but its the right lca
    else
      return {right.first, right.second + 1};
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) { return helper(root).first; }
};

class Solution3 {
  unordered_map<int, unordered_set<TreeNode*>> depth_to_node;

 public:
  pair<TreeNode*, int> lca(TreeNode* curr,
                           const unordered_set<TreeNode*>& leaves) {
    if (!curr) return {nullptr, 0};
    int N = leaves.size();
    auto left = lca(curr->left, leaves);
    if (left.second == N) return left;
    auto right = lca(curr->right, leaves);
    if (right.second == N) return right;
    int total = left.second + right.second + leaves.count(curr);
    return {curr, total};
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].insert(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    return lca(root, depth_to_node[max_depth]).first;
  }
};

class Solution2 {
  unordered_map<int, vector<TreeNode*>> depth_to_node;

 public:
  TreeNode* lca(TreeNode* curr, TreeNode* a, TreeNode* b) {
    if (!curr || curr == a || curr == b) return curr;
    auto left = lca(curr->left, a, b);
    auto right = lca(curr->right, a, b);
    if (left && right)
      return curr;
    else if (left)
      return left;
    else
      return right;
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].push_back(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    auto v = depth_to_node[max_depth];
    TreeNode* prev = nullptr;
    for (auto e : v) prev = lca(root, prev, e);
    return prev;
  }
};

int main() { return 0; }
