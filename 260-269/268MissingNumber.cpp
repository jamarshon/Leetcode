/*
268. Missing Number
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, 
find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement 
it using only constant extra space complexity?

/*
    Submission Date: 2017-08-12
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        int N = nums.size();
        for(int i = 1; i <= N; i++) {
            res ^= i;
            res ^= nums[i-1];
        }
        return res;
    }
};

int main() {
    return 0;
}