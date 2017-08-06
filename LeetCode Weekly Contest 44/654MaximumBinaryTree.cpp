/*
654. Maximum Binary Tree
Given an integer array with no duplicates. A maximum tree building on this array is defined as 
follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum 
number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum 
number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].

/*
    Submission Date: 2017-08-06
    Runtime: 66 ms
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

class Solution2 {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int N = nums.size();
        
        int top = -1;
        vector<int> st(N, 0);
        vector<int> T(N, 0);
        for(int i = 0; i < N; i++) {
            int temp_top = top;
            while(temp_top >= 0 && nums[st[temp_top]] < nums[i]) {
                temp_top--;
            }
            
            if(temp_top != -1) T[i] = st[temp_top];
            
            if(temp_top < top) {
                T[st[temp_top + 1]] = i;
            }
            st[++temp_top] = i;
            top = temp_top;
        }
        
        T[st[0]] = -1;
        
        TreeNode* nodes[N];
        for(int i = 0; i < N; i++) nodes[i] = new TreeNode(nums[i]);
        
        TreeNode* root;
        for(int i = 0; i < N; i++) {
            int parent_ind = T[i];
            if(parent_ind == -1) root = nodes[i];
            else if(i < parent_ind) nodes[parent_ind] -> left = nodes[i];
            else nodes[parent_ind] -> right = nodes[i];
        }
        
        return root;
    }
};

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for(auto num: nums) {
            TreeNode* curr = new TreeNode(num);
            TreeNode* left = NULL;
            while(!stk.empty() && stk.back() -> val < num) {
                left = stk.back();
                stk.pop_back();
            }

            curr -> left = left;
            if(!stk.empty()) {
                stk.back() -> right = curr;
            }
            stk.push_back(curr);
        }
        return stk.front();
    }
};

int main() {
    return 0;
}