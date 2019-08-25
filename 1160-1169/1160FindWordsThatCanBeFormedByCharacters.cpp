/*
1160. Find Words That Can Be Formed by Characters
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each
character can only be used once).

Return the sum of lengths of all good strings in words.

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation:
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.

Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation:
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 =
10.

Note:

  1 <= words.length <= 1000
  1 <= words[i].length, chars.length <= 100
  All strings contain lowercase English letters only.
/*
  Submission Date: 2019-08-25
  Runtime: 172 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // count the frequency of letters in chars and
  // make sure the string has at most that many letters
  // and no unknown letters
  int countCharacters(vector<string>& words, string chars) {
    unordered_map<char, int> freqs;
    for (const auto& e : chars) freqs[e]++;
    int res = 0;
    for (const auto& s : words) {
      unordered_map<char, int> freqs_copy = freqs;
      bool ok = true;
      for (const auto& e : s) {
        if (!freqs_copy.count(e)) {
          ok = false;
          break;
        }
        freqs_copy[e]--;
        if (freqs_copy[e] == 0) freqs_copy.erase(e);
      }
      if (ok) res += s.size();
    }
    return res;
  }
};

int main() { return 0; }
