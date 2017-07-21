/*
140. Word Break II
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces 
in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary 
does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-20
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

class Solution {
public:
    void convertLenToStr(int i, string s, string curr, vector<vector<int>>& dp, vector<string>& res) {
        if(i == s.size()) {
            res.push_back(curr);
            return;
        }

        for(const int word_size: dp[i]) {
            string word = s.substr(i, word_size);
            string new_curr = curr.empty() ? word : curr + " " + word;
            convertLenToStr(i + word_size, s, new_curr, dp, res);
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int N = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        set<int> word_sizes;

        for(const string word: dict) 
            word_sizes.insert(word.size());

        vector<vector<int>> dp(N + 1, vector<int>{});
        dp[N].push_back(INT_MAX);

        for(int j = N; j >= 0; j--) {
            if(dp[j].empty()) continue;
            for(const int word_size: word_sizes) {
                if(j - word_size < 0) break;
                string word = s.substr(j - word_size, word_size);
                // we store at dp[j-word_size] the word_size if it is a valid word and it ends at a valid index 
                // meaning dp[j] isn't empty
                if(dict.count(word)) {
                    dp[j - word_size].push_back(word_size);
                }
            }
        }

        vector<string> res;
        convertLenToStr(0, s, "", dp, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}