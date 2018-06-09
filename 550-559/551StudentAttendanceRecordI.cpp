/*
551. Student Attendance Record I
You are given a string representing an attendance record for a student. The record only contains the following three characters:
'A' : Absent.
'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False
/*
    Submission Date: 2018-06-08
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool checkRecord(string s) {
        int l_streak = 0;
        bool seen_absent = false;
        for(const auto& c: s) {
            if(c == 'L') {
                if(l_streak == 2) return false;
                l_streak++;
            } else {
                if(c == 'A') {
                    if(seen_absent) return false;
                    seen_absent = true;
                } // c == 'P'
                
                l_streak = 0;
            }
        }
        return true;
    }
};

int main() {
    return 0;
}