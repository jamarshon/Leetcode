/*
530. Minimum Absolute Difference in BST
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.
/*
    Submission Date: 2018-06-07
    Runtime: 19 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
public:
    /*
    help called on node returns the smallest and largest value with node as the root
    this means for a node, it is help(root->left)'s smallest value and help(root->right)'s largest value
    if they exist else it is just the node
    
    the minimum difference is this node minus largest value in the left subtree or smallest value in right subtree 
    minus this node
    */
    vector<int> help(TreeNode* root, int& res) {
        if(root == NULL) return {};
        vector<int> left = help(root->left, res);
        vector<int> right = help(root->right, res);
        
        int min_left = left.empty() ? root->val : left[0];
        int max_right = right.empty() ? root->val : right[1];
        
        if(!left.empty()) res = min(res, root->val - left[1]);
        if(!right.empty()) res = min(res, right[0] - root->val);
        
        return {min_left, max_right};
    }
    
    int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX;
        help(root, res);
        return res;
    }
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
    
    int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX, prev = INT_MAX;
        help(root, res, prev);
        return res;
    }
};

int main() {
    return 0;
}