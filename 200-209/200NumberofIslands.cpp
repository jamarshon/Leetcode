/*
200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is 
surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may 
assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3

/*
    Submission Date: 2017-08-03
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int dx_[4] = {0, 0, -1, 1};
    int dy_[4] = {-1, 1, 0, 0};
public:
    void fill(vector<vector<char>>& grid, int i, int j, int rows, int cols) {
        for(int k = 0; k < 4; k++) {
            int new_row = i + dx_[k];
            int new_col = j + dy_[k];
            if(0 <= new_row && new_row < rows && 0 <= new_col && new_col < cols) {
                if(grid[new_row][new_col] == '1') {
                    grid[new_row][new_col] = '0';
                    fill(grid, new_row, new_col, rows, cols);
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        if(rows == 0) return 0;
        int cols = grid.front().size();
        int res = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] == '1') {
                    fill(grid, i, j, rows, cols);
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    return 0;
}