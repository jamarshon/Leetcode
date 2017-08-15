/*
169. Majority Element
Given an array of size n, find the majority element. The majority element is the element that appears more 
than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
/*
Moore’s Voting Algorithm
When applying the algorithm on an array, only one of below two cases might happen:

A. the first candidate’s counter never drops to zero through out the array, or;
B. the first candidate’s counter drops to zero at some point (reset point).

If A, then apparently this candidate is the majority;

If B, then (let’s say we have an array of n elements, and by the first time 
counter drops to zero we have gone through x elements so far):

    If the real majority element M never appeared in the subarray before the 
    reset point, then it will still be the majority in the remaining subarray 
    — do the algorithm again on remaining subarray;

    If the majority element M has appeared in the subarray before reset 
    point, then it must only have appeared up to x/2 times (because counter 
    is now zero). Thus in remaining subarray we have (n-x) elements 
    in total, of which at least (n/2 +1 – x/2) = (n-x)/2 +1 are M [to 
    be more precise, it's at least (floor(n/2) +1 - x/2) = floor((n-x)/2)+1 ], 
    making it still the majority in remaining subarray — do the 
    algorithm again on remaining subarray;

And there we have it like a recursive function. Note that this is when 
there IS a majority (more than half) in the array. When there's no majority, 
this process will give you a wrong candidate, that's why you always have to 
do a second pass to check.
    */
    int majorityElement(vector<int>& nums) {
        if(nums.empty()) return 0;

        int res = nums.front();
        int count = 1;
        int N = nums.size();
        
        // find candidate
        for(int i = 1; i < N; i++) {
            count += nums[i] == res ? 1: -1;
            if(count == 0) {
                res = nums[i];
                count = 1;
            }
        }

        // confirm that this a majority
        count = 0;
        for(auto num: nums) count += num == res;
        assert(count >= N/2);
        return res;
    }
};

class Solution2 {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> value_to_freq;
        int max_freq_value = nums.front();
        for(auto num: nums) {
            value_to_freq[num]++;
            if(value_to_freq[num] > value_to_freq[max_freq_value])
                max_freq_value = num;
        }
        return max_freq_value;
    }
};

int main() {
    Solution s;
    return 0;
}