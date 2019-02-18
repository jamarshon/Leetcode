/*
994. Rotting Oranges
In a given grid, each cell can have one of three values:

  the value 0 representing an empty cell;
  the value 1 representing a fresh orange;
  the value 2 representing a rotten orange.

Every minute, any fresh orange that is adjacent (4-directionally) to a rotten
orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh
orange.  If this is impossible, return -1 instead.

Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never
rotten, because rotting only happens 4-directionally.

Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer
is just 0.

Note:

  1 <= grid.length <= 10
  1 <= grid[0].length <= 10
  grid[i][j] is only 0, 1, or 2.
/*
  Submission Date: 2019-02-17
  Runtime: 16 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

enum Orange { kEmpty, kFresh, kRotten };

class Solution {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

 public:
  typedef pair<int, int> pii;
  int orangesRotting(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;

    int num_fresh = 0;
    queue<pii> q;
    int N = grid.size();
    int M = grid[0].size();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] == kFresh)
          num_fresh++;
        else if (grid[i][j] == kRotten)
          q.emplace(i, j);
      }
    }

    int minutes = 0;
    int i, j;
    while (!q.empty() && num_fresh > 0) {
      minutes++;
      for (int l = 0, size = q.size(); l < size; l++) {
        tie(i, j) = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
          int new_i = i + dx[k];
          int new_j = j + dy[k];
          if (0 <= new_i && new_i < N && 0 <= new_j && new_j < M &&
              grid[new_i][new_j] == kFresh) {
            grid[new_i][new_j] = kRotten;
            num_fresh--;
            q.emplace(new_i, new_j);
          }
        }
      }
    }

    return (num_fresh == 0) ? minutes : -1;
  }
};

int main() { return 0; }
