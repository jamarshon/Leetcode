/*
819. Most Common Word
Given a paragraph and a list of banned words, return the most frequent word that
is not in the list of banned words. It is guaranteed there is at least one word
that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of
punctuation.  Words in the paragraph are not case sensitive. The answer is in
lowercase.

Example:
Input:
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
Output: "ball"
Explanation:
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent
non-banned word in the paragraph. Note that words in the paragraph are not case
sensitive, that punctuation is ignored (even if adjacent to words, such as
"ball,"), and that "hit" isn't the answer even though it occurs more because it
is banned.
 

Note:

1 <= paragraph.length <= 1000.
1 <= banned.length <= 100.
1 <= banned[i].length <= 10.
The answer is unique, and written in lowercase (even if its occurrences in
paragraph may have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
Different words in paragraph are always separated by a space.
There are no hyphens or hyphenated words.
Words only consist of letters, never apostrophes or other punctuation symbols.
/*
    Submission Date: 2018-06-04
    Runtime:  ms
    Difficulty:
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  string mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_set<string> banned_set(banned.begin(), banned.end());
    unordered_map<string, int> freq;

    stringstream ss(paragraph);
    string temp;

    string res = "";
    while (getline(ss, temp, ' ')) {
      for (int i = 0; i < temp.size(); i++) temp[i] = tolower(temp[i]);
      while (!temp.empty() && !isalpha(temp.back())) temp.pop_back();
      if (banned_set.count(temp)) continue;
      freq[temp]++;
      if (res.empty() || freq[res] < freq[temp]) res = temp;
    }

    return res;
  }
};

int main() { return 0; }