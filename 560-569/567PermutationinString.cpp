/*
567. Permutation in String
Given two strings s1 and s2, write a function to return true if s2 contains the
permutation of s1. In other words, one of the first string's permutations is the
substring of the second string. Example 1: Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
/*
    Submission Date: 2018-06-02
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  frequency map of s1 with variable to_use as global to check if everything
  equals 0 use sliding window where everything in a window is a valid character
  and does not exceed the frequency map limit for certain character for a new
  character, if it exceeds the limit or its not a valid character than keep
  moving front (restoring freq map). if it is not a valid character, the map
  will be restored and to_do = original Check if character is valid, if it is
  use it else move front so that it is not included
  */
  bool checkInclusion(string s1, string s2) {
    vector<int> freq(26, 0);
    unordered_set<char> letters(s1.begin(), s1.end());
    for (const auto& c : s1) freq[c - 'a']++;

    int front = 0;
    int back = 0;

    int N = s2.size();
    int to_use = s1.size();

    while (back < N) {
      if (to_use == 0) return true;
      // slide the front until the letter is removed
      int back_val = s2[back] - 'a';
      while (front < back && freq[back_val] == 0) {
        freq[s2[front] - 'a']++;
        front++;
        to_use++;
      }

      /* if the back letter is in s1, decrease the frequency and to_use
          else it means front == back as freq[s2[back]] == 0 so increase front
          to not include this letter
      */
      if (letters.count(s2[back])) {
        freq[back_val]--;
        to_use--;
      } else {
        front++;
      }

      back++;
    }

    return to_use == 0;
  }
};

int main() { return 0; }