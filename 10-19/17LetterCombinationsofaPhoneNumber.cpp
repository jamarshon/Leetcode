/*
17. Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

/*
    Submission Date: 2016-11-29
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;

#include <unordered_map>
class Solution {
private:
    unordered_map<char, vector<char>> LETTER_DIGIT_MAP = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };
public:
    vector<string> letterCombinations(string digits) {
        if(digits == ""){ return {}; }
        vector<string> result = {""};
        for(char digit : digits) {
            vector<char> letters = LETTER_DIGIT_MAP[digit];
            vector<string> temp = {};
            for(char letter : letters) {
                for(string str: result) {
             		temp.push_back(str + letter);
             	}
            }
            result = temp;
        }
        return result;
    }
};