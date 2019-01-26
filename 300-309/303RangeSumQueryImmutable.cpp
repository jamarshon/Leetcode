/*
303. Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and
j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
/*
    Submission Date: 2017-03-11
    Runtime: 162 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
  vector<int> dp_;

 public:
  NumArray(vector<int> nums) {
    if (nums.empty()) return;

    int N = nums.size();
    dp_.resize(N);

    dp_[0] = nums[0];
    for (int i = 1; i < N; i++) {
      dp_[i] = dp_[i - 1] + nums[i];
    }
  }

  int sumRange(int i, int j) { return dp_[j] - (i - 1 >= 0 ? dp_[i - 1] : 0); }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */

int main() { return 0; }