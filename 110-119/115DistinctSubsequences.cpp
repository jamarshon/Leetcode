/*
115. Distinct Subsequences
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some 
(can be none) of the characters without disturbing the relative positions of the remaining characters. 
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.

/*
    Submission Date: 2017-08-02
    Runtime: 28 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int M = t.size();
        int N = s.size();

        // row is template and column is pattern
        vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

        // if template is empty then there is one way to make pattern into it
        // if pattern is empty, there is no way to make it match template so 0
        fill(dp[0].begin(), dp[0].begin() + N + 1, 1);

        for(int i = 1; i <= M; i++) {
            for(int j = 1; j <= N; j++) {
                // if they are same character it means it is the number of ways
                // using this common character so dp[i-1][j-1] and number of ways
                // not using this character dp[i][j-1]
                // e.g. t = rab and s = rabb it is number of sequences of ra and rab ("b" of pattern used)
                // plus rab and rab ("b" of pattern not used)
                if(t[i-1] == s[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }

        return dp[M][N];
    }
};

int main() {
    return 0;
}