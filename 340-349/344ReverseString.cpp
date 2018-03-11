/*
344. Reverse String
Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".
/*
    Submission Date: 2017-03-11
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string reverseString(string s) {
        int N = s.size();
        for(int i = 0; i < N/2; i++) {
            swap(s[i], s[N-i-1]);
        }
        return s;
    }
};

int main() {
    return 0;
}