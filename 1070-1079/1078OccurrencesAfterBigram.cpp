/*
1078. Occurrences After Bigram
Given words first and second, consider occurrences in some text of the form
"first second third", where second comes immediately after first, and third
comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second
= "good"
Output: ["girl","student"]

Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]

Note:

  1 <= text.length <= 1000
  text consists of space separated words, where each word consists of lowercase
English letters.
  1 <= first.length, second.length <= 10
  first and second consist of lowercase English letters.
/*
  Submission Date: 2019-09-04
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  // store the last two words and return the current word
  // if the last two words match `first`, `second`
  vector<string> findOcurrences(string text, string first, string second) {
    vector<string> res;
    stringstream ss(text);
    string token;
    string last, lastlast;
    while (ss >> token) {
      if (lastlast.empty()) {
        lastlast = token;
      } else if (last.empty()) {
        last = token;
      } else {
        if (lastlast == first && last == second) {
          res.push_back(token);
        }
        lastlast = last;
        last = token;
      }
    }
    return res;
  }
};

int main() { return 0; }
