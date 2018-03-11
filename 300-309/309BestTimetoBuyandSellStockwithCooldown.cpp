/*
309. Best Time to Buy and Sell Stock with Cooldown
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before 
you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        if(N < 2) return 0;
        
        vector<int> dp(N);
        dp[N-1] = 0;
        dp[N-2] = max(0, prices[N-1] - prices[N-2]);
        
        int max_sold = max(prices[N-1], prices[N-2]);
        for(int i = N-3; i >= 0; i--) {
            // buy now prices[i] and sell on day j then get dp[j+2]
            // -prices[i] + prices[j] + dp[j+2];
            dp[i] = max(dp[i+1], -prices[i] + max_sold); 
            max_sold = max(max_sold, prices[i] + dp[i+2]);
        }
        
        return dp[0];
    }
};

int main() {
    return 0;
}