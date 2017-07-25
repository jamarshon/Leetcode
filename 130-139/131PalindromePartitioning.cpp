/*
131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

/*
    Submission Date: 2017-07-24
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void generate(vector<int>& dp, string str, vector<string>& temp, int index, vector<vector<string>>& res) {
        if(index == str.size() - 1) {
            const char kNullChar = '\0';
            vector<string> temp_copy(temp.size());
            transform(temp.begin(), temp.end(), temp_copy.begin(), [&kNullChar](string s){
                s.erase(remove_if(s.begin(), s.end(), [&kNullChar](const char& c){ return c == kNullChar; }), s.end());
                return s;
            });
            res.push_back(temp_copy);
            return;
        }
        for(int i = index + 1; i < str.size(); i++) {
            if(dp[i] > 0) {
                if(i - dp[i] <= index) { // the palindrome extends to or past our current word so we can take a substring of it
                    int end = i - index;
                    string sub = str.substr(index, 2*end); // includes null at front but not back
                    temp.push_back(sub);
                    // index + sub.size() is the null behind sub
                    generate(dp, str, temp, index + sub.size(), res); 
                    temp.pop_back();
                }
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;

        const char kNullChar = '\0';

        string str = string(1, kNullChar);
        for(auto c: s) str += string(1,c) + kNullChar;

        int N = str.size();
        vector<int> dp(N, 0);
        int right = 0;
        int center = 0;

        for(int i = 1; i < N; i++) {
            int mirr = 2*center - i;
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            int left = i - (1 + dp[i]);
            int right = i + (1 + dp[i]);

            while(left >= 0 && right < N && str[left] == str[right]) {
                left--;
                right++;
                dp[i]++;
            }

            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }

        vector<string> temp;
        generate(dp, str, temp, 0, res);
        return res;
    }
};

int main() {
    return 0;
}