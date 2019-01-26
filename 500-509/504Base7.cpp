/*
504. Base 7
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].
/*
    Submission Date: 2018-06-08
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  string convertToBase7(int num) {
    if (num == 0) return "0";

    string sgn = num < 0 ? "-" : "";
    num = abs(num);

    string res = "";
    while (num) {
      res.push_back((num % 7) + '0');
      num /= 7;
    }

    reverse(res.begin(), res.end());
    return sgn + res;
  }
};

int main() { return 0; }