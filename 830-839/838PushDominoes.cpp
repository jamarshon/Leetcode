/*
838. Push Dominoes
There are N dominoes in a line, and we place each domino vertically upright.

In the beginning, we simultaneously push some of the dominoes either to the left
or to the right.

After each second, each domino that is falling to the left pushes the adjacent
domino on the left.

Similarly, the dominoes falling to the right push their adjacent dominoes
standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays
still due to the balance of the forces.

For the purposes of this question, we will consider that a falling
domino expends no additional force to a falling or already fallen domino.

Given a string "S" representing the initial state. S[i] = 'L', if the i-th
domino has been pushed to the left; S[i] = 'R', if the i-th domino has been
pushed to the right; S[i] = '.', if the i-th domino has not been pushed.

Return a string representing the final state. 

Example 1:

Input: ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."

Example 2:

Input: "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.

Note:

  0 <= N <= 10^5
  String dominoes contains only 'L', 'R' and '.'
/*
  Submission Date: 2019-01-26
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string pushDominoes(string s) {
    int last_ind = -1;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '.') continue;
      if (s[i] == 'L') {
        if (last_ind == -1 || s[last_ind] == 'L') {
          fill(s.begin() + max(0, last_ind), s.begin() + i, 'L');
        } else {
          int j = 0;
          while (last_ind + j < i - j) {
            s[last_ind + j] = 'R';
            s[i - j] = 'L';
            j++;
          }
        }
      } else if (last_ind != -1 && s[last_ind] != 'L') {
        fill(s.begin() + last_ind, s.begin() + i, 'R');
      }
      last_ind = i;
    }

    if (last_ind != -1 && s[last_ind] == 'R') {
      fill(s.begin() + last_ind, s.end(), 'R');
    }

    return s;
  }
};

int main() { return 0; }
