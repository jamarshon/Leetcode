/*
693. Binary Number with Alternating Bits
Given a positive integer, check whether it has alternating bits: namely, if two
adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
/*
    Submission Date: 2018-06-02
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution2 {
 public:
  // 0x5555555555555555 checks if any of the even bits are set as 5 is 0101
  bool IsPowerOfFour(long long x) {
    return (x & ~(x - 1)) == x && (x & 0x5555555555555555);
  }

  // 0xaaaaaaaaaaaaaaaa checks if any of the odd bits are set as a is 1010
  bool IsPowerOfFourTimesTwo(long long x) {
    return (x & ~(x - 1)) == x && (x & 0xaaaaaaaaaaaaaaaa);
  }
  /*
      sum of geometric series is (1-r^n)/(1-r) so sum 2^(2i) and sum 2^(2i+1)
     becomes sum(2^(2i)) = sum(4^i) = (1-4^n)/(1-4) = (4^n-1)/3 sum(2^(2i+1)) =
     2*sum(4^i) = 2*(1-4^n)/(1-4) = (2*4^n-2)/3 so check if the number x =
     (4^n-1)/3 or x = (2*4^n-2)/3 works
  */
  bool hasAlternatingBits(long long n) {
    return IsPowerOfFour(3 * n + 1) || IsPowerOfFourTimesTwo(n * 3 + 2);
  }
};

class Solution {
 public:
  /*
      shift number by two bits and xor it with itself. only the leading one
     should remeain first operation gives one if x[i] != x[i+2] so if they are
     all zero it means x[0] = x[2] = x[4] = ... x[2*n] and x[1] = x[3] = x[5] =
     ... x[2*n+1]

      x[0] and x[1] can give 4 combinations 00, 01, 10, 11 so checking that
     there is just a leading one ensures there is only one 1 and one 0 that
     propogate correctly to the rest of the numbers.
  */
  bool hasAlternatingBits(int n) {
    int x = ((n >> 2) ^ n);
    return (x & ~(x - 1)) == x;
  }
};

int main() { return 0; }