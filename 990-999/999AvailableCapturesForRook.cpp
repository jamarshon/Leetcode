/*
999. Available Captures for Rook
On an 8 x 8 chessboard, there is one white rook.  There also may be empty
squares, white bishops, and black pawns.  These are given as characters 'R',
'.', 'B', and 'p' respectively. Uppercase characters represent white pieces, and
lowercase characters represent black pieces.

The rook moves as in the rules of Chess: it chooses one of four cardinal
directions (north, east, west, and south), then moves in that direction until it
chooses to stop, reaches the edge of the board, or captures an opposite colored
pawn by moving to the same square it occupies.  Also, rooks cannot move into the
same square as other friendly bishops.

Return the number of pawns the rook can capture in one move.

Example 1:

Input:
[[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation:
In this example the rook is able to capture all the pawns.

Example 2:

Input:
[[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 0
Explanation:
Bishops are blocking the rook to capture any pawn.

Example 3:

Input:
[[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation:
The rook can capture the pawns at positions b5, d6 and f5.

Note:

  board.length == board[i].length == 8
  board[i][j] is either 'R', '.', 'B', or 'p'
  There is exactly one cell with board[i][j] == 'R'
/*
  Submission Date: 2019-09-03
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int di[4] = {0, 0, 1, -1};
  int dj[4] = {1, -1, 0, 0};

  int numRookCaptures(vector<vector<char>>& board) {
    int N = board.size();
    int M = board[0].size();

    int rook_i = -1, rook_j = -1;
    // find the rook
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (board[i][j] == 'R') {
          rook_i = i;
          rook_j = j;
          i = board.size();
          break;
        }
      }
    }

    int cnt = 0;
    // traverse in 4 directions until reaching a piece
    for (int k = 0; k < 4; k++) {
      int i = rook_i;
      int j = rook_j;
      while (0 <= i && i < N && 0 <= j && j < M) {
        if (board[i][j] == 'p') {
          cnt++;
          break;
        } else if (board[i][j] == 'B') {
          break;
        }
        i += di[k];
        j += dj[k];
      }
    }
    return cnt;
  }
};

int main() { return 0; }
