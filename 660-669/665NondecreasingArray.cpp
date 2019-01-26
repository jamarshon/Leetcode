/*
665. Non-decreasing Array
Given an array with n integers, your task is to check if it could become
non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every
i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].
/*
    Submission Date: 2018-06-09
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  for the first number where nums[i] < nums[i-1] where nums[i] = c
  a b c d
  
  then a <= b and c < b.
  the condition must hold c <= d as if c < d then it will be a a c (c-x)
  or 10 10 7 6 where c has to be fixed and d as well
  
  if problem_ind == -1 means the array is already sorted in increasing order
  if it is 1 then just update nums[0] to equal nums[1]
  
  if a <= c then it is true as well as a <= b, a <= c and c <= d (from before)
  so a <= b <= c <= d
  
  if d does not exist or b <= d as a <= b and b <= d so replace c with any
  number between [b,d] to get a b b d
  */
  bool checkPossibility(vector<int>& nums) {
    int problem_ind = -1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] < nums[i - 1]) {
        if (problem_ind != -1) return false;
        problem_ind = i;
      }
    }

    return problem_ind < 2 || nums[problem_ind - 2] <= nums[problem_ind] ||
           (problem_ind + 1 == nums.size() ||
            nums[problem_ind - 1] <= nums[problem_ind + 1]);
  }
};

int main() { return 0; }