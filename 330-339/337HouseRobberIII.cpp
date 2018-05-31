/*
337. House Robber III
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." 
Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place 
forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
     3
    / \
   2   3
    \   \ 
     3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
     3
    / \
   4   5
  / \   \ 
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.
/*
    Submission Date: 2018-05-30
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /*
        if we use the node, then the maximium value is node's val + rob(root->left's children) + rob(root->right's children)
        if we dont use the node, then maximum value is rob(root->left) + rob(root->right)
        Take the max of use node and not using node
    */
    unordered_map<TreeNode*, int> dp_;
    int rob(TreeNode* root) {
        if(root == NULL) return 0;
        if(dp_.count(root)) return dp_[root];
        
        int use_node = root->val;
        int not_use_node = 0;
        
        if(root -> left) {
            use_node += rob(root->left->left) + rob(root->left->right);
            not_use_node += rob(root->left);
        }
        
        if(root -> right) {
            use_node += rob(root->right->left) + rob(root->right->right);
            not_use_node += rob(root->right);
        }
        
        return dp_[root] = max(use_node, not_use_node);
    }
};

int main() {
    return 0;
}