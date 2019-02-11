/*
959. Regions Cut By Slashes
In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \,
or blank space.  These characters divide the square into contiguous regions.

(Note that backslash characters are escaped, so a \ is represented as "\\".)

Return the number of regions.

Example 1:

Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:

Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:

Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/,
and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:

Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\,
and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:

Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

Note:

  1 <= grid.length == grid[0].length <= 30
  grid[i][j] is either '/', '\', or ' '.
/*
  Submission Date: 2019-02-10
  Runtime: 176 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct UnionFind {
  unordered_map<int, int> parent_, rank_;
  void Create(int x) {
    parent_[x] = x;
    rank_[x] = 0;
  }

  int Find(int x) {
    if (parent_[x] != x) parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Union(int x, int y) {
    int r1 = Find(x);
    int r2 = Find(y);

    if (r1 == r2) return;
    if (rank_[r1] < rank_[r2]) {
      parent_[r1] = r2;
    } else {
      parent_[r2] = r1;
      if (rank_[r1] == rank_[r2]) rank_[r1]++;
    }
  }
};

enum Directions { NORTH, EAST, SOUTH, WEST };

class Solution {
 public:
  /*
  4*n*n grid where the four represents north, east, south, west of a single
  1x1 block where the block is split into 4 by the diagonals
  ----
  |\/|
  |/\|
  ----

  if grid[i][j] is '/' then we can only join north,west and south,east
  if grid[i][j] is '\' then we can only join north,east and south,west
  if its empty join all 4

  then connect adjacent cells.

  flatten a 2d array of [N][M] than element [i][j] is i*M + j
  flatten a 3d array of [N][M][O] than element [i][j][k] is i*M + j + k*N*M or
    O*(i*M + j) + k which has the z elements be contiguous and not the x elments
  */
  int regionsBySlashes(vector<string>& grid) {
    UnionFind uf;
    int N = grid.size();
    for (int i = 0; i < 4 * N * N; i++) uf.Create(i);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        char c = grid[i][j];
        int key = 4 * (i * N + j);
        if (c != '/') {
          uf.Union(key + NORTH, key + EAST);  // north,east
          uf.Union(key + SOUTH, key + WEST);  // south,west
        }
        if (c != '\\') {
          uf.Union(key + NORTH, key + WEST);  // north,west
          uf.Union(key + SOUTH, key + EAST);  // south,east
        }

        // adjacent cells
        // north and south
        if (i > 0) uf.Union(key + NORTH, (key - 4 * N) + SOUTH);
        if (i + 1 < N) uf.Union(key + SOUTH, (key + 4 * N) + NORTH);

        // west and east
        if (j > 0) uf.Union(key + WEST, (key - 4) + EAST);
        if (j + 1 < N) uf.Union(key + EAST, (key + 4) + WEST);
      }
    }

    int ans = 0;
    // find the number of components
    for (int i = 0; i < 4 * N * N; i++) ans += uf.Find(i) == i;
    return ans;
  }
};

int main() { return 0; }
