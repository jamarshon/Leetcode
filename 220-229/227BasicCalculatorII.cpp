/*
227. Basic Calculator II
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators
and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Note: Do not use the eval built-in library function.

/*
    Submission Date: 2017-08-12
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int getNumber(const string& s, int& i, const int& N) {
    int num = 0;
    bool seen_digit = false;
    while (i < N) {
      if (isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        seen_digit = true;
      } else if (seen_digit) {  // have seen a digit but current is not a digit
                                // meaning end of sequence
        break;
      }
      i++;
    }

    return num;
  }

  int calculate(string s) {
    s = "+" + s + "+";
    int N = s.size();
    int total = 0, prev_val = 0, temp;
    for (int i = 0; i < N;) {
      if (isspace(s[i])) {
        i++;
      } else if (s[i] == '+' || s[i] == '-') {
        total += prev_val;

        bool is_neg = s[i] == '-';
        prev_val = getNumber(s, i, N);
        if (is_neg) prev_val *= -1;
      } else if (s[i] == '*' || s[i] == '/') {
        bool is_multply = s[i] == '*';
        temp = getNumber(s, i, N);

        if (is_multply)
          prev_val *= temp;
        else
          prev_val /= temp;
      } else {
        assert(false);
      }
    }
    return total;
  }
};

class Solution2 {
  unordered_map<char, function<int(int, int)>> ops_m_{
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'/', [](const int& a, const int& b) { return a / b; }},
  };

 public:
  int getNumber(const string& s, int& i, const int N) {
    int num = 0;
    while (i < N && isdigit(s[i])) num = num * 10 + (s[i++] - '0');
    i--;
    return num;
  }

  int evaluate(const vector<int>& nums, const vector<char>& ops) {
    assert(nums.size() == ops.size() + 1);
    int num = nums.front();
    for (int i = 0; i < ops.size(); i++) {
      num = ops_m_[ops[i]](num, nums[i + 1]);
    }
    return num;
  }

  int calculate(string s) {
    int N = s.size();
    vector<int> to_add_nums, to_mul_nums;
    vector<char> to_add_ops, to_mul_ops;
    for (int i = 0; i < N; i++) {
      if (isspace(s[i])) continue;
      if (isdigit(s[i])) {
        int num = getNumber(s, i, N);
        to_mul_nums.push_back(num);
      } else if (s[i] == '+' || s[i] == '-') {
        // once we get to a '+' or '-' it is safe
        // to evaluate whatever multiplication/divide/subtract/add
        // that appears before this
        int num = evaluate(to_mul_nums, to_mul_ops);
        to_mul_nums.clear();
        to_mul_ops.clear();
        to_add_nums.push_back(num);
        to_add_ops.push_back(s[i]);
      } else if (s[i] == '*' || s[i] == '/') {
        to_mul_ops.push_back(s[i]);
      }
    }

    // if it ends on a multiplication
    if (!to_mul_nums.empty()) {
      int num = evaluate(to_mul_nums, to_mul_ops);
      to_add_nums.push_back(num);
    }

    // evaluate the whole stack
    int res = 0;
    if (!to_add_nums.empty()) {
      res = evaluate(to_add_nums, to_add_ops);
    }

    return res;
  }
};

int main() { return 0; }