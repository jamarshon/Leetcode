/*
1128. Number of Equivalent Domino Pairs
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] =
[c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one
domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length,
and dominoes[i] is equivalent to dominoes[j].

Example 1:
Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1

Constraints:

  1 <= dominoes.length <= 40000
  1 <= dominoes[i][j] <= 9
/*
  Submission Date: 2019-09-23
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    unordered_map<string, int> freq;
    int res = 0;
    for (const auto& d : dominoes) {
      auto p = minmax(d[0], d[1]);
      string key = to_string(p.first) + ',' + to_string(p.second);
      res += freq[key];
      freq[key]++;
    }
    return res;
  }
};

int main() { return 0; }
