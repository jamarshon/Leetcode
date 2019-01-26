/*
40. Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all
unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  void combinationSum2(vector<int>& candidates, vector<int>& curr, int sum,
                       int target, int index, vector<vector<int>>& res) {
    if (sum > target) return;
    if (sum == target) {
      res.push_back(curr);
      return;
    }

    for (int i = index; i < candidates.size(); i++) {
      if (i != index && candidates[i - 1] == candidates[i]) continue;
      curr.push_back(candidates[i]);
      combinationSum2(candidates, curr, sum + candidates[i], target, i + 1,
                      res);
      curr.pop_back();
    }
  }

 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> curr;
    combinationSum2(candidates, curr, 0, target, 0, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}