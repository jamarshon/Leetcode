/*
633. Sum of Square Numbers
Given a non-negative integer c, your task is to decide whether there're two
integers a and b such that a2 + b2 = c.

Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False
/*
    Submission Date: 2018-05-30
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

/*
    use newton's method to find roots where xn_plus_1 = (xn + x/xn)/2
*/
class Solution2 {
  bool is_square(int x) {
    if (x < 0) return -1;
    int xn = 0;
    int xn_plus_1 = x;
    while (abs(xn - xn_plus_1) > 1) {
      xn = xn_plus_1;
      xn_plus_1 = (xn + x / xn) / 2;
    }

    return xn * xn == x || xn_plus_1 * xn_plus_1 == x;
  }

 public:
  bool judgeSquareSum(int c) {
    for (int i = 0; i <= sqrt(c); i++) {
      if (is_square(c - i * i)) return true;
    }
    return false;
  }
};

class Solution {
 public:
  /*
      two pointers. if a^2 + b^2 > c then increasing a will not help so decrease
     b if it is < c then decreasing b will not help so increase a
  */
  bool judgeSquareSum(int c) {
    int low = 0;
    int high = sqrt(c);
    while (low <= high) {
      int x = low * low + high * high;
      if (x == c) return true;
      if (x < c) {
        low++;
      } else {
        high--;
      }
    }
    return false;
  }
};

int main() { return 0; }