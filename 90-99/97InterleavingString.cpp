/*
97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    
    bool isInterleave(string s1, string s2, string s3) {
        int M = s1.size();
        int N = s2.size();
        if(M + N != s3.size()) return false;

        bool dp[M + 1][N + 1];

        for(int i = 0; i <= M; i++) {
            for(int j = 0; j <= N; j++) {
                if(i == 0 && j == 0) dp[i][j] = true;
                else if(i == 0) dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i + j - 1];
                else if(j == 0) dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i + j - 1];
                else dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i + j - 1]) || (dp[i-1][j] && s1[i-1] == s3[i + j - 1]);
            }
        }

        return dp[M][N];
    }
};


int main() {
    Solution s;
    return 0;
}