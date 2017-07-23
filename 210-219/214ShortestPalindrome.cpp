/*
214. Shortest Palindrome
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

/*
    Submission Date: 2017-07-23
    Runtime: 56 ms
    Difficulty: HARD
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    string Manacher(string s) {
        const char kNullChar = '\0';
        string str = string(1, kNullChar);

        for(auto c: s) str += string(1, c) + kNullChar;

        string max_str = "";
        int len = str.size();
        int right = 0;
        int center = 0;
        vector<int> dp(len, 0);
        
        int start_right = -1;
        for(int i = 1; i < len; i++) {
            int mirr = 2*center - i;

            // i is within right so can take the minimum of the mirror or distance from right
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            // keep expanding around i while it is the same and increment P[i]
            int left_index = i - (1 + dp[i]);
            int right_index = i + (1 + dp[i]);
            while(left_index != -1 && right_index != len && str[left_index] == str[right_index]) {
                left_index--;
                right_index++;
                dp[i]++;
            }
            
            if(left_index == -1) {
                string item = str.substr(left_index + 1, right_index - left_index - 2);           
                if(item.size() > max_str.size()) {
                    start_right = right_index;
                    max_str = item;
                }
            }

            // i goes beyond current right so it is the new center
            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }
        
        string suffix = "";
        max_str.erase(remove_if(max_str.begin(), max_str.end(), [&kNullChar](char c){ return c == kNullChar; }), max_str.end());
        for(int k = start_right; k < len; k++) {
            if(str[k] != kNullChar) {
                suffix += str[k];
            }
        }
        
        string reversed = suffix;
        reverse(reversed.begin(), reversed.end());
        return reversed + max_str + suffix;
    }

    string shortestPalindrome(string s) {
        return Manacher(s);
    }

    string shortestPalindrome2(string s) {
        int N = s.size();
        for(int i = N - 1; i >= 0; i--) {
            bool decision = true;
            for(int j = 0; j < (i + 1)/2; j++) {
                if(s[j] != s[i - j]) {
                    decision = false;
                    break;
                }
            }
            
            if(decision) {
                string suffix = "";
                for(int j = i + 1; j < N; j++) suffix += s[j];
                string reversed = suffix;
                reverse(reversed.begin(), reversed.end());
                return reversed + s.substr(0, i + 1) + suffix;
            }
        }
        return "";
    }
};

int main() {
    Solution s;
    return 0;
}