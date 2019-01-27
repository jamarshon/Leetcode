/*
977. Squares of a Sorted Array
Given an array of integers A sorted in non-decreasing order, return an array of
the squares of each number, also in sorted non-decreasing order.

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:

  1 <= A.length <= 10000
  -10000 <= A[i] <= 10000
  A is sorted in non-decreasing order.
/*
  Submission Date: 2019-01-26
  Runtime: 132 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& A) {
    int N = A.size();
    vector<int> res(N);
    int i = 0;
    int j = N - 1;
    int wr = N - 1;

    while (i < j && A[i] < 0) {
      if (-A[i] > A[j]) {
        res[wr--] = A[i] * A[i];
        i++;
      } else {
        res[wr--] = A[j] * A[j];
        j--;
      }
    }

    while (j >= i) {
      res[wr--] = A[j] * A[j];
      j--;
    }

    return res;
  }
};

int main() { return 0; }
