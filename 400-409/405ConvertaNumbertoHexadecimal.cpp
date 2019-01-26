/*
405. Convert a Number to Hexadecimal
Given an integer, write an algorithm to convert it to hexadecimal. For negative
integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero,
it is represented by a single zero character '0'; otherwise, the first character
in the hexadecimal string will not be the zero character. The given number is
guaranteed to fit within the range of a 32-bit signed integer. You must not use
any method provided by the library which converts/formats the number to hex
directly. Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"
/*
    Submission Date: 2018-05-26
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
      % 16 gets the last 4 bits. if it is negative then add 16 ie -1 -> 15.
      >> 4 shifts by 4 bits through sign extending so it is not equivalent to /
     16 since the last 4 bits are added first the string must be reversed. the
     last non zero character is the first character in the string so trim it.
  */
  char helper(int x) {
    if (x < 0) x += 16;
    return (x % 10) + (x < 10 ? '0' : 'a');
  }
  string toHex(int num) {
    string res = "";
    int last_non_zero = 0;

    for (int i = 0; i < 8; i++) {
      res.push_back(helper(num % 16));
      num >>= 4;
      if (res.back() != '0') last_non_zero = i;
    }

    res = res.substr(0, last_non_zero + 1);
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }