/*
283. Move Zeroes
Given an array nums, write a function to move all 0's to the end
of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your
function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

/*
    Submission Date: 2017-08-30
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int N = nums.size();
    int read_idx = 0, write_idx = 0;
    while (read_idx < N) {
      if (nums[read_idx] != 0) {
        nums[write_idx] = nums[read_idx];
        write_idx++;
      }
      read_idx++;
    }

    while (write_idx < N) nums[write_idx++] = 0;
  }
};

int main() { return 0; }