/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

/*
	Submission Date: 2016-07-09
	Runtime: 20ms
	Difficulty: EASY
*/
using namespace std;
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../UtilityHelper.hpp"

class Solution {
	private:
		// An unordered map is a hash table with a look up time of O(1)
		// The key is the number that was seen already and the value is the index
		// if the value is -1, then it means it has been used already
		unordered_map <int, int> hashTable; 
	public:
		// Assumes numbers in nums is unqiue
	    vector<int> twoSum(vector<int> nums, int target) {
	    	int complement, currentElement, complementIndex;
	    	vector<int> result;

	        for(int i = 0, len = nums.size(); i < len; i++) {
	        	currentElement = nums[i];
	        	complement = target - currentElement;

	        	// Checks to see if the complement has already been seen
	        	if (hashTable.find(complement) != hashTable.end()) {
	        		// The element has only been seen once
	        		complementIndex = hashTable[complement];
	        		if(complementIndex >= 0) {
	        			result.push_back(complementIndex);
	        			result.push_back(i);
	        			hashTable[complement] = -1;
	        		}
	        	}

	        	hashTable[currentElement] = i;
	        }

	        hashTable.clear();
	        return result;
	    }
};

////////////////////TestCases////////////////////////////////////////
int main() {
	Solution s;
	UtilityHelper<int, int> util;

	vector<vector<int>> inputs = {
		{2, 7, 11, 15},
		{-3, 4, 3, 90}
	};
	vector<vector<int>> outputs = {
		{0, 1},
		{0, 2}
	};

	vector<function< vector<int>(vector<int>) >> funcs = {
		bind(&Solution::twoSum, &s, placeholders::_1, 9),
		bind(&Solution::twoSum, &s, placeholders::_1, 0)
	};

	util.run(inputs, outputs, funcs);
}