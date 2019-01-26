/*
224. Basic Calculator
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus +
or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
Note: Do not use the eval built-in library function.

/*
    Submission Date: 2017-08-07
    Runtime: 26 ms
    Difficulty: HARD
*/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <functional>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution2 {
  unordered_map<char, function<int(int, int)>> ops_m{
      {'+', [](const int a, const int b) { return a + b; }},
      {'-', [](const int a, const int b) { return a - b; }},
  };

  unordered_map<char, char> toggle{{'+', '-'}, {'-', '+'}};

 public:
  int calculate(string s) {
    for (int i = 0, len = s.size(); i < len; i++) {
      if (i > 0 && s[i - 1] == '-' && s[i] == '(') {
        // the idea is to keep track of "-(" and "("
        // if we get to a ")" we pop. Maintain "-(" count in the stack
        // if it is odd then toggle all '-' and '+' we come across
        stack<char> stk;
        int minus_open_count = 1;
        stk.push('-');
        while (!stk.empty() && ++i < len) {
          if (isspace(s[i]) || isdigit(s[i])) continue;
          if (s[i] == ')') {
            if (stk.top() == '-') minus_open_count--;
            stk.pop();
          } else if (s[i] == '(') {
            stk.push(')');
          } else if (s[i] == '+' || s[i] == '-') {
            bool should_push = s[i] == '-' && s[i + 1] == '(';
            if (minus_open_count % 2 == 1) {
              s[i] = toggle[s[i]];
            }
            if (should_push) {
              stk.push('-');
              minus_open_count++;
              i++;
            }
          } else {
            assert(false);
          }
        }
      }
    }

    s.erase(remove_if(s.begin(), s.end(),
                      [](const char& c) {
                        return isspace(c) || c == '(' || c == ')';
                      }),
            s.end());

    int N = s.size();
    if (N == 0) return 0;

    int res = 0;

    function<int(int, int)> op = ops_m['+'];

    for (int i = 0; i < N; i++) {
      int start = i;
      while (i < N && isdigit(s[i])) {
        i++;
      }

      int val = stoi(s.substr(start, i - start));

      res = op(res, val);
      if (i < N) {
        op = ops_m[s[i]];
      }
    }

    return res;
  }
};

class Solution {
 public:
  int calculate(string s) {
    stack<string> stk;
    int N = s.size();

    for (int i = 0; i < N; i++) {
      // space continue
      if (isspace(s[i])) continue;
      // '(', '+', '-' push to stack
      if (s[i] == '(' || s[i] == '+' || s[i] == '-') {
        stk.push(string(1, s[i]));
      } else if (isdigit(s[i])) {
        // number so get the whole number and push to stack
        int start = i;
        while (i < N && isdigit(s[i])) i++;
        string val = s.substr(start, i - start);
        stk.push(val);
        i--;
      } else if (s[i] == ')') {
        // closing bracket keep popping until one "(" is removed
        // keep evaluating the expression, check if number is preceded by
        // a negative
        int curr = 0;
        while (!stk.empty()) {
          string top = stk.top();
          stk.pop();
          if (top == "(") break;
          int val = stoi(top);
          if (!stk.empty()) {
            if (stk.top() == "-") {
              val *= -1;
              stk.pop();
            } else {
              if (stk.top() == "+") {
                stk.pop();
              } else {
                assert(stk.top() == "(");
              }
            }
          }
          curr += val;
        }
        stk.push(to_string(curr));
      } else {
        assert(false);
      }
    }

    // evaluate remaining stack
    int res = 0;
    while (!stk.empty()) {
      int val = stoi(stk.top());
      stk.pop();
      if (!stk.empty()) {
        if (stk.top() == "-") {
          val *= -1;
        } else {
          assert(stk.top() == "+");
        }
        stk.pop();
      }
      res += val;
    }

    return res;
  }
};

int main() {
  Solution s;
  cout << s.calculate("1 + 1") << ' ' << 2 << endl;
  cout << s.calculate(" 2-1 + 2 ") << ' ' << 3 << endl;
  cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << ' ' << 23 << endl;
  cout << s.calculate("2-(5-6)") << ' ' << 3 << endl;
  cout << s.calculate("(3-(2-(5-(9-(4)))))") << ' ' << 1 << endl;
  return 0;
}