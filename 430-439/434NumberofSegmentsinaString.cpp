/*
434. Number of Segments in a String
Count the number of segments in a string, where a segment is defined to be a
contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5
/*
    Submission Date: 2018-06-09
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  int countSegments(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
      if (!isspace(s[i]) && (i == 0 || isspace(s[i - 1]))) {
        res++;
      }
    }

    return res;
  }
};

int main() { return 0; }