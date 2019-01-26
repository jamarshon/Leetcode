/*
922. Sort Array By Parity II
Given an array A of non-negative integers, half of the integers in A are odd,
and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is
even, i is even.

You may return any answer array that satisfies this condition.

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

Note:

  2 <= A.length <= 20000
  A.length % 2 == 0
  0 <= A[i] <= 1000
/*
  Submission Date: 2019-01-26
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortArrayByParityII(vector<int>& A) {
    int even_ind = 0;
    int odd_ind = 1;
    while (even_ind < A.size() && odd_ind < A.size()) {
      while (even_ind < A.size() && A[even_ind] % 2 == 0) {
        even_ind += 2;
      }

      while (odd_ind < A.size() && A[odd_ind] % 2 == 1) {
        odd_ind += 2;
      }

      int cnt = (even_ind < A.size()) + (odd_ind < A.size());

      if (cnt == 0) break;
      assert(cnt != 1);
      swap(A[even_ind], A[odd_ind]);
      even_ind += 2;
      odd_ind += 2;
    }

    return A;
  }
};

int main() { return 0; }
