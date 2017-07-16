/*
643. Maximum Average Subarray I
Given an array consisting of n integers, find the contiguous subarray of given length k that 
has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
Note:
1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].

/*
    Submission Date: 2017-07-15
    Runtime: 199 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        int max_average = INT_MIN;
        for(int i = 0; i < nums.size(); i++) {
            if(i < k) {
                sum += nums[i];
            } else {
                if(i == k) max_average = max(max_average, sum);
                sum = sum - nums[i - k] + nums[i];
                max_average = max(max_average, sum);
            }
        }
        if(k == nums.size()) return (double)sum/k;
        return (double)max_average/k;
    }
};

int main() {
    return 0;
}