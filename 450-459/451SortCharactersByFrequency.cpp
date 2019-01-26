/*
451. Sort Characters By Frequency
Given a string, sort it in decreasing order based on the frequency of
characters.

Example 1:
Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid
answer.



Example 2:
Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.



Example 3:
Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

/*
    Submission Date: 2018-06-30
    Runtime: 201 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string frequencySort(string s) {
    unordered_map<char, int> letter_to_freq;
    for (const auto& c : s) letter_to_freq[c]++;
    sort(s.begin(), s.end(),
         [&letter_to_freq](const char& lhs, const char& rhs) {
           return letter_to_freq[lhs] == letter_to_freq[rhs]
                      ? lhs > rhs
                      : letter_to_freq[lhs] > letter_to_freq[rhs];
         });
    return s;
  }
};

int main() { return 0; }