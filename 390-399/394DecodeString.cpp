/*
394. Decode String
Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
/*
    Submission Date: 2018-05-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        find a '[', use count to determine the matching ']'. recursively determine the string in between.
        find the number beside '[' and repeat the string in between that many times. look for '[' and repeat
        until there is no more '[', then just add the suffix.
    */
    string decodeString(string s) {
        int start = 0;
        
        string res = "";
        while(s.find('[', start) != string::npos) {
            int bracket_index = s.find('[', start);
        
            int num_index = bracket_index - 1;
            while(num_index >= 0 && isdigit(s[num_index])) {
                num_index--;
            }

            res += s.substr(start, num_index + 1 - start);
            
            int num = stoi(s.substr(num_index + 1, bracket_index - num_index - 1));
            int cnt = 0;
            for(int i = bracket_index; i < s.size(); i++) {
                cnt += s[i] == '[';            
                cnt -= s[i] == ']';
                if(cnt == 0) {
                    string to_repeat = decodeString(s.substr(bracket_index + 1, i - bracket_index - 1));
                    for(int j = 0; j < num; j++) {
                        res += to_repeat;
                    }
                    start = i + 1;
                    break;
                }
            }
        }
        
        return res + s.substr(start);
    }
};

int main() {
    return 0;
}