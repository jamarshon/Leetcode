/*
783. Minimum Distance Between BST Nodes
Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the 
values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value is different.
/*
    Submission Date: 2018-06-08
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <climits>

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
    inorder traversal keeping tracking of prev
    */
    void help(TreeNode* root, int& res, int& prev) {
        if(root == NULL) return;
        help(root->left, res, prev);
        if(prev != INT_MAX) {
            res = min(res, root->val - prev);
        }
        
        prev = root->val;
        help(root->right, res, prev);
    }
    
    int minDiffInBST(TreeNode* root) {
        int res = INT_MAX, prev = INT_MAX;
        help(root, res, prev);
        return res;
    }
};

int main() {
    return 0;
}