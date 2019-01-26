/*
3. Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating
characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
must be a substring, "pwke" is a subsequence and not a substring.
*/

/*
        Submission Date: 2016-07-10
        Runtime: 116 ms
        Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 private:
  // key is the letter that has been seen and value is its indexes in the string
  unordered_map<string, vector<int>> hashTable;

 public:
  int lengthOfLongestSubstring(string s) {
    string startLetter, lastLetter;
    vector<int> indices;

    int currentLen;

    string longestSubstring;  // not returned only for debugging purpose
    int longestSubstrLen = 0, longestSubstrStartInd = 0;

    int startIndex = 0, endIndex = 0, len = s.length();

    while (endIndex != len) {
      lastLetter = s[endIndex];

      // if the letter has been seen already then find the new startIndex
      // it should be the largest of the already seen indexes of that letter
      // which will always be the last element of the vector
      if (hashTable.find(lastLetter) != hashTable.end()) {
        indices = hashTable[lastLetter];
        startIndex = max(indices[indices.size() - 1] + 1, startIndex);
      }

      currentLen = endIndex - startIndex + 1;
      if (currentLen > longestSubstrLen) {
        longestSubstrStartInd = startIndex;
        longestSubstrLen = currentLen;
      }
      hashTable[lastLetter].push_back(endIndex);
      endIndex++;
    }

    longestSubstring = s.substr(longestSubstrStartInd, longestSubstrLen);
    hashTable.clear();
    return longestSubstring.length();
  }
};

int main() { return 0; }