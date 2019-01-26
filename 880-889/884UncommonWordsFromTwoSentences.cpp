/*
884. Uncommon Words from Two Sentences
We are given two sentences A and B.  (A sentence is a string of space separated
words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does
not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]

Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]

Note:

  0 <= A.length <= 200
  0 <= B.length <= 200
  A and B both contain only spaces and lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> uncommonFromSentences(string A, string B) {
    unordered_map<string, int> freq;
    stringstream ssA(A), ssB(B);
    string temp;

    while (ssA >> temp) freq[temp]++;
    while (ssB >> temp) freq[temp]++;

    vector<string> res;
    for (const auto& kv : freq)
      if (kv.second == 1) res.push_back(kv.first);

    return res;
  }
};

int main() { return 0; }
