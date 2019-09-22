
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
988. Smallest String Starting From Leaf
Given the root of a binary tree, each node has a value from 0 to 25 representing
the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents
'b', and so on.

Find the lexicographically smallest string that starts at a leaf of this tree
and ends at the root.

(As a reminder, any shorter prefix of a string is lexicographically smaller: for
example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a
node that has no children.)

Example 1:

Input: [0,1,2,3,4,3,4]
Output: "dba"

Example 2:

Input: [25,1,3,1,3,0,2]
Output: "adz"

Example 3:

Input: [2,2,1,null,1,0,null,0]
Output: "abc"

Note:

  The number of nodes in the given tree will be between 1 and 1000.
  Each node in the tree will have a value between 0 and 25.
/*
  Submission Date: 2019-02-17
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  string smallestFromLeaf(TreeNode *root) {
    if (!root) return "";
    string left = smallestFromLeaf(root->left);
    string right = smallestFromLeaf(root->right);
    char c = root->val + 'a';
    // if left and right is empty, this is leaf return c
    // if left or right is empty, this isnt a leaf return the non empty + c
    // if both or right isnt empty, return the smallest one + c
    if (left.empty()) return right + c;
    if (right.empty()) return left + c;
    return min(left, right) + c;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
989. Add to Array-Form of Integer
For a non-negative integer X, the array-form of X is an array of its digits in
left to right order.  For example, if X = 1231, then the array form
is [1,2,3,1].

Given the array-form A of a non-negative integer X, return the array-form of the
integer X+K.

Example 1:

Input: A = [1,2,0,0], K = 34
Output: [1,2,3,4]
Explanation: 1200 + 34 = 1234

Example 2:

Input: A = [2,7,4], K = 181
Output: [4,5,5]
Explanation: 274 + 181 = 455

Example 3:

Input: A = [2,1,5], K = 806
Output: [1,0,2,1]
Explanation: 215 + 806 = 1021

Example 4:

Input: A = [9,9,9,9,9,9,9,9,9,9], K = 1
Output: [1,0,0,0,0,0,0,0,0,0,0]
Explanation: 9999999999 + 1 = 10000000000

Note：

  1 <= A.length <= 10000
  0 <= A[i] <= 9
  0 <= K <= 10000
  If A.length > 1, then A[0] != 0
/*
  Submission Date: 2019-02-10
  Runtime: 132 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> addToArrayForm(vector<int>& A, int K) {
    reverse(A.begin(), A.end());
    int i = 0;
    int carry = 0;
    while (K || carry) {
      int k = K % 10 + carry;
      if (i == A.size()) {
        A.push_back(k % 10);
      } else {
        k += A[i];
        A[i] = k % 10;
      }

      carry = k / 10;
      i++;
      K /= 10;
    }

    reverse(A.begin(), A.end());
    return A;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
993. Cousins in Binary Tree
In a binary tree, the root node is at depth 0, and children of each depth k node
are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have
different parents.

We are given the root of a binary tree with unique values, and the values x and
y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are
cousins.

Example 1:

Input: root = [1,2,3,4], x = 4, y = 3
Output: false

Example 2:

Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true

Example 3:

Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false

Note:

  The number of nodes in the tree will be between 2 and 100.
  Each node has a unique integer value from 1 to 100.
/*
  Submission Date: 2019-02-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool isCousins(TreeNode* root, int x, int y) {
    if (!root || root->val == x || root->val == y) return false;
    queue<TreeNode*> q;
    q.push(root);
    vector<TreeNode*> v;
    while (!q.empty()) {
      for (int i = 0, size = q.size(); i < size; i++) {
        TreeNode* curr = q.front();
        q.pop();
        if (curr->left) {
          q.push(curr->left);
          if (q.back()->val == x || q.back()->val == y) {
            v.push_back(curr);
          }
        }

        if (curr->right) {
          q.push(curr->right);
          if (q.back()->val == x || q.back()->val == y) {
            v.push_back(curr);
          }
        }
      }

      if (!v.empty()) {
        if (v.size() != 2) return false;
        return v[0] != v[1];
      }
    }

    return false;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
994. Rotting Oranges
In a given grid, each cell can have one of three values:

  the value 0 representing an empty cell;
  the value 1 representing a fresh orange;
  the value 2 representing a rotten orange.

Every minute, any fresh orange that is adjacent (4-directionally) to a rotten
orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh
orange.  If this is impossible, return -1 instead.

Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never
rotten, because rotting only happens 4-directionally.

Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer
is just 0.

Note:

  1 <= grid.length <= 10
  1 <= grid[0].length <= 10
  grid[i][j] is only 0, 1, or 2.
/*
  Submission Date: 2019-02-17
  Runtime: 16 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

enum Orange { kEmpty, kFresh, kRotten };

class Solution {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

 public:
  typedef pair<int, int> pii;
  int orangesRotting(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;

    int num_fresh = 0;
    queue<pii> q;
    int N = grid.size();
    int M = grid[0].size();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] == kFresh)
          num_fresh++;
        else if (grid[i][j] == kRotten)
          q.emplace(i, j);
      }
    }

    int minutes = 0;
    int i, j;
    while (!q.empty() && num_fresh > 0) {
      minutes++;
      for (int l = 0, size = q.size(); l < size; l++) {
        tie(i, j) = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
          int new_i = i + dx[k];
          int new_j = j + dy[k];
          if (0 <= new_i && new_i < N && 0 <= new_j && new_j < M &&
              grid[new_i][new_j] == kFresh) {
            grid[new_i][new_j] = kRotten;
            num_fresh--;
            q.emplace(new_i, new_j);
          }
        }
      }
    }

    return (num_fresh == 0) ? minutes : -1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
999. Available Captures for Rook
On an 8 x 8 chessboard, there is one white rook.  There also may be empty
squares, white bishops, and black pawns.  These are given as characters 'R',
'.', 'B', and 'p' respectively. Uppercase characters represent white pieces, and
lowercase characters represent black pieces.

The rook moves as in the rules of Chess: it chooses one of four cardinal
directions (north, east, west, and south), then moves in that direction until it
chooses to stop, reaches the edge of the board, or captures an opposite colored
pawn by moving to the same square it occupies.  Also, rooks cannot move into the
same square as other friendly bishops.

Return the number of pawns the rook can capture in one move.

Example 1:

Input:
[[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation:
In this example the rook is able to capture all the pawns.

Example 2:

Input:
[[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 0
Explanation:
Bishops are blocking the rook to capture any pawn.

Example 3:

Input:
[[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation:
The rook can capture the pawns at positions b5, d6 and f5.

Note:

  board.length == board[i].length == 8
  board[i][j] is either 'R', '.', 'B', or 'p'
  There is exactly one cell with board[i][j] == 'R'
/*
  Submission Date: 2019-09-03
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int di[4] = {0, 0, 1, -1};
  int dj[4] = {1, -1, 0, 0};

  int numRookCaptures(vector<vector<char>>& board) {
    int N = board.size();
    int M = board[0].size();

    int rook_i = -1, rook_j = -1;
    // find the rook
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (board[i][j] == 'R') {
          rook_i = i;
          rook_j = j;
          i = board.size();
          break;
        }
      }
    }

    int cnt = 0;
    // traverse in 4 directions until reaching a piece
    for (int k = 0; k < 4; k++) {
      int i = rook_i;
      int j = rook_j;
      while (0 <= i && i < N && 0 <= j && j < M) {
        if (board[i][j] == 'p') {
          cnt++;
          break;
        } else if (board[i][j] == 'B') {
          break;
        }
        i += di[k];
        j += dj[k];
      }
    }
    return cnt;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1002. Find Common Characters
Given an array A of strings made only from lowercase letters, return a list of
all characters that show up in all strings within the list (including
duplicates).  For example, if a character occurs 3 times in all strings but not
4 times, you need to include that character three times in the final answer.

You may return the answer in any order.

Example 1:

Input: ["bella","label","roller"]
Output: ["e","l","l"]

Example 2:

Input: ["cool","lock","cook"]
Output: ["c","o"]

Note:

  1 <= A.length <= 100
  1 <= A[i].length <= 100
  A[i][j] is a lowercase letter
/*
  Submission Date: 2019-09-03
  Runtime: 28 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> commonChars(vector<string>& A) {
    // get the min occurence of each letter for each string
    // include missing characters so that the min
    // occurence would be zero making it not show in the
    // output
    vector<int> cnt(26, INT_MAX);
    for (const auto& s : A) {
      vector<int> cnt1(26, 0);
      for (const auto& c : s) cnt1[c - 'a']++;
      for (int i = 0; i < 26; i++) cnt[i] = min(cnt[i], cnt1[i]);
    }

    vector<string> res;
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < cnt[i]; j++) res.push_back(string(1, i + 'a'));
    }
    return res;
  }
};

class Solution2 {
 public:
  vector<string> commonChars(vector<string>& A) {
    // count how many strings has a certain letter in
    // `freq_cnt`. count the minimum frequency of a
    // letter in `min_freq_cnt`
    unordered_map<char, int> freq_cnt, min_freq_cnt;
    for (const auto& s : A) {
      unordered_map<char, int> s_freq;
      for (const auto& c : s) s_freq[c]++;
      for (const auto& kv : s_freq) {
        freq_cnt[kv.first]++;
        if (!min_freq_cnt.count(kv.first)) {
          min_freq_cnt[kv.first] = kv.second;
        } else {
          min_freq_cnt[kv.first] = min(min_freq_cnt[kv.first], kv.second);
        }
      }
    }

    vector<string> res;
    for (const auto& kv : freq_cnt) {
      // if the letter does not appear in every string skip it
      if (kv.second != A.size()) continue;
      // repeat the min occurences of the letter in the result
      int occurences = min_freq_cnt[kv.first];
      for (int i = 0; i < occurences; i++) res.push_back(string(1, kv.first));
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1009. Complement of Base 10 Integer
Every non-negative integer N has a binary representation.  For example, 5 can be
represented as "101" in binary, 11 as "1011" in binary, and so on.  Note that
except for N = 0, there are no leading zeroes in any binary representation.

The complement of a binary representation is the number in binary you get when
changing every 1 to a 0 and 0 to a 1.  For example, the complement of "101" in
binary is "010" in binary.

For a given number N in base-10, return the complement of it's binary
representation as a base-10 integer.

Example 1:

Input: 5
Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2
in base-10.

Example 2:

Input: 7
Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0
in base-10.

Example 3:

Input: 10
Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is
5 in base-10.

Note:

  0 <= N < 10^9
/*
  Submission Date: 2019-09-17
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  int bitwiseComplement(int N) {
    if (N == 0) return 1;
    int num_bits = floor(log2(N)) + 1;
    // return last num_bits
    return ~N & ((1 << num_bits) - 1);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1013. Partition Array Into Three Parts With Equal Sum
Given an array A of integers, return true if and only if we can partition the
array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i+1 < j with (A[0] +
A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... +
A[A.length - 1])

Example 1:

Input: [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

Example 2:

Input: [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false

Example 3:

Input: [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

Note:

  3 <= A.length <= 50000
  -10000 <= A[i] <= 10000
/*
  Submission Date: 2019-09-18
  Runtime: 68 ms
  Difficulty: EASY
*/
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canThreePartsEqualSum(vector<int>& A) {
    /*
    get the total sum of the array, if its not divisible
    by three return false.
    iterate and increment until reaching the total sum / 3 then
    increase the number of parts by one and reset the sum
    if there are three parts then return true
    */
    int total_sum = accumulate(A.begin(), A.end(), 0);
    if (total_sum % 3 != 0) return false;
    int part_sum = total_sum / 3;
    int sum = 0;
    int num_parts = 0;
    for (const auto& e : A) {
      sum += e;
      if (sum == part_sum) {
        sum = 0;
        num_parts++;
      }
    }
    return num_parts == 3;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1021. Remove Outermost Parentheses
A valid parentheses string is either empty (""), "(" + A + ")", or A + B, where
A and B are valid parentheses strings, and + represents string concatenation. 
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses
strings.

A valid parentheses string S is primitive if it is nonempty, and there does not
exist a way to split it into S = A+B, with A and B nonempty valid parentheses
strings.

Given a valid parentheses string S, consider its primitive decomposition: S =
P_1 + P_2 + ... + P_k, where P_i are primitive valid parentheses strings.

Return S after removing the outermost parentheses of every primitive string in
the primitive decomposition of S.

Example 1:

Input: "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" +
"(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:

Input: "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())"
+ "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())"
= "()()()()(())".

Example 3:

Input: "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

Note:

  S.length <= 10000
  S[i] is "(" or ")"
  S is a valid parentheses string
/*
  Submission Date: 2019-08-25
  Runtime: 12 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string removeOuterParentheses(string S) {
    int cnt = 0;
    string res, token;
    for (const auto& c : S) {
      if (c == '(') {
        cnt++;
      } else {
        cnt--;
      }
      token.push_back(c);
      if (cnt == 0) {
        res += token.substr(1, token.size() - 2);
        token = "";
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1022. Sum of Root To Leaf Binary Numbers
Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path
represents a binary number starting with the most significant bit.  For example,
if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary,
which is 13.

For all leaves in the tree, consider the numbers represented by the path from
the root to that leaf.

Return the sum of these numbers.

Example 1:

Input: [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

Note:

  The number of nodes in the tree is between 1 and 1000.
  node.val is 0 or 1.
  The answer will not exceed 2^31 - 1.
/*
  Submission Date: 2019-09-17
  Runtime: 8 ms
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
  int sumRootToLeaf(TreeNode* root) {
    int res = 0;
    f(root, res, 0);
    return res;
  }

  void f(TreeNode* root, int& res, int curr) {
    if (root == nullptr) return;
    curr = curr * 2 + root->val;
    if (root->left == nullptr && root->right == nullptr) {
      res += curr;
    } else {
      f(root->left, res, curr);
      f(root->right, res, curr);
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1025. Divisor Game
Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number N on the chalkboard.  On each player's turn, that
player makes a move consisting of:

  Choosing any x with 0 < x < N and N % x == 0.
  Replacing the number N on the chalkboard with N - x.

Also, if a player cannot make a move, they lose the game.

Return True if and only if Alice wins the game, assuming both players play
optimally.

Example 1:

Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:

Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

Note:

  1 <= N <= 1000
/*
  Submission Date: 2019-09-07
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool divisorGame(int N) {
    // suppose N is odd, then it cannot be divided by 2
    // or any multiples of 2. the divisor is odd meaning
    // N - divisor would be odd - odd = even. hence, if
    // N is odd, then the current user will have to make
    // it even for the next user.
    //
    // if N is even, the current user can force the
    // opponent to get an odd number by subtracting one.
    //
    // even => odd
    // odd => even
    //
    // base case odd 1 is a lost
    // at even 2, it is a win as even (2) => odd (1)
    // at odd 3, it is a lost as odd (3) => even (2) => odd (1)
    // at even 4, it is a win as even (4) => odd (3) => even (2) => odd (1)
    // thus, we can win only if N is even by forcing
    // the oponent to get odd numbers until they reach 1
    return N % 2 == 0;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1029. Two City Scheduling
There are 2N people a company is planning to interview. The cost of flying the
i-th person to city A is costs[i][0], and the cost of flying the i-th person to
city B is costs[i][1].

Return the minimum cost to fly every person to a city such that exactly N people
arrive in each city.

Example 1:

Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation:
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people
interviewing in each city.

Note:

  1 <= costs.length <= 100
  It is guaranteed that costs.length is even.
  1 <= costs[i][0], costs[i][1] <= 1000
/*
  Submission Date: 2019-09-20
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    /*
    dp[i][j] represents the min cost of i + j people where
    i people go to A and j people go to B. this represents
    people from indices [0, i + j]
    dp[0][j] would just be the cumulative cost of B
    dp[i][0] would just be the cumulative cost of A
    dp[i][j] = min(
        dp[i-1][j] + costs[i+j-1][0], // person goes to A
        dp[i][j-1] + costs[i+j-1][1] // person goes to B
      )
    */
    int N = costs.size() / 2;
    int dp[N + 1][N + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) dp[i][0] = dp[i - 1][0] + costs[i - 1][0];
    for (int j = 1; j <= N; j++) dp[0][j] = dp[0][j - 1] + costs[j - 1][1];
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        dp[i][j] = min(dp[i - 1][j] + costs[i + j - 1][0],
                       dp[i][j - 1] + costs[i + j - 1][1]);
    return dp[N][N];
  }
};

class Solution2 {
 public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    /*
    for a person if they go to one city for costs[i][0], it means
    we get the benefit of not going to the other city by costs[i][1] -
    costs[i][0]

    e.g 100 to go to city A and 110 to go to city B, if they go
    to city A we save 110-100=10

    so we sort by the savings and the top half savings go to A
    the bottom half go to B
    */
    sort(costs.begin(), costs.end(),
         [](const vector<int>& left, const vector<int>& right) {
           return left[0] - left[1] < right[0] - right[1];
         });

    int res = 0;
    for (int i = 0, N = costs.size(); i < N; i++) {
      res += i >= N / 2 ? costs[i][1] : costs[i][0];
    }
    return res;
  }
};

int main() { return 0; }
