/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?

Note: Given n will be a positive integer.

/*
    Submission Date: 2017-06-18
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int climbStairs(int n) {
    if (n == 0) return 0;

    int two_behind = 1;
    int one_behind = 2;

    while (--n) {
      int new_val = two_behind + one_behind;
      two_behind = one_behind;
      one_behind = new_val;
    }

    return two_behind;
  }
};

int main() { return 0; }