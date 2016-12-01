/*
8. String to Integer (atoi)
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, 
please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). 
You are responsible to gather all the input requirements up front.

/*
    Submission Date: 2016-11-30
    Runtime: 9 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <limits.h>

class Solution {
public:
    int myAtoi(string str) {
        int len = str.length();
        int result = 0;
        bool seenNumeric = false;
        bool seenNonNumeric = false;
        bool negative = false;
        for(int i = 0; i < len; i++) {
            if(str[i] == ' ') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
            } else if(str[i] == '+') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
                seenNonNumeric = true;
                negative = false;
            } else if(str[i] == '-') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
                seenNonNumeric = true;
                negative = true;
            } else{
                int possibleDigit = str[i] - '0';
                if(possibleDigit < 0 || possibleDigit > 9){ // invalid character
                    return result;
                } else {
                    if(negative) {
                        if(result < INT_MIN / 10) return INT_MIN;
                        result *= 10;
                        if(result < INT_MIN + possibleDigit) return INT_MIN;
                        result -= possibleDigit;
                    } else {
                        if(result > INT_MAX / 10) return INT_MAX;
                        result *= 10;
                        if(result > INT_MAX - possibleDigit) return INT_MAX;
                        result += possibleDigit;
                    }
                    seenNumeric = true;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    // cout << s.reverse(-2147483412) << endl;
    cout << s.myAtoi("-2147483647") << endl;
    // cout << abs(INT_MIN + 1) << endl;
    return 0;
}
