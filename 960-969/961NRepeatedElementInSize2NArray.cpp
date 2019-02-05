/*
961. N-Repeated Element in Size 2N Array
In a array A of size 2N, there are N+1 unique elements, and exactly one of these
elements is repeated N times.

Return the element repeated N times.

Example 1:

Input: [1,2,3,3]
Output: 3

Example 2:

Input: [2,1,2,5,3,2]
Output: 2

Example 3:

Input: [5,1,5,2,5,3,5,4]
Output: 5

Note:

  4 <= A.length <= 10000
  0 <= A[i] < 10000
  A.length is even
/*
  Submission Date: 2019-01-26
  Runtime: 32 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int repeatedNTimes(vector<int>& A) {
    /*
    2N elements with N+1 unique and one that repeats N times.
    That means half the elements are the repeating value so we can check
    adjacent values. If not, it must be [x, x, y, z] or [x, y, z, x] where we
    miss the check between A[0] and A[1]
    */

    for (int i = 2; i < A.size(); i++) {
      if (A[i] == A[i - 1] || A[i] == A[i - 2]) return A[i];
    }
    return A[0];
  }
};

int main() { return 0; }
