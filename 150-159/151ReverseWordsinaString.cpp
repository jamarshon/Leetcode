/*
151. Reverse Words in a String
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.

Clarification:
What constitutes a word?
A sequence of non-space characters constitutes a word.
Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing
spaces. How about multiple spaces between two words? Reduce them to a single
space in the reversed string.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  void reverseWords(string &s) {
    int write_idx = 0;
    int N = s.size();

    for (int i = 0; i < N;) {
      // finding first non space char
      while (i < N && isspace(s[i])) {
        i++;
      }

      if (i < N) {
        // add space if needed between words
        if (write_idx != 0) {
          s[write_idx++] = ' ';
        }

        // write all non space char to write_idx
        while (i < N && !isspace(s[i])) {
          s[write_idx++] = s[i++];
        }
      }
    }

    s.resize(write_idx);
    N = s.size();

    reverse(s.begin(), s.end());
    for (int i = 0; i < N; i++) {
      int start = i;
      while (i < N && !isspace(s[i])) {
        i++;
      }
      reverse(s.begin() + start, s.begin() + i);
    }
  }
};

int main() { return 0; }