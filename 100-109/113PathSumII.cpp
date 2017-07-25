/*
113. Path Sum II
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]

/*
    Submission Date: 2017-07-24
    Runtime: 9 ms
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
    void pathSum(TreeNode* root, int curr_sum, int sum, vector<int>& curr, vector<vector<int>>& res) {
        if(root == NULL) return;

        curr.push_back(root -> val);
        curr_sum += root -> val;

        if(root -> left == NULL && root -> right == NULL) {
            if(curr_sum == sum) {
                res.push_back(curr);
            }
        } else {
            pathSum(root -> left, curr_sum, sum, curr, res);
            pathSum(root -> right, curr_sum, sum, curr, res);
        }

        curr.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> curr;
        pathSum(root, 0, sum, curr, res);
        return res;
    }
};

int main() {
    return 0;
}