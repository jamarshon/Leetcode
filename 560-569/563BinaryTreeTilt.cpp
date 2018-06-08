/*
563. Binary Tree Tilt
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and 
the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
/*
    Submission Date: 2018-06-08
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /*
    returns the sum of subtree with node as root
    */
    int help(TreeNode* node, int& res) {
        if(node == NULL) return 0;
        int left = help(node->left, res);
        int right = help(node->right, res);
        res += abs(left - right);
        return node->val + left + right;
    }
    
    int findTilt(TreeNode* root) {
        int res = 0;
        help(root, res);
        return res;
    }
};

int main() {
    return 0;
}