/*
137. Single Number II
Given an array of integers, every element appears three times except for one, which appears exactly once. 
Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

/*
    Submission Date: 2017-08-02
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0;
        for(auto num: nums) {
            int common_with_one = one & num;
            int common_with_two = two & num;

            two &= ~common_with_two;
            two |= common_with_one;

            one |= num;
            one &= ~common_with_one;
            one &= ~common_with_two;
        }

        return one;
    }
};

int main() {
    return 0;
}