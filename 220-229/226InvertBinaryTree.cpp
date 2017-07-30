/*
226. Invert Binary Tree
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1

/*
    Submission Date: 2017-07-30
    Runtime: 3 ms
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
    TreeNode* invertTree(TreeNode* root) {
        if(root == NULL) return NULL;
        TreeNode* left = invertTree(root -> left);
        TreeNode* right = invertTree(root -> right);
        root -> left = right;
        root -> right = left;
        return root;
    }
};

int main() {
    return 0;
}