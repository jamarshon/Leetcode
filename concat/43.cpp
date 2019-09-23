
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
985. Sum of Even Numbers After Queries
We have an array A of integers, and an array queries of queries.

For the i-th query val = queries[i][0], index = queries[i][1], we add val to
A[index].  Then, the answer to the i-th query is the sum of the even values of
A.

(Here, the given index = queries[i][1] is a 0-based index, and each query
permanently modifies the array A.)

Return the answer to all queries.  Your answer array should
have answer[i] as the answer to the i-th query.

Example 1:

Input: A = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation:
At the beginning, the array is [1,2,3,4].
After adding 1 to A[0], the array is [2,2,3,4], and the sum of even values is 2
+ 2 + 4 = 8.
After adding -3 to A[1], the array is [2,-1,3,4], and the sum of even values is
2 + 4 = 6.
After adding -4 to A[0], the array is [-2,-1,3,4], and the sum of even values is
-2 + 4 = 2.
After adding 2 to A[3], the array is [-2,-1,3,6], and the sum of even values is
-2 + 6 = 4.

Note:

  1 <= A.length <= 10000
  -10000 <= A[i] <= 10000
  1 <= queries.length <= 10000
  -10000 <= queries[i][0] <= 10000
  0 <= queries[i][1] < A.length
/*
  Submission Date: 2019-02-04
  Runtime: 96 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sumEvenAfterQueries(vector<int>& A,
                                  vector<vector<int>>& queries) {
    int N = queries.size();
    vector<int> res(N);

    int even_sum = 0;
    for (const auto& e : A) {
      if (e % 2 == 0) even_sum += e;
    }

    for (int i = 0; i < N; i++) {
      int val = queries[i][0];
      int ind = queries[i][1];

      if ((A[ind] + val) % 2 == 0) {
        if (A[ind] % 2 == 0) {
          even_sum += val;  // even to new_even
        } else {
          even_sum += A[ind] + val;  // odd to new_even
        }
      } else {
        if (A[ind] % 2 == 0) {
          even_sum -= A[ind];  // even to odd
        }
        // odd to odd nothing happens
      }

      A[ind] += val;
      res[i] = even_sum;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
986. Interval List Intersections
Given two lists of closed intervals, each list of intervals is pairwise disjoint
and in sorted order.

Return the intersection of these two interval lists.

(Formally, a closed interval [a, b] (with a <= b) denotes the set of real
numbers x with a <= x <= b.  The intersection of two closed intervals is a set
of real numbers that is either empty, or can be represented as a closed
interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)

Example 1:

Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
Reminder: The inputs and the desired output are lists of Interval objects, and
not arrays or lists.

Note:

  0 <= A.length < 1000
  0 <= B.length < 1000
  0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
/*
  Submission Date: 2019-02-10
  Runtime: 44 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
 public:
  vector<Interval> intervalIntersection(vector<Interval>& A,
                                        vector<Interval>& B) {
    int i = 0, j = 0;
    int N = A.size(), M = B.size();
    vector<Interval> res;
    res.reserve(N + M);

    while (i < N && j < M) {
      if (A[i].end < B[j].start) {
        i++;
      } else if (B[j].end < A[i].start) {
        j++;
      } else {
        // intersect
        res.emplace_back(max(A[i].start, B[j].start), min(A[i].end, B[j].end));
        if (A[i].end > B[j].end) {
          j++;
        } else if (A[i].end < B[j].end) {
          i++;
        } else {
          i++;
          j++;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

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
997. Find the Town Judge
In a town, there are N people labelled from 1 to N.  There is a rumor that one
of these people is secretly the town judge.

If the town judge exists, then:

  The town judge trusts nobody.
  Everybody (except for the town judge) trusts the town judge.
  There is exactly one person that satisfies properties 1 and 2.

You are given trust, an array of pairs trust[i] = [a, b] representing that the
person labelled a trusts the person labelled b.

If the town judge exists and can be identified, return the label of the town
judge.  Otherwise, return -1.

Example 1:

Input: N = 2, trust = [[1,2]]
Output: 2

Example 2:

Input: N = 3, trust = [[1,3],[2,3]]
Output: 3

Example 3:

Input: N = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1

Example 4:

Input: N = 3, trust = [[1,2],[2,3]]
Output: -1

Example 5:

Input: N = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
Output: 3

Note:

  1 <= N <= 1000
  trust.length <= 10000
  trust[i] are all different
  trust[i][0] != trust[i][1]
  1 <= trust[i][0], trust[i][1] <= N
/*
  Submission Date: 2019-09-23
  Runtime: 172 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int findJudge(int N, vector<vector<int>>& trust) {
    if (N == 1) return 1;

    // num_trusted_by[i] means the number of people who
    // trust person[i], num_people_they_trust means the
    // number of people who person[i] trusts
    unordered_map<int, int> num_people_they_trust, num_trusted_by;

    vector<int> trusted_by_everyone;
    for (const auto& e : trust) {
      num_people_they_trust[e[0]]++;
      num_trusted_by[e[1]]++;
      if (num_trusted_by[e[1]] == N - 1) trusted_by_everyone.push_back(e[1]);
    }

    for (const auto& e : trusted_by_everyone) {
      if (!num_people_they_trust.count(e)) return e;
    }
    return -1;
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
1005. Maximize Sum Of Array After K Negations
Given an array A of integers, we must modify the array in the following way: we
choose an i and replace A[i] with -A[i], and we repeat this process K times in
total.  (We may choose the same index i multiple times.)

Return the largest possible sum of the array after modifying it in this way.

Example 1:

Input: A = [4,2,3], K = 1
Output: 5
Explanation: Choose indices (1,) and A becomes [4,-2,3].

Example 2:

Input: A = [3,-1,0,2], K = 3
Output: 6
Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].

Example 3:

Input: A = [2,-3,-1,5,-4], K = 2
Output: 13
Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].

Note:

  1 <= A.length <= 10000
  1 <= K <= 10000
  -100 <= A[i] <= 100
/*
  Submission Date: 2019-09-21
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestSumAfterKNegations(vector<int>& A, int K) {
    /*
    sort A to toggle the most negative if we can
    if we have remaining K then we should spend it all
    on the smallest absolute value as it has the
    least potential to reduce the sum
    */
    sort(A.begin(), A.end());
    int sum = 0;
    int smallest_abs_val = INT_MAX;
    for (const auto& e : A) {
      smallest_abs_val = min(smallest_abs_val, abs(e));
      if (K > 0 && e <= 0) {
        sum += -e;
        K--;
      } else {
        sum += e;
      }
    }

    if (K > 0) {
      // everything is positive
      if (K % 2 == 1) sum -= 2 * smallest_abs_val;
    }
    return sum;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1007. Minimum Domino Rotations For Equal Row
In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the
i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each
half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same,
or all the values in B are the same.

If it cannot be done, return -1.

Example 1:

Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any
rotations.
If we rotate the second and fourth dominoes, we can make every value in the top
row equal to 2, as indicated by the second figure.

Example 2:

Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of
values equal.

Note:

  1 <= A[i], B[i] <= 6
  2 <= A.length == B.length <= 20000
/*
  Submission Date: 2019-09-22
  Runtime: 192 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int f(const vector<int>& A, const vector<int>& B) {
    int N = A.size();
    int target = A[0];
    int A_cnt = 0;
    int B_cnt = 0;
    for (int i = 0; i < N; i++) {
      if (A[i] != target && B[i] != target) return -1;
      A_cnt += A[i] == target;
      B_cnt += B[i] == target;
    }
    return min(min(B_cnt, N - B_cnt), min(A_cnt, N - A_cnt));
  }
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    /*
    check that every element has either A[0] or B[0]
    count the number of occurences in A or B
    if it is A_cnt it means swap all the occurences in A where (A[i] == target)
    if it is N-A_cnt it means swap all the occurrences in B where
      (B[i] for i where A[i] != target)
    if it is B_cnt it means swap all the occurences in B where (B[i] == target)
    if it is N-B_cnt it means swap all the occurrences in A where
      (A[i] for i where B[i] != target)
    */
    int f1 = f(A, B);
    int f2 = f(B, A);
    if (f1 == -1)
      return f2;
    else if (f2 == -1)
      return f1;
    else
      return min(f1, f2);
  }
};

class Solution2 {
 public:
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    /*
    get the most frequent character in A and B, assume A's most
    frequent character > B's most frequent character
    A_freq[A_max_key] should at least be N/2 as to cover the whole
    array, the minimum size of a half is N/2
    A_freq[A_max_key] + B_freq[B_max_key] >= N as there should be
    enough characters in B to make N
    just swap all non A_max_key in B which is N - A_freq[A_max_key]
    need to check that for i in A[i] B[i] must have at least one
    A_max_key
    */
    unordered_map<int, int> A_freq, B_freq;
    int A_max_key = -1;
    for (const auto& e : A) {
      A_freq[e]++;
      if (A_max_key == -1 || A_freq[A_max_key] < A_freq[e]) A_max_key = e;
    }
    int B_max_key = -1;
    for (const auto& e : B) {
      B_freq[e]++;
      if (B_max_key == -1 || B_freq[B_max_key] < B_freq[e]) B_max_key = e;
    }

    if (A_freq[A_max_key] < B_freq[B_max_key]) {
      A_freq.swap(B_freq);
      A.swap(B);
      swap(A_max_key, B_max_key);
    }

    // A has the majority frequency
    int N = A.size();
    if (A_freq[A_max_key] < N / 2 || A_freq[A_max_key] + B_freq[B_max_key] < N)
      return -1;
    for (int i = 0; i < N; i++) {
      if (A[i] != A_max_key && B[i] != A_max_key) return -1;
    }
    return N - A_freq[A_max_key];
  }
};

int main() { return 0; }
