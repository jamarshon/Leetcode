/*
162. Find Peak Element
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its
index.

The array may contain multiple peaks, in that case return the index to any one
of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should
return the index number 2.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    int N = nums.size();
    int low = 0;
    int high = N - 1;

    while (low <= high) {
      int mid = (low + high) >> 1;

      bool left_is_smaller = mid == 0 || nums[mid - 1] < nums[mid];
      bool right_is_smaller = mid == N - 1 || nums[mid] > nums[mid + 1];

      if (left_is_smaller && right_is_smaller) {  // peak
        return mid;
      } else if (left_is_smaller && !right_is_smaller) {  // peak on right
        low = mid + 1;
      } else if (!left_is_smaller && right_is_smaller) {  // peak on left
        high = mid - 1;
      } else {  // both sides have peak
        low = mid + 1;
      }
    }

    return -1;
  }
};

int main() {
  Solution s;
  return 0;
}