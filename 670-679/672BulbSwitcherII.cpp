/*
672. Bulb Switcher II
There is a room with n lights which are turned on initially and 4 buttons on the
wall. After performing exactly m unknown operations towards buttons, you need to
return how many different kinds of status of the n lights could be.



Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4
buttons are given below:


Flip all the lights.
Flip lights with even numbers.
Flip lights with odd numbers.
Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...




Example 1:
Input: n = 1, m = 1.
Output: 2
Explanation: Status can be: [on], [off]




Example 2:
Input: n = 2, m = 1.
Output: 3
Explanation: Status can be: [on, off], [off, on], [off, off]




Example 3:
Input: n = 3, m = 1.
Output: 4
Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off],
[off, on, on].



Note:
n and m both fit in range [0, 1000].

/*
    Submission Date: 2018-07-07
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  8 states:
  All_on, 1, 2, 3, 4, 1+4, 2+4, 3+4
  
  m == 0: All_on (no possible moves) => 1
  m > 0:
      n == 1: All_on (3 apply odd which doesnt affect anything) or 1 => 2
      n == 2:
          m == 1: 1, 2, 3 => 3
          m >= 2: All_on (1 1), 1 (2 3), 2 (1 3), 3 (1 2) => 4
      n >= 3:
          m == 1: 1, 2, 3, 4 => 4
          m == 2: All_on (1 1), 1 (2 3), 2 (1 3), 3 (1 2), 1+4, 2+4, 3+4 => 7
          m > 2: All_on (1 2 3), 1 (1 1 1), 2 (1 1 2), 3 (1 1 2), 4 (1 1 4),
                  1+4 (2 3 4), 2+4 (1 3 4), 3+4 (1 2 4) => 8
      
  */
  int flipLights(int n, int m) {
    if (m == 0) return 1;
    if (n == 1) return 2;
    if (n == 2) {
      if (m == 1) return 3;
      return 4;
    } else {
      if (m == 1) return 4;
      if (m == 2) return 7;
      return 8;
    }
  }
};

int main() { return 0; }