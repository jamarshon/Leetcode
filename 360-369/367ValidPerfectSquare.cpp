/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False
/*
    Submission Date: 2018-05-02
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPerfectSquare(int num) {
      long long low = 1;
      long long high = num;
      while(low <= high) {
        long long mid = low + (high-low)/2;
        if(mid*mid == num) {
          return true;
        } else if(mid*mid < num) {
          low = mid + 1;
        } else {
          high = mid -1;
        }
      }
      return false;
    }
};

int main() {
    return 0;
}