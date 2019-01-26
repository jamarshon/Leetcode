/*
520. Detect Capital
Given a word, you need to judge whether the usage of capitals
in it is right or not.

We define the usage of capitals in a word to be right when one
of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than
one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a
right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase
and lowercase latin letters.

/*
    Submission Date: 2017-07-30
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool detectCapitalUse(string word) {
    int N = word.size();
    int capital_count = 0, lower_count = 0;
    for (auto c : word) {
      capital_count += isupper(c) != 0;
      lower_count += islower(c) != 0;
    }

    return capital_count == N || lower_count == N ||
           (capital_count == 1 && lower_count == N - 1 && isupper(word[0]));
  }
};

int main() { return 0; }