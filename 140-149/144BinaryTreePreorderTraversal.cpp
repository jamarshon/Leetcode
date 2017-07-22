/*
144. Binary Tree Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-07-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st{{root}};
        vector<int> res;
        while(!st.empty()) {
            TreeNode* top = st.top();
            st.pop();

            if(top == NULL) continue;
            res.push_back(top -> val);
            st.push(top -> right);
            st.push(top -> left);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}