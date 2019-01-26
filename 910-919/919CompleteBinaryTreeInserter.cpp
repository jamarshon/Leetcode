/*
919. Complete Binary Tree Inserter
A complete binary tree is a binary tree in which every level, except possibly
the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary
tree and supports the following operations:

  CBTInserter(TreeNode root) initializes the data structure on a given tree with
head node root;
  CBTInserter.insert(int v) will insert a TreeNode into the tree with value
node.val = v so that the tree remains complete, and returns the value of the
parent of the inserted TreeNode;
  CBTInserter.get_root() will return the head node of the tree.

Example 1:

Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]

Example 2:

Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs =
[[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]

Note:

  The initial given tree is complete and contains between 1 and 1000 nodes.
  CBTInserter.insert is called at most 10000 times per test case.
  Every value of a given or inserted node is between 0 and 5000.
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class CBTInserter {
  vector<TreeNode*> nodes;

 public:
  CBTInserter(TreeNode* root) {
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
      TreeNode* front = q.front();
      q.pop();
      if (front->left) q.push(front->left);
      if (front->right) q.push(front->right);
      nodes.push_back(front);
    }
  }

  int insert(int v) {
    nodes.emplace_back(new TreeNode(v));
    int parent_ind = (nodes.size() - 2) / 2;
    if (nodes[parent_ind]->left == NULL)
      nodes[parent_ind]->left = nodes.back();
    else
      nodes[parent_ind]->right = nodes.back();
    return nodes[parent_ind]->val;
  }

  TreeNode* get_root() { return nodes[0]; }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter obj = new CBTInserter(root);
 * int param_1 = obj.insert(v);
 * TreeNode* param_2 = obj.get_root();
 */

int main() { return 0; }
