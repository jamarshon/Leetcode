/*
78. Subsets
Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

/*
    Submission Date: 2017-07-08
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void subsets(vector<int>& curr, vector<int>& nums, vector<vector<int>>& res,
               int index) {
    res.push_back(curr);

    for (int i = index; i < nums.size(); i++) {
      curr.push_back(nums[i]);
      subsets(curr, nums, res, i + 1);
      curr.pop_back();
    }
  }
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> curr;
    vector<vector<int>> res;
    subsets(curr, nums, res, 0);
    return res;
  }
};
int main() {
  Solution s;
  return 0;
}