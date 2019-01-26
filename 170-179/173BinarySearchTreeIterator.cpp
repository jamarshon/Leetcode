/*
173. Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST). Your iterator will be
initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory,
where h is the height of the tree.

/*
    Submission Date: 2017-07-26
    Runtime: 22 ms
    Difficulty: MEDIUM
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

class BSTIterator {
  vector<TreeNode *> path_;

 public:
  BSTIterator(TreeNode *root) {
    TreeNode *curr = root;
    while (curr) {
      path_.push_back(curr);
      curr = curr->left;
    }
  }

  /** @return whether we have a next smallest number */
  bool hasNext() { return !path_.empty(); }

  /** @return the next smallest number */
  int next() {
    TreeNode *curr = path_.back();
    path_.pop_back();

    int ret_val = curr->val;

    curr = curr->right;
    while (curr) {
      path_.push_back(curr);
      curr = curr->left;
    }

    return ret_val;
  }
};

int main() { return 0; }