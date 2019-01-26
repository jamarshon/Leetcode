/*
746. Min Cost Climbing Stairs
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0
indexed).

Once you pay the cost, you can either climb one or two steps. You need to find
minimum cost to reach the top of the floor, and you can either start from the
step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping
cost[3]. Note: cost will have a length in the range [2, 1000]. Every cost[i]
will be an integer in the range [0, 999].
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    if (cost.empty()) return 0;
    int N = cost.size();

    vector<int> dp(N + 2, 0);
    for (int i = N - 1; i >= 0; i--) {
      dp[i] = cost[i] + min(dp[i + 1], dp[i + 2]);
    }

    return N == 1 ? dp[0] : min(dp[0], dp[1]);
  }
};

int main() { return 0; }