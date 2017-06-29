/*
103. Binary Tree Zigzag Level Order Traversal
Given a binary tree, return the zigzag level order traversal of its nodes' values. 
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;

        bool forward = true;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int level_size = q.size();
            vector<int> temp;
            for(int i = 0; i < level_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    temp.push_back(curr -> val);
                    q.push(curr -> left);
                    q.push(curr -> right);
                }
                q.pop();
            }

            if(!forward) {
                reverse(temp.begin(), temp.end());
            }

            if(!temp.empty()) res.push_back(temp);
            forward ^= true;
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}