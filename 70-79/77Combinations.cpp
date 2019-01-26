/*
77. Combinations
Given two integers n and k, return all possible combinations of k numbers out of
1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

/*
    Submission Date: 2017-07-08
    Runtime: 73 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void combine(vector<int>& curr, vector<vector<int>>& res, int start, int n,
               int k) {
    if (curr.size() == k) {
      res.push_back(curr);
      return;
    }

    for (int i = start; i <= n; i++) {
      curr.push_back(i);
      combine(curr, res, i + 1, n, k);
      curr.pop_back();
    }
  }
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> curr;
    combine(curr, res, 1, n, k);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}