/*
441. Arranging Coins
You have a total of n coins that you want to form in a staircase shape, where
every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed
integer.

Example 1:

n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.
Example 2:

n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.
/*
    Submission Date: 2018-06-09
    Runtime: 33 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  sum of 0 to x = x(x+1)/2
  x(x+1)/2 = n
  x^2 + x - 2n = 0

  quadratic formula: x = (-1 + sqrt(8n + 1))/2
  */
  int arrangeCoins(int n) { return (-1 + sqrt(8LL * n + 1)) / 2; }
};

int main() { return 0; }