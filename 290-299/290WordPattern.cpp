/*
290. Word Pattern
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a 
letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains 
lowercase letters separated by a single space.
/*
    Submission Date: 2017-09-10
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char,string> letter_to_word;
        unordered_map<string,char> word_to_letter;
        
        stringstream ss(str);
        string word;
        
        int i = 0, N = pattern.size();
        while(i < N) {
            ss >> word;
            if(word.empty()) return false;
            if(letter_to_word.count(pattern[i]) || word_to_letter.count(word)) {
                if(word_to_letter[word] != pattern[i] || letter_to_word[pattern[i]] != word) return false;
            } else {
                letter_to_word[pattern[i]] = word;
                word_to_letter[word] = pattern[i];
            }
            i++;
        }
        
        bool rem = (bool)(ss >> word);
        return !rem;
    }
};

int main() {
    return 0;
}