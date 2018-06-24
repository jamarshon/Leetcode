/*
507. Perfect Number
We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.
Example:
Input: 28
Output: True
Explanation: 28 = 1 + 2 + 4 + 7 + 14
Note: The input number n will not exceed 100,000,000. (1e8)
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    bool checkPerfectNumber(int num) {
        if(num < 2) return false;
        int res = 1;
        for(int i = 2; i <= sqrt(num); i++) {
            if(num % i == 0) {
                res += i;
                res += num/i;
            }
        }
        
        return res == num;
    }
};

int main() {
    return 0;
}