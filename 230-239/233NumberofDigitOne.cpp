/*
233. Number of Digit One
Given an integer n, count the total number of digit 1 
appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 
1, 10, 11, 12, 13.

/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution2 {
public:
    // low is the form of 10^n where 10^n <= high < 10^(n+1) meaning low and high have same number of digits
    int countDigitOne(int low, int high) {
        while(low > high) low /= 10; // 100 and 002 we need to make them the same so 10 and 2

        if(low == 0) return 0;
        if(low == 1) return 1;

        int res = 0;
        int diff = min(high-low+1, low); // 461-100 -> 100 or 120-100 -> 20

        res += diff;

        int high_first_digit = high/low;
        
        // high_first_digit = 461/100 = 4 
        // we consider 0-99 100-199 200-299, 300-399, 400-461
        // there are high_first_digit - 1 full intervals countDigitOne(10, 99)
        // there is one incomplete interval countDigitOne(10,61)
        int full_interval = countDigitOne(low/10, low-1);
        for(int i = 0; i < high_first_digit; i++) { 
            res += full_interval;
        }

        res += countDigitOne(low/10, high % low);
        return res;
    }

    int countDigitOne(int x) {
        if(x < 0) return 0;

        int n = floor(log10(x));
        int low = round(pow(10, n));
        return countDigitOne(low, x);
    } 
};

class Solution {
public:
    int countDigitOne(int n) {
        typedef long long ll;
        ll res = 0;

        /*
            Given a number xxxxyzzz where indices are 76543210 and k=3 which is where y appears
            we want to count how many times y is one. 
            xxxx would be numbers 0000 to xxxx so they appear xxxx - 0000 + 1 times or (xxxx + 1)
            if y >= 2 then it means for the (xxxx+1) times, there is 10^k occurences that y is 1
                so it is just (xxxx+1)*10^k
            if y == 1 then for the (xxxx+1) times, there is (xxxx+1)-1 full intervals of 10^k that has 
                y equal to 1 and there is one partial interval for the numbers zzz which occur zzz - 000 + 1
                times or (zzz+1) so it is xxxx*10^k + zzz+1
            if y == 0 then the (xxxx+1) complete intervals do not include the last one as y is not greater than
                one so it is xxxx*10^k

            e.g (y >= 2) 4(3)zz there is x + 1 = 5 times x(1)zz can occur 0(1)zz, 1(1)zz, 2(1)zz, 3(1)zz, 4(1)zz
                y >= 2 meaning the last interval 4(1)zz is considered complete (4100 to 4199) is included by 4(3)zz
                so it is 5*10^2

                (y == 1) 4(1)zz the last interval 4(1)zz is not considered complete but for 0(1)zz, 1(1)zz, 2(1)zz, 
                3(1)zz there are 4*10^2 ones. The partial interval of 4(1)zz has zz + 1 number of ones as 4(1)00
                to 4(1)zz include zz + 1 elements for a total of 4*10^2 + (zz + 1)
                
                (y == 0) 4(0)zz the last interval 4(1)zz is not complete so there is 4*10^2 for 0(1)zz, 1(1)zz, 2(1)zz, 
                3(1)zz and the zz + 1 elements do not count towards the total as y is not one so just 4*10^2
        */
        for(ll i = 1; i <= n; i *= 10) { // i is 10^k
            // denote xxxxy as temp, xxxx as prefix, y as digit, and zz as suffix
            ll temp = n/i;
            ll prefix = temp / 10;
            ll digit = temp % 10;
            ll suffix = n % i;

            if(digit >= 2) {
                res += (prefix + 1)*i; // (xxxx+1)*10^k
            } else if(digit == 1) {
                res += (prefix)*i + (suffix + 1); // xxxx*10^k + zzz+1
            } else { // digit == 0
                res += (prefix)*i; // xxxx*10^k
            }
        }
        return res;
        
    }
};

int main() {
    Solution s;
    cout << s.countDigitOne(13) << endl; // 6
    cout << s.countDigitOne(100) << endl; // 21
    cout << s.countDigitOne(101) << endl; // 23
    cout << s.countDigitOne(102) << endl; // 24
    cout << s.countDigitOne(1410065408) << endl; // 1737167499
    return 0;
}