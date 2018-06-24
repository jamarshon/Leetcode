/*
479. Largest Palindrome Product
Find the largest palindrome made from the product of two n-digit numbers.

Since the result could be very large, you should return the largest palindrome mod 1337.

Example:

Input: 2

Output: 987

Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

Note:

The range of n is [1,8].
/*
    Submission Date: 2018-06-24
    Runtime: 713 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    typedef long long ll;
    int largestPalindrome(int n) {
        if(n == 1) return 9;
        
        ll x = pow(10, n) - 1LL; // 99
        ll max_x = x*x;
        
        ll lower = pow(10, n-1); // 10
        ll upper = x; // 99
        while(x) {
            // take a string of n digits and reverse + concat to get string of 2n digits
            string s = to_string(x);
            string rev = s;
            reverse(rev.begin(), rev.end());
            ll num = stoll(s + rev);
            if(num > max_x) { x--; continue; }
            
            // use upper instead of sqrt(num) as upper is larger
            for(ll fact = upper; fact > lower; fact--) {
                /* fact*fact >= num ensures that fact is greater than the second factor and
                    we do not redo calculation on the lower factors e.g num = 20 fact = 5
                    5*5 >= 20 (takes in 5 and 4)
                    fact = 4
                    4*4 < 20 (does not reconsider lower factors as they have already been checked)
                    
                    fact*fact >= num
                    fact >= num/fact (upper > num/fact)
                */
                if(num/fact < lower || fact*fact < num) break;
                
                if(num % fact == 0) {
                    return num % 1337;
                }
            }
            x--;
        }
    }
};

int main() {
    return 0;
}