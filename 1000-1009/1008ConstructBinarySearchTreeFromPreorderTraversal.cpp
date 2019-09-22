/*
1008. Construct Binary Search Tree from Preorder Traversal
Return the root node of a binary search tree that matches the given preorder
traversal.

(Recall that a binary search tree is a binary tree where for every node, any
descendant of node.left has a value < node.val, and any descendant of node.right
has a value > node.val.  Also recall that a preorder traversal displays the
value of the node first, then traverses node.left, then traverses node.right.)

Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Note: 

  1 <= preorder.length <= 100
  The values of preorder are distinct.
/*
  Submission Date: 2019-09-21
  Runtime: 8 ms
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
  int index = 0;

 public:
  TreeNode* f(vector<int>& preorder, int low, int high) {
    /*
    recursive create tree, if current value in preorder fits
    in [low, high] then create a node else backtrack
    */
    int N = preorder.size();
    if (index >= N) return nullptr;
    if (preorder[index] < low || preorder[index] > high) return nullptr;
    TreeNode* curr = new TreeNode(preorder[index++]);
    curr->left = f(preorder, low, curr->val);
    curr->right = f(preorder, curr->val, high);
    return curr;
  }
  TreeNode* bstFromPreorder(vector<int>& preorder) {
    return f(preorder, INT_MIN, INT_MAX);
  }
};

int main() { return 0; }
