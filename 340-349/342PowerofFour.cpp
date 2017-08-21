/*
342. Power of Four
Given an integer (signed 32 bits), write a function to check 
whether it is a power of 4.

Example:
Given num = 16, return true. Given num = 5, return false.

Follow up: Could you solve it without loops/recursion?
/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfFour(int x) {
        // (x & (x-1)) == 0 checks for power of two as it would 
        // series of zeros with only one 1. so x-1 will AND with nothing
        // leaving zero
        // geometric series 1 + 4 + 16 + 64 + 256 -> a = 1, r = 4, n = 5
        // sum{i = 0 to n-1}(a*r^i = a*(1-r^n/(1-r)
        // so let x = sum{i = 0 to n-1}((1-4^n)/(1-4))
        // x = (4^n - 1)/3
        // 3*x = 4^n - 1 <- thus 4^n - 1 must be a multiple of 3
        return x > 0 && (x & (x-1)) == 0 && (x-1) % 3 == 0;
    }
};

int main() {
    Solution s;
    return 0;
}