/*
41. First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

/*
    Submission Date: 2017-06-19
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int len = nums.size();
        if(len == 0) return 1;

        for(int i = 0; i < len; i++) {
            while(nums[i] != i && nums[i] >= 0 && nums[i] < len && nums[i] != nums[nums[i]]) {
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i < len; i++) {
            if(nums[i] != i) {
                return i;
            }
        }

        int first_el = nums.front();
        if(first_el <= 0) {
            return len;
        }

        return len + (first_el == len);
    }
};

int main() {
    Solution s;
    return 0;
}