/*
931. Minimum Falling Path Sum
Given a square array of integers A, we want the minimum sum of a falling path
through A.

A falling path starts at any element in the first row, and chooses one element
from each row.  The next row's choice must be in a column that is different from
the previous row's column by at most one.

Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: 12
Explanation:
The possible falling paths are:

  [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
  [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
  [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]

The falling path with the smallest sum is [1,4,7], so the answer is 12.

Note:

  1 <= A.length == A[0].length <= 100
  -100 <= A[i][j] <= 100
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();

    for (int i = n - 2; i >= 0; i--) {  // skip last row
      for (int j = 0; j < m; j++) {
        int to_add = INT_MAX;
        for (int k = -1; k <= 1; k++) {
          if (j + k >= 0 && j + k < m) {
            to_add = min(to_add, A[i + 1][j + k]);
          }
        }

        A[i][j] += to_add;
      }
    }
    return *min_element(A[0].begin(), A[0].end());
  }
};

int main() { return 0; }
