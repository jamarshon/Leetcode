/*
73. Set Matrix Zeroes
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do
it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

/*
    Submission Date: 2017-06-23
    Runtime: 65 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int M = matrix.size();
    if (M == 0) return;
    int N = matrix[0].size();

    bool has_zero_first_row = false;
    bool has_zero_first_col = false;

    for (int i = 0; i < M; i++) {
      if (matrix[i][0] == 0) {
        has_zero_first_col = true;
      }
    }

    for (int j = 0; j < N; j++) {
      if (matrix[0][j] == 0) {
        has_zero_first_row = true;
      }
    }

    for (int i = 1; i < M; i++) {
      for (int j = 1; j < N; j++) {
        if (matrix[i][j] == 0) {
          // mark row and column
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    for (int i = 1; i < M; i++) {
      for (int j = 1; j < N; j++) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }

    if (has_zero_first_row) {
      for (int j = 0; j < N; j++) {
        matrix[0][j] = 0;
      }
    }

    if (has_zero_first_col) {
      for (int i = 0; i < M; i++) {
        matrix[i][0] = 0;
      }
    }
  }
};

int main() { return 0; }