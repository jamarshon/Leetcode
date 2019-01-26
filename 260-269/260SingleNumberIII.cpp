/*
260. Single Number III
Given an array of numbers nums, in which exactly two elements
appear only once and all the other elements appear exactly twice.
Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example,
[5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you
implement it using only constant space complexity?
/*
    Submission Date: 2017-08-23
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> singleNumber(vector<int>& nums) {
    // 1, 2, 1, 3, 2, 5 -> 3 ^ 5 = 011 ^ 101 = 110
    int xor_all = 0;  // x ^ y
    for (auto num : nums) xor_all ^= num;

    // lsb of 110 is 010 so xor all number that has this bit set
    // 2 ^ 2 ^ 3 = 010 ^ 010 ^ 011 = 011
    int lsb = xor_all & ~(xor_all - 1);
    int xor_same_lsb = 0;
    for (auto num : nums) {
      if (num & lsb) xor_same_lsb ^= num;
    }

    // xor_same_lsb is x and xor_all ^ x = (x ^ y) ^ x = y
    int x = xor_same_lsb;
    int y = xor_all ^ x;
    return {x, y};
  }
};

int main() {
  Solution s;
  return 0;
}