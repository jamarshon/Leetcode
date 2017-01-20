/*
67. Add Binary
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
*/

using namespace std;
#include <unordered_map>
#include <string>

class Solution {
public:
    unordered_map<char, int> MAP = {
       { '0', 0},
        {'1', 1}
    };
    string addBinary(string a, string b) {
        string result = "";
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        int aCurrent, bCurrent;
        
        while(i >= 0 && j >= 0) {
            aCurrent = MAP[a[i]];
            bCurrent = MAP[b[j]];
            result = to_string(aCurrent ^ bCurrent ^ carry) + result;
            carry = aCurrent & bCurrent | aCurrent & carry | bCurrent & carry;
            i--;
            j--;
        }

        while(i >= 0) {
            aCurrent = MAP[a[i]];
            result = to_string(aCurrent ^ carry) + result;
            carry &= aCurrent;
            i--;
        }

        while(j >= 0) {
            bCurrent = MAP[b[j]];
            result = to_string(bCurrent ^ carry) + result;
            carry &= bCurrent;
            j--;
        }

        if(carry > 0) result = "1" + result;
        return result;
    }
};

int main() {
	return 0;
}