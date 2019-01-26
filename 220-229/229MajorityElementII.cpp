/*
229. Majority Element II
Given an integer array of size n, find all elements that appear more than
⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
/*
    Submission Date: 2017-08-22
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    /*
    Moore’s Voting Algorithm
    using two variables. Candidate search followed by verification step
    */
    // if(nums.empty()) return {};

    int c1 = 0, c2 = 1;
    int c1_count = 0, c2_count = 0;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      if (nums[i] == c1) {
        c1_count++;
      } else if (nums[i] == c2) {
        c2_count++;
      } else if (c1_count == 0) {
        c1 = nums[i];
        c1_count = 1;
      } else if (c2_count == 0) {
        c2 = nums[i];
        c2_count = 1;
      } else {
        c1_count--;
        c2_count--;
      }
    }

    c1_count = 0, c2_count = 0;
    for (int i = 0; i < N; i++) {
      c1_count += nums[i] == c1;
      c2_count += nums[i] == c2;
    }

    vector<int> res;
    if (c1_count > N / 3) res.push_back(c1);
    if (c2_count > N / 3) res.push_back(c2);

    return res;
  }
};

int main() {
  Solution s;
  return 0;
}