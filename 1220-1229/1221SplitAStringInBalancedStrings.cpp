/*
1221. Split a String in Balanced Strings
Balanced strings are those who have equal quantity of 'L' and 'R' characters.

Given a balanced string s split it in the maximum amount of balanced strings.

Return the maximum amount of splitted balanced strings.

Example 1:

Input: s = "RLRRLLRLRL"
Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring
contains same number of 'L' and 'R'.

Example 2:

Input: s = "RLLLLRRRLR"
Output: 3
Explanation: s can be split into "RL", "LLLRRR", "LR", each substring contains
same number of 'L' and 'R'.

Example 3:

Input: s = "LLLLRRRR"
Output: 1
Explanation: s can be split into "LLLLRRRR".

Constraints:

  1 <= s.length <= 1000
  s[i] = 'L' or 'R'
/*
  Submission Date: 2019-10-14
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int balancedStringSplit(string s) {
    // greedily get substrings where as soon as we hit
    // 0 again then use it and start the next substring
    // as we need to use all characters of s
    int res = 0;
    int cnt = 0;
    for (const auto& e : s) {
      cnt += e == 'L';
      cnt -= e == 'R';
      res += cnt == 0;
    }
    return res;
  }
};

int main() { return 0; }
