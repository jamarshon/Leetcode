#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
class Solution {
    void solveNQueens(int n, vector<pair<int, int>>& queens, int row, vector<vector<string>>& res) {
        // cout << queens.size() << endl;
        if(queens.size() == n) {
            vector<string> board(n, string(n, '.'));
            for(auto queen: queens) {
                board[queen.first][queen.second] = 'Q';
            }
            res.push_back(board);
            return;
        }
        
        // iterate through the columns
        for(int c = 0; c < n; c++) {

            bool intersect = false;
            for(auto queen: queens) {
                // check diagonal and column
                intersect = (abs(queen.first - row) == abs(queen.second - c)) || queen.second == c;
                if(intersect) break;
            }

            if(intersect) continue;
            queens.emplace_back(row, c);
            solveNQueens(n, queens, row + 1, res);
            queens.pop_back();
        }
        
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<pair<int, int>> queens;
        solveNQueens(n, queens, 0, res);
        return res;
        
    }
};

int main() {
    Solution s;
    vector<vector<string>> r = s.solveNQueens(4);
    for(auto v: r) {
        for(auto e: v) cout << e << endl;
            cout << endl;
    }
    return 0;
}