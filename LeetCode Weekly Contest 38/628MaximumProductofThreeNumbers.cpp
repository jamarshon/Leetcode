/*
628. Maximum Product of Three Numbers
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:
Input: [1,2,3]
Output: 6
Example 2:
Input: [1,2,3,4]
Output: 24
Note:
The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.

/*
    Submission Date: 2017-07-09
    Runtime: 79 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int N = nums.size();
        
        if(N < 3) return INT_MIN;
        
        sort(nums.begin(), nums.end());
        
        // three largest or 1 largest and 2 smallest
        return max(nums[N-1]*nums[N-2]*nums[N-3], nums[N-1]*nums[0]*nums[1]);
    }
};

int main() {
    Solution s;
    return 0;
}