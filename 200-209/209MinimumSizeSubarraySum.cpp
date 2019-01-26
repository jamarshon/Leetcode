/*
209. Minimum Size Subarray Sum
Given an array of n positive integers and a positive integer s, find the minimal
length of a contiguous subarray of which the sum ≥ s. If there isn't one, return
0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

/*
    Submission Date: 2017-07-26
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minSubArrayLen(int s, vector<int>& nums) {
    if (nums.empty()) return 0;

    int N = nums.size();
    int i = 0;
    int curr_sum = 0;
    int start = 0;
    int min_size = INT_MAX;
    while (i < N) {
      curr_sum += nums[i++];
      while (curr_sum >= s) {
        min_size = min(min_size, i - start);
        curr_sum -= nums[start++];
      }
    }
    return min_size == INT_MAX ? 0 : min_size;
  }
};

int main() {
  Solution s;
  return 0;
}