/*
123. Best Time to Buy and Sell Stock III
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you 
buy again).

/*
    Submission Date: 2017-08-02
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int K = 2;
        int N = prices.size();

        if(N <= 1) return 0;

        /**
            dp[k][i] represents maximum profit of at most k transactions until index i
            dp[k][0] = 0 as no points
            dp[0][i] = 0 as no transactions
            dp[k][i] = max(
                    dp[k][i-1], <- ignore element i 
                    price[i] + max{j = 0 to i}(-price[j] + dp[k-1][j]) <- take element i with element j
                                                                    and have k-1 transactions until index j 
                    )
        */
        vector<vector<int>> dp(K + 1, vector<int>(N, 0));
        for(int k = 1; k <= K; k++) {
            int tmp_max = dp[k-1][0] - prices[0];
            for(int i = 1; i < N; i++) {
                dp[k][i] = max(dp[k][i-1], prices[i] + tmp_max);
                tmp_max = max(tmp_max, dp[k-1][i] - prices[i]);
            }
        }

        return dp[K][N-1];
    }
    int maxProfit3(vector<int>& prices) {
        int lowest_price1 = INT_MAX,
            lowest_price2 = INT_MAX,
            max_profit1 = 0,
            max_profit2 = 0;

        // lowest_price2 = buy2 - max_profit_one_buy_one_sell (ie. sell1 - buy1)
        // max_profit2 = sell2 - (buy2 - max_profit_one_buy_one_sell)
        //             = profit2 + profit1
        for(auto price: prices) {
            lowest_price1 = min(lowest_price1, price);
            max_profit1 = max(max_profit1, price - lowest_price1);
            lowest_price2 = min(lowest_price2, price - max_profit1);
            max_profit2 = max(max_profit2, price - lowest_price2);
        }

        return max_profit2;
    }

    int maxProfit2(vector<int>& prices) {
        int N = prices.size();
        if(N == 0) return 0;

        // forward[i] is max profit from [0, i] and backward[i] is max profit from [i,N)
        vector<int> forward(N, 0), backward(N, 0);
        int min_price = prices[0]; 
        for(int i = 1; i < N; i++) {
            forward[i] = max(forward[i-1], prices[i] - min_price);
            if(prices[i] < min_price) min_price = prices[i];
        }

        int max_price = prices[N-1]; 
        for(int i = N - 2; i >= 0; i--) {
            backward[i] = max(backward[i+1], max_price - prices[i]);
            if(prices[i] > max_price) max_price = prices[i];
        }

        int res = 0;
        for(int i = 0; i < N; i++) {
            if(i + 1 < N) res = max(res, forward[i] + backward[i+1]);
            res = max(max(res, forward[i]), backward[i]);
        }

        return res;
    }
};

int main() {
    return 0;
}