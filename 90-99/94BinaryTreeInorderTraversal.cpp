/*
94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <stack>
#include <unordered_set>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        unordered_set<TreeNode*> set;
        
        vector<int> result;
        s.push(root);
        
        while(!s.empty()){
            TreeNode* top = s.top();
            s.pop();
            if(top == NULL) { 
                continue;
            } else if(set.find(top) == set.end()) {
                s.push(top -> right);
                s.push(top);
                s.push(top -> left);
                set.insert(top);
            } else {
                result.push_back(top -> val);
            }
        }
        
        return result;
    }
};

int main() {
    return 0;
}