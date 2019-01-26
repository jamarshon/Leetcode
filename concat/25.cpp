
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
525. Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

/*
    Submission Date: 2017-04-01
    Runtime: 162 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLen = 0;
        int currentSum = 0;
        
        // unordered_map has key to currentSum and value to earliest index seen with that 
        // currentSum. the idea is that if the cumulative sum is the same then the sum of 
        // elements between those two indices is zero meaning equal number of 0's and 1's
        // so finding the smallest index with the same currentSum results in the largest subarray
        unordered_map<int, int> m = {{0, -1}};
    
        for(int i = 0, len = nums.size(); i < len; i++) {
            if(nums[i] == 0) {
                currentSum--;
            } else {
                currentSum++;
            }
            
            if(m.find(currentSum) == m.end()) {
                m[currentSum] = i;
            } else {
                maxLen = max(maxLen, i - m[currentSum]);
            }
        }
        
        return maxLen;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
529. Minesweeper
Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an
unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a
revealed blank square that has no adjacent (above, below, left, right, and all 4
diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to
this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the
unrevealed squares ('M' or 'E'), return the board after revealing this position
according to the following rules:



If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to
revealed blank ('B') and all of its adjacent unrevealed squares should be
revealed recursively.
If an empty square ('E') with at least one adjacent mine is revealed, then
change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.



Example 1:
Input:

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:




Example 2:
Input:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:






Note:

The range of the input matrix's height and width is [1,50].
The click position will only be an unrevealed square ('M' or 'E'), which also
means the input board contains at least one clickable square.
The input board won't be a stage when game is over (some mines have been
revealed).
For simplicity, not mentioned rules should be ignored in this problem. For
example, you don't need to reveal all the unrevealed mines when the game is
over, consider any cases that you will win the game or flag any squares.

/*
    Submission Date: 2018-07-05
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void dfs(vector<vector<char>>& board, const int i, const int j, int N,
           int M) {
    if (board[i][j] == 'B') return;

    int mine_count = 0;
    vector<pair<int, int>> to_visit;

    for (int ii = -1; ii <= 1; ii++) {
      int new_i = i + ii;
      if (!(0 <= new_i && new_i < N)) continue;
      for (int jj = -1; jj <= 1; jj++) {
        if (ii == 0 && jj == 0) continue;
        int new_j = j + jj;
        if (!(0 <= new_j && new_j < M)) continue;

        if (board[new_i][new_j] == 'M') {
          mine_count++;
        } else if (board[new_i][new_j] == 'B') {
          continue;
        } else {  // board[new_i][new_j] == 'E'
          to_visit.emplace_back(new_i, new_j);
        }
      }
    }

    if (mine_count > 0) {
      board[i][j] = mine_count + '0';
    } else {
      board[i][j] = 'B';
      for (const auto& kv : to_visit) {
        dfs(board, kv.first, kv.second, N, M);
      }
    }
  }

  vector<vector<char>> updateBoard(vector<vector<char>>& board,
                                   vector<int>& click) {
    int N = board.size();
    int M = board[0].size();
    int y = click[0];
    int x = click[1];

    if (board[y][x] == 'M') {
      board[y][x] = 'X';
    } else {  // board[y][x] == 'E'
      dfs(board, y, x, N, M);
    }

    return board;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
530. Minimum Absolute Difference in BST
Given a binary search tree with non-negative values, find the minimum absolute
difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1
(or between 2 and 3). Note: There are at least two nodes in this BST.
/*
    Submission Date: 2018-06-07
    Runtime: 19 ms
    Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
 public:
  /*
  help called on node returns the smallest and largest value with node as the
  root this means for a node, it is help(root->left)'s smallest value and
  help(root->right)'s largest value if they exist else it is just the node
  
  the minimum difference is this node minus largest value in the left subtree or
  smallest value in right subtree minus this node
  */
  vector<int> help(TreeNode* root, int& res) {
    if (root == NULL) return {};
    vector<int> left = help(root->left, res);
    vector<int> right = help(root->right, res);

    int min_left = left.empty() ? root->val : left[0];
    int max_right = right.empty() ? root->val : right[1];

    if (!left.empty()) res = min(res, root->val - left[1]);
    if (!right.empty()) res = min(res, right[0] - root->val);

    return {min_left, max_right};
  }

  int getMinimumDifference(TreeNode* root) {
    int res = INT_MAX;
    help(root, res);
    return res;
  }
};

class Solution {
 public:
  /*
  inorder traversal keeping tracking of prev
  */
  void help(TreeNode* root, int& res, int& prev) {
    if (root == NULL) return;
    help(root->left, res, prev);
    if (prev != INT_MAX) {
      res = min(res, root->val - prev);
    }

    prev = root->val;
    help(root->right, res, prev);
  }

  int getMinimumDifference(TreeNode* root) {
    int res = INT_MAX, prev = INT_MAX;
    help(root, res, prev);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
532. K-diff Pairs in an Array
Given an array of integers and an integer k, you need to find the number of
unique k-diff pairs in the array. Here a k-diff pair is defined as an integer
pair (i, j), where i and j are both numbers in the array and their absolute
difference is k.

Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique
pairs. Example 2: Input:[1, 2, 3, 4, 5], k = 1 Output: 4 Explanation: There are
four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5). Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Note:
The pairs (i, j) and (j, i) count as the same pair.
The length of the array won't exceed 10,000.
All the integers in the given input belong to the range: [-1e7, 1e7].
/*
    Submission Date: 2018-06-24
    Runtime: 43 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int findPairs(vector<int>& nums, int k) {
    if (k < 0) return 0;
    int res = 0;
    unordered_set<int> st;
    unordered_set<int> counted;
    for (const auto& e : nums) {
      if (st.count(e)) {
        counted.insert(e);
        continue;
      }
      res += st.count(e + k);
      res += st.count(e - k);
      st.insert(e);
    }

    return k == 0 ? counted.size() : res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
535. Encode and Decode TinyURL
TinyURL is a URL shortening service where you enter a URL such as
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as
http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no
restriction on how your encode/decode algorithm should work. You just need to
ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded
to the original URL.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
A vector and return the encoded as an index to retrieve the original string
The encode called upon the same string should not return the same encoded string
as it would have collision problems so usually a randomizer and a storage of
encoded to original is needed.
*/
class Solution {
 public:
  vector<string> m;
  // Encodes a URL to a shortened URL.
  string encode(string longUrl) {
    m.push_back(longUrl);
    return to_string(m.size());
  }

  // Decodes a shortened URL to its original URL.
  string decode(string shortUrl) { return m[stoi(shortUrl) - 1]; }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
536. Construct Binary Tree from String
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, 
one or two pairs of parenthesis. The integer represents the root's value and a pair 
of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   

Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.

/*
    Submission Date: 2017-03-11
    Runtime: 42 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* str2tree(string s) {
        int len = s.size();
        if(len == 0) return NULL;

        int firstBracketIndex = s.find('(');
        if(firstBracketIndex == string::npos) return new TreeNode(stoi(s));

        TreeNode* node = new TreeNode(stoi(s.substr(0, firstBracketIndex)));
        int count = 1;
        int offset = firstBracketIndex + 1;
        int i = offset;

        while(count != 0) {
            if(s[i] == ')') count--;
            else if(s[i] == '(') count++;
            i++;
        }

        string leftExpression = s.substr(offset, i - 1 - offset);
        string rightExpression = (i == len) ? "" : s.substr(i + 1, len - i - 2);

        node -> left = str2tree(leftExpression);
        node -> right = str2tree(rightExpression);

        return node;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
537. Complex Number Multiplication
Given two strings representing two complex numbers.

You need to return a string representing their multiplication. Note i2 = -1
according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to
the form of 0+2i. Example 2: Input: "1+-1i", "1+-1i" Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it
to the form of 0+-2i. Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b
will both belong to the range of
[-100, 100]. And the output should be also in this form.
/*
    Submission Date: 2018-06-24
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <tuple>

using namespace std;

class Solution {
 public:
  pair<int, int> Extract(string S) {
    int plus_S_ind = S.find("+");
    string a = S.substr(0, plus_S_ind);
    string b = S.substr(plus_S_ind + 1, S.size() - (plus_S_ind + 1) - 1);
    return {stoi(a), stoi(b)};
  }
  string complexNumberMultiply(string S1, string S2) {
    int a, b, c, d;
    tie(a, b) = Extract(S1);
    tie(c, d) = Extract(S2);

    int real = a * c - b * d;
    int imag = b * c + d * a;

    string res = to_string(real) + "+" + to_string(imag) + "i";
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
538. Convert BST to Greater Tree
Given a Binary Search Tree (BST), convert it to a Greater Tree such that every
key of the original BST is changed to the original key plus sum of all keys
greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
/*
    Submission Date: 2018-06-07
    Runtime:  ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  /*
  reverse inorder traversal with curr storing the sum of all elements greater
  than current node
  */
  void help(TreeNode* node, int& curr) {
    if (node == NULL) return;
    help(node->right, curr);
    node->val += curr;
    curr = node->val;
    help(node->left, curr);
  }
  TreeNode* convertBST(TreeNode* root) {
    int curr = 0;
    help(root, curr);
    return root;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
539. Minimum Time Difference
Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum 
minutes difference between any two time points in the list.

Example 1:
Input: ["23:59","00:00"]
Output: 1

Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.

/*
    Submission Date: 2017-03-11
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

class Solution {
public:
    // Assume time b is larger than a
    int getDifference(string a, string b) {
        int hours = stoi(b.substr(0,2)) - stoi(a.substr(0,2));
        int minutes = stoi(b.substr(3,2)) - stoi(a.substr(3,2));
        return hours*60 + minutes;
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int minDiff = INT_MAX;
        int len = timePoints.size();

        for(int i = 1; i < len; i++) {
            int diff = getDifference(timePoints[i-1], timePoints[i]);
            if(diff < minDiff) minDiff = diff;
        }

        string firstTimePoint = timePoints.front();
        int wrappedHour = stoi(firstTimePoint.substr(0,2)) + 24;
        string wrap = to_string(wrappedHour) + firstTimePoint.substr(2);
        int wrapDiff = getDifference(timePoints.back(), wrap);

        if(wrapDiff < minDiff) minDiff = wrapDiff;
        return minDiff;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
540. Single Element in a Sorted Array
Given a sorted array consisting of only integers where every element appears
twice except for one element which appears once. Find this single element that
appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNonDuplicate(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if ((mid % 2 == 0 && nums[mid] == nums[mid + 1]) ||
          (mid % 2 == 1 && nums[mid] == nums[mid - 1])) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return nums[low];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
541. Reverse String II
Given a string and an integer k, you need to reverse the first k characters for every 2k 
characters counting from the start of the string. If there are less than k characters left, 
reverse all of them. If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>

class Solution {
public:
    string reverseStr(string s, int k) {
        string finalStr = "";
        bool reverse = true;
        int i = 0, len = s.size();
        while(i < len) {
            string currentStr = string(1, s[i++]);
            while(i%k != 0 && i < len) {
                currentStr = reverse ? s[i] + currentStr : currentStr + s[i];
                i++;
            }
            finalStr += currentStr;
            reverse ^= true;
        }
        
        return finalStr;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two
nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges
between them.
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  /*
  returns the height of a node so height(root) = 1 + max(height(left),
  height(right)) res can be updated to 2 + height(left) + height(right) as the
  longest path in the left and right go through this node.
  */
  int help(TreeNode* root, int& res) {
    if (root == NULL) return -1;
    int left = help(root->left, res);
    int right = help(root->right, res);
    res = max(res, 2 + left + right);
    return 1 + max(left, right);
  }

  int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    help(root, res);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
547. Friend Circles
There are N students in a class. Some of them are friends, while some are not.
Their friendship is transitive in nature. For example, if A is a direct friend
of B, and B is a direct friend of C, then A is an indirect friend of C. And we
defined a friend circle is a group of students who are direct or indirect
friends.



Given a N*N matrix M representing the friend relationship between students in
the class. If M[i][j] = 1, then the ith and jth students are direct friends with
each other, otherwise not. And you have to output the total number of friend
circles among all the students.


Example 1:
Input:
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend
circle. The 2nd student himself is in a friend circle. So return 2.



Example 2:
Input:
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
students are direct friends, so the 0th and 2nd students are indirect friends.
All of them are in the same friend circle, so return 1.




Note:

N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.

/*
    Submission Date: 2018-07-05
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class UnionFind {
  // key is element, value is rank
  unordered_map<T, int> rank_;
  // key is element, value is parent
  unordered_map<T, T> parent_;

 public:
  bool IsWithinSet(T e) { return parent_.count(e); }

  void CreateSet(T e) {
    assert(!IsWithinSet(e));
    parent_[e] = e;
    rank_[e] = 0;
  }

  // finds the root of e
  T Find(T e) {
    if (parent_[e] != e) {
      // this is not a root (root has parent to be equal itself)
      // so find root and apply path compression along path
      parent_[e] = Find(parent_[e]);
    }
    return parent_[e];
  }

  // unions the sets of e1 and e2 if necessary
  // return whether an union took place
  bool Union(T e1, T e2) {
    T e1_root = Find(e1);
    T e2_root = Find(e2);

    if (e1_root == e2_root) return false;  // same root

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (rank_[e1_root] < rank_[e2_root]) {
      parent_[e1_root] = e2_root;
    } else {
      parent_[e2_root] = e1_root;
      if (rank_[e1_root] == rank_[e2_root]) {
        rank_[e1_root]++;
      }
    }

    return true;
  }
};

class Solution {
 public:
  /*
  basically find how many connected graphs there are
  so use union-find, for every edge from u to v, merge the sets u and v
  at the end find how many sets there are by finding the root of all
  the nodes and counting the distinct ones.
  
  O(N^2) as Union and Find are O(1)
  */
  int findCircleNum(vector<vector<int>>& M) {
    int N = M.size();
    UnionFind<int> uf;
    for (int i = 0; i < N; i++) uf.CreateSet(i);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (M[i][j] == 0) continue;
        uf.Union(i, j);
      }
    }

    unordered_set<int> roots;
    for (int i = 0; i < N; i++) roots.insert(uf.Find(i));
    return roots.size();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
551. Student Attendance Record I
You are given a string representing an attendance record for a student. The
record only contains the following three characters: 'A' : Absent. 'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than
one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his
attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False
/*
    Submission Date: 2018-06-08
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool checkRecord(string s) {
    int l_streak = 0;
    bool seen_absent = false;
    for (const auto& c : s) {
      if (c == 'L') {
        if (l_streak == 2) return false;
        l_streak++;
      } else {
        if (c == 'A') {
          if (seen_absent) return false;
          seen_absent = true;
        }  // c == 'P'

        l_streak = 0;
      }
    }
    return true;
  }
};

int main() { return 0; }