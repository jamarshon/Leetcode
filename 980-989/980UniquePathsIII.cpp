/*
980. Unique Paths III
On a 2-dimensional grid, there are 4 types of squares:

  1 represents the starting square.  There is exactly one starting square.
  2 represents the ending square.  There is exactly one ending square.
  0 represents empty squares we can walk over.
  -1 represents obstacles that we cannot walk over.

Return the number of 4-directional walks from the starting square to the ending
square, that walk over every non-obstacle square exactly once.

Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation:
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Note:

  1 <= grid.length * grid[0].length <= 20
/*
  Submission Date: 2019-02-20
  Runtime: 16 ms
  Difficulty: HARD
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {-1, 1, 0, 0};
  int N, M, zeros;
  unordered_set<int> s;

 public:
  /*
  count number of zeros and do dfs keep tracking of visited cells
  (don't revisit cells). if reach end point and number of visited
  equals number of zero return 1.
  */
  int dfs(const vector<vector<int>>& grid, int i, int j) {
    int res = 0;
    for (int k = 0; k < 4; k++) {
      int n_i = i + dx[k];
      int n_j = j + dy[k];
      if (0 <= n_i && n_i < N && 0 <= n_j && n_j < M) {
        int key = n_i * M + n_j;
        if (grid[n_i][n_j] == 2 && s.size() == zeros) {
          res += 1;
          continue;
        }
        if (grid[n_i][n_j] != 0 || s.count(key)) continue;
        s.insert(key);
        res += dfs(grid, n_i, n_j);
        s.erase(key);
      }
    }

    return res;
  }

  int uniquePathsIII(vector<vector<int>>& grid) {
    N = grid.size();
    M = grid[0].size();
    s.clear();
    int s_i = -1, s_j = -1;
    zeros = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        zeros += (grid[i][j] == 0);
        if (grid[i][j] == 1) {
          s_i = i;
          s_j = j;
        }
      }
    }
    return dfs(grid, s_i, s_j);
  }
};

int main() { return 0; }
