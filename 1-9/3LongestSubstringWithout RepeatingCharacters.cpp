/*
3. Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, 
"pwke" is a subsequence and not a substring.
*/

/*
	Submission Date: 2016-07-10
	Runtime: 116 ms
	Difficulty: MEDIUM
*/

using namespace std;
#include "../UtilityHelper.hpp"

#include <unordered_map>
#include <algorithm>

class Solution {
	private:
		// key is the letter that has been seen and value is its indexes in the string
		unordered_map <string, vector<int>> hashTable; 
	public:
	    int lengthOfLongestSubstring(string s) {
	    	string startLetter, lastLetter;
	    	vector<int> indices;

	    	int currentLen;

	    	string longestSubstring; // not returned only for debugging purpose
	    	int longestSubstrLen = 0,
	    		longestSubstrStartInd = 0;

	    	int startIndex = 0,
	    		endIndex = 0,
	    		len = s.length();
	    	
	    	while(endIndex != len) {
	    		lastLetter = s[endIndex];
	    		
	    		// if the letter has been seen already then find the new startIndex
	    		// it should be the largest of the already seen indexes of that letter
	    		// which will always be the last element of the vector
	    		if (hashTable.find(lastLetter) != hashTable.end()) {
	    			indices = hashTable[lastLetter];
	        		startIndex = max(indices[indices.size() - 1] + 1, startIndex);
	        	}

	        	currentLen = endIndex - startIndex + 1;
	    		// cout << "Longest Substring is: " << s.substr(startIndex, currentLen) << endl;
	        	if(currentLen > longestSubstrLen) {
	        		longestSubstrStartInd = startIndex;
	        		longestSubstrLen = currentLen;
	        	}
	        	hashTable[lastLetter].push_back(endIndex);
	        	endIndex++;
	    	}
	    	
	    	longestSubstring = s.substr(longestSubstrStartInd, longestSubstrLen);
	    	cout << "Longest Substring is: " << longestSubstring << endl;
	    	hashTable.clear();
	        return longestSubstring.length();
	    }
};

int main() {
	Solution s;
	UtilityHelper<string, int> util;
	vector<string> inputs = {
		"abcabcbb", // testcase 1
		"bbbbb", // testcase 2
		"pwwkew", // testcase 3
		"", // testcase 4
		"abba", // testcase 5
		"tmmzuxt", // testcase 6
	};
	vector<string> printables = {
		"abc", // testcase 1
		"b", // testcase 2
		"wke", // testcase 3
		"", // testcase 4
		"ba", // testcase 5
		"mzuxt", // testcase 6
	};
	vector<int> outputs = {
		3, // testcase 1
		1, // testcase 2
		3, // testcase 3
		0, // testcase 4
		2, // testcase 5
		5, // testcase 5
	};

	function<int(string)> func = bind(&Solution::lengthOfLongestSubstring, &s, placeholders::_1);
	util.run(inputs, outputs, printables, func);
	//s.lengthOfLongestSubstring("tmmzuxt");
	return 0;
}