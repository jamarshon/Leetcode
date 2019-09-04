/*
1002. Find Common Characters
Given an array A of strings made only from lowercase letters, return a list of
all characters that show up in all strings within the list (including
duplicates).  For example, if a character occurs 3 times in all strings but not
4 times, you need to include that character three times in the final answer.

You may return the answer in any order.

Example 1:

Input: ["bella","label","roller"]
Output: ["e","l","l"]

Example 2:

Input: ["cool","lock","cook"]
Output: ["c","o"]

Note:

  1 <= A.length <= 100
  1 <= A[i].length <= 100
  A[i][j] is a lowercase letter
/*
  Submission Date: 2019-09-03
  Runtime: 28 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> commonChars(vector<string>& A) {
    // get the min occurence of each letter for each string
    // include missing characters so that the min
    // occurence would be zero making it not show in the
    // output
    vector<int> cnt(26, INT_MAX);
    for (const auto& s : A) {
      vector<int> cnt1(26, 0);
      for (const auto& c : s) cnt1[c - 'a']++;
      for (int i = 0; i < 26; i++) cnt[i] = min(cnt[i], cnt1[i]);
    }

    vector<string> res;
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < cnt[i]; j++) res.push_back(string(1, i + 'a'));
    }
    return res;
  }
};

class Solution2 {
 public:
  vector<string> commonChars(vector<string>& A) {
    // count how many strings has a certain letter in
    // `freq_cnt`. count the minimum frequency of a
    // letter in `min_freq_cnt`
    unordered_map<char, int> freq_cnt, min_freq_cnt;
    for (const auto& s : A) {
      unordered_map<char, int> s_freq;
      for (const auto& c : s) s_freq[c]++;
      for (const auto& kv : s_freq) {
        freq_cnt[kv.first]++;
        if (!min_freq_cnt.count(kv.first)) {
          min_freq_cnt[kv.first] = kv.second;
        } else {
          min_freq_cnt[kv.first] = min(min_freq_cnt[kv.first], kv.second);
        }
      }
    }

    vector<string> res;
    for (const auto& kv : freq_cnt) {
      // if the letter does not appear in every string skip it
      if (kv.second != A.size()) continue;
      // repeat the min occurences of the letter in the result
      int occurences = min_freq_cnt[kv.first];
      for (int i = 0; i < occurences; i++) res.push_back(string(1, kv.first));
    }
    return res;
  }
};

int main() { return 0; }
