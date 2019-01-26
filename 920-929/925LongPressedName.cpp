/*
925. Long Pressed Name
Your friend is typing his name into a keyboard.  Sometimes, when typing a
character c, the key might get long pressed, and the character will be typed 1
or more times.

You examine the typed characters of the keyboard.  Return True if it is possible
that it was your friends name, with some characters (possibly none) being long
pressed.

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.

Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed
output.

Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true

Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.

Note:

  name.length <= 1000
  typed.length <= 1000
  The characters of name and typed are lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isLongPressedName(string name, string typed) {
    int n = name.size();
    int m = typed.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
      if (name[i] != typed[j]) return false;
      int new_i = i;
      int new_j = j;
      while (new_i < n && name[i] == name[new_i]) new_i++;
      while (new_j < m && typed[j] == typed[new_j]) new_j++;

      int name_cnt = new_i - i + 1;
      int typed_cnt = new_j - j + 1;

      if (typed_cnt < name_cnt) return false;
      i = new_i;
      j = new_j;
    }

    return i == n && j == m;
  }
};

int main() { return 0; }
