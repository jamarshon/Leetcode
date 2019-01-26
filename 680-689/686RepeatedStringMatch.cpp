/*
686. Repeated String Match
Given two strings A and B, find the minimum number of times A has to be repeated
such that B is a substring of it. If no such solution, return -1.


For example, with A = "abcd" and B = "cdabcdab".


Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring
of it; and B is not a substring of A repeated two times ("abcdabcd").


Note:
The length of A and B will be between 1 and 10000.
/*
    Submission Date: 2018-06-24
    Runtime: 716 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  if A is already in B, return 1
  else it is a suffix of A + A repeated n times + prefix of A
  so return n + 2
  for all suffix of A, check if it is a prefix of B. if it is then see how many
  times A repeats if it does repeat n times and the prefix of A is a suffix of
  B, then the answer is just n + 2.
  */
  int repeatedStringMatch(string A, string B) {
    if (A.find(B) != string::npos) return 1;
    for (int i = 0; i < A.size(); i++) {
      bool got_suffix = true;
      for (int j = 0; j < A.size() - i; j++) {
        if (B[j] != A[i + j]) {
          got_suffix = false;
          break;
        }
      }

      if (!got_suffix) continue;
      int res = 1;
      int A_ind = 0;
      for (int j = A.size() - i; j < B.size(); j++) {
        if (A_ind == 0) res++;

        if (B[j] != A[A_ind]) {
          res = -1;
          break;
        }

        A_ind = (A_ind + 1) % A.size();
      }

      if (res == -1) continue;
      return res;
    }

    return -1;
  }
};

int main() { return 0; }