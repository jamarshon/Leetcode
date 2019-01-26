/*
844. Backspace String Compare
Given two strings S and T, return if they are equal when both are typed into
empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string eval(string s) {
    string res = "";
    for (const auto& c : s) {
      if (c == '#') {
        if (!res.empty()) res.pop_back();
      } else {
        res.push_back(c);
      }
    }
    return res;
  }
  bool backspaceCompare(string S, string T) { return eval(S) == eval(T); }
};

int main() { return 0; }