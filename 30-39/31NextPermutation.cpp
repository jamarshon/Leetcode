/*
31. Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

/*
    Submission Date: 2017-01-24
    Runtime: 13 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if(len <= 1) return;
        
        // starting from the right find any elements that are after it that are larger than it
        // if there is, swap them and sort in descending order all the elements after it
        int i = len - 2;
        while(i >= 0 && nums[i] >= nums[i + 1]) i--;

        int offset;
        if(i == -1) {
            offset = 0;
        } else {
            int j = len - 1;
            while(nums[i] >= nums[j]) j--;
            swap(nums[i], nums[j]);
            offset = i + 1;
        }

        reverse(nums.begin() + offset, nums.end());   
    }
};

int main() {
    Solution s;
    vector<int> v{1,5,1};
    s.nextPermutation(v);
    return 0;
}