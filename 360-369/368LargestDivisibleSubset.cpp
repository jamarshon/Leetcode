/*
368. Largest Divisible Subset
Given a set of distinct positive integers, find the largest subset
such that every pair (Si, Sj) of elements in this subset satisfies:
Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)
Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]
/*
    Submission Date: 2017-08-21
    Runtime: 33 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> largestDivisibleSubset(vector<int>& nums) {
    if (nums.empty()) return {};

    sort(nums.begin(), nums.end());
    int N = nums.size();

    vector<int> dp(N, 1), P(N, -1);
    int max_dp_ind = 0;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] % nums[j] == 0) {
          if (dp[j] + 1 > dp[i]) {
            dp[i] = dp[j] + 1;
            P[i] = j;
          }
        }
      }

      if (dp[max_dp_ind] < dp[i]) max_dp_ind = i;
    }

    vector<int> res(dp[max_dp_ind]);
    int index = res.size();
    for (int i = max_dp_ind; i >= 0; i = P[i]) {
      res[--index] = nums[i];
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}