/*
201. Bitwise AND of Numbers Range
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of
all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.

/*
    Submission Date: 2017-07-25
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  int rangeBitwiseAnd(int m, int n) {
    int res = 0;
    for (int i = 30; i >= 0; i--) {
      int shift = 1 << i;
      if ((shift & m) == (shift & n)) {
        res |= shift & m;
      } else {
        break;
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  cout << s.rangeBitwiseAnd(5, 7) << endl;
  cout << s.rangeBitwiseAnd(5, 5) << endl;
  cout << s.rangeBitwiseAnd(INT_MAX, INT_MAX - 1) << endl;
  cout << s.rangeBitwiseAnd(0, 0) << endl;
  return 0;
}