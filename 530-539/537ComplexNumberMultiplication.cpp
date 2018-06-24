/*
537. Complex Number Multiplication
Given two strings representing two complex numbers.

You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of 
[-100, 100]. And the output should be also in this form.
/*
    Submission Date: 2018-06-24
    Runtime: 4 ms
    Difficulty: MEDIUM 
*/
#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
    pair<int,int> Extract(string S) {
        int plus_S_ind = S.find("+");
        string a = S.substr(0, plus_S_ind);
        string b = S.substr(plus_S_ind + 1, S.size() - (plus_S_ind + 1) - 1);
        return {stoi(a), stoi(b)};
    }
    string complexNumberMultiply(string S1, string S2) {
        int a, b, c, d;
        tie(a,b) = Extract(S1);
        tie(c,d) = Extract(S2);
        
        int real = a*c - b*d;
        int imag = b*c + d*a;
        
        string res = to_string(real) + "+" + to_string(imag) + "i";
        return res;
        
    }
};

int main() {
    return 0;
}