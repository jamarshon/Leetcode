/*
172. Factorial Trailing Zeroes
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        return n == 0 ? 0 : n/5 + trailingZeroes(n/5);
    }
};

int main() {
    return 0;
}