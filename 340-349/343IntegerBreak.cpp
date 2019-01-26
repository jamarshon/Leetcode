/*
343. Integer Break
Given a positive integer n, break it into the sum of at least two positive
integers and maximize the product of those integers. Return the maximum product
you can get.

For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3
+ 3 + 4).

Note: You may assume that n is not less than 2 and not larger than 58.
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  unordered_map<int, int> dp;

 public:
  int integerBreak(int N) { return integerBreak(N, N); }

  int integerBreak(int n, int N) {
    if (dp.count(n)) return dp[n];

    int res = n == N ? 1 : n;
    for (int i = 1; i < n; i++) {
      res = max(res, i * integerBreak(n - i, N));
    }

    return dp[n] = res;
  }
};

int main() { return 0; }