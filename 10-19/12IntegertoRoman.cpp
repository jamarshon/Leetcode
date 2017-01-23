/*
12. Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

/*
    Submission Date: 2017-01-23
    Runtime: 138 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>

struct Denomination {
    int value;
    string symbol;
};

class Solution {
public:
    vector<Denomination> VEC = {
        Denomination{1000, "M"},
        Denomination{500, "D"},
        Denomination{100, "C"},
        Denomination{50, "L"},
        Denomination{10, "X"},
        Denomination{5, "V"},
        Denomination{1, "I"}
    };

    void checkAndAddDenomination(int i, int offset, int len, Denomination denomination, int& num, string& result) {
        if(i + offset < len) {
            Denomination smallerDenomination = VEC[i + offset];
            int difference = denomination.value - smallerDenomination.value;
            if(num >= difference && difference > smallerDenomination.value) {
              num -= difference;
              result += smallerDenomination.symbol + denomination.symbol;
            }
        }
    }
    string intToRoman(int num) {
        int difference;
        string result = "";
        Denomination denomination, smallerDenomination;
        int i = 0, len = VEC.size();

        while(num) {
            denomination = VEC[i];
            if(num >= denomination.value) {
                num -= denomination.value;
                result += denomination.symbol;
            } else {
                checkAndAddDenomination(i, 1, len, denomination, num, result);
                checkAndAddDenomination(i, 2, len, denomination, num, result);
                i++;
            }
        }

        return result;
    }
};

int main() {
    return 0;
}