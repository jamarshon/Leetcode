/*
166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction,
return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

/*
    Submission Date: 2017-06-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string fractionToDecimal(long long numerator, long long denominator) {
    if (numerator == 0) return "0";

    unordered_map<int, int> m;
    string sign = ((numerator < 0) ^ (denominator < 0)) ? "-" : "";

    string res = "";

    numerator = abs(numerator);
    denominator = abs(denominator);
    int num_of_digits =
        numerator < denominator ? 1 : floor(log10(numerator / denominator)) + 1;

    while (numerator) {
      if (m.count(numerator)) {
        res =
            res.substr(0, m[numerator]) + "(" + res.substr(m[numerator]) + ")";
        break;
      }
      m[numerator] = res.size();
      res += to_string(numerator / denominator);
      numerator %= denominator;
      numerator *= 10;
    }

    string rem = res.substr(num_of_digits);
    res = sign + res.substr(0, num_of_digits) + (rem.size() ? "." : "") + rem;
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}