/*
108. Convert Sorted Array to Binary Search Tree
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

/*
    Submission Date: 2017-07-18
    Runtime: 12 ms
    Difficulty: EASY
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
public:
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        if(start > end) return NULL;
        int mid = start + (end - start + 1)/2;
        // cout << mid << ' ' << start << ' ' << end << endl;
        TreeNode* root = new TreeNode(nums[mid]);
        root -> left = sortedArrayToBST(nums, start, mid - 1);
        root -> right = sortedArrayToBST(nums, mid + 1, end);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }
};

int main() {
    return 0;
}