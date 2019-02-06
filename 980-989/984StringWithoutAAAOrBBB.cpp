/*
984. String Without AAA or BBB
Given two integers A and B, return any string S such that:

  S has length A + B and contains exactly A 'a' letters, and exactly B 'b'
letters;
  The substring 'aaa' does not occur in S;
  The substring 'bbb' does not occur in S.

Example 1:

Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.

Example 2:

Input: A = 4, B = 1
Output: "aabaa"

Note:

  0 <= A <= 100
  0 <= B <= 100
  It is guaranteed such an S exists for the given A and B.
/*
  Submission Date: 2019-02-05
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  always write the most abundant character (greedy) unless last two letters are
  the same
  */
  string strWithout3a3b(int A, int B) {
    string S = "";
    while (A || B) {
      int n = S.size();
      bool same_last_letter = n >= 2 && S[n - 1] == S[n - 2];
      bool write_A = (same_last_letter && S[n - 1] == 'b') ||
                     (!same_last_letter && A >= B);
      if (write_A) {
        A--;
        S.push_back('a');
      } else {
        B--;
        S.push_back('b');
      }
    }

    return S;
  }
};

int main() { return 0; }
