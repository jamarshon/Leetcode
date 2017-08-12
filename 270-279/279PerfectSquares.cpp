/*
279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers 
(for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, 
return 2 because 13 = 4 + 9.

/*
    Submission Date: 2017-08-12
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        if(n == 0) return 0;
        int sq = sqrt(n);
        vector<int> dp(n + 1);

        iota(dp.begin(), dp.end(), 0);

        // dp[i][j] means minimum number using [0,i] squares for the number j
        // dp[i][j] = min(
        //              dp[i-1][j], // we don't use this square
        //              dp[i][j-i*i] // we use this square )
        // since we only use the previous row, just save space with 1d vector
        for(int i = 2; i <= sq; i++) {
            for(int j = 1; j <= n; j++) {
                int r = j - i*i;
                if(r >= 0) {
                    dp[j] = min(dp[j], dp[r] + 1);
                }
            }
        }

        return dp[n];
    }
};

int main() {
    return 0;
}