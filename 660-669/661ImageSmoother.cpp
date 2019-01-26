/*
661. Image Smoother
Given a 2D integer matrix M representing the gray scale of an image, you need to
design a smoother to make the gray scale of each cell becomes the average gray
scale (rounding down) of all the 8 surrounding cells and itself. If a cell has
less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
Note:
The value in the given matrix is in the range of [0, 255].
The length and width of the given matrix are in the range of [1, 150].
/*
    Submission Date: 2018-06-08
    Runtime: 178 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int help(const vector<vector<int>>& A, int i, int j, int N, int M) {
    int sum = 0;
    int points = 0;
    for (int k = -1; k <= 1; k++) {
      for (int l = -1; l <= 1; l++) {
        int new_i = i + k;
        int new_j = j + l;
        if (0 <= new_i && new_i < N && 0 <= new_j && new_j < M) {
          points++;
          sum += A[new_i][new_j];
        }
      }
    }

    return sum / points;
  }

  vector<vector<int>> imageSmoother(vector<vector<int>>& A) {
    if (A.empty()) return A;
    int N = A.size();
    int M = A[0].size();

    vector<vector<int>> res(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        res[i][j] = help(A, i, j, N, M);
      }
    }

    return res;
  }
};

int main() { return 0; }