/*
230. Kth Smallest Element in a BST
Given a binary search tree, write a function kthSmallest to find the kth smallest 
element in it.

Note: 
You may assume k is always valid, 1 ? k ? BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you 
need to find the kth smallest frequently? How would you optimize the 
kthSmallest routine?

/*
    Submission Date: 2017-08-14
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool inorder(TreeNode* root, int& count, int k, int& res) {
        if(root == NULL) return false;
        
        if(inorder(root -> left, count, k, res)) return true;
        count++;
        if(count == k) {
            res = root -> val;
            return true;
        }
        
        if(inorder(root -> right, count, k, res)) return true;
        return false;
    }
    int kthSmallest(TreeNode* root, int k) {
        int count = 0, res = 0;
        inorder(root, count, k, res);
        return res;
    }
};

class Solution2 {
public:
    int updateMap(unordered_map<TreeNode*, int>& node_to_num_children, TreeNode* root) {
        if(node_to_num_children.count(root)) return node_to_num_children[root];
        int res = 1;
        res += updateMap(node_to_num_children, root -> left);
        res += updateMap(node_to_num_children, root -> right);
        return node_to_num_children[root] = res;
    }

    int traverse(TreeNode* root, int k, unordered_map<TreeNode*, int>& node_to_num_children) {
        assert(root != NULL);
        int left_num = node_to_num_children[root -> left];
        
        if(left_num == k - 1) return root -> val;

        if(left_num >= k) {
            return traverse(root -> left, k, node_to_num_children);
        } else {
            return traverse(root -> right, k - 1 - left_num, node_to_num_children);
        }
    }
    int kthSmallest(TreeNode* root, int k) {
        unordered_map<TreeNode*, int> node_to_num_children{{NULL, 0}};
        updateMap(node_to_num_children, root);
        return traverse(root, k, node_to_num_children);
    }
};

int main() {
    return 0;
}