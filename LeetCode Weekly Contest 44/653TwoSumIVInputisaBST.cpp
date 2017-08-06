/*
653. Two Sum IV - Input is a BST
Given a Binary Search Tree and a target number, return true if there exist two 
elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

/*
    Submission Date: 2017-08-06
    Runtime: 45 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
    unordered_map<int, vector<TreeNode*>> visited;
public:
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL) return false;
        int target = k - (root -> val);
        
        if(visited.count(target)) {
            for(auto l: visited[target]) {
                if(l != root) return true;
            }
        }
        
        TreeNode* curr = root;
        while(curr) {
            if(curr != root && curr -> val == target) return true;
            visited[curr -> val].push_back(curr);
            if(curr -> val > target) {
                curr = curr -> right;
            } else {
                curr = curr -> left;
            }
        }
        
        return findTarget(root -> left, k) || findTarget(root -> right, k);
    }
};

class Solution {
public:
    void inorder(TreeNode* curr, vector<int>& res) {
        if(curr == NULL) return;
        inorder(curr -> left, res);
        res.push_back(curr -> val);
        inorder(curr -> right, res);
    }
    bool findTarget(TreeNode* root, int k) {
        vector<int> sorted_arr;
        inorder(root, sorted_arr);
        int low = 0;
        int high = sorted_arr.size() - 1;
        
        while(low < high) {
            int sum = sorted_arr[low] + sorted_arr[high];
            if(sum == k) return true;
            if(sum < k) low++;
            else high--;
        }
        return false;
    }
};

int main() {
    return 0;
}