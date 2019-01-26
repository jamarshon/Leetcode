/*
26. Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element
appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with
constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums
being 1 and 2 respectively. It doesn't matter what you leave beyond the new
length.

/*
    Submission Date: 2017-01-22
    Runtime: 48 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int i = 0, j = 1, len = nums.size();
    if (len == 0) return 0;

    while (true) {
      while (j < len && nums[i] == nums[j]) j++;
      if (j == len) return i + 1;
      swap(nums[++i], nums[j++]);
    }
  }
};

int main() { return 0; }