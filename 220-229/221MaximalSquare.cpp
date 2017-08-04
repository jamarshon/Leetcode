/*
221. Maximal Square
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and 
return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

/*
    Submission Date: 2017-08-03
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int M = matrix.size();
        if(M == 0) return 0;
        int N = matrix[0].size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));

        int res = 0;
        for(int i = M-1; i >= 0; i--) {
            for(int j = N-1; j >= 0; j--) {
                if(matrix[i][j] == '0') continue;
                dp[i][j] = 1 + min(min(dp[i+1][j], dp[i+1][j+1]), dp[i][j+1]);
                res = max(res, dp[i][j]);
            }
        }

        return res*res;
    }
};

int main() {
    return 0;
}