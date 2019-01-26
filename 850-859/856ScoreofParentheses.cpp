/*
856. Score of Parentheses
Given a balanced parentheses string S, compute the score of the string based on
the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
/*
    Submission Date: 2018-06-29
    Runtime: 4 ms
    Difficulty:MEDIUM
*/
#include <iostream>
#include <stack>

using namespace std;

class Solution {
 public:
  int scoreOfParentheses(string S) {
    // first is the value or -1 if it is a character '('
    stack<pair<int, char>> stk;
    for (const auto& e : S) {
      if (e == '(') {
        stk.emplace(-1, '(');
      } else {  // e == ')'
        // S is balanced so keep going back until '(' (ie not value)
        // add all the numbers in between and multiply by 2
        int in_between = 0;
        while (stk.top().first != -1) {
          in_between += stk.top().first;
          stk.pop();
        }

        stk.pop();
        stk.emplace(max(1, 2 * in_between), 'r');
      }
    }

    int res = 0;
    // since S is balanced then stk must only contain values so add
    // up and return value
    while (!stk.empty()) {
      res += stk.top().first;
      stk.pop();
    }

    return res;
  }
};

int main() { return 0; }