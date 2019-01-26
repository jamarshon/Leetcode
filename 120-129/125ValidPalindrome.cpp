/*
125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric
characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask
during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    int len = s.size();
    int i = 0;
    int j = len - 1;

    while (i < j) {
      while (!isalnum(s[i]) && i < j) i++;
      if (i >= j) return true;

      while (!isalnum(s[j]) && i < j) j--;
      if (i >= j) return true;

      if (tolower(s[i]) != tolower(s[j])) return false;
      i++;
      j--;
    }

    return true;
  }
};

int main() {
  Solution s;
  return 0;
}