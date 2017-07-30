/*
652. Find Duplicate Subtrees
Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to 
return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1: 
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.

/*
    Submission Date: 2017-07-30
    Runtime: 45 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    string preorder(TreeNode* root, unordered_map<string, int>& freq, vector<TreeNode*>& res) {
        if(root != NULL) {
            string left = preorder(root -> left, freq, res);
            string right = preorder(root -> right, freq, res);
            
            string str = to_string(root -> val) + " " + left + right;
            
            if(freq[str] == 1) res.push_back(root);
            freq[str]++;
            return str;
        } else {
            return "null ";
        }
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> freq;
        vector<TreeNode*> res;
        preorder(root, freq, res);
        return res;
    }
};

int main() {
    return 0;
}