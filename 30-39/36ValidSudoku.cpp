/*
36. Valid Sudoku
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled
with the character '.'.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable.
Only the filled cells need to be validated.


/*
    Submission Date: 2017-06-18
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<pair<int, int>> getNeighbors(const vector<vector<char>>& board,
                                      const int& i, const int& j) {
    vector<pair<int, int>> neighbors;
    // traverse row and col
    for (int temp = 0; temp < 9; temp++) {
      // traverse row
      if (isdigit(board[i][temp])) neighbors.emplace_back(i, temp);
      // traverse col
      if (isdigit(board[temp][j])) neighbors.emplace_back(temp, j);
    }

    // traverse subgrid
    int sb_row_low = (i / 3) * 3;
    int sb_col_low = (j / 3) * 3;

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        char c = board[sb_row_low + row][sb_col_low + col];
        if (isdigit(c))
          neighbors.emplace_back(sb_row_low + row, sb_col_low + col);
      }
    }

    return neighbors;
  }

 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        vector<pair<int, int>> neighbors = getNeighbors(board, i, j);
        for (auto p : neighbors) {
          if (i == p.first && j == p.second) continue;
          if (board[i][j] == board[p.first][p.second]) return false;
        }
      }
    }

    return true;
  }
};

int main() { return 0; }