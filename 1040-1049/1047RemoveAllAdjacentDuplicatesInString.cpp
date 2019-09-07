/*
1047. Remove All Adjacent Duplicates In String
Given a string S of lowercase letters, a duplicate removal consists of choosing
two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is
guaranteed the answer is unique.

Example 1:

Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and
equal, and this is the only possible move.  The result of this move is that the
string is "aaca", of which only "aa" is possible, so the final string is "ca".

Note:

  1 <= S.length <= 20000
  S consists only of English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeDuplicates(string S) {
    // using a stack if we encounter a character
    // that was previously seen then we can pop from
    // the stack and not add the current character.
    // this exposes a previous character in the string
    // which can match with the next character as needed.
    vector<char> stk;
    for (int i = 0; i < S.size(); i++) {
      if (!stk.empty() && stk.back() == S[i])
        stk.pop_back();
      else
        stk.push_back(S[i]);
    }

    return string(stk.begin(), stk.end());
  }
};

int main() { return 0; }
