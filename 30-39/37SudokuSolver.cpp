/*
37. Sudoku Solver
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

/*
    Submission Date: 2017-06-18
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <functional>

using namespace std;
struct ValidNums {
    bool avail[10] = {true, true, true, true, true, 
                        true, true, true, true, true};
    int num_avail = 9;
};

class Solution {
    vector<pair<int, int>> getNeighborsDigits(const vector<vector<char>>& board, const int& i, const int& j) {
        function<bool(char)> is_digit = [](const char& c) -> bool { return isdigit(c); };
        return getNeighbors(board, i, j, is_digit);
    }

    vector<pair<int, int>> getNeighborsEmpty(const vector<vector<char>>& board, const int& i, const int& j) {
        function<bool(char)> is_empty = [](const char& c) -> bool { return c == '.'; };
        return getNeighbors(board, i, j, is_empty);
    }

    vector<pair<int, int>> getNeighbors(const vector<vector<char>>& board, const int& i, const int& j, const function<bool(char)>& f) {
        vector<pair<int, int>> neighbors;
        // traverse row and col
        for(int temp = 0; temp < 9; temp++) {
            // traverse row
            if(f(board[i][temp])) neighbors.emplace_back(i, temp);
            // traverse col
            if(f(board[temp][j])) neighbors.emplace_back(temp, j);
        }

        // traverse subgrid
        int sb_row_low = (i/3)*3;
        int sb_col_low = (j/3)*3;

        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 3; col++) {
                char c = board[sb_row_low + row][sb_col_low + col];
                if(f(c)) neighbors.emplace_back(sb_row_low + row, sb_col_low + col);
            }
        }

        return neighbors;
    }

    bool canSolveSudoku(vector<vector<char>>& board, vector<vector<ValidNums>>& dof) {
        ValidNums min_vn;
        min_vn.num_avail = -1;
        int row, col;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                ValidNums vn = dof[i][j];
                if(vn.num_avail == 0 && board[i][j] == '.') {
                    return false;
                }
                
                if(vn.num_avail > 0 && (min_vn.num_avail == -1 || vn.num_avail < min_vn.num_avail)) {
                    min_vn = vn;
                    row = i;
                    col = j;
                }
            }
        }

        if(min_vn.num_avail == -1) return true;

        vector<pair<int, int>> neighbors = getNeighborsEmpty(board, row, col);

        int& curr_num_avail = dof[row][col].num_avail;
        int temp = curr_num_avail;
        curr_num_avail = 0;

        for(char c = '1'; c <= '9'; c++) {
            if(!min_vn.avail[c - '0']) continue;

            vector<pair<int, int>> need_to_correct;

            board[row][col] = c;

            for(auto p: neighbors) {
                if(p.first == row && p.second == col) continue;
                ValidNums& neighbor_vn = dof[p.first][p.second];
                if(neighbor_vn.num_avail > 0 && neighbor_vn.avail[c - '0']) {
                    need_to_correct.emplace_back(p.first, p.second);
                    neighbor_vn.avail[c - '0'] = false;
                    neighbor_vn.num_avail--;
                }
            }

            
            if(canSolveSudoku(board, dof)) {
                return true;
            }

            for(auto p: need_to_correct) {
                ValidNums& vn = dof[p.first][p.second];
                vn.avail[c - '0'] = true;
                vn.num_avail++;
            }
        }
        
        board[row][col] = '.';
        curr_num_avail = temp;
        return false;
    }
public:
    void populateDof(const vector<vector<char>>& board, vector<vector<ValidNums>>& dof) {
        for(int i = 0; i < 9; i++) {
            vector<ValidNums> temp;
            for(int j = 0; j < 9; j++) {
                ValidNums vn;

                if(isdigit(board[i][j])) {
                    vn.num_avail = 0;
                } else{
                    vector<pair<int, int>> neighbors = getNeighborsDigits(board, i, j);
                    for(auto p: neighbors) {
                        char c = board[p.first][p.second];
                        if(vn.avail[c - '0']) {
                            vn.avail[c - '0'] = false;
                            vn.num_avail--;
                        }
                    }
                }

                temp.push_back(vn);
            }
            dof.push_back(temp);
        }
    }

    bool canSolveSudoku(vector<vector<char>>& board) {
        vector<vector<ValidNums>> dof;
        populateDof(board, dof);
        return canSolveSudoku(board, dof);
    }

    void solveSudoku(vector<vector<char>>& board) {
        bool solved = canSolveSudoku(board);
        return;
    }
};

int main() {
    Solution s;
    function<vector<char>(string)> to_v = [](string s) -> vector<char> { return vector<char>(s.begin(), s.end()); };

    // vector<vector<char>> board{to_v(".87654321"),to_v("2........"),to_v("3........"),to_v("4........"),to_v("5........"),to_v("6........"),to_v("7........"),to_v("8........"),to_v("9........")};
    vector<vector<char>> board{to_v("..9748..."),to_v("7........"),to_v(".2.1.9..."),to_v("..7...24."),to_v(".64.1.59."),to_v(".98...3.."),to_v("...8.3.2."),to_v("........6"),to_v("...2759..")};
    // vector<vector<char>> board{to_v("..4...63."),to_v("........."),to_v("5......9."),to_v("...56...."),to_v("4.3.....1"),to_v("...7....."),to_v("...5....."),to_v("........."),to_v(".........")};
    
    s.solveSudoku(board);
    for(auto v: board) {
        for(auto c: v) cout << c << ' ';
            cout << endl;
    }
    return 0;
}