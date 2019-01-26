/*
171. Excel Sheet Column Number
Given a column title as appear in an Excel sheet, return its corresponding
column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int titleToNumber(string s) {
    return s == "" ? 0
                   : titleToNumber(s.substr(0, s.size() - 1)) * 26 +
                         (s[s.size() - 1] - 'A' + 1);
  }
};

int main() { return 0; }