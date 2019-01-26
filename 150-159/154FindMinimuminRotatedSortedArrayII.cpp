/*
154. Find Minimum in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMin(vector<int>& nums) {
    if (nums.empty()) return 0;

    int low = 0;
    int high = nums.size() - 1;

    int min_item = nums[low];
    while (low <= high) {
      int mid = (low + high) >> 1;
      if (nums[low] < nums[mid]) {  // first half is sorted
        min_item = min(min_item, nums[low]);
        low = mid + 1;
      } else if (nums[low] > nums[mid]) {  // second half is sorted
        min_item = min(min_item, nums[mid]);
        high = mid - 1;
      } else {
        min_item = min(min_item, nums[low]);
        low++;
      }
    }
    return min_item;
  }
};

int main() { return 0; }