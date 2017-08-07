/*
219. Contains Duplicate II
Given an array of integers and an integer k, find out whether there are two distinct indices 
i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j 
is at most k.

/*
    Submission Date: 2017-08-07
    Runtime: 39 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int N = nums.size();
        for(int i = 0; i < N; i++) {
            if(m.count(nums[i])) {
                if(i - m[nums[i]] <= k) return true;
            }
            m[nums[i]] = i;
        }
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}