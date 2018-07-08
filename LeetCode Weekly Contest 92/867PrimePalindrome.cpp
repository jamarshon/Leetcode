/*
867. Prime Palindrome
Find the smallest prime palindrome greater than or equal to N.

Recall that a number is prime if it's only divisors are 1 and itself, and it is 

For example, 2,3,5,7,11 and 13 are primes.

Recall that a number is a palindrome if it reads the same from left to right as 

For example, 12321 is a palindrome.

 


Example 1:

Input: 6
Output: 7



Example 2:

Input: 8
Output: 11



Example 3:

Input: 13
Output: 101




 

Note:


    1 <= N <= 10^8
    The answer is guaranteed to exist and be less than 2 * 10^8.
/*
    Submission Date: 2018-07-08
    Runtime: 172 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isprime(int x) {
        if(x < 2) return false;
        for(int i = 2; i <= sqrt(x); i++) {
            if(x % i == 0) return false;
        }
        return true;
    }
    
    typedef long long ll;
    /*
    generate increasing palindrome as odd or even by taking a number, reversing it and appending
    to self. find the first palindrome that is >= N and prime then break compare the even and odd
    result to see which is smaller and return that.
    */
    int primePalindrome(int N) {
        int res = INT_MAX;
       // odd
        for(int i = 0; i < INT_MAX; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string pal = s + rev.substr(1);
            
            ll pal_long = stoll(pal);
            if(pal_long >= INT_MAX) break;
            
            int pal_int = pal_long;
            if(pal_int >= N && isprime(pal_int)) {
                res = pal_int;
                break;
            }
        }
        // even
        for(int i = 0; i < INT_MAX; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string pal = s + rev;
            
            ll pal_long = stoll(pal);
            
            if(pal_long >= INT_MAX) break;
            int pal_int = pal_long;

            if(pal_int >= N && isprime(pal_int)) {
                res = min(pal_int, res);
                break;
            }
        }
        return res;
    }
};

int main() {
    return 0;
}