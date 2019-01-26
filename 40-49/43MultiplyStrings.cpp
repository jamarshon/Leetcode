/*
43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings, return the
product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to
integer directly.

/*
    Submission Date: 2017-06-19
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  unordered_map<char, string> m;

 public:
  string multiply_d(string num1, char d) {
    if (m.count(d)) return m[d];

    string res;
    int carry = 0;

    int d_n = d - '0';
    for (int i = num1.size() - 1; i >= 0; i--) {
      int c = num1[i] - '0';
      int temp = carry + c * d_n;
      res = to_string(temp % 10) + res;
      carry = temp / 10;
    }

    if (carry > 0) res = to_string(carry) + res;
    return m[d] = res;
  }

  string add(string num1, string num2, int offset) {
    int M = num1.size();
    int N = num2.size();

    string res = num2;

    while (N++ < offset) res = "0" + res;

    N = num2.size();
    int carry = 0;
    int index = N - offset - 1;
    for (int i = M - 1; i >= 0; i--) {
      if (index < 0) {
        int temp = carry + (num1[i] - '0');
        res = to_string(temp % 10) + res;
        carry = temp / 10;
      } else {
        int temp = carry + (num1[i] - '0') + (num2[index] - '0');
        res[index] = (temp % 10) + '0';
        carry = temp / 10;
      }
      index--;
    }

    if (carry > 0) res = to_string(carry) + res;
    return res;
  }

  string multiply(string num1, string num2) {
    if (num1.size() > num2.size()) swap(num1, num2);

    if (num1 == "0") return "0";

    int M = num1.size();
    int N = num2.size();

    string res = "0";
    for (int i = N - 1; i >= 0; i--) {
      if (num2[i] == '0') continue;
      string mul = multiply_d(num1, num2[i]);
      res = add(mul, res, N - 1 - i);
    }

    return res;
  }
};

int main() {
  Solution s;
  return 0;
}