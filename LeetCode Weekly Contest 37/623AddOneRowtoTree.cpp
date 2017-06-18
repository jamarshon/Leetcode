/*
623. Add One Row to Tree
Given the root of a binary tree, then value v and depth d, you need to add a row of 
nodes with value v at the given depth d. The root node is at depth 1.

The adding rule is: given a positive integer depth d, for each NOT null tree nodes 
N in depth d-1, create two tree nodes with value v as N's left subtree root and right 
subtree root. And N's original left subtree should be the left subtree of the new left 
subtree root, its original right subtree should be the right subtree of the new right 
subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a 
tree node with value v as the new root of the whole original tree, and the original 
tree is the new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.

/*
    Submission Date: 2017-06-18
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    void getRow(TreeNode* root, int d, vector<TreeNode*>& vec) {
        if(root == NULL) return;
        if(d == 0) {
            vec.push_back(root);
            return;
        }
        
        getRow(root -> left, d - 1, vec);
        getRow(root -> right, d - 1, vec);
    }
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        // get all nodes at depth d - 1
        vector<TreeNode*> vec;
        if(d == 1) {
            TreeNode* new_root = new TreeNode(v);
            new_root -> left = root;
            root = new_root;
        } else {
            getRow(root, d - 2, vec);
            for(auto t: vec) {
                TreeNode* left = t -> left;
                TreeNode* right = t -> right;
                t -> left = new TreeNode(v);
                t -> right = new TreeNode(v);
                t -> left -> left = left;
                t -> right -> right = right;
            }
        }
        return root;
    }
};

int main() {
    return 0;
}