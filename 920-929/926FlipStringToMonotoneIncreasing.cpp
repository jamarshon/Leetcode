/*
926. Flip String to Monotone Increasing
A string of '0's and '1's is monotone increasing if it consists of some number
of '0's (possibly 0), followed by some number of '1's (also possibly 0.)

We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a
'1' to a '0'.

Return the minimum number of flips to make S monotone increasing.

Example 1:

Input: "00110"
Output: 1
Explanation: We flip the last digit to get 00111.

Example 2:

Input: "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.

Example 3:

Input: "00011000"
Output: 2
Explanation: We flip to get 00000000.

Note:

  1 <= S.length <= 20000
  S only consists of '0' and '1' characters.
/*
  Submission Date: 2019-02-21
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  for index i if we have number of ones from [0, i) ones_left
  and number of ones from [i,N) ones_right then the cost
  of partitioning at i would be number of ones on left +
  number of zeros on right
  */
  int minFlipsMonoIncr(string S) {
    int N = S.size();
    int ones_right = 0;
    for (const auto& c : S) ones_right += c == '1';

    int res = min(ones_right, N - ones_right);
    int ones_left = 0;
    for (int i = 0; i < N; i++) {
      res = min(res, ones_left + N - i - ones_right);
      if (S[i] == '1') {
        ones_left++;
        ones_right--;
      }
    }

    return res;
  }
};

int main() { return 0; }
