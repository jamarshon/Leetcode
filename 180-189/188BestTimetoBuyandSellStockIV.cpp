/*
188. Best Time to Buy and Sell Stock IV
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock 
before you buy again).

/*
    Submission Date: 2017-08-07
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(int K, vector<int>& prices) {
        int N = prices.size();
        if(N < 2) return 0;
        
        if(K > N) {
            // unlimited transactions
            int count = 0;
            for(int i = 1; i < N; i++) {
                count += max(prices[i] - prices[i-1], 0);
            }
            return count;
        }

        // space saving dp where dp[k][i] is maximum of k transactions from indices 0 to i
        // dp[k][i] = max(
        //              dp[k][i-1], 
        //              prices[i] + max(dp[k-1][j] - prices[j]) for all j < i )
        // dp[0][i] = 0
        vector<int> dp(N, 0);
        for(int k = 1; k <= K; k++) {
            int max_prev_trans = -prices[0];
            for(int i = 1; i < N; i++) {
                max_prev_trans = max(max_prev_trans, dp[i] - prices[i]);
                dp[i] = max(dp[i-1], prices[i] + max_prev_trans);
            }
        }
        
        return dp[N-1];
    }
};

int main() {
    Solution s;
    return 0;
}