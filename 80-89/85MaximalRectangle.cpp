/*
85. Maximal Rectangle
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int num_rows = matrix.size();
        int num_cols = matrix[0].size();

        int area = 0;
        int curr;
        vector<int> height(num_cols, 0);
        vector<int> left(num_cols, 0);
        vector<int> right(num_cols, num_cols);
        for(int i = 0; i < num_rows; i++) {
            for(int j = 0; j < num_cols; j++) {
                if(matrix[i][j] == '1') height[j]++;
                else height[j] = 0;
            }

            // curr reprsent 1 + index of most recent zero seen from left
            curr = 0;
            for(int j = 0; j < num_cols; j++) {
                if(matrix[i][j] == '1') left[j] = max(curr, left[j]);
                else {
                    curr = j + 1;
                    left[j] = 0;
                }
            }

            // curr represents index of most recent zero seen from right
            curr = num_cols;
            for(int j = num_cols - 1; j >= 0; j--) {
                if(matrix[i][j] == '1') right[j] = min(curr, right[j]);
                else {
                    curr = j;
                    right[j] = num_cols;
                }
            }

            for(int j = 0; j < num_cols; j++) {
                area = max(area, (right[j] - left[j])*height[j]);
            }
        }
        return area;
    }
};

int main() {
    return 0;
}