/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) 
which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

If you have figured out the O(n) solution, try coding another solution using the 
divide and conquer approach, which is more subtle.

/*
    Submission Date: 2017-06-22
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return 0;

        int max_sub_arr = nums.front();
        int current = max_sub_arr;

        for(int i = 1; i < len; i++) {
            current = max(nums[i], current + nums[i]);
            max_sub_arr = max(current, max_sub_arr);
        }
        
        return max_sub_arr;
    }
};


int main() {
    return 0;
}