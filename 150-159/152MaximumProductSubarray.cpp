/*
152. Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number)
which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int N = nums.size();

    if (N == 0) return 0;

    int min_dp[N];
    int max_dp[N];

    min_dp[0] = max_dp[0] = nums.front();

    int res = max_dp[0];

    for (int i = 1; i < N; i++) {
      min_dp[i] =
          min(min(min_dp[i - 1] * nums[i], max_dp[i - 1] * nums[i]), nums[i]);
      max_dp[i] =
          max(max(min_dp[i - 1] * nums[i], max_dp[i - 1] * nums[i]), nums[i]);
      res = max(res, max_dp[i]);
    }

    return res;
  }
};

int main() {
  Solution s;
  return 0;
}