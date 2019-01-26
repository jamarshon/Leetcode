/*
877. Stone Game
Alex and Lee play a game with piles of stones.  There are an even number
of piles arranged in a row, and each pile has a positive integer number of
stones piles[i].

The objective of the game is to end with the most stones.  The total number of
stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes
the entire pile of stones from either the beginning or the end of the row.  This
continues until there are no more piles left, at which point the person with the
most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the
game.

Example 1:

Input: [5,3,4,5]
Output: true
Explanation:
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10
points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with
9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we
return true.

Note:

  2 <= piles.length <= 500
  piles.length is even.
  1 <= piles[i] <= 500
  sum(piles) is odd.
/*
  Submission Date: 2019-01-26
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int N;

 public:
  int get(const vector<vector<int>>& dp, int i, int j) {
    if (i <= j && i >= 0 && i < N && j >= 0 && j < N) {
      return dp[i][j];
    }
    return 0;
  }
  bool stoneGame(vector<int>& piles) {
    N = piles.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    for (int gap = 0; gap < N; gap++) {
      for (int i = 0; i + gap < N; i++) {
        int j = gap;
        dp[i][j] =
            max(piles[i] + min(get(dp, i + 1, j - 1), get(dp, i + 2, j)),
                piles[j] + min(get(dp, i, j - 2), get(dp, i + 1, j - 1)));
      }
    }

    return get(dp, 0, N - 1) > get(dp, 1, N - 1) ||
           get(dp, 0, N - 1) > get(dp, 0, N - 2);
  }
};

int main() { return 0; }
