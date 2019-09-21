/*
1013. Partition Array Into Three Parts With Equal Sum
Given an array A of integers, return true if and only if we can partition the
array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i+1 < j with (A[0] +
A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... +
A[A.length - 1])

Example 1:

Input: [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

Example 2:

Input: [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false

Example 3:

Input: [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

Note:

  3 <= A.length <= 50000
  -10000 <= A[i] <= 10000
/*
  Submission Date: 2019-09-18
  Runtime: 68 ms
  Difficulty: EASY
*/
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canThreePartsEqualSum(vector<int>& A) {
    /*
    get the total sum of the array, if its not divisible
    by three return false.
    iterate and increment until reaching the total sum / 3 then
    increase the number of parts by one and reset the sum
    if there are three parts then return true
    */
    int total_sum = accumulate(A.begin(), A.end(), 0);
    if (total_sum % 3 != 0) return false;
    int part_sum = total_sum / 3;
    int sum = 0;
    int num_parts = 0;
    for (const auto& e : A) {
      sum += e;
      if (sum == part_sum) {
        sum = 0;
        num_parts++;
      }
    }
    return num_parts == 3;
  }
};

int main() { return 0; }
