/*
540. Single Element in a Sorted Array
Given a sorted array consisting of only integers where every element appears
twice except for one element which appears once. Find this single element that
appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNonDuplicate(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if ((mid % 2 == 0 && nums[mid] == nums[mid + 1]) ||
          (mid % 2 == 1 && nums[mid] == nums[mid - 1])) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return nums[low];
  }
};

int main() { return 0; }