/*
45. Jump Game II
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, 
then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

/*
    Submission Date: 2017-06-21
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();

        int curr_max_dist = 0;
        int next_max_dist = 0;
        int min_jumps = 0;
        for(int i = 0; i < len; i++) {
            if(curr_max_dist >= len - 1) {
                return min_jumps;
            }
            
            next_max_dist = max(i + nums[i], next_max_dist);
            if(next_max_dist >= len - 1) {
                return min_jumps + 1;
            }

            if(i == curr_max_dist) {
                curr_max_dist = next_max_dist;
                min_jumps++;
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}