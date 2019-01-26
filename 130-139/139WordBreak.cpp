/*
139. Word Break
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, determine if s can be segmented into a space-separated sequence
of one or more dictionary words. You may assume the dictionary does not contain
duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<string, bool> memo;

 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    if (s.empty()) return true;

    if (memo.count(s)) return memo[s];

    for (string word : wordDict) {
      int word_len = word.size();
      string prefix = s.substr(0, word_len);
      if (prefix == word) {
        // we can take this word
        if (wordBreak(s.substr(word_len), wordDict)) {
          return memo[s] = true;
        }
      }
    }

    return memo[s] = false;
  }
};

int main() {
  Solution s;
  return 0;
}