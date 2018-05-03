/*
236. Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in 
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is 
defined between two nodes v and w as the lowest node in T that has both v and w 
as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another 
example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of 
itself according to the LCA definition.

/*
    Submission Date: 2017-08-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || root == p || root == q) return root;

        auto* left = lowestCommonAncestor(root->left,p,q);
        auto* right = lowestCommonAncestor(root->right,p,q);

        if(left && right) return root;
        else if(left) return left;
        else return right;
    }
};

class Solution {
public:
    int lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& res) {
        if(root == NULL) return 0;
        
        int count = 0;
        if(root == p) count++;
        if(root == q) count++;

        if(count == 2) { // root == p == q so root is lca
            res = root; 
            return 2; 
        }
        
        int left_count = lowestCommonAncestor(root -> left, p, q, res);
        if(left_count == 2) return 2; // found p and q in root -> left
        count += left_count;

        // root is either p or q and the other is in the left tree so root is lca
        if(count == 2) { 
            res = root;
            return 2;
        }
        
        int right_count = lowestCommonAncestor(root -> right, p, q, res);
        if(right_count == 2) return 2; // found p and q in root -> right
        count += right_count;

        // root and left_tree has either p or q and the other is in the right tree 
        // so root is lca
        if(count == 2) {
            res = root;
            return 2;
        }
        
        return count; 
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = NULL;
        lowestCommonAncestor(root, p, q, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}