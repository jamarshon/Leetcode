/*
326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?
/*
    Submission Date: 2018-05-02
    Runtime: 80 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isPowerOfThree(int n) {
    // 1162261467 largest power of 3 that can be represented by int and all it's
    // factors are powers of 3. a = nq + r where n < r means a % n = r 3^19 % y
    // => 3^19 = n*y + r if y == 3^x, then this only true if r == 0 and n ==
    // 3^(19-x)
    return n > 0 && 1162261467 % n == 0;
  }
};

int main() { return 0; }