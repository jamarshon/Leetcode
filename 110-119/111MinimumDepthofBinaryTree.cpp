/*
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path 
from the root node down to the nearest leaf node.

/*
    Submission Date: 2017-07-16
    Runtime: 9 ms
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
    int minDepth(TreeNode* root) {
        if(root == NULL) return 0;
        if(root -> left == NULL && root -> right == NULL) {
            return 1;
        }

        // either one child or two child meaning res will be updated at least once
        int res = INT_MAX;
        if(root -> left) {
            res = min(res, minDepth(root -> left));
        }

        if(root -> right) {
            res = min(res, minDepth(root -> right));
        }

        return res + 1;
    }
};

int main() {
    return 0;
}