/*
126. Word Ladder II
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation 
sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please 
reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-21
    Runtime: 712 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

struct QueueItem {
    string vertex;
    vector<int> path;
    QueueItem(string _vertex, vector<int> _path=vector<int>{}): vertex(_vertex), path(_path) {}
};

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, vector<string>> vertex_to_edges;

        wordList.push_back(beginWord);

        int N = wordList.size();
        int word_len = beginWord.size();

        unordered_map<string, int> vertex_to_index;

        for(int i = 0; i < N; i++) {
            vertex_to_index[wordList[i]] = i;

            if(wordList[i] == beginWord && i != N - 1) continue;
            for(int j = i + 1; j < N; j++) {
                if(wordList[j] == beginWord && j != N - 1) continue;

                bool seen_different = false;
                bool can_add = true;
                for(int k = 0; k < word_len; k++) {
                    if(wordList[i][k] != wordList[j][k]) {
                        if(seen_different) {
                            can_add = false;
                            break;
                        }
                        seen_different = true;
                    }
                }

                if(can_add) {
                    vertex_to_edges[wordList[i]].push_back(wordList[j]);
                    vertex_to_edges[wordList[j]].push_back(wordList[i]);
                }
            }
        }

        queue<QueueItem> to_do;
        to_do.emplace(beginWord);

        unordered_set<string> visited;
        vector<vector<string>> res;

        vector<vector<int>> paths;
        int min_path = -1;

        while(!to_do.empty()) {
            QueueItem curr = to_do.front();
            to_do.pop();
            if(min_path != -1 && curr.path.size() > min_path) continue;

            if(curr.vertex == endWord) {
                if(min_path == -1) {
                    min_path = curr.path.size();
                }
                paths.push_back(curr.path);
                continue;
            }

            visited.insert(curr.vertex);

            curr.path.push_back(vertex_to_index[curr.vertex]);
            for(auto neighbor: vertex_to_edges[curr.vertex]) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr.path);
            }
        }

        for(auto path: paths) {
            vector<string> temp(path.size());
            transform(path.begin(), path.end(), temp.begin(), [wordList](const int index){
                return wordList[index];
            });

            temp.push_back(endWord);
            res.push_back(temp);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}