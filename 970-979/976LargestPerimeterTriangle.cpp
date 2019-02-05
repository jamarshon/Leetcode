/*
976. Largest Perimeter Triangle
Given an array A of positive lengths, return the largest perimeter of a triangle
with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

Example 1:

Input: [2,1,2]
Output: 5

Example 2:

Input: [1,2,1]
Output: 0

Example 3:

Input: [3,2,3,4]
Output: 10

Example 4:

Input: [3,6,2,3]
Output: 8

Note:

  3 <= A.length <= 10000
  1 <= A[i] <= 10^6
/*
  Submission Date: 2019-02-05
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestPerimeter(vector<int>& A) {
    /*
    triangle inequality formula: sum of two sides greater than the other
    a + b > c
    a + c > b
    b + c > a */
    sort(A.begin(), A.end());
    for (int i = A.size() - 1; i >= 2; i--) {
      // don't need to check A[i] + A[i-1] > A[i-2] and A[i] + A[i-2] > A[i-i]
      // because A[i] >= A[i-2] and A[i] >= A[i-1] and A only consists of
      // numbers > 1
      if (A[i - 1] + A[i - 2] > A[i]) return A[i] + A[i - 1] + A[i - 2];
    }

    return 0;
  }
};

int main() { return 0; }
