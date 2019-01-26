/*
892. Surface Area of 3D Shapes
On a N * N grid, we place some 1 * 1 * 1 cubes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid
cell (i, j).

Return the total surface area of the resulting shapes.

Example 1:

Input: [[2]]
Output: 10

Example 2:

Input: [[1,2],[3,4]]
Output: 34

Example 3:

Input: [[1,0],[0,2]]
Output: 16

Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 32

Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 46

Note:

  1 <= N <= 50
  0 <= grid[i][j] <= 50
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int di[2] = {-1, 0};
  int dj[2] = {0, -1};

 public:
  int surfaceArea(vector<vector<int>>& grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == 0) continue;
        res += 4 * grid[i][j] + 2;
        for (int k = 0; k < 2; k++) {
          int n_i = i + di[k];
          int n_j = j + dj[k];
          if (0 <= n_i && n_i < grid.size() && 0 <= n_j &&
              n_j < grid[j].size()) {
            res -= 2 * min(grid[i][j], grid[n_i][n_j]);
          }
        }
      }
    }
    return res;
  }
};

int main() { return 0; }
