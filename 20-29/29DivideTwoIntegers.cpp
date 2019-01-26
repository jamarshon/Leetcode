/*
29. Divide Two Integers
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

/*
    Submission Date: 2017-06-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <iostream>

using namespace std;

class Solution {
 public:
  int divide(int dividend, int divisor) {
    if (dividend == 0) return 0;
    if (divisor == 0) return INT_MAX;
    if (dividend == INT_MIN && divisor == -1)
      return INT_MAX;  // INT_MIN/-1 overflow

    int sign = ((divisor < 0) ^ (dividend < 0)) ? -1 : 1;

    // make both negative as range is larger
    if (divisor > 0) divisor = -divisor;
    if (dividend > 0) dividend = -dividend;
    if (divisor < dividend) return 0;

    int count = 0;
    for (int i = 31; i >= 0; i--) {
      // maintain (divisor << i) >= INT_MIN
      if (divisor >= INT_MIN >> i) {
        int divisor_shift = divisor << i;
        // check if (divisor << (i+1)) < dividend < (divisor << i)  then i can
        // be used in the result
        if (divisor_shift >= dividend) {
          count += 1 << i;
          dividend -= divisor_shift;
          if (dividend == 0) {
            break;
          }
        }
      }
    }

    return sign * count;
  }
};

int main() {
  Solution s;
  return 0;
}