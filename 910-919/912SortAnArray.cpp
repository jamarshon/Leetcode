/*
912. Sort an Array
Given an array of integers nums, sort the array in ascending order.

Example 1:

Input: [5,2,3,1]
Output: [1,2,3,5]

Example 2:

Input: [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]

Note:

  1 <= A.length <= 10000
  -50000 <= A[i] <= 50000
/*
  Submission Date: 2019-09-23
  Runtime: 84 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void sort(vector<int>& nums, int l, int r) {
    if (l < r) {
      int mid = l + (r - l) / 2;
      int pivot = nums[mid];
      swap(nums[mid], nums[l]);
      int j = l + 1;
      for (int i = l + 1; i <= r; i++) {
        if (nums[i] < pivot) {
          swap(nums[i], nums[j]);
          j++;
        }
      }
      swap(nums[j - 1], nums[l]);
      sort(nums, l, j - 2);
      sort(nums, j, r);
    }
  }
  vector<int> sortArray(vector<int>& nums) {
    // quick sort
    sort(nums, 0, nums.size() - 1);
    return nums;
  }
};

int main() { return 0; }
