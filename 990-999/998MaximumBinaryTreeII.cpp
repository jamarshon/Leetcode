/*
998. Maximum Binary Tree II
We are given the root node of a maximum tree: a tree where every node has a
value greater than any other value in its subtree.

Just as in the previous problem, the given tree was constructed from an
list A (root = Construct(A)) recursively with the following Construct(A)
routine:

  If A is empty, return null.
  Otherwise, let A[i] be the largest element of A.  Create a root node with
value A[i]. The left child of root will be Construct([A[0], A[1], ..., A[i-1]])
  The right child of root will be Construct([A[i+1], A[i+2], ..., A[A.length -
1]])
  Return root.

Note that we were not given A directly, only a root node root = Construct(A).

Suppose B is a copy of A with the value val appended to it.  It is guaranteed
that B has unique values.

Return Construct(B).

Example 1:

Input: root = [4,1,3,null,null,2], val = 5
Output: [5,4,null,1,3,null,null,2]
Explanation: A = [1,4,2,3], B = [1,4,2,3,5]

Example 2:

Input: root = [5,2,4,null,1], val = 3
Output: [5,2,4,null,1,null,3]
Explanation: A = [2,1,5,4], B = [2,1,5,4,3]

Example 3:

Input: root = [5,2,3,null,1], val = 4
Output: [5,2,4,null,1,3]
Explanation: A = [2,1,5,3], B = [2,1,5,3,4]

Note:

  1 <= B.length <= 100
/*
  Submission Date: 2019-09-24
  Runtime: 4 ms
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
  TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    /*
    keep the right spine, the last value which is smaller than
    val becomes the left subtree and curr becomes the right
    subtree of the node above the last value
    */
    TreeNode* curr = new TreeNode(val);
    if (!root) return curr;
    vector<TreeNode*> stk;
    stk.push_back(root);
    while (root->right) {
      root = root->right;
      stk.push_back(root);
    }

    TreeNode* last = nullptr;
    while (!stk.empty()) {
      if (stk.back()->val < val) {
        last = stk.back();
        stk.pop_back();
      } else {
        break;
      }
    }

    curr->left = last;
    if (stk.empty()) return curr;
    stk.back()->right = curr;
    return stk[0];
  }
};

int main() { return 0; }
