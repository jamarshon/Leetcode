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

using namespace std;

class Solution {
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