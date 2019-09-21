/*
1029. Two City Scheduling
There are 2N people a company is planning to interview. The cost of flying the
i-th person to city A is costs[i][0], and the cost of flying the i-th person to
city B is costs[i][1].

Return the minimum cost to fly every person to a city such that exactly N people
arrive in each city.

Example 1:

Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation:
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people
interviewing in each city.

Note:

  1 <= costs.length <= 100
  It is guaranteed that costs.length is even.
  1 <= costs[i][0], costs[i][1] <= 1000
/*
  Submission Date: 2019-09-20
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    /*
    dp[i][j] represents the min cost of i + j people where
    i people go to A and j people go to B. this represents
    people from indices [0, i + j]
    dp[0][j] would just be the cumulative cost of B
    dp[i][0] would just be the cumulative cost of A
    dp[i][j] = min(
        dp[i-1][j] + costs[i+j-1][0], // person goes to A
        dp[i][j-1] + costs[i+j-1][1] // person goes to B
      )
    */
    int N = costs.size() / 2;
    int dp[N + 1][N + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) dp[i][0] = dp[i - 1][0] + costs[i - 1][0];
    for (int j = 1; j <= N; j++) dp[0][j] = dp[0][j - 1] + costs[j - 1][1];
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        dp[i][j] = min(dp[i - 1][j] + costs[i + j - 1][0],
                       dp[i][j - 1] + costs[i + j - 1][1]);
    return dp[N][N];
  }
};

class Solution2 {
 public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    /*
    for a person if they go to one city for costs[i][0], it means
    we get the benefit of not going to the other city by costs[i][1] -
    costs[i][0]

    e.g 100 to go to city A and 110 to go to city B, if they go
    to city A we save 110-100=10

    so we sort by the savings and the top half savings go to A
    the bottom half go to B
    */
    sort(costs.begin(), costs.end(),
         [](const vector<int>& left, const vector<int>& right) {
           return left[0] - left[1] < right[0] - right[1];
         });

    int res = 0;
    for (int i = 0, N = costs.size(); i < N; i++) {
      res += i >= N / 2 ? costs[i][1] : costs[i][0];
    }
    return res;
  }
};

int main() { return 0; }
