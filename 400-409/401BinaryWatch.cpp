/*
401. Binary Watch
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
/*
    Submission Date: 2018-06-08
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    int NumBits(int x) {
        int res = 0;
        while(x) {
            x &= (x-1);
            res++;
        }
        
        return res;
    }
public:
    /*
    map with key being number of bits and value being the number
    for each hour, get the number of bits and then lookup the remaining
    number of bits needed
    */
    vector<string> readBinaryWatch(int num) {
        unordered_map<int, vector<string>> m;
        for(int i = 0; i < 60; i++) 
            m[NumBits(i)].push_back((i < 10 ? ":0" : ":") + to_string(i));
        
        vector<string> res;
        for(int i = 0; i < 12; i++) {
            int target = num - NumBits(i);
            if(!m.count(target)) continue;
            for(const auto& e: m[target])
                res.push_back(to_string(i) + e);
        }
        return res;
    }
};

int main() {
    return 0;
}