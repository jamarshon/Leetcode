/*
13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

/*
    Submission Date: 2017-01-25
    Runtime: 172 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>

struct Denomination {
  int value;
  string symbol;
  int numChar;
};

class Solution {
 public:
  unordered_map<char, vector<Denomination>> CHAR_TO_DENOMINATIONS_MAP = {
      {'M', {Denomination{1000, "M", 1}}},
      {'D', {Denomination{500, "D", 1}}},
      {'C',
       {Denomination{900, "CM", 2}, Denomination{400, "CD", 2},
        Denomination{100, "C", 1}}},
      {'L', {Denomination{50, "L", 1}}},
      {'X',
       {Denomination{90, "XC", 2}, Denomination{40, "XL", 2},
        Denomination{10, "X", 1}}},
      {'V', {Denomination{5, "V", 1}}},
      {'I',
       {Denomination{9, "IX", 2}, Denomination{4, "IV", 2},
        Denomination{1, "I", 1}}}};

  int romanToInt(string s) {
    int result = 0, i = 0, len = s.size();

    vector<Denomination> possibleDenominations;
    Denomination denomination;

    while (i < len) {
      possibleDenominations = CHAR_TO_DENOMINATIONS_MAP[s[i]];
      for (int j = 0, jLen = possibleDenominations.size(); j < jLen; j++) {
        denomination = possibleDenominations[j];
        if (s.substr(i, denomination.numChar) == denomination.symbol) {
          result += denomination.value;
          i += denomination.numChar;
          break;
        }
      }
    }

    return result;
  }
};

int main() {
  Solution s;
  cout << s.romanToInt("MCMXCVI") << endl;
  return 0;
}