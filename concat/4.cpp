
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
60. Permutation Sequence

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

/*
    Submission Date: 2017-06-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<int, int> combinations{
      {0, 1},   {1, 1},   {2, 2},    {3, 6},     {4, 24},
      {5, 120}, {6, 720}, {7, 5040}, {8, 40320}, {9, 362880}};

 public:
  string getPermutation(vector<char>& available, int n, int k, int comb_index) {
    if (available.empty()) return "";

    int index = (k - 1) / combinations[comb_index];
    char leading_char = available[index];
    available.erase(available.begin() + index);

    k -= index * combinations[comb_index];

    return string(1, leading_char) +
           getPermutation(available, n, k, comb_index - 1);
  }
  string getPermutation(int n, int k) {
    vector<char> available;

    char target = '0' + n;
    for (char i = '1'; i <= target; i++) {
      available.push_back(i);
    }

    return getPermutation(available, n, k, n - 1);
  }
};

int main() {
  Solution s;
  for (int i = 1; i <= 6; i++) cout << s.getPermutation(3, i) << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
61. Rotate List
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

/*
    Submission Date: 2017-01-19
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* rotateRight(ListNode* head, int k) {
    if (k == 0 || head == NULL) return head;

    ListNode* current = head;
    ListNode* lastNode;
    int len = 0;
    while (current != NULL) {
      len++;
      lastNode = current;
      current = current->next;
    }

    k %= len;
    if (k == 0) return head;

    int target = len - k;
    ListNode* kLast = head;
    while (--target) {
      kLast = kLast->next;
    }

    ListNode* newHead = kLast->next;
    kLast->next = NULL;
    lastNode->next = head;

    return newHead;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
62. Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
diagram below).

The robot can only move either down or right at any point in time. The robot is
trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

How many possible unique paths are there?

/*
    Submission Date: 2017-06-22
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int uniquePaths(int m, int n) {
    if (m == 0 || n == 0) return 0;

    int arr[m][n];

    for (int i = 0; i < m; i++) arr[i][0] = 1;
    for (int i = 0; i < n; i++) arr[0][i] = 1;

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
      }
    }

    return arr[m - 1][n - 1];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
63. Unique Paths II
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths
would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

/*
    Submission Date: 2017-06-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <unordered_map>
#include <vector>

struct PairHash {
  size_t operator()(pair<int, int> const& p) const {
    return ((hash<int>()(p.first) ^ (hash<int>()(p.second) << 1)) >> 1);
  }
};

class Solution {
  unordered_map<pair<int, int>, int, PairHash> m;

 public:
  int uniquePathsWithObstacles(vector<vector<int>>& grid, int i, int j, int M,
                               int N) {
    pair<int, int> p = {i, j};

    auto it = m.find(p);
    if (it != m.end()) return it->second;

    if (i >= M || j >= N) return 0;
    if (grid[i][j]) return 0;
    if (i == M - 1 && j == N - 1) return 1;

    int res = uniquePathsWithObstacles(grid, i + 1, j, M, N) +
              uniquePathsWithObstacles(grid, i, j + 1, M, N);
    return m[p] = res;
  }
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty()) return 0;
    int M = obstacleGrid.size();
    int N = obstacleGrid.front().size();
    return uniquePathsWithObstacles(obstacleGrid, 0, 0, M, N);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left
to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

/*
    Submission Date: 2017-06-23
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int M = grid.size();

    if (M == 0) return 0;
    int N = grid[0].size();

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int min_path = INT_MAX;
        if (j > 0) {
          min_path = min(min_path, grid[i][j - 1]);
        }
        if (i > 0) {
          min_path = min(min_path, grid[i - 1][j]);
        }

        min_path = (min_path == INT_MAX) ? 0 : min_path;
        grid[i][j] += min_path;
      }
    }

    return grid[M - 1][N - 1];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
65. Valid Number
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should
gather all requirements up front before implementing one.

/*
    Submission Date: 2017-06-22
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  bool isNumber(string s) {
    int len = s.size();
    bool seen_number = false;
    char last_special = '\0';

    bool seen_non_space = false;

    if (s.front() == 'e' || s.back() == 'e' || s.back() == '-' ||
        s.back() == '+')
      return false;

    for (int i = 0; i < len; i++) {
      if (isdigit(s[i])) {
        seen_number = true;
      } else {
        if (isspace(s[i])) {
          if (seen_number || last_special != '\0') {
            while (++i < len) {
              if (!isspace(s[i])) return false;
            }
          }
        } else if (s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i] == '+') {
          // consecutive '.' not allowed
          if (last_special == s[i]) return false;

          // first char can't be 'e' and last char can't be '-' or 'e'
          if (s[i] == '-' || s[i] == '+') {
            if (last_special != '\0' || seen_number) return false;
          } else if (s[i] == 'e') {
            if (s[i - 1] == '-' || !seen_number) return false;
            if (s[i + 1] == '-' || s[i + 1] == '+') i++;

            seen_number = false;

            // keep iterating until we find a number
            while (++i < len) {
              if (s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i + 1] == '+')
                return false;
              if (isdigit(s[i])) {
                seen_number = true;
              } else if (isspace(s[i])) {
                if (!seen_number) return false;
                while (++i < len) {
                  if (!isspace(s[i])) return false;
                }
              } else {
                return false;
              }
            }

            return seen_number;
          }

          last_special = s[i];
        } else {
          return false;
        }
      }
    }
    return seen_number;
  }
};

int main() {
  Solution s;
  cout << s.isNumber("0") << ' ' << true << endl;
  cout << s.isNumber(" 0.1 ") << ' ' << true << endl;
  cout << s.isNumber("abc") << ' ' << false << endl;
  cout << s.isNumber("1 a") << ' ' << false << endl;
  cout << s.isNumber("1  ") << ' ' << true << endl;
  cout << s.isNumber("2e10") << ' ' << true << endl;
  cout << s.isNumber("-2e10") << ' ' << true << endl;
  cout << s.isNumber("2ee") << ' ' << false << endl;
  cout << s.isNumber(" ") << ' ' << false << endl;
  cout << s.isNumber(".1") << ' ' << true << endl;
  cout << s.isNumber("0e") << ' ' << false << endl;
  cout << s.isNumber(". 1") << ' ' << false << endl;
  cout << s.isNumber("1e.") << ' ' << false << endl;
  cout << s.isNumber("1e.2") << ' ' << false << endl;
  cout << s.isNumber("2e0") << ' ' << true << endl;
  cout << s.isNumber("1.e2") << ' ' << true << endl;
  cout << s.isNumber(".e1") << ' ' << false << endl;
  cout << s.isNumber("1e-.2") << ' ' << false << endl;
  cout << s.isNumber("2e0.1") << ' ' << false << endl;
  cout << s.isNumber("1e2e3") << ' ' << false << endl;
  cout << s.isNumber("0e ") << ' ' << false << endl;
  cout << s.isNumber(" e0") << ' ' << false << endl;
  cout << s.isNumber("3-2") << ' ' << false << endl;
  cout << s.isNumber("+.8") << ' ' << true << endl;
  cout << s.isNumber(" 005047e+6") << ' ' << true << endl;
  cout << s.isNumber("+") << ' ' << false << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
66. Plus One
Given a non-negative integer represented as a non-empty array of digits, plus
one to the integer.

You may assume the integer do not contain any leading zero, except the number 0
itself.

The digits are stored such that the most significant digit is at the head of the
list.

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <vector>

class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    int i = digits.size() - 1;
    int currentSum;
    int carryIn = 1;

    while (carryIn > 0 && i >= 0) {
      currentSum = digits[i] + carryIn;
      digits[i] = currentSum % 10;
      carryIn = currentSum / 10;
      i--;
    }

    if (carryIn > 0) digits.emplace(digits.begin(), carryIn);
    return digits;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
67. Add Binary
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
*/

using namespace std;
#include <string>
#include <unordered_map>

class Solution {
 public:
  unordered_map<char, int> MAP = {{'0', 0}, {'1', 1}};
  string addBinary(string a, string b) {
    string result = "";
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;
    int aCurrent, bCurrent;

    while (i >= 0 && j >= 0) {
      aCurrent = MAP[a[i]];
      bCurrent = MAP[b[j]];
      result = to_string(aCurrent ^ bCurrent ^ carry) + result;
      carry = aCurrent & bCurrent | aCurrent & carry | bCurrent & carry;
      i--;
      j--;
    }

    while (i >= 0) {
      aCurrent = MAP[a[i]];
      result = to_string(aCurrent ^ carry) + result;
      carry &= aCurrent;
      i--;
    }

    while (j >= 0) {
      bCurrent = MAP[b[j]];
      result = to_string(bCurrent ^ carry) + result;
      carry &= bCurrent;
      j--;
    }

    if (carry > 0) result = "1" + result;
    return result;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
68. Text Justification
Given an array of words and a length L, format the text such that each line has
exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line do not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is
inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do
in this case? In this case, that line should be left-justified.

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> res;
    int len = words.size();
    for (int i = 0; i < len; i++) {
      int temp = i;
      int count = 1;
      int width = words[i].size();
      while (++temp < len) {
        if (width + count - 1 >= maxWidth) break;
        width += words[temp].size();
        count++;
      }

      string line = "";
      // either last line or fits
      if (width + count - 1 <= maxWidth) {
        for (int j = i; j < temp; j++)
          line += words[j] + ((j == temp - 1) ? "" : " ");
      } else {
        // now below maxWidth and add spacing
        width -= words[--temp].size();
        count--;

        if (count == 1) {
          line = words[i];
        } else {
          int num_spaces = (maxWidth - width) / (count - 1);
          string space = string(num_spaces, ' ');

          int remainder_space = (maxWidth - width) % (count - 1);

          for (int j = i; j < temp; j++) {
            line += words[j];
            if (j != temp - 1) {
              line += space + (remainder_space-- > 0 ? " " : "");
            }
          }
        }
      }

      while (line.size() != maxWidth) line += " ";
      res.push_back(line);
      i = temp - 1;
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
69. Sqrt(x)
Implement int sqrt(int x).

Compute and return the square root of x.
/*
    Submission Date: 2017-01-19
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

class Solution {
 public:
  int mySqrt(int x) {
    if (x == 0) return 0;
    int low = 1;
    int high = x;
    int mid, midComplement;
    while (true) {
      mid = (low + high) / 2;
      if (midComplement == mid) {
        return mid;
      } else if (mid > x / mid) {
        high = mid - 1;
      } else if (mid + 1 > x / (mid + 1)) {
        return mid;
      } else {
        low = mid + 1;
      }
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?

Note: Given n will be a positive integer.

/*
    Submission Date: 2017-06-18
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int climbStairs(int n) {
    if (n == 0) return 0;

    int two_behind = 1;
    int one_behind = 2;

    while (--n) {
      int new_val = two_behind + one_behind;
      two_behind = one_behind;
      one_behind = new_val;
    }

    return two_behind;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
71. Simplify Path
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together,
such as "/home//foo/". In this case, you should ignore redundant slashes and
return "/home/foo".

/*
    Submission Date: 2017-06-22
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

class Solution {
 public:
  string simplifyPath(string path) {
    path += "/";

    stack<string> s;

    stringstream ss(path);
    string token;
    while (getline(ss, token, '/')) {
      // cout << "SS" << token << endl;
      if (token.empty() || token == ".")
        continue;
      else if (token == "..") {
        if (!s.empty()) s.pop();
      } else
        s.push(token);
    }

    string res;
    while (!s.empty()) {
      res = s.top() + (res.empty() ? "" : "/" + res);
      s.pop();
    }

    return "/" + res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
72. Edit Distance
Given two words word1 and word2, find the minimum number of steps required to
convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

/*
    Submission Date: 2017-06-22
    Runtime: 13 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int minDistance(string word1, string word2) {
    int M = word1.size();
    int N = word2.size();

    int dp[M + 1][N + 1];
    for (int i = 0; i <= M; i++) dp[i][0] = i;
    for (int i = 0; i <= N; i++) dp[0][i] = i;

    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= N; j++) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
        }
      }
    }

    return dp[M][N];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
73. Set Matrix Zeroes
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do
it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

/*
    Submission Date: 2017-06-23
    Runtime: 65 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int M = matrix.size();
    if (M == 0) return;
    int N = matrix[0].size();

    bool has_zero_first_row = false;
    bool has_zero_first_col = false;

    for (int i = 0; i < M; i++) {
      if (matrix[i][0] == 0) {
        has_zero_first_col = true;
      }
    }

    for (int j = 0; j < N; j++) {
      if (matrix[0][j] == 0) {
        has_zero_first_row = true;
      }
    }

    for (int i = 1; i < M; i++) {
      for (int j = 1; j < N; j++) {
        if (matrix[i][j] == 0) {
          // mark row and column
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    for (int i = 1; i < M; i++) {
      for (int j = 1; j < N; j++) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }

    if (has_zero_first_row) {
      for (int j = 0; j < N; j++) {
        matrix[0][j] = 0;
      }
    }

    if (has_zero_first_col) {
      for (int i = 0; i < M; i++) {
        matrix[i][0] = 0;
      }
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
74. Search a 2D Matrix
Write an efficient algorithm that searches for a value in an m x n matrix. This
matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous
row. For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.

/*
    Submission Date: 2017-06-23
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int M = matrix.size();
    if (M == 0) return false;
    int N = matrix[0].size();

    int j = N - 1;
    for (int i = 0; i < M; i++) {
      for (; j >= 0; j--) {
        if (matrix[i][j] == target)
          return true;
        else if (matrix[i][j] < target) {
          // skip row
          break;
        } else {
          continue;
        }
      }
    }

    return false;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
75. Sort Colors
Given an array with n objects colored red, white or blue, sort them so that
objects of the same color are adjacent, with the colors in the order red, white
and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white,
and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite
array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

enum Color { red, white, blue };

class Solution {
 public:
  void sortColors(vector<int>& nums) {
    int len = nums.size();
    int left_bound = 0;
    int right_bound = len - 1;
    while (left_bound < len) {
      if (nums[left_bound] != red) break;
      left_bound++;
    }

    while (right_bound >= 0) {
      if (nums[right_bound] != blue) break;
      right_bound--;
    }

    int i = left_bound;
    while (i <= right_bound) {
      switch (nums[i]) {
        case red:
          swap(nums[left_bound], nums[i]);
          left_bound++;
          i = max(left_bound, i);
          break;
        case blue:
          swap(nums[right_bound], nums[i]);
          right_bound--;
          break;
        case white:
          i++;
          break;
      }
    }
  }
};

int main() { return 0; }