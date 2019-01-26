/*
59. Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from 1 to n2
in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> v(n, vector<int>(n, 0));
    function<int(int, int)> mod = [](const int& x, const int& n) -> int {
      int r = x % n;
      return r < 0 ? r + n : r;
    };

    int i = 0;
    int j = 0;
    int di = 0;
    int dj = 1;

    for (int count = 1; count <= n * n; count++) {
      v[i][j] = count;
      if (v[mod(i + di, n)][mod(j + dj, n)]) {
        swap(di, dj);
        dj *= -1;
      }
      i += di;
      j += dj;
    }
    return v;
  }
};

int main() {
  Solution s;
  vector<vector<int>> t = s.generateMatrix(4);
  for (auto v2 : t) {
    for (auto e : v2) cout << e << ' ';
    cout << endl;
  }
  return 0;
}