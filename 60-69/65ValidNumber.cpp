/*
65. Valid Number
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should
gather all requirements up front before implementing one.

/*
    Submission Date: 2017-06-22
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  bool isNumber(string s) {
    int len = s.size();
    bool seen_number = false;
    char last_special = '\0';

    bool seen_non_space = false;

    if (s.front() == 'e' || s.back() == 'e' || s.back() == '-' ||
        s.back() == '+')
      return false;

    for (int i = 0; i < len; i++) {
      if (isdigit(s[i])) {
        seen_number = true;
      } else {
        if (isspace(s[i])) {
          if (seen_number || last_special != '\0') {
            while (++i < len) {
              if (!isspace(s[i])) return false;
            }
          }
        } else if (s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i] == '+') {
          // consecutive '.' not allowed
          if (last_special == s[i]) return false;

          // first char can't be 'e' and last char can't be '-' or 'e'
          if (s[i] == '-' || s[i] == '+') {
            if (last_special != '\0' || seen_number) return false;
          } else if (s[i] == 'e') {
            if (s[i - 1] == '-' || !seen_number) return false;
            if (s[i + 1] == '-' || s[i + 1] == '+') i++;

            seen_number = false;

            // keep iterating until we find a number
            while (++i < len) {
              if (s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i + 1] == '+')
                return false;
              if (isdigit(s[i])) {
                seen_number = true;
              } else if (isspace(s[i])) {
                if (!seen_number) return false;
                while (++i < len) {
                  if (!isspace(s[i])) return false;
                }
              } else {
                return false;
              }
            }

            return seen_number;
          }

          last_special = s[i];
        } else {
          return false;
        }
      }
    }
    return seen_number;
  }
};

int main() {
  Solution s;
  cout << s.isNumber("0") << ' ' << true << endl;
  cout << s.isNumber(" 0.1 ") << ' ' << true << endl;
  cout << s.isNumber("abc") << ' ' << false << endl;
  cout << s.isNumber("1 a") << ' ' << false << endl;
  cout << s.isNumber("1  ") << ' ' << true << endl;
  cout << s.isNumber("2e10") << ' ' << true << endl;
  cout << s.isNumber("-2e10") << ' ' << true << endl;
  cout << s.isNumber("2ee") << ' ' << false << endl;
  cout << s.isNumber(" ") << ' ' << false << endl;
  cout << s.isNumber(".1") << ' ' << true << endl;
  cout << s.isNumber("0e") << ' ' << false << endl;
  cout << s.isNumber(". 1") << ' ' << false << endl;
  cout << s.isNumber("1e.") << ' ' << false << endl;
  cout << s.isNumber("1e.2") << ' ' << false << endl;
  cout << s.isNumber("2e0") << ' ' << true << endl;
  cout << s.isNumber("1.e2") << ' ' << true << endl;
  cout << s.isNumber(".e1") << ' ' << false << endl;
  cout << s.isNumber("1e-.2") << ' ' << false << endl;
  cout << s.isNumber("2e0.1") << ' ' << false << endl;
  cout << s.isNumber("1e2e3") << ' ' << false << endl;
  cout << s.isNumber("0e ") << ' ' << false << endl;
  cout << s.isNumber(" e0") << ' ' << false << endl;
  cout << s.isNumber("3-2") << ' ' << false << endl;
  cout << s.isNumber("+.8") << ' ' << true << endl;
  cout << s.isNumber(" 005047e+6") << ' ' << true << endl;
  cout << s.isNumber("+") << ' ' << false << endl;
  return 0;
}