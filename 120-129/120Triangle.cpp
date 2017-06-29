/*
120. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to 
adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total 
number of rows in the triangle.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int M = triangle.size();
        for(int i = 0; i < M; i++) {
            int N = triangle[i].size();
            for(int j = 0; j < N; j++) {
                if(i == 0 && j == 0) continue;
                if(j == 0) 
                    triangle[i][j] += triangle[i-1][j];
                else if(j == N - 1)
                    triangle[i][j] += triangle[i-1][j-1];
                else
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
            }
        }

        int res = INT_MAX;
        for(auto e: triangle.back()) res = min(res, e);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}