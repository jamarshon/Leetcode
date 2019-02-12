/*
542. 01 Matrix
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each
cell.

The distance between two adjacent cells is 1.

Example 1:
Input:
0 0 0
0 1 0
0 0 0

Output:
0 0 0
0 1 0
0 0 0

Example 2:
Input:
0 0 0
0 1 0
1 1 1

Output:
0 0 0
0 1 0
1 2 1

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
/*
  Submission Date: 2019-02-10
  Runtime: 220 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<vector<int>> res(N, vector<int>(M, -1));
    // from the top left
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (matrix[i][j] == 0) {
          res[i][j] = 0;
        } else {
          if (i > 0 && res[i - 1][j] != -1) {
            int x = 1 + res[i - 1][j];
            res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
          }
          if (j > 0 && res[i][j - 1] != -1) {
            int x = 1 + res[i][j - 1];
            res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
          }
        }
      }
    }

    // from the bottom right
    for (int i = N - 1; i >= 0; i--) {
      for (int j = M - 1; j >= 0; j--) {
        if (i + 1 < N && res[i + 1][j] != -1) {
          int x = 1 + res[i + 1][j];
          res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
        }
        if (j + 1 < M && res[i][j + 1] != -1) {
          int x = 1 + res[i][j + 1];
          res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
