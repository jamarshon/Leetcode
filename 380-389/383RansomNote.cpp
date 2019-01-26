/*
383. Ransom Note
Given an arbitrary ransom note string and another string containing letters from
all the magazines, write a function that will return true if the ransom note can
be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
/*
    Submission Date: 2018-05-02
    Runtime: 34 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> m;
    for (auto e : magazine) m[e]++;
    for (auto e : ransomNote) {
      if (m.count(e)) {
        if (m[e] == 0) return false;
        m[e]--;
      } else {
        return false;
      }
    }
    return true;
  }
};

int main() { return 0; }