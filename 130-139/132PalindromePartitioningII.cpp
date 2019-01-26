/*
132. Palindrome Partitioning II
Given a string s, partition s such that every substring of the partition is a
palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1
cut.

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int minCut(string s) {
    int len = s.size();
    int dp[len + 1];
    for (int i = 0; i <= len; i++) dp[i] = i - 1;

    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (i + j > len || i - j < 0) break;
        if (s[i + j] != s[i - j]) break;
        dp[i + j + 1] = min(1 + dp[i - j], dp[i + j + 1]);
      }

      for (int j = 0; j < len; j++) {
        if (i + j + 1 > len || i - j < 0) break;
        if (s[i + j + 1] != s[i - j]) break;
        if (i + j + 2 > len) break;
        dp[i + j + 2] = min(1 + dp[i - j], dp[i + j + 2]);
      }
    }

    return dp[len];
  }
};

int main() {
  Solution s;
  return 0;
}