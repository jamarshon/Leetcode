/*
235. Lowest Common Ancestor of a Binary Search Tree
Given a binary search tree (BST), find the lowest common ancestor
(LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest
common ancestor is defined between two nodes v and w as the
lowest node in T that has both v and w as descendants (where
we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6.
Another example is LCA of nodes 2 and 4 is 2, since a node can be a
descendant of itself according to the LCA definition.

/*
    Submission Date: 2017-08-21
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
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) return NULL;
    if (p == NULL || q == NULL) return p ? p : q;

    int p_val = p->val, q_val = q->val, root_val = root->val;

    if (root_val > p_val && root_val > q_val) {
      return lowestCommonAncestor(root->left, p, q);
    } else if (root_val < p_val && root_val < q_val) {
      return lowestCommonAncestor(root->right, p, q);
    } else {
      return root;
    }
  }
};

int main() {
  Solution s;
  return 0;
}