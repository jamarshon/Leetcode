/*
1021. Remove Outermost Parentheses
A valid parentheses string is either empty (""), "(" + A + ")", or A + B, where
A and B are valid parentheses strings, and + represents string concatenation. 
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses
strings.

A valid parentheses string S is primitive if it is nonempty, and there does not
exist a way to split it into S = A+B, with A and B nonempty valid parentheses
strings.

Given a valid parentheses string S, consider its primitive decomposition: S =
P_1 + P_2 + ... + P_k, where P_i are primitive valid parentheses strings.

Return S after removing the outermost parentheses of every primitive string in
the primitive decomposition of S.

Example 1:

Input: "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" +
"(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:

Input: "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())"
+ "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())"
= "()()()()(())".

Example 3:

Input: "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

Note:

  S.length <= 10000
  S[i] is "(" or ")"
  S is a valid parentheses string
/*
  Submission Date: 2019-08-25
  Runtime: 12 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string removeOuterParentheses(string S) {
    int cnt = 0;
    string res, token;
    for (const auto& c : S) {
      if (c == '(') {
        cnt++;
      } else {
        cnt--;
      }
      token.push_back(c);
      if (cnt == 0) {
        res += token.substr(1, token.size() - 2);
        token = "";
      }
    }
    return res;
  }
};

int main() { return 0; }
