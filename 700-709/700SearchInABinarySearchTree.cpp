/*
700. Search in a Binary Search Tree
Given the root node of a binary search tree (BST) and a value. You need to find 
the node in the BST that the node's value equals the given value. Return the 
subtree rooted with that node. If such node doesn't exist, you should return 
NULL. 

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3

And the value to search: 2


You should return this subtree:

      2     
     / \   
    1   3


In the example above, if we want to search the value 5, since there is no node 
with value 5, we should return NULL. 

/*
    Submission Date: 2018-07-13
    Runtime: 24 ms
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == NULL || root->val == val) return root;
        if(root->val > val) return searchBST(root->left, val);
        else return searchBST(root->right, val);
    }
};

int main() {
    return 0;
}
