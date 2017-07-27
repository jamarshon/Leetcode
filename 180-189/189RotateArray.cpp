/*
189. Rotate Array
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int start, int end, int k) {
        if(start >= end) return;
        int N = end - start;

        k %= N;
        if(k == 0) return;

        for(int i = 0; i < k; i++) {
            swap(nums[start + i], nums[end - k + i]);
        }

        rotate(nums, start + k, end, k);
    }
    void rotate2(vector<int>& nums, int k) {
        rotate(nums, 0, nums.size(), k);
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

int main() {
    return 0;
}