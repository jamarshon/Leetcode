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
    Runtime: 32 ms
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
        
        vector<int>::reverse_iterator ceilIt, endIt;
        // starting from the right find any elements that are after it that are larger than it
        // if there is, swap them and sort in descending order all the elements after it
        for(int i = 0; i < len; i++) {
            endIt = nums.rbegin() + i;
            ceilIt = upper_bound(nums.rbegin(), endIt, nums[len - i - 1]);
            if(ceilIt != endIt) {
              swap(nums[len - i - 1], *ceilIt);
              sort(nums.rbegin(), endIt, greater<int>());
              return;
            }
        }
        
        reverse(nums.begin(), nums.end());
    }
};

int main() {
    Solution s;
    vector<int> v{1,3,2};
    s.nextPermutation(v);
    return 0;
}