/*
10. Regular Expression Matching
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

/*
    Submission Date: 2017-05-25
    Runtime: 15 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
class Solution {
 public:
  bool isMatch(string s, string p) {
    int M = s.size();
    int N = p.size();
    bool dp[M + 1][N + 1];
    for (int i = 0; i < M + 1; i++) {
      for (int j = 0; j < N + 1; j++) {
        dp[i][j] = false;
      }
    }
    dp[0][0] = true;
    for (int i = 0; i < M + 1; i++) {
      for (int j = 1; j < N + 1; j++) {
        if (p[j - 1] == '*') {
          // repeat zero times so take the result of excluding the last two
          // characters of p
          bool repeat_zero_times = dp[i][j - 2];
          // or repeat many times which is matching preceding char to '*' and
          // previous characters excluding current character in s
          dp[i][j] =
              repeat_zero_times || (i > 0 && dp[i - 1][j] &&
                                    (s[i - 1] == p[j - 2] || p[j - 2] == '.'));

        } else {
          // s must not be empty and the current characters of s and j must
          // match and the previous characters excluding the current must match
          dp[i][j] = i > 0 && dp[i - 1][j - 1] &&
                     (s[i - 1] == p[j - 1] || p[j - 1] == '.');
        }
      }
    }
    return dp[M][N];
  }
};

int main() { return 0; }