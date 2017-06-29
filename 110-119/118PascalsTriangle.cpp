/*
118. Pascal's Triangle
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows, vector<int>{});

        for(int i = 0; i < numRows; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0 || j == i) res[i].push_back(1);
                else res[i].push_back(res[i-1][j-1] + res[i-1][j]);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}