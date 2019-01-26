/*
44. Wildcard Matching
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

/*
    Submission Date: 2017-06-20
    Runtime: 75 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isMatch(string s, string p) {
    int M = p.size();
    int N = s.size();

    vector<vector<bool>> dp(M + 1, vector<bool>(N + 1, false));

    dp[0][0] = true;

    for (int j = 1; j <= N; j++) {
      dp[0][j] = false;
    }

    for (int i = 1; i <= M; i++) {
      if (p[i - 1] == '?')
        dp[i][0] = false;
      else if (p[i - 1] == '*')
        dp[i][0] = dp[i - 1][0];
    }

    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= N; j++) {
        // same or single character means diagonal
        if (p[i - 1] == s[j - 1] || p[i - 1] == '?') {
          dp[i][j] = dp[i - 1][j - 1];
        } else if (p[i - 1] == '*') {
          // either empty sequence or everything not including s[j]
          dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        } else {
          // different letters
          dp[i][j] = false;
        }
      }
    }

    return dp[M][N];
  }
};

int main() {
  Solution s;
  cout << s.isMatch("aa", "a") << ' ' << false << endl;
  cout << s.isMatch("aa", "aa") << ' ' << true << endl;
  cout << s.isMatch("aaa", "aa") << ' ' << false << endl;
  cout << s.isMatch("aa", "*") << ' ' << true << endl;
  cout << s.isMatch("aa", "a*") << ' ' << true << endl;
  cout << s.isMatch("ab", "?*") << ' ' << true << endl;
  cout << s.isMatch("aab", "c*a*b") << ' ' << false << endl;
  return 0;
}