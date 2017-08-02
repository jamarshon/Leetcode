/*
198. House Robber
You are a professional robber planning to rob houses along a street. Each house has a certain amount of 
money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have 
security system connected and it will automatically contact the police if two adjacent houses were broken 
into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int N = nums.size();
        vector<int> dp(N);
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