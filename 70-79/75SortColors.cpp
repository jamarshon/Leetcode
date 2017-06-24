/*
75. Sort Colors
Given an array with n objects colored red, white or blue, sort them so that objects of the same 
color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total 
number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

enum Color{red, white, blue};

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int len = nums.size();
        int left_bound = 0;
        int right_bound = len - 1;
        while(left_bound < len) {
            if(nums[left_bound] != red) break;
            left_bound++;
        }

        while(right_bound >= 0) {
            if(nums[right_bound] != blue) break;
            right_bound--;
        }

        int i = left_bound;
        while(i <= right_bound) {
            switch(nums[i]) {
                case red:
                    swap(nums[left_bound], nums[i]);
                    left_bound++;
                    i = max(left_bound, i);
                    break;
                case blue:
                    swap(nums[right_bound], nums[i]);
                    // cout << "swap" << nums[right_bound] << endl;
                    right_bound--;
                    break;
                case white:
                    i++;
                    break;
            }
        }
    }
};

int main() {
    return 0;
}