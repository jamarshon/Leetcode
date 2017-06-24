/*
79. Word Search
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where 
"adjacent" cells are those horizontally or vertically neighboring. The same letter 
cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
/*
    Submission Date: 2017-06-23
    Runtime: 119 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool exist(vector<vector<char>>& board, vector<pair<int, int>>& offset, string word, string curr, int row, int col, int M, int N) {
        if(curr == word) return true;
        char c = word[curr.size()];

        for(auto p: offset) {
            int new_row = row + p.first;
            int new_col = col + p.second;
            if(new_row >= 0 && new_row < M && new_col >= 0 && new_col < N) {
                if(board[new_row][new_col] == c) {
                    board[new_row][new_col] = '\0';
                    if(exist(board, offset, word, curr + c, new_row, new_col, M, N)) {
                        board[new_row][new_col] = c;
                        return true;
                    }
                    board[new_row][new_col] = c;
                }
            }
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int M = board.size();

        if(M == 0) return false;
        int N = board[0].size();

        vector<pair<int, int>> offset{{-1, 0}, {0, 0}, {1, 0}, {0, -1}, {0, 1}};
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(exist(board, offset, word, "", i, j, M, N)) return true;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}