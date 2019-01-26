/*
48. Rotate Image
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

/*
    Submission Date: 2016-12-15
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <vector>
class Solution {
 public:
  int replace(int value, int i, int j, vector<vector<int>>& matrix) {
    int prev = matrix[i][j];
    matrix[i][j] = value;
    return prev;
  }

  void rotate(vector<vector<int>>& matrix) {
    int n = matrix[0].size();
    for (int i = 0, numLayers = n / 2; i < numLayers; i++) {
      for (int j = i, rightBoundary = n - i - 1; j < rightBoundary; j++) {
        int temp = matrix[n - j - 1][i];
        temp = replace(temp, i, j, matrix);
        temp = replace(temp, j, n - i - 1, matrix);
        temp = replace(temp, n - i - 1, n - j - 1, matrix);
        temp = replace(temp, n - j - 1, i, matrix);
      }
    }
  }
};

int main() { return 0; }