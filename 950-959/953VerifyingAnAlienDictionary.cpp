/*
953. Verifying an Alien Dictionary
In an alien language, surprisingly they also use english lowercase letters, but
possibly in a different order. The order of the alphabet is some permutation of
lowercase letters.

Given a sequence of words written in the alien language, and the order of the
alphabet, return true if and only if the given words are sorted lexicographicaly
in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is
sorted.

Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1],
hence the sequence is unsorted.

Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is
shorter (in size.) According to lexicographical rules "apple" > "app", because
'l' > '∅', where '∅' is defined as the blank character which is less than any
other character (More info).

Note:

  1 <= words.length <= 100
  1 <= words[i].length <= 20
  order.length == 26
  All characters in words[i] and order are english lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool less(const string& s1, const string& s2,
            unordered_map<char, int>& rank) {
    int i = 0;
    while (i < min(s1.size(), s2.size()) && s1[i] == s2[i]) i++;
    int r1 = i == s1.size() ? INT_MIN : rank[s1[i]];
    int r2 = i == s2.size() ? INT_MIN : rank[s2[i]];
    return r1 <= r2;
  }

  bool isAlienSorted(vector<string>& words, string order) {
    unordered_map<char, int> rank;
    for (int i = 0; i < order.size(); i++) rank[order[i]] = i;

    for (int i = 1; i < words.size(); i++) {
      if (!less(words[i - 1], words[i], rank)) return false;
    }

    return true;
  }
};

int main() { return 0; }
