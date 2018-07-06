/*
529. Minesweeper
Let's play the minesweeper game (Wikipedia, online game)! 

You are given a 2D char matrix representing the game board. 'M' represents an 
unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a 
revealed blank square that has no adjacent (above, below, left, right, and all 4 
diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to 

Now given the next click position (row and column indices) among all the 
unrevealed squares ('M' or 'E'), return the board after revealing this position 



If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to 
revealed blank ('B') and all of its adjacent unrevealed squares should be 
If an empty square ('E') with at least one adjacent mine is revealed, then 
Return the board when no more squares will be revealed.



Example 1:
Input: 

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:




Example 2:
Input: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:






Note:

The range of the input matrix's height and width is [1,50].
The click position will only be an unrevealed square ('M' or 'E'), which also 
The input board won't be a stage when game is over (some mines have been 
For simplicity, not mentioned rules should be ignored in this problem. For 
example, you don't need to reveal all the unrevealed mines when the game is 
/*
    Submission Date: 2018-07-05
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& board, const int i, const int j, int N, int M) {
        if(board[i][j] == 'B') return;
        
        int mine_count = 0;
        vector<pair<int,int>> to_visit;
        
        for(int ii = -1; ii <= 1; ii++) {
            int new_i = i + ii;
            if(!(0 <= new_i && new_i < N)) continue;
            for(int jj = -1; jj <= 1; jj++) {
                if(ii == 0 && jj == 0) continue;
                int new_j = j + jj;
                if(!(0 <= new_j && new_j < M)) continue;
                
                if(board[new_i][new_j] == 'M') {
                    mine_count++;
                } else if(board[new_i][new_j] == 'B') {
                    continue;
                } else { // board[new_i][new_j] == 'E'
                    to_visit.emplace_back(new_i, new_j);
                }
            }
        }
        
        if(mine_count > 0) {
            board[i][j] = mine_count + '0';
        } else {
            board[i][j] = 'B';
            for(const auto& kv: to_visit) {
                dfs(board, kv.first, kv.second, N, M);
            }
        }
    }
    
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int N = board.size();
        int M = board[0].size();
        int y = click[0];
        int x = click[1];
        
        if(board[y][x] == 'M') {
            board[y][x] = 'X';
        } else { // board[y][x] == 'E'
            dfs(board, y, x, N, M);
        }
        
        return board;
    }
};

int main() {
    return 0;
}