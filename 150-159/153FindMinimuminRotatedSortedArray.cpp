/*
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMin(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;

    int min_item = INT_MAX;
    while (low <= high) {
      int mid = (low + high) >> 1;
      if (nums[low] <= nums[mid]) {  // this region is sorted
        min_item = min(min_item, nums[low]);
        low = mid + 1;
      } else {
        min_item = min(min_item, nums[mid]);
        high = mid - 1;
      }
    }

    return min_item;
  }
};

int main() {
  Solution s;
  return 0;
}