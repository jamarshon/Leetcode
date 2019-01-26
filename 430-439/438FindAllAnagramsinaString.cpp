/*
438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's
anagrams in s.

Strings consists of lowercase English letters only and the length of both
strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

/*
    Submission Date: 2017-08-06
    Runtime: 106 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    int M = s.size();
    int N = p.size();

    if (M < N) return res;
    unordered_map<char, int> freq, curr_freq;

    for (auto c : p) freq[c]++;

    for (int i = 0; i < N; i++) curr_freq[s[i]]++;

    int low = 0;
    int high = N;
    while (high <= M) {
      bool is_match = true;
      if (curr_freq.size() == freq.size()) {
        for (auto kv : freq) {
          if (curr_freq.count(kv.first) && curr_freq[kv.first] == kv.second)
            continue;
          is_match = false;
          break;
        }
      } else {
        is_match = false;
      }

      if (is_match) res.push_back(low);
      if (high == M) break;
      char to_erase = s[low++];
      curr_freq[s[high++]]++;
      if (curr_freq[to_erase] == 1)
        curr_freq.erase(to_erase);
      else
        curr_freq[to_erase]--;
    }

    return res;
  }
};

int main() { return 0; }