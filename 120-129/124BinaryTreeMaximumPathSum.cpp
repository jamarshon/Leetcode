/*
124. Binary Tree Maximum Path Sum
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any 
node in the tree along the parent-child connections. The path must contain at least one node and 
does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.

/*
    Submission Date: 2017-07-21
    Runtime: 19 ms
    Difficulty: HARD
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
    int maxPathSum(TreeNode* root) {
        if(root == NULL) return 0;
        int max_curr = root -> val;
        maxPathSum(root, max_curr);
        return max_curr;
    }
    int maxPathSum(TreeNode* root, int& max_curr) {
        if(root == NULL) return 0;

        int curr = root -> val;
        int left = maxPathSum(root -> left, max_curr);
        int right = maxPathSum(root -> right, max_curr);
        max_curr = max(max_curr, curr + left + right);
        curr = max(max(curr, curr + left), curr + right);
        max_curr = max(max_curr, curr);
        return curr;
    }
};

int main() {
    Solution s;
    return 0;
}