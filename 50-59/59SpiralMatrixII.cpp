/*
59. Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> v(n, vector<int>(n, 0));
        
        int top = 0;
        int left = 0;
        int right = n-1;
        int bottom = n-1;
        int temp;
        int count = 1;
        while(left <= right && top <= bottom) {
            temp = left;
            while(temp <= right) {
                v[top][temp++] = count++;
            }
            
            top++;
            temp = top;
            while(temp <= bottom) {
                v[temp++][right] = count++;
            }
            
            if(top > bottom) break;
            
            right--;
            temp = right;
            while(temp >= left) {
                v[bottom][temp--] = count++;
            }
            
            if(left > right) break;
            
            bottom--;
            temp = bottom;
            while(temp >= top) {
                v[temp--][left] = count++;
            }
            
            left++;
        }
        return v;
    }
};

int main() {
    return 0;
}