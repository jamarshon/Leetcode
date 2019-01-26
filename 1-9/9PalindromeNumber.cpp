/*
9. Palindrome Number
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of
using extra space.

You could also try reversing an integer. However, if you have solved the problem
"Reverse Integer", you know that the reversed integer might overflow. How would
you handle such case?

There is a more generic way of solving this problem.

/*
    Submission Date: 2016-12-06
    Runtime: 95 ms
    Difficulty: EASY
*/

using namespace std;
#include <cmath>
#include <iostream>

class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0) {
      return false;
    }
    int i = floor(log10(x));
    while (i > 0) {
      int leftDigit = floor(x / pow(10, i));
      int rightDigit = x % 10;
      if (leftDigit != rightDigit) {
        return false;
      }
      x %= (int)pow(10, i);
      x /= 10;
      i -= 2;
    }
    return true;
  }
};

int main() {
  Solution s;
  int input = -2147483648;
  cout << s.isPalindrome(input) << endl;
  return 0;
}