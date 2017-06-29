/*
97. Interleaving String
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings 
recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

struct PairHash{
    size_t operator()(const pair<string, string>& p) const {
        hash<string> string_hash;
        return string_hash(p.first) ^ (string_hash(p.second) >> 1);
    }
};

class Solution {
    unordered_map<pair<string, string>, bool, PairHash> m;
public:
    bool isScramble(string s1, string s2) {
        pair<string, string> p{s1, s2};

        if(m.count(p)) return m[p];

        int N = s1.size();
        int M = s2.size();

        assert(M == N);
        if(N == 0) return true;
        if(N == 1) return s1 == s2;

        int freq[26] = {0};
        for(int i = 0; i < N; i++) {
            freq[s1[i] - 'a']++;
            freq[s2[i] - 'a']--;
        }

        for(int i = 0; i < 26; i++) {
            if(freq[i] != 0) return m[p] = false;
        }
        
        for(int i = 0; i < N-1; i++) {
            if(isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) && isScramble(s1.substr(i + 1), s2.substr(i + 1))) {
                return m[p] = true;
            }
            if(isScramble(s1.substr(N - i - 1), s2.substr(0, i + 1)) && isScramble(s1.substr(0, N - i - 1), s2.substr(i + 1))) {
                return m[p] = true;
            }
        }

        return m[p] = false;
    }
};

int main() {
    Solution s;
    return 0;
}