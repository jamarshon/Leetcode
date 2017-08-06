/*
242. Valid Anagram
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

/*
    Submission Date: 2017-08-06
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        
        unordered_map<char, int> s_freq, t_freq;
        for(int i = 0, len = s.size(); i < len; i++) {
            s_freq[s[i]]++;
            t_freq[t[i]]++;
        }
        
        if(s_freq.size() != t_freq.size()) return false;
        for(auto kv: s_freq) {
            if(t_freq.count(kv.first) && t_freq[kv.first] == kv.second) continue;
            return false;
        }
        return true;
    }
};

int main() {
    return 0;
}