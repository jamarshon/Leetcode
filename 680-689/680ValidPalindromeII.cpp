/*
680. Valid Palindrome II
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
/*
    Submission Date: 2018-06-24
    Runtime: 129 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
public:
    /*
    dp[i][j] represents number of deletes to make a palindrome for string [i, j]
    */
    bool validPalindrome(string s) {
        int N = s.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        for(int gap = 1; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                dp[i][j] = s[i] == s[j] ? dp[i+1][j-1] : 1 + min(dp[i+1][j], dp[i][j-1]);
            }
        }
        
        return dp[0][N-1] <= 1;
    }
};

class Solution {
public:
    bool IsPalindrome(const string& s, int l, int r) {
        while(l < r) {
            if(s[l] == s[r]) {
                l++;
                r--;
            } else {
                return false;
            }
        }
        return true;
    }
    
    /*
    loop l and r until they do not match then check either if skipping l IsPalindrome(s, l+1, r)
    or skipping r IsPalindrome(s, l, r-1) will result in a palindrome
    */
    bool validPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;
        while(l < r) {
            if(s[l] == s[r]) {
                l++;
                r--;
            } else {
                return IsPalindrome(s, l+1, r) || IsPalindrome(s, l, r-1);
            }
        }
        return true;
    }
};

int main() {
    return 0;
}