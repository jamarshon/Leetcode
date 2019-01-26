/*
64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left
to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

/*
    Submission Date: 2017-06-23
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int M = grid.size();

    if (M == 0) return 0;
    int N = grid[0].size();

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int min_path = INT_MAX;
        if (j > 0) {
          min_path = min(min_path, grid[i][j - 1]);
        }
        if (i > 0) {
          min_path = min(min_path, grid[i - 1][j]);
        }

        min_path = (min_path == INT_MAX) ? 0 : min_path;
        grid[i][j] += min_path;
      }
    }

    return grid[M - 1][N - 1];
  }
};

int main() { return 0; }