/*
893. Groups of Special-Equivalent Strings
You are given an array A of strings.

Two strings S and T are special-equivalent if after any number of moves, S == T.

A move consists of choosing two indices i and j with i % 2 == j % 2, and
swapping S[i] with S[j].

Now, a group of special-equivalent strings from A is a non-empty subset S of
A such that any string not in S is not special-equivalent with any string in S.

Return the number of groups of special-equivalent strings from A.

Example 1:

Input: ["a","b","c","a","c","c"]
Output: 3
Explanation: 3 groups ["a","a"], ["b"], ["c","c","c"]

Example 2:

Input: ["aa","bb","ab","ba"]
Output: 4
Explanation: 4 groups ["aa"], ["bb"], ["ab"], ["ba"]

Example 3:

Input: ["abc","acb","bac","bca","cab","cba"]
Output: 3
Explanation: 3 groups ["abc","cba"], ["acb","bca"], ["bac","cab"]

Example 4:

Input: ["abcd","cdab","adcb","cbad"]
Output: 1
Explanation: 1 group ["abcd","cdab","adcb","cbad"]

Note:

  1 <= A.length <= 1000
  1 <= A[i].length <= 20
  All A[i] have the same length.
  All A[i] consist of only lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numSpecialEquivGroups(vector<string>& A) {
    unordered_map<string, int> freq;

    for (const auto& s : A) {
      string even = "";
      string odd = "";
      for (int i = 0; i < s.size(); i++) {
        if (i % 2 == 0) {
          even.push_back(s[i]);
        } else {
          odd.push_back(s[i]);
        }
      }

      sort(even.begin(), even.end());
      sort(odd.begin(), odd.end());

      freq[even + odd]++;
    }

    return freq.size();
  }
};

int main() { return 0; }
