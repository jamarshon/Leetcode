/*
199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes 
you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

/*
    Submission Date: 2017-07-23
    Runtime: 3 ms
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

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        rightSideView(root, res, 0);
        return res;
    }
    
    void rightSideView(TreeNode* root, vector<int>& res, int depth) {
        if(root == NULL) return;
        if(res.size() <= depth) {
            res.push_back(root -> val);
        }
        
        rightSideView(root -> right, res, depth + 1);
        rightSideView(root -> left, res, depth + 1);
    }
};

int main() {
    Solution s;
    return 0;
}