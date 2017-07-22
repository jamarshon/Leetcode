/*
28. Implement strStr()
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int hLen = haystack.size();
        int nLen = needle.size();
        if(nLen == 0) return 0;
        if(nLen == hLen) return haystack == needle ? 0 : -1;
        if(nLen > hLen) return -1;
        
        vector<int> start;
        int i = 0, j = 0;
        
        while(i < hLen) {
            if(haystack[i] == needle[0]) start.push_back(i);
            i++;
        }
        
        for(int index : start) {
            i = index;
            j = 0;
            while(i < hLen && j < nLen) {
                if(haystack[i] != needle[j]) break;
                i++;
                j++;
            }
            if(j == nLen) {
                return index;
            }
        }
        
        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}