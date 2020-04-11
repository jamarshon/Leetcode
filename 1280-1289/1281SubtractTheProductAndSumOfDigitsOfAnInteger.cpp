/*
1281. Subtract the Product and Sum of Digits of an Integer
Given an integer number n, return the difference between the product of its
digits and the sum of its digits.
 
Example 1:

Input: n = 234
Output: 15
Explanation:
Product of digits = 2 * 3 * 4 = 24
Sum of digits = 2 + 3 + 4 = 9
Result = 24 - 9 = 15

Example 2:

Input: n = 4421
Output: 21
Explanation:
Product of digits = 4 * 4 * 2 * 1 = 32
Sum of digits = 4 + 4 + 2 + 1 = 11
Result = 32 - 11 = 21

Constraints:

  1 <= n <= 10^5
/*
  Submission Date: 2020-04-10
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int subtractProductAndSum(int n) {
    int product = 1;
    int sum = 0;
    while (n) {
      int x = n % 10;
      n /= 10;
      product *= x;
      sum += x;
    }
    return product - sum;
  }
};

int main() { return 0; }
