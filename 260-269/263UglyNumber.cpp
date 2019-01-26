/*
263. Ugly Number
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
For example, 6, 8 are ugly while 14 is not ugly since it includes another prime
factor 7.

Note that 1 is typically treated as an ugly number.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  bool isUgly2(int num) {
    if (num <= 0) return false;
    if (num == 1) return true;

    if (num % 2 == 0) return isUgly(num / 2);
    if (num % 3 == 0) return isUgly(num / 3);
    if (num % 5 == 0) return isUgly(num / 5);

    return false;
  }

  bool isUgly(int num) {
    if (num <= 0) return false;

    int primes[3] = {2, 3, 5};
    for (int i = 0; i < 3; i++) {
      while (num % primes[i] == 0) {
        num /= primes[i];
      }
    }

    return num == 1;
  }
};

int main() { return 0; }