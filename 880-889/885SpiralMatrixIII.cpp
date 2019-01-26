/*
885. Spiral Matrix III
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing
east.

Here, the north-west corner of the grid is at the first row and column, and the
south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk
outside the grid (but may return to the grid boundary later.) 

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order
they were visited.

Example 1:

Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]

Example 2:

Input: R = 5, C = 6, r0 = 1, c0 = 4
Output:
[[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

Note:

  1 <= R <= 100
  1 <= C <= 100
  0 <= r0 < R
  0 <= c0 < C
/*
  Submission Date: 2019-01-26
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int key(int i, int j, int R, int C) { return i * C + j; }
  vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
    unordered_set<int> visited;

    vector<vector<int>> res;
    res.push_back({r0, c0});
    visited.insert(key(r0, c0, R, C));

    int i = r0, j = c0;
    int dx = 1;
    int dy = 0;
    while (visited.size() != R * C) {
      if (!(0 <= i + dy && i + dy < R) || !(0 <= j + dx && j + dx < C)) {
        // will go out of bounds so change direction
        swap(dx, dy);
        dx *= -1;
      } else {
        i += dy;
        j += dx;
        if (visited.count(key(i, j, R, C))) {
          continue;
        } else {
          // an unvisited cell so push it to result
          res.push_back({i, j});
          visited.insert(key(i, j, R, C));

          // if node to the right isn't visited or if it is out of bounds change
          // directions
          int rot_dx = -dy;
          int rot_dy = dx;

          if (!(0 <= i + rot_dy && i + rot_dy < R) ||
              !(0 <= j + rot_dx && j + rot_dx < C) ||
              !visited.count(key(i + rot_dy, j + rot_dx, R, C))) {
            swap(dx, dy);
            dx *= -1;
          }
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
