/*
867. Transpose Matrix
Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal, 
switching the row and column indices of the matrix. 

 


Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]



Example 2:

Input: [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]


 

Note:


    1 <= A.length <= 1000
    1 <= A[0].length <= 1000

/*
    Submission Date: 2018-07-08
    Runtime: 20 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        int N = A.size();
        int M = A[0].size();
        vector<vector<int>> res(M, vector<int>(N));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                res[j][i] = A[i][j];
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}