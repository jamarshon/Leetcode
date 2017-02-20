/*
49. Group Anagrams

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 

Return:
    [
      ["ate", "eat","tea"],
      ["nat","tan"],
      ["bat"]
    ]

Note: All inputs will be in lower-case.

/*
    Submission Date: 2017-02-19
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    unordered_map<char, int> m = {{'a',2},{'b',3},{'c',5},{'d',7},{'e',11},{'f',13},{'g',17},{'h',19},{'i',23},{'j',29},{'k',31},{'l',37},{'m',41},{'n',43},{'o',47},{'p',53},{'q',59},{'r',61},{'s',67},{'t',71},{'u',73},{'v',79},{'w',83},{'x',89},{'y',97},{'z',101}};
    
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<int, vector<string>> groups;

        for(string str : strs) {
            int product = 1;
            for(char c: str) product *= m[c];
            unordered_map<int, vector<string>>::iterator i = groups.find(product);

            if(i == groups.end()) {
                groups[product] = {str};
            } else {
                (i -> second).push_back(str);
            }
        }

        vector<vector<string>> result;
        for(auto kv: groups) {
            result.push_back(kv.second);
        }
        
        return result;
    }
};



int main() {
    return 0;
}