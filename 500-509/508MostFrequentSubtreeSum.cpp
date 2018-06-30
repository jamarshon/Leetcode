/*
508. Most Frequent Subtree Sum
Given the root of a tree, you are asked to find the most frequent subtree sum. The 
subtree sum of a node is defined as the sum of all the node values formed by the subtree 
rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, 
return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
/*
    Submission Date: 2018-06-30
    Runtime: 16 ms
    Difficulty: MEDIUM
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

class Solution {
public:
    int f(TreeNode* node, unordered_map<int,int>& sum_to_freq, int& max_freq) {
        if(node == NULL) return 0;
        
        int sum = node->val + f(node->left, sum_to_freq, max_freq) + f(node->right, sum_to_freq, max_freq);
        sum_to_freq[sum]++;
        max_freq = max(max_freq, sum_to_freq[sum]);
        return sum;
    }
    
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int,int> sum_to_freq;
        int max_freq = 0;
        f(root, sum_to_freq, max_freq);
        vector<int> res;
        for(const auto& kv: sum_to_freq) 
            if(kv.second == max_freq) res.push_back(kv.first);
        return res;
    }
};

int main() {
    return 0;
}