/*
22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>

class Solution {
 private:
  void generateParenthesis(const int& n, const int& left, const int& right,
                           const string& current, vector<string>& result) {
    if (left == n && right == n) {
      result.push_back(current);
      return;
    }
    if (right > left) return;
    if (left > n || right > n) return;
    generateParenthesis(n, left + 1, right, current + "(", result);
    generateParenthesis(n, left, right + 1, current + ")", result);
  }

 public:
  vector<string> generateParenthesis(int n) {
    vector<string> result;
    generateParenthesis(n, 0, 0, "", result);
    return result;
  }
};

int main() { return 0; }