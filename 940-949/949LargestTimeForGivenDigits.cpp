/*
949. Largest Time for Given Digits
Given an array of 4 digits, return the largest 24 hour time that can be made.

The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from
00:00, a time is larger if more time has elapsed since midnight.

Return the answer as a string of length 5.  If no valid time can be made, return
an empty string.

Example 1:

Input: [1,2,3,4]
Output: "23:41"

Example 2:

Input: [5,5,5,5]
Output: ""

Note:

  A.length == 4
  0 <= A[i] <= 9
/*
  Submission Date: 2019-02-05
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string largestTimeFromDigits(vector<int>& A) {
    /*
    ab:cd
    a [0, 2]
    b a == 2 [0-3] else [0-9]
    c [0, 5]
    d [0, 9]
    */

    unordered_map<int, int> freq;
    for (const auto& e : A) freq[e]++;
    for (int i = 2; i >= 0; i--) {
      if (!freq.count(i)) continue;
      freq[i]--;

      int cap = (i == 2) ? 3 : 9;
      for (int j = cap; j >= 0; j--) {
        if (!freq.count(j) || freq[j] == 0) continue;
        freq[j]--;
        for (int k = 5; k >= 0; k--) {
          if (!freq.count(k) || freq[k] == 0) continue;
          freq[k]--;
          for (int l = 9; l >= 0; l--) {
            if (!freq.count(l) || freq[l] == 0) continue;
            return to_string(i) + to_string(j) + string(":") + to_string(k) +
                   to_string(l);
          }
          freq[k]++;
        }

        freq[j]++;
      }
      freq[i]++;
    }

    return "";
  }
};

int main() { return 0; }
