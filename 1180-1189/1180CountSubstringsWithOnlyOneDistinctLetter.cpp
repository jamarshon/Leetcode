/*
1180. Count Substrings with Only One Distinct Letter
Given a string S, return the number of substrings that have only one distinct
letter.

Example 1:

Input: S = "aaaba"
Output: 8
Explanation: The substrings with one distinct letter are "aaa", "aa", "a", "b".
"aaa" occurs 1 time.
"aa" occurs 2 times.
"a" occurs 4 times.
"b" occurs 1 time.
So the answer is 1 + 2 + 4 + 1 = 8.

Example 2:

Input: S = "aaaaaaaaaa"
Output: 55

Constraints:

  1 <= S.length <= 1000
  S[i] consists of only lowercase English letters.
/*
  Submission Date: 2019-09-07
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int countLetters(string S) {
    // count the number of repeating consecutive characters
    // there are n*(n+1) substrings of them
    int N = S.size();
    int res = 0;
    for (int i = 0; i < N;) {
      int j = i;
      while (j < N && S[i] == S[j]) j++;
      res += (j - i) * (j - i + 1) / 2;
      i = j;
    }
    return res;
  }
};

int main() { return 0; }
