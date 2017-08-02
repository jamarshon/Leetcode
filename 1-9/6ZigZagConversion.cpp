/*
6. ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

/*
    Submission Date: 2016-11-30
    Runtime: 16 ms
    Difficulty: EASY
*/
using namespace std;

#include <iostream>
#include <string>

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1){ return s; }
        
        string result = "";
        int len = s.length();
        int distBtwnCol = 2 * numRows - 2;
        for(int i = 0; i < numRows; i++) {
            int secondJumpDist = 2*i;
            int firstJumpDist = distBtwnCol - secondJumpDist;
            
            if(firstJumpDist == 0 || secondJumpDist == 0){ 
                firstJumpDist = secondJumpDist = distBtwnCol;
            }
            
            int j = i;
            bool jumpToggle = true;
            while(j < len) {
                result += s[j];
                if(jumpToggle) {
                    j += firstJumpDist;
                } else {
                    j += secondJumpDist;
                }
                jumpToggle = !jumpToggle;
            }
        }
        
        return result;
    }
};

int main(){
    Solution s;
    s.convert("PAYPALISHIRING", 3);
    return 0;
}