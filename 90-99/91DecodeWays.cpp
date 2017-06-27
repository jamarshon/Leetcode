/*
91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, int> m;
public:
    int numDecodingsHelper(string s) {
        if(m.count(s)) return m[s];
        
        int len = s.size();
        if(len == 0) return 1;
        if(len == 1) return s[0] > '0';
        
        // length is at least 2
        int res = 0;
        if(s[0] > '0') {
            if(s[0] < '2' || (s[0] == '2' && s[1] <= '6')) {
                res += numDecodingsHelper(s.substr(2));
            }
            
            res += numDecodingsHelper(s.substr(1));
        }
        
        
        return m[s] = res;
    }

    int numDecodings(string s) {
        if(s.empty()) return 0;
        return numDecodingsHelper(s);
    }
};

int main() {
    Solution s;
    cout << s.numDecodings("12") << endl; // 2
    cout << s.numDecodings("17") << endl; // 2
    cout << s.numDecodings("1273") << endl; // 2
    cout << s.numDecodings("0") << endl; // 0
    return 0;
}