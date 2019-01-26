/*
168. Excel Sheet Column Title
Given a positive integer, return its corresponding column title as appear in an
Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB

/*
    Submission Date: 2017-07-26
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  string convertToTitle(int n) {
    return n == 0
               ? ""
               : convertToTitle((n - 1) / 26) + string(1, ((n - 1) % 26) + 'A');
  }
};

int main() {
  Solution s;
  return 0;
}