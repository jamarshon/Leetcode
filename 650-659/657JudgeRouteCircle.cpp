/*
657. Judge Route Circle
Initially, there is a Robot at position (0, 0). Given a sequence of its moves, judge if this robot makes 
a circle, which means it moves back to the original place.

The move sequence is represented by a string. And each move is represent by a character. The valid robot moves are 
R (Right), L (Left), U (Up) and D (down). The output should be true or false representing whether the robot makes a circle.

Example 1:
Input: "UD"
Output: true
Example 2:
Input: "LL"
Output: false
/*
    Submission Date: 2018-05-31
    Runtime: 43 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    unordered_map<char, vector<int>> m_{
        {'U', {0,1}},
        {'D', {0,-1}},
        {'L', {-1,0}},
        {'R', {1,0}},
    };
public:
    bool judgeCircle(string moves) {
        int x = 0;
        int y = 0;
        for(const auto& c: moves) {
            x += m_[c][0];
            y += m_[c][1];
        }
        return x == 0 && y == 0;
    }
};

int main() {
    return 0;
}