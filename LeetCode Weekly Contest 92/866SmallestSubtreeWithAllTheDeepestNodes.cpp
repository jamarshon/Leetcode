/*
866. Smallest Subtree with all the Deepest Nodes
Given a binary tree rooted at root, the depth of each node is the shortest 

A node is deepest if it has the largest depth possible among any node in the 

The subtree of a node is that node, plus the set of all descendants of that 

Return the node with the largest depth such that it contains all the deepest 

 

Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:



We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the 
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with 
Both the input and output have TreeNode type.


 

Note:


    The number of nodes in the tree will be between 1 and 500.
    The values of each node are unique.
/*
    Submission Date: 2018-07-08
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lca(TreeNode* root, TreeNode* A, TreeNode* B) {
        if(root == NULL) return NULL;
        if(root == A || root == B) return root;
        TreeNode* l = lca(root->left, A, B);
        TreeNode* r = lca(root->right, A, B);
        if(l && r) return root;
        return l ? l: r;
    }
    
    /*
    do level order search and keep track of the deepest nodes
    then for all the deepest nodes do lca and return that result.
    by folding lca, curr goes higher and higher such that further
    calls to lca are faster (does not reprocess same nodes)
    */
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if(root == NULL) return root;
        queue<TreeNode*> q;
        q.push(root);
        
        vector<TreeNode*> last;
        
        while(!q.empty()) {
            last.clear();
            int q_size = q.size();
            for(int i = 0; i < q_size; i++) {
                TreeNode* temp = q.front();
                last.push_back(temp);
                q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        
        TreeNode* curr = last[0];
        for(int i = 1; i < last.size(); i++) {
            curr = lca(root, curr, last[i]);
        }
        
        return curr;
    }
};

int main() {
    return 0;
}