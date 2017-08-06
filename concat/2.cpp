
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <stack>

class Solution {
public:
    // Run time 12 ms
    int longestValidParentheses(string s) {
        int len = s.length();

        if(len == 0) return 0;

        int dp[len];
        int max_len = -1;
        for(int i = 0; i < len; i++) {
            // longest valid ends here so dp[i] is 0
            if(s[i] == '(') {
                dp[i] = 0;
            } else {
                if(i == 0) { 
                    // ')...' first char is ) so 0
                    dp[i] = 0;
                } else if(s[i-1] == '(') {
                    // '...()' it is two plus the longest valid at i - 2
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else {
                    // '...))' check if it is '...((...))' then it is just the inner length 
                    // dp[i - 1] plus the two brackets completed on the outer plus whatever
                    // was before the first (
                    int ind_prev = i - dp[i - 1] - 1;
                    if(s[ind_prev] == '(') {
                        dp[i] = dp[i - 1] + (ind_prev == 0 ? 0: dp[i - dp[i - 1] - 2]) + 2;
                    } else {
                        dp[i] = 0;
                    }
                }
            }
            max_len = max(dp[i], max_len);
        }
        return max_len;
    }

    // Run time 12 ms
    int longestValidParentheses2(string s) {
        int len = s.size();

        int left, right;
        int max_len = 0;

        // traverse right
        left = right = 0;
        for(int i = 0; i < len; i++) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(right > left) {
                left = right = 0;
            }
        }

        // traverse right
        left = right = 0;
        for(int i = len - 1; i >= 0; i--) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(left > right) {
                left = right = 0;
            }
        }
        return max_len;
    }

    // Run time 6 ms
    int longestValidParentheses3(string s) {
        int len = s.size();

        int max_len = 0;

        stack<int> st;

        st.push(-1);

        for(int i = 0; i < len; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else {
                // ')'
                st.pop();
                if(st.empty()) {
                    st.push(i);
                } else {
                    int prev = st.top();
                    max_len = max(i - prev, max_len);
                }
            }
        }

        return max_len;
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("(()") << endl;
    cout << s.longestValidParentheses(")()())") << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
33. Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2016-12-30
    Runtime: 6 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low)/2;

            if(nums[mid] == target) return mid;
            if(nums[low] <= nums[mid]) {
                if(target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // nums[mid] < nums[high]
                if(target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
34. Search for a Range
Given an array of integers sorted in ascending order, find the starting and ending 
position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        int low = 0;
        int high = len - 1;

        int start = -1;
        int end = -1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) {
                if(mid == 0 || nums[mid - 1] != nums[mid]) {
                    start = mid;
                    break;
                } else {
                    high = mid - 1;
                }
            } else if(nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if(start != -1) {
            low = 0;
            high = len - 1;
            while(low <= high) {
                int mid = low + (high - low)/2;
                if(nums[mid] == target) {
                    if(mid == len - 1 || nums[mid] != nums[mid + 1]) {
                        end = mid;
                        break;
                    } else {
                        low = mid + 1;
                    }
                } else if(nums[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        
        return {start, end};
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
35. Search Insert Position
Given a sorted array and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0

/*
    Submission Date: 2017-06-19
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int len = nums.size();

        int low = 0;
        int high = len - 1;

        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) high = mid - 1;
            else low = mid + 1;
        }

        return low;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
36. Valid Sudoku
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled 
with the character '.'.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. 
Only the filled cells need to be validated.


/*
    Submission Date: 2017-06-18
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<pair<int, int>> getNeighbors(const vector<vector<char>>& board, const int& i, const int& j) {
        vector<pair<int, int>> neighbors;
        // traverse row and col
        for(int temp = 0; temp < 9; temp++) {
            // traverse row
            if(isdigit(board[i][temp])) neighbors.emplace_back(i, temp);
            // traverse col
            if(isdigit(board[temp][j])) neighbors.emplace_back(temp, j);
        }

        // traverse subgrid
        int sb_row_low = (i/3)*3;
        int sb_col_low = (j/3)*3;

        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 3; col++) {
                char c = board[sb_row_low + row][sb_col_low + col];
                if(isdigit(c)) neighbors.emplace_back(sb_row_low + row, sb_col_low + col);
            }
        }

        return neighbors;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                vector<pair<int, int>> neighbors = getNeighbors(board, i, j);
                for(auto p: neighbors) {
                    if(i == p.first && j == p.second) continue;
                    if(board[i][j] == board[p.first][p.second]) return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
38. Count and Say
The count-and-say sequence is the sequence of integers with the first five terms as 
following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

/*
    Submission Date: 2017-06-18
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string prev = countAndSay(n - 1);
        int len = prev.size();
        string res = "";
        for(int i = 0; i < len; i++) {
            int j = i + 1;
            for(; j < len; j++) {
                if(prev[i] != prev[j]) {
                    break;
                }
            }
            
            int count = j - i;
            res += to_string(count) + prev[i];
            i = j - 1;
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
39. Combination Sum
Given a set of candidate numbers (C) (without duplicates) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7, 
A solution set is: 
[
  [7],
  [2, 2, 3]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void combinationSum(vector<int>& candidates, int sum, vector<vector<int>>& res, vector<int>& curr, int index) {
        for(int i = index; i < candidates.size(); i++) {
            int c = candidates[i];
            if(c > sum) break;

            curr.push_back(c);
            if(c == sum) {
                res.push_back(curr);
                curr.pop_back();
                break;
            } else {
                combinationSum(candidates, sum - c, res, curr, i);
                curr.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> curr;
        combinationSum(candidates, target, res, curr, 0);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
40. Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all 
unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void combinationSum2(vector<int>& candidates, vector<int>& curr, int sum, int target, int index, vector<vector<int>>& res) {
        if(sum > target) return;
        if(sum == target) {
            res.push_back(curr);
            return;
        }

        for(int i = index; i < candidates.size(); i++) {
            if(i != index && candidates[i - 1] == candidates[i]) continue;
            curr.push_back(candidates[i]);
            combinationSum2(candidates, curr, sum + candidates[i], target, i + 1, res);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> curr;
        combinationSum2(candidates, curr, 0, target, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
41. First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

/*
    Submission Date: 2017-06-19
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int len = nums.size();
        if(len == 0) return 1;

        for(int i = 0; i < len; i++) {
            while(nums[i] != i && nums[i] >= 0 && nums[i] < len && nums[i] != nums[nums[i]]) {
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i < len; i++) {
            if(nums[i] != i) {
                return i;
            }
        }

        int first_el = nums.front();
        if(first_el <= 0) {
            return len;
        }

        return len + (first_el == len);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
42. Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();

        int temp = 0;
        int res = 0;
        int curr_max = 0;
        for(int i = 1; i < len; i++) {
            if(height[i] >= height[curr_max]) {
                res += (i - curr_max - 1)*height[curr_max] - temp;
                curr_max = i;
                temp = 0;
            } else {
                temp += height[i];
            }
        }
        temp = 0;
        curr_max = len - 1;
        for(int i = len - 2; i >= 0; i--) {
            if(height[i] > height[curr_max]) {
                res += (curr_max - i - 1)*height[curr_max] - temp;
                curr_max = i;
                temp = 0;
            } else {
                temp += height[i];
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{0,1,0,2,1,0,1,3,2,1,2,1};
    // vector<int> v{2,0,2};
    cout << s.trap(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings, return the 
product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer 
directly.

/*
    Submission Date: 2017-06-19
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<char, string> m;
public:
    string multiply_d(string num1, char d) {
        if(m.count(d)) return m[d];

        string res;
        int carry = 0;

        int d_n = d - '0';
        for(int i = num1.size() - 1; i >= 0; i--) {
            int c = num1[i] - '0';
            int temp = carry + c*d_n;
            res = to_string(temp % 10) + res;
            carry = temp / 10;
        }

        if(carry > 0) res = to_string(carry) + res;
        return m[d] = res;
    }

    string add(string num1, string num2, int offset) {
        int M = num1.size();
        int N = num2.size();

        string res = num2;

        while(N++ < offset) res = "0" + res;

        N = num2.size();
        int carry = 0;
        int index = N - offset - 1;
        for(int i = M - 1; i >= 0; i--) {
            if(index < 0) {
                int temp = carry + (num1[i] - '0');
                res = to_string(temp % 10) + res;
                carry = temp / 10;
            } else {
                int temp = carry + (num1[i] - '0') + (num2[index] - '0');
                res[index] = (temp % 10) + '0';
                carry = temp / 10;
            }
            index--;
        }

        if(carry > 0) res = to_string(carry) + res;
        return res;
    }

    string multiply(string num1, string num2) {
        if(num1.size() > num2.size()) swap(num1, num2);

        if(num1 == "0") return "0";

        int M = num1.size();
        int N = num2.size();

        string res = "0";
        for(int i = N - 1; i >= 0; i--) {
            if(num2[i] == '0') continue;
            string mul = multiply_d(num1, num2[i]);
            res = add(mul, res, N - 1 - i);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}