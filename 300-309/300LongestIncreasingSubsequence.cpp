/*
300. Longest Increasing Subsequence
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there 
may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?
/*
    Submission Date: 2017-03-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int N = nums.size(), dp_len = 0;
        vector<int> dp(N, -1), P(N, -1);
        
        for(int i = 0; i < N; i++) {
            auto it = lower_bound(dp.begin(), dp.begin() + dp_len, nums[i], [&nums](const int& dp_el, const int& val){
                return nums[dp_el] < val;
            });
            
            int it_ind = it - dp.begin();
            dp[it_ind] = i;
            
            if(it_ind > 0) P[i] = dp[it_ind - 1];
            if(it_ind == dp_len) dp_len++;
        }
        
        vector<int> lis_seq(dp_len);
        int index = lis_seq.size();
        for(int i = dp[dp_len - 1]; i >= 0; i = P[i])
            lis_seq[--index] = nums[i];
        
        return dp_len;
    }
};

int main() {
    return 0;
}