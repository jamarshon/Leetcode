/*
18. 4Sum
Given an array S of n integers, are there elements a, b, c, and d in S such that
a + b + c + d = target? Find all unique quadruplets in the array which gives the
sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

/*
    Submission Date: 2017-06-19
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());

    int len = nums.size();
    vector<vector<int>> res;

    for (int i = 0; i < len; i++) {
      if (nums[i] > 0 && nums[i] > target) break;
      if (i != 0 && nums[i] == nums[i - 1]) continue;
      for (int j = i + 1; j < len; j++) {
        if (j != i + 1 && nums[j] == nums[j - 1]) continue;
        int low = j + 1;
        int high = len - 1;
        int curr_target = target - nums[i] - nums[j];
        while (low < high) {
          if (nums[low] + nums[high] == curr_target) {
            res.push_back({nums[i], nums[j], nums[low], nums[high]});
            while (++low < high && nums[low] == nums[low - 1]) {
            }
          } else if (nums[low] + nums[high] > curr_target) {
            high--;
          } else {
            low++;
          }
        }
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}