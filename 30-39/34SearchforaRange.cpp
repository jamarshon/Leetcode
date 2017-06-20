/*
34. Search for a Range
Given an array of integers sorted in ascending order, find the starting and ending 
position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        int low = 0;
        int high = len - 1;

        int start = -1;
        int end = -1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) {
                if(mid == 0 || nums[mid - 1] != nums[mid]) {
                    start = mid;
                    break;
                } else {
                    high = mid - 1;
                }
            } else if(nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if(start != -1) {
            low = 0;
            high = len - 1;
            while(low <= high) {
                int mid = low + (high - low)/2;
                if(nums[mid] == target) {
                    if(mid == len - 1 || nums[mid] != nums[mid + 1]) {
                        end = mid;
                        break;
                    } else {
                        low = mid + 1;
                    }
                } else if(nums[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        
        return {start, end};
    }
};

int main() {
    Solution s;
    return 0;
}