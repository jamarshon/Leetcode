/*
1137. N-th Tribonacci Number
The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:

Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:

Input: n = 25
Output: 1389537

Constraints:

  0 <= n <= 37
  The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 -
1.
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int tribonacci(int n) {
    if (n <= 1) return n;
    int T0 = 0, T1 = 1, T2 = 1;
    for (int i = 2; i < n; i++) {
      int T3 = T0 + T1 + T2;
      T0 = T1;
      T1 = T2;
      T2 = T3;
    }

    return T2;
  }
};

int main() { return 0; }
