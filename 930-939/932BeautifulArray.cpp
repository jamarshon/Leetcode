/*
932. Beautiful Array
For some fixed N, an array A is beautiful if it is a permutation of the integers
1, 2, ..., N, such that:

For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].

Given N, return any beautiful array A.  (It is guaranteed that one exists.)

Example 1:

Input: 4
Output: [2,1,4,3]

Example 2:

Input: 5
Output: [3,1,2,5,4]

Note:

  1 <= N <= 1000
/*
  Submission Date: 2019-02-19
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  generate all the odd numbers followed by the even
  this partition helps because if even_a + even_b = x and odd_a + odd_b = y
  then if x is 2*odd number or y is 2*even number, it will never violate
  the beautiful condition due to the partition

  even_a + odd_a is always odd so concatenate an array of odd numbers and
  even numbers is still beautiful

  given a beautiful array A of size N, the operations are supported
  1) remove element
  -removing element will never violate condition as it relaxes the criteria
  2) multiplication
  since beautiful A[k]*2 != A[i] + A[j], if all elements multiplied by x
  # (A[k]*x)*2
  ## (A[i]*x) + (A[j]*x)
  divide # and ## by x and get A[k]*2 and A[i] + A[j] which are not equal so
  still beautiful

  3) addition
  add x to each element
  # (A[k]+x)*2 = A[k]*2 + 2x
  ## (A[i]+x) + (A[j]+x) = A[i] + A[j] + 2x
  subtract 2x from # and ## and get A[k]*2 and A[i] + A[j] which are not equal
  so still beautiful

  so start with the base case of A = {1} for size 1 and build it recursively
  to size N by multiply, add and remove elements that are too large

  odd = A[i]*2-1 for all i (generates all odd from 1 to 2*N-1)
  even = A[i]*2 for all i (generates all even from 0 to 2*N)
  new_A = concat odd and even (size of 2*N)
  */
  vector<int> beautifulArray(int N) {
    vector<int> res{1};
    res.reserve(N);
    while (res.size() < N) {
      vector<int> tmp;
      for (const auto& i : res)
        if (2 * i - 1 <= N) tmp.push_back(2 * i - 1);
      for (const auto& i : res)
        if (2 * i <= N) tmp.push_back(2 * i);
      res = tmp;
    }
    return res;
  }
};

int main() { return 0; }
