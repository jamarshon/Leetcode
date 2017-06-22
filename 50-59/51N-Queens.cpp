/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n 
chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' 
both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void solveNQueens(int n, vector<pair<int, int>>& queens, int row, vector<vector<string>>& res) {
        if(queens.size() == n) {
            vector<string> board(n, string(n, '.'));
            for(auto queen: queens) {
                board[queen.first][queen.second] = 'Q';
            }
            res.push_back(board);
            return;
        }
        
        // iterate through the columns
        for(int c = 0; c < n; c++) {

            bool intersect = false;
            for(auto queen: queens) {
                // check diagonal and column
                intersect = (abs(queen.first - row) == abs(queen.second - c)) || queen.second == c;
                if(intersect) break;
            }

            if(intersect) continue;
            queens.emplace_back(row, c);
            solveNQueens(n, queens, row + 1, res);
            queens.pop_back();
        }
        
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<pair<int, int>> queens;
        solveNQueens(n, queens, 0, res);
        return res;
        
    }
};

int main() {
    Solution s;
    return 0;
}