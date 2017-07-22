/*
121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the 
stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;

        int smallest, profit;
        smallest = prices.front();
        profit = 0;

        for(int i = 0; i < prices.size(); i++) {
            smallest = min(prices[i], smallest);
            profit = max(profit, prices[i] - smallest);
        }
        return profit;
    }
};

int main() {
    Solution s;
    return 0;
}