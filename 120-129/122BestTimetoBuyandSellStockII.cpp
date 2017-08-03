/*
122. Best Time to Buy and Sell Stock II
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple 
transactions at the same time (ie, you must sell the stock before you buy again).

/*
    Submission Date: 2017-08-02
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        int res = 0;
        // "a <= b <= c <= d"
        // the profit is "d - a = (b - a) + (c - b) + (d - c)" 
        // "a <= b >= b' <= c <= d"
        // the profit is "(b - a) + (d - b')"
        for(int i = 0; i < N - 1 ; i++) res += max(prices[i+1] - prices[i], 0);
        return res;
    }
};


int main() {
    return 0;
}