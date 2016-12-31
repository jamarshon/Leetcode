/*
33. Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2016-12-30
    Runtime: 6 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, 0, nums.size(), target);
    }
    int binarySearch(vector<int>& nums, int low, int high, int target) {
        if(low >= high) return -1;
        
        int midIndex = (low + high) >> 1,
            midValue = nums[midIndex];
            
        if(midValue == target) return midIndex;
        
        if(nums[low] < midValue) {
            if(nums[low] <= target && target <= midValue) {
                return binarySearch(nums, low, midIndex, target);
            } else {
                return binarySearch(nums, midIndex, high, target);
            }
        } else {
            if(nums[low] <= target || target <= midValue) {
               return binarySearch(nums, low, midIndex, target);
            } else {
                return binarySearch(nums, midIndex, high, target);
            }
        }
    }
};