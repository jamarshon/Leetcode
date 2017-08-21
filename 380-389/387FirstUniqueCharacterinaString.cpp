/*
387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return 
it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

/*
    Submission Date: 2017-08-21
    Runtime: 93 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char,int> letter_to_first_ind;
        set<int> st;
        for(int i = 0; i < s.size(); i++) {
            if(letter_to_first_ind.count(s[i])) { 
                // we've seen this letter before so we remove it from the set
                if(st.count(letter_to_first_ind[s[i]])) {
                    st.erase(letter_to_first_ind[s[i]]);
                }
            } else {
                letter_to_first_ind[s[i]] = i;
                st.insert(i);
            }
        }

        return st.empty() ? -1 : *st.begin();
    }
};

int main() {
    Solution s;
    return 0;
}