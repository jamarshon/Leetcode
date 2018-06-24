/*
840. Magic Squares In Grid
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).
Example 1:

Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:
438
951
276

while this one is not:
384
519
762

In total, there is only one magic square inside the given grid.
Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
0 <= grid[i][j] <= 15
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool IsMagicSquare(const vector<vector<int>>& grid, int i, int j) {
        unordered_set<int> st;
        vector<int> row_sum(3, 0), col_sum(3, 0);
        int diag1 = 0, diag2 = 0;
        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                int e = grid[i+y][j+x];
                if(e < 1 || e > 9 || st.count(e)) return false;
                row_sum[y] += e;
                col_sum[x] += e;
                if(y == x) diag1 += e;
                if(x + y == 2) diag2 += e;
            }
        }
        
        for(int x = 1; x < 3; x++) {
            if(row_sum[x] != row_sum[x-1]) return false;
            if(col_sum[x] != col_sum[x-1]) return false;
        }
        
        return diag1 == diag2;
    }
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        int res = 0;
        for(int i = 0; i < N - 2; i++) {
            for(int j = 0; j < M - 2; j++) {
                res += IsMagicSquare(grid, i, j);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}