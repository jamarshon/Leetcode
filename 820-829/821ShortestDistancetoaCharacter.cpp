/*
821. Shortest Distance to a Character
Given a string S and a character C, return an array of integers representing the
shortest distance from the character C in the string.

Example 1:

Input: S = "loveleetcode", C = 'e'
Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

Note:

S string length is in [1, 10000].
C is a single character, and guaranteed to be in string S.
All letters in S and C are lowercase.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  keep track of last seen C and use that as the distance
  then do it from the back and take the min of this value with the previous
  value
  */
  vector<int> shortestToChar(string S, char C) {
    int N = S.size();
    vector<int> res(N, INT_MAX);

    int last_C_forward = -1;
    int last_C_backward = -1;
    for (int i = 0; i < N; i++) {
      if (S[i] == C) last_C_forward = i;
      if (S[N - i - 1] == C) last_C_backward = N - i - 1;

      if (last_C_forward >= 0) {
        res[i] = min(res[i], i - last_C_forward);
      }

      if (last_C_backward >= 0) {
        res[N - i - 1] = min(res[N - i - 1], last_C_backward - (N - i - 1));
      }
    }

    return res;
  }
};

int main() { return 0; }