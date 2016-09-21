/*
5. Longest Palindromic Substring
Given a string S, find the longest palindromic substring in S. You may assume 
that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/

/*
	Submission Date: 2016-07-X
	Runtime: X ms
	Difficulty: MEDIUM
*/

using namespace std;
#include <algorithm>
#include "../UtilityHelper.hpp"
class Solution {
public:
    string longestPalindrome(string s) {
        string lp, lpLen, cp, cpLen;
        for(int i = 0, len = s.length(); i < len; i++) {
            cp = longestPalindromeAt(s, i);
            cpLen = cp.length();
            if(cpLen > lpLen) {
                lp = cp;
                lpLen = cpLen;
            }
        }
        return lp;
    }

    string longestPalindromeAt(string s, int i) {
        string subString;
        for(int j = s.length(); j > i; j--) {
            subString = s.substr(i, j - i);
            if(isPalindrome(subString)) {
                return subString;
            }
        }
        return subString;
    }

    bool isPalindrome(string s) {
        string reversed = s;
        reverse(reversed.begin(), reversed.end());
        return s == reversed;
    }
};

///////////////////TestCases////////////////////////////////////////
int main() {
	Solution s;
    UtilityHelper<string, string> util;
    double output, result;

    vector<string> inputs = {
        "jasonracecar",
    };
    vector<string> outputs = {
        "test",
    };

    function<string(string)> func = bind(&Solution::longestPalindrome, &s, placeholders::_1);
    util.run(inputs, outputs, func);
    return 0;
}