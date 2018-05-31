/*
357. Count Numbers with Unique Digits
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])
/*
    Submission Date: 2018-05-30
    Runtime: 2 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        let dp[n] denote a number with n digits (no leading zeros) that is completely unique
        dp[0] = 1           {0}
        dp[1] = 9           {1, 2, 3, 4, 5, 6, 8, 9}
        dp[2] = 9*dp[1]     for each number in dp[1], there are 9 numbers to choose from that are not in dp[1].
                            e.g. for dp[1] element 1, there is {10, 12, 13, 14, 15, 16, 17, 18, 19}
        dp[3] = 8*dp[2]     for each number in dp[2], there are 8 numbers to choose from that are not in dp[2]
                            e.g. for dp[2] element 12, there is {120, 123, 124, 125, 126, 127, 128, 129}
        ...
        dp[i] = min(9, 9 - i + 2)*dp[i-1]
        
        the result of length n is just the sum of dp[i] from [0, n]
    */
    int countNumbersWithUniqueDigits(int n) {
        int prev = 1;
        int res = 1;
        for(int i = 1; i <= min(10, n); i++) {
            prev *= min(9, 9 - i + 2);
            res += prev;
        }

        return res;
    }
};

int main() {
    return 0;
}