/*
1189. Maximum Number of Balloons
Given a string text, you want to use the characters of text to form as many
instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of
instances that can be formed.

Example 1:

Input: text = "nlaebolko"
Output: 1

Example 2:

Input: text = "loonbalxballpoon"
Output: 2

Example 3:

Input: text = "leetcode"
Output: 0

Constraints:

  1 <= text.length <= 10^4
  text consists of lower case English letters only.
/*
  Submission Date: 2019-09-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  string target = "balloon";
  unordered_map<char, int> target_freq;

 public:
  Solution() {
    for (const auto& c : target) target_freq[c]++;
  }

  // count the frequency of chars in text and then
  // count the frequency of chars in target
  // for all the characters in target,
  // if it does not exist in text, then return 0
  // as a target letter is not present
  // else take the minimum of the frequency in the
  // text divide by the frequency in the target
  int maxNumberOfBalloons(string text) {
    unordered_map<char, int> freq;
    for (const auto& c : text) freq[c]++;
    int res = INT_MAX;
    for (const auto& c : target) {
      if (!freq.count(c)) return 0;
      res = min(res, freq[c] / target_freq[c]);
    }
    return res;
  }
};

int main() { return 0; }
