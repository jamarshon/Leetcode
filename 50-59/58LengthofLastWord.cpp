/*
58. Length of Last Word
Given a string s consists of upper/lower-case alphabets and empty space
characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters
only.

For example,
Given s = "Hello World",
return 5.

/*
    Submission Date: 2017-01-19
    Runtime: 6 ms
    Difficulty: EASY
*/
using namespace std;
#include <iostream>

class Solution {
 public:
  int lengthOfLastWord(string s) {
    if (s == "") return 0;

    int nonSpaceCharIndex = s.size() - 1;
    while (s[nonSpaceCharIndex] == ' ') {
      if (nonSpaceCharIndex == 0) return 0;
      nonSpaceCharIndex--;
    }

    int lastWordEndIndex = nonSpaceCharIndex;
    int lastWordStartIndex = nonSpaceCharIndex;
    while (lastWordStartIndex >= 0 && s[lastWordStartIndex] != ' ') {
      lastWordStartIndex--;
    }

    return lastWordEndIndex - lastWordStartIndex;
  }
};

int main() { return 0; }