/*
400. Nth Digit
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9,
10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n <
231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0,
which is part of the number 10.
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  1-9, 10-99, 100-999
  have digits i=1,2,3 respectively
  so find the smallest i which does not exceed n
  
  so 10^(i-1) + allowed is the number
  allowed is (n - (sum of previous numbers with less than i digits))/i
  
  once the number is found, find the character by seeing the remainder
  */
  int findNthDigit(int n) {
    int sum = 0;
    int i = 1;
    while (i < 10) {
      if (sum + 9 * pow(10, i - 1) * i >= n) {
        int allowed = (n - (sum + 1)) / i;
        int num = pow(10, i - 1) + allowed;
        string num_s = to_string(num);
        return num_s[(n - (sum + 1)) % i] - '0';
      }
      sum += 9 * pow(10, i - 1) * i;
      i++;
    }

    return -1;
  }
};

int main() { return 0; }