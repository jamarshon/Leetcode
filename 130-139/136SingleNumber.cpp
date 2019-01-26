/*
136. Single Number
Given an array of integers, every element appears twice except for one. Find
that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

/*
    Submission Date: 2017-06-29
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto e : nums) res ^= e;
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}