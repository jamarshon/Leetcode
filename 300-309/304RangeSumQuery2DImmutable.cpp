/*
304. Range Sum Query 2D - Immutable
Given a 2D matrix matrix, find the sum of the elements inside the rectangle
defined by its upper left corner (row1, col1) and lower right corner (row2,
col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1)
and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
  int rows_, cols_;
  vector<vector<int>> dp_;

 public:
  NumMatrix(vector<vector<int>> matrix) {
    rows_ = matrix.size();
    cols_ = matrix.empty() ? 0 : matrix[0].size();

    dp_.assign(rows_, vector<int>(cols_));
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        dp_[i][j] = matrix[i][j];
        if (i > 0) dp_[i][j] += dp_[i - 1][j];
        if (i > 0 && j > 0) dp_[i][j] -= dp_[i - 1][j - 1];
        if (j > 0) dp_[i][j] += dp_[i][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int res = dp_[row2][col2];
    if (row1 > 0) res -= dp_[row1 - 1][col2];
    if (col1 > 0) res -= dp_[row2][col1 - 1];
    if (row1 > 0 && col1 > 0) res += dp_[row1 - 1][col1 - 1];
    return res;
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

int main() { return 0; }