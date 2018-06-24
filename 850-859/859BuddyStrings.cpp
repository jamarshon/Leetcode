/*
859. Buddy Strings
Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool buddyStrings(string A, string B) {
        if(A.size() != B.size()) return false;
        
        vector<int> diff;
        for(int i = 0; i < A.size(); i++) {
            if(A[i] != B[i]) {
                diff.push_back(i);
                if(diff.size() > 2) return false;
            }
        }
        
        if(diff.size() == 1) return false;
        if(diff.size() == 0) return unordered_set<char>(A.begin(), A.end()).size() < A.size();
        return A[diff[0]] == B[diff[1]] && A[diff[1]] == B[diff[0]];
    }
};

int main() {
    return 0;
}