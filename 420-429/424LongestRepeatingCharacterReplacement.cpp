/*
424. Longest Repeating Character Replacement
Given a string that consists of only uppercase English letters, you can replace 
any letter in the string with another letter at most k times. Find the length of 
a longest substring containing all repeating letters you can get after 
performing the above operations. 

Note:
Both the string's length and k will not exceed 104.



Example 1:
Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.




Example 2:
Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
/*
    Submission Date: 2018-07-15
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /*
    find the longest substring where there are k characters that are not the main character
    use sliding window and keep track of frequency of characters in window,
    end - start + 1 - max_occurence > k means too many characters that are not the main
    character so shift start and end by 1. this keeps the size of the window always
    increasing as looking at smaller windows will not change the result.
    
    max_occurence will also always increase as suppose max_occurence is > actual
    max_occurence in the window then this window will not be part of the result as the number
    of not main characters will actually be higher than calculated. only when max_occurence
    updates can the window be extended/result updated.
    */
    int characterReplacement(string s, int k) {
        unordered_map<char,int> freq;
        int start = 0;
        int max_occurence = 0;
        for(int end = 0; end < s.size(); end++) {
            max_occurence = max(max_occurence, ++freq[s[end] - 'A']);
            if(end - start + 1 - max_occurence > k) {
                freq[s[start++] - 'A']--;
            }
        }
        
        return s.size() - start;
    }
};

int main() {
    return 0;
}
