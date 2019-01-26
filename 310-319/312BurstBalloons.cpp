/*
312. Burst Balloons
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number
on it represented by array nums. You are asked to burst all the balloons. If the
you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here
left and right are adjacent indices of i. After the burst, the left and right
then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not
burst them. 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100 Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
/*
    Submission Date: 2018-06-24
    Runtime: 14 ms
    Difficulty: HARD
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution2 {
 public:
  unordered_map<string, int> dp;
  int help(vector<int>& nums, int l, int r) {
    string key = to_string(l) + "," + to_string(r);
    if (dp.count(key)) return dp[key];
    int res = 0;
    for (int i = l + 1; i <= r - 1; i++) {
      res = max(res, nums[l] * nums[i] * nums[r] + help(nums, l, i) +
                         help(nums, i, r));
    }
    return dp[key] = res;
  }
  int maxCoins(vector<int>& nums) {
    vector<int> x;
    x.reserve(nums.size() + 2);
    x.push_back(1);
    for (auto e : nums) x.push_back(e);
    x.push_back(1);
    return help(x, 0, x.size() - 1);
  }
};

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    vector<int> x;
    x.reserve(nums.size() + 2);
    x.push_back(1);
    for (auto e : nums) x.push_back(e);
    x.push_back(1);

    int N = x.size();
    /*
    O(n^3)
    r-l < 2  gives 0 as needs at least 3 elements
    if l and r are adjacent and i is popped, it means no number between y =
    [l,i] can be adjacent to z = [i,r]. if y is adjacent to z, then i must have
    been popped to get y adjacent to z. the result would be finding what it
    takes to make l adjacent to i (dp[l][i]) and to make i adjacent to r
    (dp[i][r]) + value from popping i (x[l]*x[i]*x[r]).
    */
    vector<vector<int>> dp(N, vector<int>(N, 0));
    for (int gap = 2; gap < N; gap++) {
      for (int l = 0; l + gap < N; l++) {
        int r = l + gap;

        for (int i = l + 1; i <= r - 1; i++) {
          dp[l][r] = max(dp[l][r], x[l] * x[i] * x[r] + dp[l][i] + dp[i][r]);
        }
      }
    }

    return dp[0][N - 1];
  }
};

int main() { return 0; }