/*
12. Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

/*
    Submission Date: 2017-01-23
    Runtime: 59 ms
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
                if(i + 1 < len) {
                    smallerDenomination = VEC[i + 1];
                    difference = denomination.value - smallerDenomination.value;
                    if(num >= difference && difference > smallerDenomination.value) {
                      num -= difference;
                      result += smallerDenomination.symbol + denomination.symbol;
                    }
                }

                if(i + 2 < len) {
                    smallerDenomination = VEC[i + 2];
                    difference = denomination.value - smallerDenomination.value;
                    if(num >= difference && difference > smallerDenomination.value) {
                      num -= difference;
                      result += smallerDenomination.symbol + denomination.symbol;
                    }
                }
                i++;
            }
        }

        return result;
    }
};

int main() {
    return 0;
}