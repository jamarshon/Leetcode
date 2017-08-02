/*
213. House Robber II
After robbing those houses on that street, the thief has found himself a new place for his thievery 
so that he will not get too much attention. This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses 
remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();

        if(N == 0) return 0;
        if(N == 1) return nums.front();

        vector<int> dp(N);

        int res = 0;
        rob(nums, N, dp);
        res = max(res, dp[1]);
        rob(nums, N-1, dp);
        res = max(res, dp[0]);
        return res;
    }
    
    int rob(vector<int>& nums, int N, vector<int>& dp) {
        dp[N-1] = nums[N-1];

        for(int i = N - 2; i >= 0; i--) {
            dp[i] = max(dp[i + 1], nums[i] + (i + 2 < N ? dp[i+2] : 0));
        }

        return dp[0];
    }
};

int main() {
    return 0;
}