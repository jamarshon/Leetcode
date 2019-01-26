/*
592. Fraction Addition and Subtraction
Given a string representing an expression of fraction addition
and subtraction, you need to return the calculation result in string
format. The final result should be irreducible fraction. If your final
result is an integer, say 2, you need to change it to the format of
fraction that has denominator 1. So in this case, 2 should be
converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'.
So does the output.
Each fraction (input and output) has format ±numerator/denominator.
If the first input fraction or the output is positive, then '+' will
be omitted.
The input only contains valid irreducible fractions, where the
numerator and denominator of each fraction will always be in the
range [1,10]. If the denominator is 1, it means this fraction is
actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed
to be valid and in the range of 32-bit int.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
struct Fraction {
  ll num, den;
};

class Solution {
 public:
  ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

  ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

  // a/b + c/d = (a*lcm(b,d)/b + c*lcm(b,d)/d)/lcm(b,d)
  // 1/4 + 1/16 = (1*16/4 + 1*16/16)/16 = (4+1)/16
  // 1/3 + 2/4 = (1*12/3 + 2*12/4)/12 = (4+6)/12

  // (a*(b*d/gcd(b,d))/b + c*(b*d/gcd(b,d))/d)/(b*d/gcd(b,d))
  // (a*d/gcd(b,d) + c*b/gcd(b,d))/(b*d/gcd(b,d))
  // ((a*d + c*b)/gcd(b,d)*gcd(b,d))/(b*d)
  // (a*d + b*c)/(b*d)
  Fraction add(Fraction a, Fraction b) {
    return {a.num * b.den + a.den * b.num, a.den * b.den};
  }

  Fraction reduce(Fraction a) {
    int gcd_num_den = gcd(abs(a.num), a.den);
    return {a.num / gcd_num_den, a.den / gcd_num_den};
  }

  string fractionAddition(string s) {
    vector<Fraction> v;
    int N = s.size();
    bool is_negative = false;
    for (int i = 0; i < N;) {
      // s[i] is beginning of numerator which is either '-' (negative num), '+'
      // (positive num) or a number (positive num and is start of string)
      Fraction fr;
      is_negative = s[i] == '-';

      if (s[i] == '+' || is_negative) {
        i++;
      }

      ll curr = 0;
      while (isdigit(s[i])) {
        curr = curr * 10 + (s[i] - '0');
        i++;
      }

      fr.num = is_negative ? -curr : curr;
      // s[i] is the '/' followed by a number so end i where the next operator
      // starts
      assert(s[i++] == '/');

      curr = 0;
      while (isdigit(s[i]) && i < N) {
        curr = curr * 10 + (s[i] - '0');
        i++;
      }

      fr.den = curr;
      v.push_back(fr);
    }

    Fraction res = v.front();
    res = reduce(res);
    for (int i = 1; i < v.size(); i++) {
      res = add(res, v[i]);
      res = reduce(res);
    }

    return to_string(res.num) + "/" + to_string(res.den);
  }
};

int main() {
  Solution s;
  return 0;
}