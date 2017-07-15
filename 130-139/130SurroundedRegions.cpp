/*
130. Surrounded Regions
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    void bfs(vector<vector<char>>& board, int i, int j, int N, int M) {
        queue<pair<int, int>> q;
        q.emplace(i, j);

        int dk[4] = {0, -1, 1, 0};
        int dl[4] = {-1, 0, 0, 1};
        while(!q.empty()) {
            pair<int, int>& p = q.front();

            tie(i, j) = p;
            q.pop();

            if(board[i][j] != 'O') continue;
            board[i][j] = 'L';

            int new_i, new_j;
            for(int k = 0; k < 4; k++) {
                new_i = i + dk[k];
                new_j = j + dl[k];

                if(0 <= new_i && new_i < N && 0 <= new_j && new_j < M) {
                    if(board[new_i][new_j] != 'O') continue;
                    q.emplace(new_i, new_j);
                    // dfs(board, new_i, new_j, N, M);
                }
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int N = board.size();

        if(N == 0) return;

        int M = board.front().size();
        

        for(int i = 0; i < N; i++) {
            if(board[i][0] == 'O') bfs(board, i, 0, N, M);
            if(board[i][M-1] == 'O') bfs(board, i, M-1, N, M);
        }

        for(int i = 0; i < M; i++) {
            if(board[0][i] == 'O') bfs(board, 0, i, N, M);
            if(board[N-1][i] == 'O') bfs(board, N-1, i, N, M);
        }

        unordered_map<char, char> m{{'X', 'X'}, {'L', 'O'}, {'O', 'X'}};
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                board[i][j] = m[board[i][j]];
            }
        }
    }
};

int main() {
    Solution s;
    return 0;
}