/*
1031. Maximum Sum of Two Non-Overlapping Subarrays
Given an array A of non-negative integers, return the maximum sum of elements in
two non-overlapping (contiguous) subarrays, which have lengths L and M.  (For
clarification, the L-length subarray could occur before or after the M-length
subarray.)

Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) +
(A[j] + A[j+1] + ... + A[j+M-1]) and either:

  0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
  0 <= j < j + M - 1 < i < i + L - 1 < A.length.

Example 1:

Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length
2.

Example 2:

Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with
length 2.

Example 3:

Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with
length 3.

Note:

  L >= 1
  M >= 1
  L + M <= A.length <= 1000
  0 <= A[i] <= 1000
/*
  Submission Date: 2019-09-24
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    /*
    prefix[i] is sum of A from [0, i]
    l_max[i] is max sum of L subarray before last M elements [0, i-M]
      computed as max(l_max,
        prefix[i - M] -  prefix[i-M-L] // the current sum of L subarray
        [i-M-L+1, i-M])
    m_max[i] is max sum of M subarray before last L elements [0, i-L]
      computed as max(m_max,
        prefix[i - L] -  prefix[i-L-M] // the current sum of M subarray
        [i-L-M+1, i-L])

    start m_max at prefix[M-1] and l_max at prefix[L-1]
    start res at prefix[L+M-1] as it is two subarrays of L and M
    */
    int N = A.size();
    vector<int> prefix = A;
    for (int i = 1; i < N; i++) prefix[i] += prefix[i - 1];
    int res = prefix[L + M - 1];
    int m_max = prefix[M - 1];
    int l_max = prefix[L - 1];
    for (int i = L + M; i < N; i++) {
      m_max = max(m_max, prefix[i - L] - prefix[i - L - M]);
      l_max = max(l_max, prefix[i - M] - prefix[i - M - L]);
      res = max(res, max(m_max + prefix[i] - prefix[i - L],
                         l_max + prefix[i] - prefix[i - M]));
    }

    return res;
  }
};

class Solution2 {
 public:
  vector<int> max_sliding_window_sum(const vector<int>& A, const int& K) {
    int N = A.size();
    vector<int> dp(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
      sum += A[i];
      if (i >= K - 1) {
        if (i - K >= 0) sum -= A[i - K];
        dp[i] = i - 1 >= 0 ? max(dp[i - 1], sum) : sum;
      }
    }
    return dp;
  }

  int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    /*
    [0,6,5,2,2,5,1,9,4], M = 2
    sliding window sums of size 2
    [0, 6, 11, 7, 4, 7, 6, 10, 13]
    B[i] is the maximum sliding window sum for [0, i]
    [0, 6, 11, 11, 11, 11, 11, 11, 13]
    C[i] is the maximum sliding window sum for [i, N)

    dp[i] is partition of [0, i] and [i+1, N)
    dp[i] = B[i] + C[i+1]
    the result is max(dp[i])
    */
    vector<int> A_rev = A;
    reverse(A_rev.begin(), A_rev.end());
    vector<int> l_forward = max_sliding_window_sum(A, L),
                l_backward = max_sliding_window_sum(A_rev, L),
                m_forward = max_sliding_window_sum(A, M),
                m_backward = max_sliding_window_sum(A_rev, M);
    reverse(l_backward.begin(), l_backward.end());
    reverse(m_backward.begin(), m_backward.end());
    int res = 0;
    for (int i = 0; i + 1 < A.size(); i++) {
      res = max(res, l_forward[i] + m_backward[i + 1]);
      res = max(res, m_forward[i] + l_backward[i + 1]);
    }
    return res;
  }
};

int main() { return 0; }
