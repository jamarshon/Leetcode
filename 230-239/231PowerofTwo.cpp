/*
231. Power of Two
Given an integer, write a function to determine if it is a power of two.

/*
    Submission Date: 2017-07-30
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 ? (n & (n - 1)) == 0 : false;
    }
};

int main() {
    return 0;
}