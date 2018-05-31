/*
409. Longest Palindrome
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
/*
    Submission Date: 2018-05-30
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // return all the frequencies floored to nearest multiple of 2 and add one for if any of the frequency is odd
    int longestPalindrome(string s) {
        unordered_map<char, int> letter_to_freq;
        for(const auto& c: s) letter_to_freq[c]++;
        int res = 0;
        bool has_odd = false;
        
        for(const auto& kv: letter_to_freq) {
            res += (kv.second / 2)*2;
            has_odd |= kv.second % 2;
        }
        
        return res + has_odd;
    }
};

int main() {
    return 0;
}