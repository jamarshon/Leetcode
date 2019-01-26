/*
459. Repeated Substring Pattern
Given a non-empty string check if it can be constructed by taking a substring of
it and appending multiple copies of the substring together. You may assume the
given string consists of lowercase English letters only and its length will not
exceed 10000. Example 1: Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc"
twice.)
/*
    Submission Date: 2018-06-09
    Runtime: 53 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool repeatedSubstringPattern(string s) {
    int N = s.size();

    for (int i = 1; i <= N / 2; i++) {
      if (N % i == 0) {
        // N can be split into parts containing i elements
        string pos = "";
        string part = s.substr(0, i);
        for (int j = 0; j < N / i; j++) {
          pos += part;
        }

        if (s == pos) return true;
      }
    }

    return false;
  }
};

int main() { return 0; }