/*
557. Reverse Words in a String III
Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.
/*
    Submission Date: 2018-05-31
    Runtime: 28 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    // from index 'start', find a space and reverse everything between start and space. change start to space + 1.
    string reverseWords(string s) {
        int start = 0;
        while(s.find(' ', start) != string::npos) {
            int space_ind = s.find(' ', start);
            reverse(s.begin() + start, s.begin() + space_ind);
            start = space_ind + 1;
        }
            
        reverse(s.begin() + start, s.end());
        return s;
    }
};

int main() {
    return 0;
}