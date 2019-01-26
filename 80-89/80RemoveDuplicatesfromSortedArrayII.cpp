/*
80. Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums
being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int N = nums.size();

    if (N == 0) return 0;

    int write_idx = 0;
    for (int i = 0; i < N;) {
      int start = i;
      int start_el = nums[start];
      while (i < N && nums[start] == nums[i]) {
        i++;
      }

      int occurences = min(i - start, 2);
      while (occurences--) {
        nums[write_idx++] = start_el;
      }
    }

    return write_idx;
  }
};

int main() {
  Solution s;
  return 0;
}