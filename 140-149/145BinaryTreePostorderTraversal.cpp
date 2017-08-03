/*
145. Binary Tree Postorder Traversal
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-08-02
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void storeReverse(TreeNode* curr, vector<int>& res) {
        int i = res.size();
        while(curr) {
            res.push_back(curr -> val);
            curr = curr -> right;
        }
        reverse(res.begin() + i, res.end());
    }
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* dummy = new TreeNode(-1);
        dummy -> left = root;

        vector<int> res;
        TreeNode* curr = dummy;
        while(curr) {
            if(curr -> left) {
                // left exists so find predecessor
                TreeNode* pre = curr -> left;
                while(pre -> right && pre -> right != curr) {
                    pre = pre -> right;
                }

                if(pre -> right == NULL) {
                    // apply threading and go left
                    pre -> right = curr;
                    curr = curr -> left;
                } else {
                    // restore, print reverse from curr -> left to pre and go right
                    pre -> right = NULL;
                    storeReverse(curr -> left, res);
                    curr = curr -> right;
                } 
            } else {
                // no left go right
                curr = curr -> right;
            }
        }

        dummy -> left = NULL;
        delete dummy;
        return res;
    }
};

int main() {
    return 0;
}