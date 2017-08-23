/*
240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix. 
This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
/*
    Submission Date: 2017-08-22
    Runtime: 79 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int M = matrix.size();
        int N = matrix.front().size();
        
        int i = 0;
        int j = N - 1;
        while(i < M && j >= 0) {
            if(matrix[i][j] == target) return true;
            if(matrix[i][j] > target) { // smaller than everything in this column 
                j--;
            } else if(matrix[i][j] < target) { // bigger than everything in this row
                i++;
            }
        }
        
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}