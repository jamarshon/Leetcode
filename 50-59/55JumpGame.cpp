/*
55. Jump Game
Given an array of non-negative integers, you are initially positioned at the first 
index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

/*
    Submission Date: 2017-06-19
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return false;

        int curr_len = nums.front();
        for(int i = 1; i <= curr_len && curr_len < len - 1; i++) {
            curr_len = max(curr_len, i + nums[i]);
        }

        return curr_len >= len - 1;
    }
};

int main() {
    Solution s;
    return 0;
}