/*
322. Coin Change
You are given coins of different denominations and a total amount of money
amount. Write a function to compute the fewest number of coins that you need to
make up that amount. If that amount of money cannot be made up by any
combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
/*
    Submission Date: 2017-03-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    int N = coins.size();
    vector<int> dp(amount + 1, INT_MAX);

    dp[0] = 0;

    for (int i = 1; i <= N; i++) {
      for (int j = 0; j <= amount; j++) {
        if (j - coins[i - 1] >= 0 &&
            dp[j - coins[i - 1]] != INT_MAX) {  // we can take this coin
          dp[j] = min(dp[j - coins[i - 1]] + 1, dp[j]);
        }
      }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
};

int main() { return 0; }