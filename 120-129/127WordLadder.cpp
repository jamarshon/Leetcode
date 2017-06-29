/*
127. Word Ladder
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest 
transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-06-28
    Runtime: 1449 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
    bool differByOneLetter(string s1, string s2) {
        int len = s1.size();
        bool seen_different = false;
        for(int i = 0; i < len; i++) {
            if(s1[i] != s2[i]) {
                if(seen_different) return false;
                seen_different = true;
            }
        }
        return true;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, unordered_set<string>> adj;
        unordered_set<string> distinct(wordList.begin(), wordList.end());

        if(!distinct.count(endWord)) return 0;
        distinct.insert(beginWord);

        for(auto word_it = distinct.begin(); word_it != distinct.end(); word_it++) {
            for(auto match_word_it = next(word_it); match_word_it != distinct.end(); match_word_it++) {

                string word = *word_it;
                string match_word = *match_word_it;

                if(differByOneLetter(word, match_word)) {
                    adj[word].insert(match_word);
                    adj[match_word].insert(word);
                }
            }
        }

        queue<pair<string, int>> to_do({{beginWord, 1}});
        unordered_set<string> visited{{beginWord}};
        unordered_map<string, string> parent;

        string curr_word;
        int curr_dist;
        while(!to_do.empty()) {
            pair<string, int> curr = to_do.front();
            tie(curr_word, curr_dist) = curr;

            to_do.pop();
            if(curr_word == endWord) {
                string temp = endWord;
                // while(temp != beginWord) {
                //     cout << temp << endl;
                //     temp = parent[temp];
                // }
                return curr_dist;
            }

            unordered_set<string> neighbors = adj[curr_word];
            for(auto neighbor: neighbors) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr_dist + 1);
                parent[neighbor] = curr_word;
                visited.insert(neighbor);
            }
            
        }

        return 0;
    }
};

int main() {
    Solution s;
    return 0;
}