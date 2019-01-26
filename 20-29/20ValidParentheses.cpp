/*
20. Valid Parentheses
Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid
but "(]" and "([)]" are not.

/*
    Submission Date: 2017-01-20
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <stack>
#include <unordered_map>

class Solution {
 public:
  unordered_map<char, char> MAP = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  bool isValid(string s) {
    stack<char> st;
    char topChar;
    for (char c : s) {
      if (c == ')' || c == '}' || c == ']') {
        if (st.empty()) return false;
        topChar = st.top();
        st.pop();
        if (MAP[topChar] != c) return false;
      } else {
        st.push(c);
      }
    }

    return st.empty();
  }
};

int main() { return 0; }