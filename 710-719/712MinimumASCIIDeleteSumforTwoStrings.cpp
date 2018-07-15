/*
712. Minimum ASCII Delete Sum for Two Strings
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to 
make two strings equal. 

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the 
sum. 
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum 
possible to achieve this. 



Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to 
the sum. 
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 
403. 
If instead we turned both strings into "lee" or "eet", we would get answers of 
433 or 417, which are higher. 



Note:
0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].

/*
    Submission Date: 2018-07-01
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
    dp[i][j] is minimum cost for s1[0, i) s2[0, j)
    dp[0][0] = 0
    dp[0][j] = s2[j-1] + dp[i][j-1] // sum of ascii of s2[0, j)
    dp[i][0] = s1[i-1] + dp[i-1][j] // sum of ascii of s1[0, i)
    
    if s1[i-1] == s2[j-1] 
        dp[i][j] = dp[i-1][j-1] // this character does not to be deleted so
                                // it is just excluding the two end characters
    else
        dp[i][j] = min(
            s1[i-1] + dp[i-1][j], // the cost of the end character of s1 + cost of not using that character
            s2[j-1] + dp[i][j-1] // cost of the end character of s2 + cost of not using that character
        )
    */
    int minimumDeleteSum(string s1, string s2) {
        int N = s1.size(), M = s2.size();
        int dp[N+1][M+1];
        for(int i = 0; i <= N; i++) {
            for(int j = 0; j <= M; j++) {
                if(i == 0 && j == 0) {
                    dp[i][j] = 0;
                } else if(i == 0) {
                    dp[i][j] = s2[j-1] + dp[i][j-1];
                } else if(j == 0) {
                    dp[i][j] = s1[i-1] + dp[i-1][j];
                } else if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(s1[i-1] + dp[i-1][j], s2[j-1] + dp[i][j-1]);
                }
            }
        }
        
        return dp[N][M];
    }
};

int main() {
    return 0;
}