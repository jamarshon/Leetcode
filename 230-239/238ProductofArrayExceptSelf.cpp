/*
238. Product of Array Except Self
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the 
product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

/*
    Submission Date: 2017-07-30
    Runtime: 68 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = nums.size();
        vector<int> dp(N);
        
        // forwards sweep
        int product = 1;
        for(int i = 0; i < N; i++) {
            dp[i] = product;
            product *= nums[i];
        }
        
        // backward sweep
        int back_product = 1;
        for(int i = N-1; i >=0; i--) {
            dp[i] *= back_product;
            back_product *= nums[i];
        }
        
        return dp;
    }
};

int main() {
    return 0;
}