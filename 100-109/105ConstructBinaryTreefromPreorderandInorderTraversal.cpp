/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    unordered_map<int, int> inorder_val_to_index;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i < inorder.size(); i++) {
            inorder_val_to_index[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }
    TreeNode* buildTreeHelper(const vector<int>& preorder, const vector<int>& inorder, 
        int i, int j, int k, int l) {
        assert(j - i == l - k);

        if(i == j) return NULL;

        TreeNode* root = new TreeNode(preorder[i]);
        int root_idx = inorder_val_to_index[preorder[i]];
        int left_size = root_idx - k;

        root -> left = buildTreeHelper(preorder, inorder, i + 1, i + 1 + left_size, k, root_idx);
        root -> right = buildTreeHelper(preorder, inorder, i + left_size + 1, j, root_idx + 1, l);
        return root;
    }
};

int main() {
    Solution s;
    return 0;
}