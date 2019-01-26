/*
289. Game of Life
According to the Wikipedia's article: "The Game of Life, also known
simply as Life, is a cellular automaton devised by the British
mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live
(1) or dead (0). Each cell interacts with its eight neighbors
(horizontal, vertical, diagonal) using the following four rules
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused
by under-population.
Any live cell with two or three live neighbors lives on to the next
generation.
Any live cell with more than three live neighbors dies, as if by
over-population..
Any dead cell with exactly three live neighbors becomes a live cell,
as if by reproduction.
Write a function to compute the next state (after one update) of the
board given its current state.

Follow up:
Could you solve it in-place? Remember that the board needs to be
updated at the same time: You cannot update some cells first and
then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In
principle, the board is infinite, which would cause problems
when the active area encroaches the border of the array. How
would you address these problems?
/*
    Submission Date: 2017-08-30
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  typedef pair<int, int> pii;

 public:
  int getAdajacent(const vector<vector<int>>& board, int row, int col, int M,
                   int N) {
    int res = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        int x = row + i;
        int y = col + j;
        if (0 <= x && x < M && 0 <= y && y < N) {
          res += board[x][y] & 1;
        }
      }
    }

    return res;
  }
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;

    vector<pii> make_live, make_dead;
    int M = board.size();
    int N = board[0].size();

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live = getAdajacent(board, i, j, M, N);
        if (board[i][j] == 0) {
          if (live == 3) make_live.emplace_back(i, j);
        } else {
          if (live < 2 || live > 3) make_dead.emplace_back(i, j);
        }
      }
    }

    for (auto p : make_dead) board[p.first][p.second] = 0;
    for (auto p : make_live) board[p.first][p.second] = 1;
  }

  void gameOfLife2(vector<vector<int>>& board) {
    if (board.empty()) return;

    int M = board.size();
    int N = board[0].size();

    /*
        O(1) space by storing whether to toggle for the next
        state in the second bit. 1x means needs to toggle whereas
        0x means doesn't need to toggle. Get state of z by (z & 1)
        and get whether to toggle by (z >> 1) so next state of
        z is just (z >> 1) ^ (z & 1)
    */
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live = getAdajacent(board, i, j, M, N);
        if (board[i][j] == 0) {
          board[i][j] |= (live == 3) << 1;
        } else {
          board[i][j] |= (live < 2 || live > 3) << 1;
        }
      }
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        board[i][j] = (board[i][j] >> 1) ^ (board[i][j] & 1);
      }
    }
  }
};

int main() { return 0; }