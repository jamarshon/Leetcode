/*
107. Binary Tree Level Order Traversal II
Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]

/*
    Submission Date: 2017-07-20
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <deque>
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q{{root}};
        deque<vector<int>> dq;
        
        while(!q.empty()) {
            int q_size = q.size();
            vector<int> temp;
            for(int i = 0; i < q_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    q.push(curr -> left);
                    q.push(curr -> right);
                    temp.push_back(curr -> val);
                }
                q.pop();
            }
            if(!temp.empty()) dq.push_front(temp);
        }

        vector<vector<int>> res(dq.begin(), dq.end());
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}