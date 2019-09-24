/*
1043. Partition Array for Maximum Sum
Given an integer array A, you partition the array into (contiguous) subarrays of
length at most K.  After partitioning, each subarray has their values changed to
become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.

Example 1:

Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]

Note:

  1 <= K <= A.length <= 500
  0 <= A[i] <= 10^6
/*
  Submission Date: 2019-09-23
  Runtime: 460 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumAfterPartitioning(vector<int>& A, int K) {
    /*
    same as before but keep track of the maximum element
    when iterating backwards for the remainder subarray
    */
    int N = A.size();
    vector<int> dp(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
      int res = 0;
      int max_el = INT_MIN;
      for (int j = 1; j <= K && i - j >= 0; j++) {
        max_el = max(max_el, A[i - j]);
        res = max(res, dp[i - j] + j * max_el);
      }
      dp[i] = res;
    }
    return dp[N];
  }
};

class Solution2 {
 public:
  int maxSumAfterPartitioning(vector<int>& A, int K) {
    /*
    dp[i] is the answer for A[0] ... A[i-1]
    dp[0] = 0
    dp[i] = max_{j=[1,K]}(dp[i-j] + j * max_{l=[i-j, i-1]}(A[l]))
    taking the max of previous subarray answer + the remaining
    subarray's maximum value multiplied by its length
    */
    int N = A.size();
    vector<int> dp(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
      int res = 0;
      for (int j = 1; j <= K && i - j >= 0; j++) {
        auto max_el = max_element(A.begin() + (i - 1) - j + 1, A.begin() + i);
        res = max(res, dp[i - j] + j * (*max_el));
      }
      dp[i] = res;
    }
    return dp[N];
  }
};

int main() { return 0; }
