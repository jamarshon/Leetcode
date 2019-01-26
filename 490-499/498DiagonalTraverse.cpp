/*
498. Diagonal Traverse
Given a matrix of M x N elements (M rows, N columns), return all elements of the
matrix in diagonal order as shown in the below image.


Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation:




Note:

The total number of elements of the given matrix will not exceed 10,000.

/*
    Submission Date: 2018-07-09
    Runtime: 52 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  all numbers in a diagonal indices add up to the same number (e.g i + j == x)
  the max is N-1 + M-1 = N - M - 2
  so for x = [0, N - M - 2], start from the top row go down i = [0, N) and see
  if x - i produces a j that is within the bounds [0, M). 0 <= x - i < M means
  x - M < i && i <= x
  0 <= i && i < N
  
  i > max(-1, x - M)
  i < min(N, x + 1)
  
  This creates all the diagonals going down.
  reverse the even diagonals and return
  */
  vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<int> res;

    for (int x = 0; x < N + M - 1; x++) {
      int sz = res.size();
      for (int i = max(0, x - M + 1); i < min(N, x + 1); i++) {
        res.push_back(matrix[i][x - i]);
      }
      if (x % 2 == 0) reverse(res.begin() + sz, res.end());
    }

    return res;
  }
};

class Solution2 {
  int d[2][2] = {{-1, 1}, {1, -1}};
  bool up = true;

 public:
  /*
  toggle between going up and down when hit out of bounds
  to find the new coordinate
      if going up:
          if hits the right boundary then can't keep going right so go down
          else keep going right
      if going down:
          if hits the bottom boundary then can't keep going down so go right
          else keep going down
  */
  vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<int> res;
    int x = 0, y = 0;
    for (int i = 0; i < N * M; i++) {
      res.push_back(matrix[y][x]);
      int new_x = x + d[up][0];
      int new_y = y + d[up][1];
      if (0 <= new_x && new_x < M && 0 <= new_y && new_y < N) {
        x = new_x;
        y = new_y;
      } else {
        if (up) {
          if (new_x == M)
            y++;
          else
            x++;
        } else {
          if (new_y == N)
            x++;
          else
            y++;
        }
        up ^= 1;
      }
    }

    return res;
  }
};

int main() { return 0; }
