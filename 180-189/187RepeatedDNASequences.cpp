/*
187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify
repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that
occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<string, int> freq;
    for (int i = 0; i <= (int)s.size() - 10; i++) {
      string seq = s.substr(i, 10);
      freq[seq]++;
    }

    vector<string> res;
    for (auto kv : freq) {
      if (kv.second > 1) {
        res.push_back(kv.first);
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}