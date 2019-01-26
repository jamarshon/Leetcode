/*
318. Maximum Product of Word Lengths
Given a string array words, find the maximum value of
length(word[i]) * length(word[j]) where the two words do not
share common letters. You may assume that each word will contain
only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
/*
    Submission Date: 2017-08-26
    Runtime: 42 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(vector<string>& words) {
    int res = 0;
    int N = words.size();

    // dp[i] is the bit representation of words[i] where bit at index i
    // corresponds with the ith letter of [a,b,c,...] that is in words[i] e.g
    // abcf would 0...100111

    vector<int> dp(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0, word_len = words[i].size(); j < word_len; j++) {
        dp[i] |= 1 << (words[i][j] - 'a');
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if ((dp[i] & dp[j]) == 0) {  // no intersection
          res = max(res, int(words[i].size() * words[j].size()));
        }
      }
    }

    return res;
  }
};

class Solution2 {
 public:
  int maxProduct(vector<string>& words) {
    int res = 0;
    int N = words.size();
    for (int i = 0; i < N; i++) {
      unordered_set<char> word_i(words[i].begin(), words[i].end());
      for (int j = i + 1; j < N; j++) {
        bool intersect = false;
        for (int k = 0; k < words[j].size(); k++) {
          if (word_i.count(words[j][k])) {
            intersect = true;
            break;
          }
        }

        if (intersect) continue;
        int pos_res = words[i].size() * words[j].size();
        res = max(res, pos_res);
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}