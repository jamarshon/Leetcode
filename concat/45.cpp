
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1031. Maximum Sum of Two Non-Overlapping Subarrays
Given an array A of non-negative integers, return the maximum sum of elements in
two non-overlapping (contiguous) subarrays, which have lengths L and M.  (For
clarification, the L-length subarray could occur before or after the M-length
subarray.)

Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) +
(A[j] + A[j+1] + ... + A[j+M-1]) and either:

  0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
  0 <= j < j + M - 1 < i < i + L - 1 < A.length.

Example 1:

Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length
2.

Example 2:

Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with
length 2.

Example 3:

Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with
length 3.

Note:

  L >= 1
  M >= 1
  L + M <= A.length <= 1000
  0 <= A[i] <= 1000
/*
  Submission Date: 2019-09-24
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    /*
    prefix[i] is sum of A from [0, i]
    l_max[i] is max sum of L subarray before last M elements [0, i-M]
      computed as max(l_max,
        prefix[i - M] -  prefix[i-M-L] // the current sum of L subarray
        [i-M-L+1, i-M])
    m_max[i] is max sum of M subarray before last L elements [0, i-L]
      computed as max(m_max,
        prefix[i - L] -  prefix[i-L-M] // the current sum of M subarray
        [i-L-M+1, i-L])

    start m_max at prefix[M-1] and l_max at prefix[L-1]
    start res at prefix[L+M-1] as it is two subarrays of L and M
    */
    int N = A.size();
    vector<int> prefix = A;
    for (int i = 1; i < N; i++) prefix[i] += prefix[i - 1];
    int res = prefix[L + M - 1];
    int m_max = prefix[M - 1];
    int l_max = prefix[L - 1];
    for (int i = L + M; i < N; i++) {
      m_max = max(m_max, prefix[i - L] - prefix[i - L - M]);
      l_max = max(l_max, prefix[i - M] - prefix[i - M - L]);
      res = max(res, max(m_max + prefix[i] - prefix[i - L],
                         l_max + prefix[i] - prefix[i - M]));
    }

    return res;
  }
};

class Solution2 {
 public:
  vector<int> max_sliding_window_sum(const vector<int>& A, const int& K) {
    int N = A.size();
    vector<int> dp(N, 0);
    int sum = 0;
    for (int i = 0; i < N; i++) {
      sum += A[i];
      if (i >= K - 1) {
        if (i - K >= 0) sum -= A[i - K];
        dp[i] = i - 1 >= 0 ? max(dp[i - 1], sum) : sum;
      }
    }
    return dp;
  }

  int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    /*
    [0,6,5,2,2,5,1,9,4], M = 2
    sliding window sums of size 2
    [0, 6, 11, 7, 4, 7, 6, 10, 13]
    B[i] is the maximum sliding window sum for [0, i]
    [0, 6, 11, 11, 11, 11, 11, 11, 13]
    C[i] is the maximum sliding window sum for [i, N)

    dp[i] is partition of [0, i] and [i+1, N)
    dp[i] = B[i] + C[i+1]
    the result is max(dp[i])
    */
    vector<int> A_rev = A;
    reverse(A_rev.begin(), A_rev.end());
    vector<int> l_forward = max_sliding_window_sum(A, L),
                l_backward = max_sliding_window_sum(A_rev, L),
                m_forward = max_sliding_window_sum(A, M),
                m_backward = max_sliding_window_sum(A_rev, M);
    reverse(l_backward.begin(), l_backward.end());
    reverse(m_backward.begin(), m_backward.end());
    int res = 0;
    for (int i = 0; i + 1 < A.size(); i++) {
      res = max(res, l_forward[i] + m_backward[i + 1]);
      res = max(res, m_forward[i] + l_backward[i + 1]);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1033. Moving Stones Until Consecutive
Three stones are on a number line at positions a, b, and c.

Each turn, you pick up a stone at an endpoint (ie., either the lowest or highest
position stone), and move it to an unoccupied position between those endpoints. 
Formally, let's say the stones are currently at positions x, y, z with x < y <
z.  You pick up the stone at either position x or position z, and move that
stone to an integer position k, with x < k < z and k != y.

The game ends when you cannot make any more moves, ie. the stones are in
consecutive positions.

When the game ends, what is the minimum and maximum number of moves that you
could have made?  Return the answer as an length 2 array: answer =
[minimum_moves, maximum_moves]

Example 1:

Input: a = 1, b = 2, c = 5
Output: [1,2]
Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.

Example 2:

Input: a = 4, b = 3, c = 2
Output: [0,0]
Explanation: We cannot make any moves.

Example 3:

Input: a = 3, b = 5, c = 1
Output: [1,2]
Explanation: Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.

Note:

  1 <= a <= 100
  1 <= b <= 100
  1 <= c <= 100
  a != b, b != c, c != a
/*
  Submission Date: 2019-09-23
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> numMovesStones(int a, int b, int c) {
    /*
    if a < b < c, and its a, a + 1, a + 2 then its done and minmove is 0
    if there's a gap a, a + 2 then the minmove is 1 as it can be placed in the
    gap if there's two in a row a, a + 1 then the minmove is 1 as it can be
    placed before or after for max moves its just the number of elements between
    b,a and c,b
    */
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    // a < b < c
    int min_moves;
    if (b - a == 1 && c - b == 1) {
      min_moves = 0;
    } else if (b - a <= 2 || c - b <= 2) {
      min_moves = 1;
    } else {
      min_moves = 2;
    }
    return {min_moves, (c - b - 1) + (b - a - 1)};
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1037. Valid Boomerang
A boomerang is a set of 3 points that are all distinct and not in a straight
line.

Given a list of three points in the plane, return whether these points are a
boomerang.

Example 1:

Input: [[1,1],[2,3],[3,2]]
Output: true

Example 2:

Input: [[1,1],[2,2],[3,3]]
Output: false

Note:

  points.length == 3
  points[i].length == 2
  0 <= points[i][j] <= 100
/*
  Submission Date: 2019-09-23
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isBoomerang(vector<vector<int>>& points) {
    /*
    check if the slope of points[0] points[1] and points[0] points[2]
    are the same

    (points[1][1] - points[0][1])/(points[1][0] - points[0][0])
    != (points[2][1] - points[0][1])/(points[2][0] - points[0][0])
    */
    return (points[1][1] - points[0][1]) * (points[2][0] - points[0][0]) !=
           (points[2][1] - points[0][1]) * (points[1][0] - points[0][0]);
  }
};

class Solution2 {
 public:
  bool isBoomerang(vector<vector<int>>& points) {
    /*
    calculate y=mx+b from points[0] and points[1]
    then check if plugging in points[2] returns the same
    y
    */
    if (points[0] == points[1] || points[0] == points[2] ||
        points[1] == points[2])
      return false;
    int dx = points[1][0] - points[0][0];
    int dy = points[1][1] - points[0][1];
    if (dx == 0) return points[2][0] != points[1][0];
    float m = float(dy) / dx;
    float b = points[0][1] - m * points[0][0];
    return m * points[2][0] + b != points[2][1];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1038. Binary Search Tree to Greater Sum Tree
Given the root of a binary search tree with distinct values, modify it so that
every node has a new value equal to the sum of the values of the original tree
that are greater than or equal to node.val.

As a reminder, a binary search tree is a tree that satisfies these constraints:

  The left subtree of a node contains only nodes with keys less than the node's
key.
  The right subtree of a node contains only nodes with keys greater than the
node's key.
  Both the left and right subtrees must also be binary search trees.

Example 1:

Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Note:

  The number of nodes in the tree is between 1 and 100.
  Each node will have value between 0 and 100.
  The given tree is a binary search tree.
/*
  Submission Date: 2019-09-21
  Runtime: 0 ms
  Difficulty: MEDIUM
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
  int prev = 0;

 public:
  TreeNode* bstToGst(TreeNode* root) {
    // an inorder traversal goes through a sorted array
    // smallest first, if we go the reverse than we
    // visist the largest first and do a cumulative
    // sum
    if (root == nullptr) return nullptr;
    bstToGst(root->right);
    root->val += prev;
    prev = root->val;
    bstToGst(root->left);
    return root;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1042. Flower Planting With No Adjacent
You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4
types of flowers.

paths[i] = [x, y] describes the existence of a bidirectional path from garden x
to garden y.

Also, there is no garden that has more than 3 paths coming into or leaving it.

Your task is to choose a flower type for each garden such that, for any two
gardens connected by a path, they have different types of flowers.

Return any such a choice as an array answer, where answer[i] is the type of
flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or
4.  It is guaranteed an answer exists.

Example 1:

Input: N = 3, paths = [[1,2],[2,3],[3,1]]
Output: [1,2,3]

Example 2:

Input: N = 4, paths = [[1,2],[3,4]]
Output: [1,2,1,2]

Example 3:

Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
Output: [1,2,3,4]

Note:

  1 <= N <= 10000
  0 <= paths.size <= 20000
  No garden has 4 or more paths coming into or leaving it.
  It is guaranteed an answer exists.
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
  vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
    /*
    since a node can only have 3 neighbors, it will always have
    a possible color to choose. just do it greedily.
    */
    unordered_map<int, vector<int>> G;
    for (const auto& e : paths) {
      G[e[0]].push_back(e[1]);
      G[e[1]].push_back(e[0]);
    }

    vector<int> res(N, -1);
    for (int i = 0; i < N; i++) {
      bool colors[5] = {};
      for (const auto& e : G[i + 1]) {
        if (res[e - 1] != -1) colors[res[e - 1]] = true;
      }
      for (int c = 1; c <= 4; c++) {
        if (!colors[c]) res[i] = c;
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1043. Partition Array for Maximum Sum
Given an integer array A, you partition the array into (contiguous) subarrays of
length at most K.  After partitioning, each subarray has their values changed to
become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.

Example 1:

Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]

Note:

  1 <= K <= A.length <= 500
  0 <= A[i] <= 10^6
/*
  Submission Date: 2019-09-23
  Runtime: 460 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumAfterPartitioning(vector<int>& A, int K) {
    /*
    same as before but keep track of the maximum element
    when iterating backwards for the remainder subarray
    */
    int N = A.size();
    vector<int> dp(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
      int res = 0;
      int max_el = INT_MIN;
      for (int j = 1; j <= K && i - j >= 0; j++) {
        max_el = max(max_el, A[i - j]);
        res = max(res, dp[i - j] + j * max_el);
      }
      dp[i] = res;
    }
    return dp[N];
  }
};

class Solution2 {
 public:
  int maxSumAfterPartitioning(vector<int>& A, int K) {
    /*
    dp[i] is the answer for A[0] ... A[i-1]
    dp[0] = 0
    dp[i] = max_{j=[1,K]}(dp[i-j] + j * max_{l=[i-j, i-1]}(A[l]))
    taking the max of previous subarray answer + the remaining
    subarray's maximum value multiplied by its length
    */
    int N = A.size();
    vector<int> dp(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
      int res = 0;
      for (int j = 1; j <= K && i - j >= 0; j++) {
        auto max_el = max_element(A.begin() + (i - 1) - j + 1, A.begin() + i);
        res = max(res, dp[i - j] + j * (*max_el));
      }
      dp[i] = res;
    }
    return dp[N];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1046. Last Stone Weight
We have a collection of rocks, each rock has a positive integer weight.

Each turn, we choose the two heaviest rocks and smash them together.  Suppose
the stones have weights x and y with x <= y.  The result of this smash is:

  If x == y, both stones are totally destroyed;
  If x != y, the stone of weight x is totally destroyed, and the stone of weight
y has new weight y-x.

At the end, there is at most 1 stone left.  Return the weight of this stone (or
0 if there are no stones left.)

Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation:
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value
of last stone.

Note:

  1 <= stones.length <= 30
  1 <= stones[i] <= 1000
/*
  Submission Date: 2019-09-07
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>

using namespace std;

class Solution {
 public:
  int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    while (pq.size() >= 2) {
      auto x = pq.top();
      pq.pop();
      auto y = pq.top();
      pq.pop();

      if (x != y) pq.push(abs(x - y));
    }
    return pq.empty() ? 0 : pq.top();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1047. Remove All Adjacent Duplicates In String
Given a string S of lowercase letters, a duplicate removal consists of choosing
two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is
guaranteed the answer is unique.

Example 1:

Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and
equal, and this is the only possible move.  The result of this move is that the
string is "aaca", of which only "aa" is possible, so the final string is "ca".

Note:

  1 <= S.length <= 20000
  S consists only of English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeDuplicates(string S) {
    // using a stack if we encounter a character
    // that was previously seen then we can pop from
    // the stack and not add the current character.
    // this exposes a previous character in the string
    // which can match with the next character as needed.
    vector<char> stk;
    for (int i = 0; i < S.size(); i++) {
      if (!stk.empty() && stk.back() == S[i])
        stk.pop_back();
      else
        stk.push_back(S[i]);
    }

    return string(stk.begin(), stk.end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1051. Height Checker
Students are asked to stand in non-decreasing order of heights for an annual
photo.

Return the minimum number of students not standing in the right positions. 
(This is the number of students that must move in order for all students to be
standing in non-decreasing order of height.)

Example 1:

Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right
positions.

Note:

  1 <= heights.length <= 100
  1 <= heights[i] <= 100
/*
  Submission Date: 2019-08-25
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // sort the list and see compare elmentwise between
  // the two lists to see how many elements are out of place
  int heightChecker(vector<int>& heights) {
    int res = 0;
    vector<int> v = heights;
    sort(v.begin(), v.end());
    for (int i = 0; i < heights.size(); i++) res += v[i] != heights[i];
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1071. Greatest Common Divisor of Strings
For strings S and T, we say "T divides S" if and only if S = T + ... + T  (T
concatenated with itself 1 or more times)

Return the largest string X such that X divides str1 and X divides str2.

Example 1:

Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

Example 2:

Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

Example 3:

Input: str1 = "LEET", str2 = "CODE"
Output: ""

Note:

  1 <= str1.length <= 1000
  1 <= str2.length <= 1000
  str1[i] and str2[i] are English uppercase letters.
/*
  Submission Date: 2019-09-21
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  string gcdOfStrings(string str1, string str2) {
    /*
    Lyndon and Schützenberger states that A+B=B+A
    (commutative concatenation) iff A and B consist of a
    substring C where  C^i = C+...+C = A and C^j = C+...+C = B
    ie both strings are the powers of the same
    string
    */
    return str1 + str2 == str2 + str1
               ? str1.substr(0, gcd(str1.size(), str2.size()))
               : "";
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1078. Occurrences After Bigram
Given words first and second, consider occurrences in some text of the form
"first second third", where second comes immediately after first, and third
comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second
= "good"
Output: ["girl","student"]

Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]

Note:

  1 <= text.length <= 1000
  text consists of space separated words, where each word consists of lowercase
English letters.
  1 <= first.length, second.length <= 10
  first and second consist of lowercase English letters.
/*
  Submission Date: 2019-09-04
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  // store the last two words and return the current word
  // if the last two words match `first`, `second`
  vector<string> findOcurrences(string text, string first, string second) {
    vector<string> res;
    stringstream ss(text);
    string token;
    string last, lastlast;
    while (ss >> token) {
      if (lastlast.empty()) {
        lastlast = token;
      } else if (last.empty()) {
        last = token;
      } else {
        if (lastlast == first && last == second) {
          res.push_back(token);
        }
        lastlast = last;
        last = token;
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1079. Letter Tile Possibilities
You have a set of tiles, where each tile has one letter tiles[i] printed on it. 
Return the number of possible non-empty sequences of letters you can make.

Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
"ABA", "BAA".

Example 2:

Input: "AAABBC"
Output: 188

Note:

  1 <= tiles.length <= 7
  tiles consists of uppercase English letters.
/*
  Submission Date: 2019-09-21
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int f(vector<int>& count) {
    int sum = 0;
    for (int i = 0; i < 26; i++) {
      // no letters here
      if (count[i] == 0) continue;
      // use this letter
      sum++;
      count[i]--;
      sum += f(count);
      count[i]++;
    }
    return sum;
  }
  int numTilePossibilities(string tiles) {
    vector<int> count(26, 0);
    for (const auto& c : tiles) count[c - 'A']++;
    return f(count);
  }
};

class Solution2 {
 public:
  void f(const string& tiles, const int& index, const string& curr,
         unordered_set<string>& comb) {
    if (!curr.empty()) {
      comb.insert(curr);
    }
    if (index >= tiles.size()) return;

    // use this letter by putting it any of the positions of curr
    for (int i = 0; i <= curr.size(); i++) {
      f(tiles, index + 1, curr.substr(0, i) + tiles[index] + curr.substr(i),
        comb);
    }
    // ignore this letter
    f(tiles, index + 1, curr, comb);
  }
  int numTilePossibilities(string tiles) {
    unordered_set<string> comb;
    f(tiles, 0, "", comb);
    // for(auto e: comb) cout << e << endl;
    return comb.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1089. Duplicate Zeros
Given a fixed length array arr of integers, duplicate each occurrence of zero,
shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything
from your function.

Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,0,0,2,3,0,0,4]

Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,2,3]

Note:

  1 <= arr.length <= 10000
  0 <= arr[i] <= 9
/*
  Submission Date: 2019-09-17
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    /*
    two passes where i is the original arr index
    and j is the new arr index. stop when j >= N
    then go backwards and fill
    */
    int N = arr.size();
    int i = 0, j = 0;
    for (; i < N && j < N; i++) {
      j += (arr[i] == 0) ? 2 : 1;
    }

    while (i >= 0 && j >= 0) {
      i--;
      if (i >= 0) {
        if (arr[i] == 0) {
          if (j - 1 < N) arr[j - 1] = 0;
          if (j - 2 < N) arr[j - 2] = 0;
          j -= 2;
        } else {
          arr[j - 1] = arr[i];
          j--;
        }
      }
    }
  }
};

int main() { return 0; }
