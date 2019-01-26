/*
167. Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order, find two
numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add
up to the target, where index1 must be less than index2. Please note that your
returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not
use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int N = numbers.size();
    int low = 0;
    int high = N - 1;
    while (low < high) {
      int curr_sum = numbers[low] + numbers[high];
      if (curr_sum == target) {
        return {low + 1, high + 1};
      } else if (curr_sum < target) {
        low++;
      } else {
        high--;
      }
    }
    return {};
  }
};

int main() { return 0; }