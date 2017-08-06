
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
44. Wildcard Matching
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

/*
    Submission Date: 2017-06-20
    Runtime: 75 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int M = p.size();
        int N = s.size();

        vector<vector<bool>> dp(M + 1, vector<bool>(N + 1, false));

        dp[0][0] = true;

        for(int j = 1; j <= N; j++) {
            dp[0][j] = false;
        }

        for(int i = 1; i <= M; i++) {
            if(p[i-1] == '?') 
                dp[i][0] = false;
            else if(p[i-1] == '*')
                dp[i][0] = dp[i-1][0];
        }

        for(int i = 1; i <= M; i++) {
            for(int j = 1; j <= N; j++) {
                // same or single character means diagonal
                if(p[i-1] == s[j-1] || p[i-1] == '?') { 
                    dp[i][j] = dp[i-1][j-1];
                } else if(p[i-1] == '*') {
                    // either empty sequence or everything not including s[j]
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                } else {
                    // different letters
                    dp[i][j] = false;
                }
            }
        }

        return dp[M][N];
    }
};

int main() {
    Solution s;
    cout << s.isMatch("aa","a") << ' ' <<  false << endl;
    cout << s.isMatch("aa","aa") << ' ' <<  true << endl;
    cout << s.isMatch("aaa","aa") << ' ' <<  false << endl;
    cout << s.isMatch("aa", "*") << ' ' <<  true << endl;
    cout << s.isMatch("aa", "a*") << ' ' <<  true << endl;
    cout << s.isMatch("ab", "?*") << ' ' <<  true << endl;
    cout << s.isMatch("aab", "c*a*b") << ' ' <<  false << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
45. Jump Game II
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, 
then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

/*
    Submission Date: 2017-06-21
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();

        int curr_max_dist = 0;
        int next_max_dist = 0;
        int min_jumps = 0;
        for(int i = 0; i < len; i++) {
            if(curr_max_dist >= len - 1) {
                return min_jumps;
            }
            
            next_max_dist = max(i + nums[i], next_max_dist);
            if(next_max_dist >= len - 1) {
                return min_jumps + 1;
            }

            if(i == curr_max_dist) {
                curr_max_dist = next_max_dist;
                min_jumps++;
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
46. Permutations
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void permuteHelper(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();

        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        for(int i = index; i < len; i++) {
            swap(nums[i], nums[index]);
            permuteHelper(nums, index + 1, res);
            swap(nums[i], nums[index]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        permuteHelper(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{1,2,3};
    vector<vector<int>> p = s.permute(v);
    for(auto v2: p) {
        for(auto e: v2) cout << e << ' ';
        cout << endl;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
47. Permutations II
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

/*
    Submission Date: 2017-06-20
    Runtime: 35 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    void permuteUnique(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();
        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        unordered_set<int> s;
        for(int i = index; i < len; i++) {
            // Swap any number from i in [index, len) with nums[index] if moving that number x
            // to nums[index] hasn't been done before. Basically just swapping unique x's to nums[index]
            if(s.find(nums[i]) == s.end()) {
                s.insert(nums[i]);
                swap(nums[i], nums[index]);
                permuteUnique(nums, index + 1, res);
                swap(nums[i], nums[index]);
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        permuteUnique(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v;
    vector<vector<int>> t;

    v = {1,1,2};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 3

    v = {0,1,0,0,9};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 20

    v = {2,2,1,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 6


    v = {-1,2,0,-1,1,0,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 630
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
48. Rotate Image
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

/*
    Submission Date: 2016-12-15
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <vector>
class Solution {
public:
    int replace(int value, int i, int j, vector<vector<int>>& matrix) {
    	int prev = matrix[i][j];
    	matrix[i][j] = value;
    	return prev;
    }

    void rotate(vector<vector<int>>& matrix) {
        int n = matrix[0].size();
    	for(int i = 0, numLayers = n / 2; i < numLayers; i++) {
    		for(int j = i, rightBoundary = n - i - 1; j < rightBoundary; j++) {
    			int temp =  matrix[n- j - 1][i];
    			temp = replace(temp, i, j, matrix);
                temp = replace(temp, j, n - i - 1, matrix);
                temp = replace(temp, n - i - 1, n - j - 1, matrix);
                temp = replace(temp, n - j - 1, i, matrix);
    		}
    	}
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
49. Group Anagrams

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 

Return:
    [
      ["ate", "eat","tea"],
      ["nat","tan"],
      ["bat"]
    ]

Note: All inputs will be in lower-case.

/*
    Submission Date: 2017-02-19
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    unordered_map<char, int> m = {{'a',2},{'b',3},{'c',5},{'d',7},{'e',11},{'f',13},{'g',17},{'h',19},{'i',23},{'j',29},{'k',31},{'l',37},{'m',41},{'n',43},{'o',47},{'p',53},{'q',59},{'r',61},{'s',67},{'t',71},{'u',73},{'v',79},{'w',83},{'x',89},{'y',97},{'z',101}};
    
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<int, vector<string>> groups;

        for(string str : strs) {
            int product = 1;
            for(char c: str) product *= m[c];
            unordered_map<int, vector<string>>::iterator i = groups.find(product);

            if(i == groups.end()) {
                groups[product] = {str};
            } else {
                (i -> second).push_back(str);
            }
        }

        vector<vector<string>> result;
        for(auto kv: groups) {
            result.push_back(kv.second);
        }
        
        return result;
    }
};



int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
50. Pow(x, n)
Implement pow(x, n)

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
class Solution {
public:
    double myPow(double x, int n) {
        if(n == INT_MIN) {
            double res = myPow(x, -1*((n+1)/2 - 1));
            return 1/(res*res);
        }
        if(x == 1) return 1;
        if(n < 0) return 1/myPow(x, -n);
        if(n == 0) return 1;
        if(n == 1) return x;
        double res = myPow(x, n/2);
        res *= res;
        if(n % 2 == 0) {
            return res;
        } else {
            return x*res;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n 
chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' 
both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void solveNQueens(int n, vector<pair<int, int>>& queens, int row, vector<vector<string>>& res) {
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
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
52. N-Queens II
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

/*
    Submission Date: 2017-07-08
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    int nQueens(int arr[], int n, int index) {
        if(index == n) return 1;

        bool allowed[n];
        fill(allowed, allowed + n, true);

        for(int i = 0; i < index; i++) {
            allowed[arr[i]] = false; // column
            int diff = abs(index - i); // diagonal abs(x1 - x2) == abs(y1 - y2)
            if(0 <= arr[i] + diff && arr[i] + diff < n) allowed[arr[i] + diff] = false;
            if(0 <= arr[i] - diff && arr[i] - diff < n) allowed[arr[i] - diff] = false;
        }

        int count = 0;
        for(int i = 0; i < n; i++) {
            if(allowed[i]) {
                arr[index] = i;
                count += nQueens(arr, n, index + 1);
            }
        }

        return count;
    }
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int arr[n];

        return nQueens(arr, n, 0);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) 
which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

If you have figured out the O(n) solution, try coding another solution using the 
divide and conquer approach, which is more subtle.

/*
    Submission Date: 2017-06-22
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return 0;

        int max_sub_arr = nums.front();
        int current = max_sub_arr;

        for(int i = 1; i < len; i++) {
            current = max(nums[i], current + nums[i]);
            max_sub_arr = max(current, max_sub_arr);
        }
        
        return max_sub_arr;
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
55. Jump Game
Given an array of non-negative integers, you are initially positioned at the first 
index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

/*
    Submission Date: 2017-06-19
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return false;

        int curr_len = nums.front();
        for(int i = 1; i <= curr_len && curr_len < len - 1; i++) {
            curr_len = max(curr_len, i + nums[i]);
        }

        return curr_len >= len - 1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
56. Merge Intervals
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

/*
    Submission Date: 2017-01-19
    Runtime: 49 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct sortComparison {
    inline bool operator() (const Interval& a, const Interval& b) {
        return a.start < b.start;
    }
};


class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int len = intervals.size();
        if(len == 0) return intervals;

        sort(intervals.begin(), intervals.end(), sortComparison());
        int j = 0;
        vector<Interval> retVec = {intervals[0]};
        for(int i = 1; i < len; i++) {
            if(overlap(intervals[i], retVec[j])) {
                retVec[j].start = min(intervals[i].start, retVec[j].start);
                retVec[j].end = max(intervals[i].end, retVec[j].end);
            } else {
                retVec.push_back(intervals[i]);
                j++;
            }
        }
        
        return retVec;
    }
    bool overlap(Interval a, Interval b) {
        return !(a.end < b.start || a.start > b.end);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
57. Insert Interval
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

/*
    Submission Date: 2017-06-22
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct Compare {
    bool operator() (const Interval& lhs, const Interval& rhs) {
        return lhs.start < rhs.start;
    }
    bool operator() (const Interval& lhs, int start) {
        return lhs.start < start;
    }
    bool operator() (int start, const Interval& rhs) {
        return start < rhs.start;
    }
};

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto it = upper_bound(intervals.begin(), intervals.end(), newInterval.start, Compare());

        auto prev_it = it - 1;
        auto merge_it = prev_it;
        if(it == intervals.begin() || (prev_it -> end) < newInterval.start) {
            // either insert or merge
            if(it == intervals.end() || (it -> start) > newInterval.end) {
                intervals.insert(it, newInterval);
                return intervals;
            } else {
                merge_it = it;
            }
        }

        merge_it -> start = min(merge_it -> start, newInterval.start);

        // find the next disjoint interval, as everything in between is now overlapping
        auto it_large = upper_bound(merge_it, intervals.end(), newInterval.end, Compare());
        int max_end = (it_large - 1) -> end;

        merge_it -> end = max(max(max_end, merge_it -> end), newInterval.end);

        intervals.erase(merge_it + 1, it_large);
        
        return intervals;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
58. Length of Last Word
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.

/*
    Submission Date: 2017-01-19
    Runtime: 6 ms
    Difficulty: EASY
*/
using namespace std;
#include <iostream>

class Solution {
public:
    int lengthOfLastWord(string s) {
        if(s == "") return 0;
        
        int nonSpaceCharIndex = s.size() - 1;
        while(s[nonSpaceCharIndex] == ' ') {
            if(nonSpaceCharIndex == 0) return 0;
            nonSpaceCharIndex--;
        }
        
        int lastWordEndIndex = nonSpaceCharIndex;
        int lastWordStartIndex = nonSpaceCharIndex;
        while(lastWordStartIndex >= 0 && s[lastWordStartIndex] != ' ') {
            lastWordStartIndex--;

        }
        
        return lastWordEndIndex - lastWordStartIndex;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> v(n, vector<int>(n, 0));
        function<int(int, int)> mod = [](const int& x, const int& n) -> int {
            int r = x % n;
            return r < 0 ? r + n : r;
        };

        int i = 0;
        int j = 0;
        int di = 0;
        int dj = 1;

        for(int count = 1; count <= n*n; count++) {
            v[i][j] = count;
            if(v[mod(i + di, n)][mod(j + dj, n)]) {
                swap(di, dj);
                dj *= -1;
            }
            i += di;
            j += dj;
        }
        return v;
    }
};

int main() {
    Solution s;
    vector<vector<int>> t = s.generateMatrix(4);
    for(auto v2: t) {
        for(auto e: v2) cout << e << ' ';
            cout << endl;
    }
    return 0;
}