/*
7. Reverse Integer
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

/*
    Submission Date: 2016-11-30
    Runtime: 16 ms
    Difficulty: EASY
*/

using namespace std;
#include <limits.h>
#include <iostream>

class Solution {
 public:
  int reverse(int x) {
    if (x == INT_MIN) {
      return 0;
    }
    int sign = x >= 0 ? 1 : -1;
    int absX = abs(x);
    int result = 0;
    int maxSafeResult = INT_MAX / 10;
    while (absX != 0) {
      result = result * 10 + absX % 10;
      absX /= 10;
      cout << result << endl;
      if (result > maxSafeResult && absX != 0) {
        return 0;
      }
    }

    return result * sign;
  }
};

int main() {
  Solution s;
  // cout << s.reverse(-2147483412) << endl;
  cout << s.reverse(-2147483648) << endl;
  // cout << abs(INT_MIN + 1) << endl;
  return 0;
}
