/*
5. Longest Palindromic Substring
Given a string S, find the longest palindromic substring in S. You may assume
that the maximum length of S is 1000, and there exists one unique longest
palindromic substring.
*/

/*
        Submission Date: 2016-11-29
        Runtime: 6 ms
        Difficulty: MEDIUM
*/

using namespace std;

#include <algorithm>
#include <vector>

class Solution {
 public:
  string longestPalindrome(string s) {
    const char kNullChar = '\0';
    string str = string(1, kNullChar);
    for (auto c : s) str += string(1, c) + kNullChar;

    int N = str.size();
    vector<int> dp(N, 0);
    int right = 0;
    int center = 0;

    string longest_palindrome = "";
    for (int i = 1; i < N; i++) {
      int mirror = 2 * center - i;
      if (i < right) {
        dp[i] = min(right - i, dp[mirror]);
      }

      int left_ind = i - (1 + dp[i]);
      int right_ind = i + (1 + dp[i]);
      while (left_ind >= 0 && right_ind < N &&
             str[left_ind] == str[right_ind]) {
        left_ind--;
        right_ind++;
        dp[i]++;
      }

      int pal_len = right_ind - left_ind - 1;
      if (pal_len > longest_palindrome.size()) {
        longest_palindrome = str.substr(left_ind + 1, pal_len);
      }

      if (i + dp[i] > right) {
        right = i + dp[i];
        center = i;
      }
    }

    auto it = remove_if(longest_palindrome.begin(), longest_palindrome.end(),
                        [&kNullChar](const char& c) { return c == kNullChar; });
    longest_palindrome.erase(it, longest_palindrome.end());
    return longest_palindrome;
  }
};

int main() { return 0; }