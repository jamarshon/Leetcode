/*
81. Search in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

/*
    Submission Date: 2017-08-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) return true;

            if(nums[low] < nums[mid]) { // first half is sorted
                if(nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else if(nums[low] > nums[mid]) { // second half is sorted
                if(nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else { // ambiguous (worst case is O(n))
                low++;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}