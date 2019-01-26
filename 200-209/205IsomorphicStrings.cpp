/*
205. Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while
preserving the order of characters. No two characters may map to the same
character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

/*
    Submission Date: 2017-08-01
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    int N = s.size();
    unordered_map<char, char> hash_map;
    unordered_set<char> mapped;
    for (int i = 0; i < N; i++) {
      if (hash_map.count(s[i])) {
        if (t[i] != hash_map[s[i]]) {
          return false;
        }
      } else {
        if (mapped.count(t[i])) return false;
        hash_map[s[i]] = t[i];
        mapped.insert(t[i]);
      }
    }
    return true;
  }
};

int main() { return 0; }