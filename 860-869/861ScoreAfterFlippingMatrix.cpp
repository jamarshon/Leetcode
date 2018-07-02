/*
861. Score After Flipping Matrix
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: 
changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, 
and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
/*
    Submission Date: 2018-07-01
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void FlipRow(vector<vector<int>>& A, int row, int M) {
        for(int j = 0; j < M; j++) A[row][j] ^= 1;
    }
    
    void FlipCol(vector<vector<int>>& A, int col, int N) {
        for(int i = 0; i < N; i++) A[i][col] ^= 1;
    }
    
    /*
    First get all the the elements in A[i][0] to be 1 by toggling rows
    this is because having a 1 in the left most column gives the greatest value 1000 > 0111
    Then for each column, flip the column if it gives a greater amount of 1's in that column
    */
    int matrixScore(vector<vector<int>>& A) {
        if(A.empty()) return 0;
        int N = A.size(), M = A[0].size();
        for(int i = 0; i < N; i++) {
            if(A[i][0] == 0) {
                FlipRow(A, i, M);
            }
        }
        
        for(int j = 0; j < M; j++) {
            int one_count = 0;
            for(int i = 0; i < N; i++) one_count += A[i][j] == 1;
            if(one_count < N - one_count) {
                FlipCol(A, j, N);
            }
        }
        
        int res = 0;
        for(int i = 0; i < N; i++) {
            int temp = 0;
            for(int j = 0; j < M; j++) {
                temp |= A[i][j];
                temp <<= 1;
            }
            res += temp >> 1;
        }
        return res;
    }
};

int main() {
    return 0;
}