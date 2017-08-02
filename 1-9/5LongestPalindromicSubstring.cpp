/*
5. Longest Palindromic Substring
Given a string S, find the longest palindromic substring in S. You may assume 
that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/

/*
	Submission Date: 2016-11-29
	Runtime: 106 ms
	Difficulty: MEDIUM
*/

using namespace std;

#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cstring>

class Solution {
public:
    string convertToFormat(string s) {
        string retStr;
        for(int i = 0, len = s.length(); i < len; i++) {
            retStr += s[i] + string("#");
        }
        return "$#" + retStr + "@";
    }
    string longestPalindrome(string s) {
        string str = convertToFormat(s);
        int len = str.length();
        int P[len];
        
        fill(P, P + len, 0);
        int R = 0, C = 0;

        int maxLen = 0;
        string maxStr;
        for(int i = 1; i < len; i++) {
            int mirror = 2 * C - i;
            if(i < R) {
                P[i] = min(R - i, P[mirror]);
            }
            
            while(str[i + (1 + P[i])] == str[i - (1 + P[i])]) {
                P[i]++;
            }
            if(P[i] > maxLen) {
                maxLen = P[i];
                maxStr = str.substr(i - maxLen, 2 * maxLen + 1);
            }
            
            if(i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }

        maxStr.erase(remove(maxStr.begin(), maxStr.end(), '#'), maxStr.end());
        return maxStr;
    }
};

int main() {
    return 0;
}