/*
54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the 
matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].


/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        
        int num_rows = matrix.size();
        
        if(num_rows == 0) return res;
        int num_cols = matrix[0].size();
        
        int left = 0;
        int right = num_cols - 1;
        int top = 0;
        int bottom = num_rows - 1;
        
        int temp;
        while(left <= right && top <= bottom) {
            temp = left;
            while(temp <= right) {
                res.push_back(matrix[top][temp++]);
            }
            
            top++;
            temp = top;
            
            while(temp <= bottom) {
                res.push_back(matrix[temp++][right]);
            }
            
            if(top > bottom) break;
            
            right--;
            temp = right;
            while(temp >= left) {
                res.push_back(matrix[bottom][temp--]);
            }
            
            if(left > right) break;

            bottom--;
            temp = bottom;
            while(temp >= top) {
                res.push_back(matrix[temp--][left]);
            }
            
            left++;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> v;
    v = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    v = {{1,2,3,4},{4,5,6,7},{7,8,9,10}};
    vector<int> t = s.spiralOrder(v);
    for(auto e : t) cout << e << ' ';
    return 0;
}