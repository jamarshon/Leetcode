/*
14. Longest Common Prefix
Write a function to find the longest common prefix string amongst an array of strings.

/*
    Submission Date: 2016-07-26
    Runtime: 6 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

class Solution {
public:
    tuple<string, int> longestCommonPrefix(string str1, string str2) {
    	int prefixLen = 0;
    	int len = min(str1.length(), str2.length());
    	for(int i = 0; i < len; i++) {
    		if(str1[i] == str2[i])
    			prefixLen++;
    		else
    			break;
    	}
    	return make_tuple(str1.substr(0, prefixLen), prefixLen);
    }
    string longestCommonPrefix(vector<string>& strs) {
        int currentLen;
    	string current;
    	
    	int minLength = 1000;
    	string lcp = "";
    	
    	int len = strs.size();
    	if(len == 0) return lcp;
    	if(len == 1) return strs[0];
    	
    	for(int i = 1; i < len; i++) {
    		tie(current, currentLen) = longestCommonPrefix(strs[i - 1], strs[i]);
    		if(currentLen < minLength) {
    			minLength = currentLen;
    			lcp = current;
    		}
    	}
    	return lcp;
    }
};