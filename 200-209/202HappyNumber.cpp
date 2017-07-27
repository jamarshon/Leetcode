/*
202. Happy Number
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the 
number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), 
or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
    unordered_set<int> seen;
public:
    bool isHappy(int n) {
        if(n == 1) return true;
        if(n == 0 || seen.count(n)) return false;
        seen.insert(n);
        int sum = 0;
        while(n) {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        return isHappy(sum);
    }
};

int main() {
    return 0;
}