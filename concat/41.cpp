
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
939. Minimum Area Rectangle
Given a set of points in the xy-plane, determine the minimum area of a rectangle
formed from these points, with sides parallel to the x and y axes.

If there isn't any rectangle, return 0.

Example 1:

Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4

Example 2:

Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2

Note:

  1 <= points.length <= 500
  0 <= points[i][0] <= 40000
  0 <= points[i][1] <= 40000
  All points are distinct.
/*
  Submission Date: 2019-02-19
  Runtime: 84 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution3 {
 public:
  /*
  consider each point as diagonals of the rectangle (a,b) (c,d) seach
  for (a,d) and (c,b). use hashmap for lookup.
  if same x coord a==c (a,b) (a,d) look for (a,d) (a,b) not valid
  so exclude if same x coord and same y coord.
  */
  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    unordered_set<int> s;
    for (const auto& p : points) s.insert(p[0] * 40001 + p[1]);
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        if (points[i][0] == points[j][0] || points[i][1] == points[j][1])
          continue;
        if (s.count(points[i][0] * 40001 + points[j][1]) &&
            s.count(points[j][0] * 40001 + points[i][1])) {
          int area =
              (points[i][0] - points[j][0]) * (points[i][1] - points[j][1]);
          res = (res == -1) ? abs(area) : min(abs(area), res);
        }
      }
    }
    return max(res, 0);
  }
};

class Solution {
 public:
  /*
  group by x coordinates. sort each column and do pairwise comparison of
  each column by finding intersecting elements. The smallest distance between
  intersecting elements multiplied by the distance between columns is smallest
  rectangle that is bordered by these two columns.
  */
  int ShortestCommon(const vector<int>& A, const vector<int>& B) {
    int res = -1;
    int N = A.size(), M = B.size();
    int i = 0, j = 0;
    int last_y = -1;

    while (i < N && j < M) {
      if (A[i] == B[j]) {
        if (last_y != -1)
          res = (res == -1) ? A[i] - last_y : min(res, A[i] - last_y);
        last_y = A[i];
        i++;
        j++;
      } else if (A[i] > B[j]) {
        j++;
      } else {
        i++;
      }
    }
    return res;
  }

  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    unordered_map<int, vector<int>> m;
    for (const auto& p : points) {
      m[p[0]].push_back(p[1]);
    }

    for (auto& kv : m) sort(kv.second.begin(), kv.second.end());
    for (auto it = m.begin(); it != m.end(); it++) {
      for (auto next_it = next(it); next_it != m.end(); next_it++) {
        int height = ShortestCommon(it->second, next_it->second);
        if (height == -1) continue;
        int pos_res = height * abs(it->first - next_it->first);
        res = (res == -1) ? pos_res : min(pos_res, res);
      }
    }

    return max(res, 0);
  }
};

class Solution2 {
 public:
  /*
  group points by x coordinates (into columns)
  traverse these columns starting from the left and for each column
  loop the pair of y1, y2 to see if any previous column had it. since
  we start from the left, it is guaranteed that it will be the shortest
  x distance. this is can be done by having a unordered_map<int,int>
  where key is y1*40001 + y2 where y1 <= y2 and value is the
  most recent x coordinate
  */
  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    map<int, vector<int>> m;
    for (const auto& p : points) {
      m[p[0]].push_back(p[1]);
    }

    unordered_map<int, int> x_coord;
    for (const auto& kv : m) {
      const auto& column = kv.second;
      for (int i = 0; i < column.size(); i++) {
        for (int j = i + 1; j < column.size(); j++) {
          int y1 = column[i];
          int y2 = column[j];
          if (y1 > y2) swap(y1, y2);
          auto it = x_coord.find(y1 * 40001 + y2);
          if (it != x_coord.end()) {
            int area = (kv.first - it->second) * (y2 - y1);
            res = (res == -1) ? area : min(area, res);
          }
          x_coord[y1 * 40001 + y2] = kv.first;
        }
      }
    }

    return max(res, 0);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
941. Valid Mountain Array
Given an array A of integers, return true if and only if it is a valid mountain
array.

Recall that A is a mountain array if and only if:

  A.length >= 3
  There exists some i with 0 < i < A.length - 1 such that:

    A[0] < A[1] < ... A[i-1] < A[i]
    A[i] > A[i+1] > ... > A[B.length - 1]

Example 1:

Input: [2,1]
Output: false

Example 2:

Input: [3,5,5]
Output: false

Example 3:

Input: [0,3,2,1]
Output: true

Note:

  0 <= A.length <= 10000
  0 <= A[i] <= 10000
/*
  Submission Date: 2019-02-05
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool validMountainArray(vector<int>& A) {
    int N = A.size();
    if (N < 3) return false;
    // increasing
    int i = 1;
    for (; i < N && A[i - 1] < A[i]; i++) {
    }

    if (i == 1 || i == N) return false;

    for (; i < N && A[i - 1] > A[i]; i++) {
    }
    return i == N;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
942. DI String Match
Given a string S that only contains "I" (increase) or "D" (decrease), let N =
S.length.

Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:

  If S[i] == "I", then A[i] < A[i+1]
  If S[i] == "D", then A[i] > A[i+1]

Example 1:

Input: "IDID"
Output: [0,4,1,3,2]

Example 2:

Input: "III"
Output: [0,1,2,3]

Example 3:

Input: "DDI"
Output: [3,2,0,1]

Note:

  1 <= S.length <= 10000
  S only contains characters "I" or "D".
/*
  Submission Date: 2019-02-04
  Runtime: 28 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  if S[i] is 'I', putting the smallest available number here works
  because all other numbers will be larger.
  else putting the largest available number here works.
  */
  vector<int> diStringMatch(string S) {
    int N = S.size();
    vector<int> res(N + 1);
    int low = 0;
    int high = N;
    for (int i = 0; i < N; i++) {
      if (S[i] == 'I')
        res[i] = low++;
      else
        res[i] = high--;
    }

    res[N] = low;
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
944. Delete Columns to Make Sorted
We are given an array A of N lowercase letter strings, all of the same length.

Now, we may choose any set of deletion indices, and for each string, we delete
all the characters in those indices.

For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices
{0, 2, 3}, then the final array after deletions is ["bef", "vyz"], and the
remaining columns of A are ["b","v"], ["e","y"], and ["f","z"].  (Formally, the
c-th column is [A[0][c], A[1][c], ..., A[A.length-1][c]].)

Suppose we chose a set of deletion indices D such that after deletions, each
remaining column in A is in non-decreasing sorted order.

Return the minimum possible value of D.length.

Example 1:

Input: ["cba","daf","ghi"]
Output: 1
Explanation:
After choosing D = {1}, each column ["c","d","g"] and ["a","f","i"] are in
non-decreasing sorted order.
If we chose D = {}, then a column ["b","a","h"] would not be in non-decreasing
sorted order.

Example 2:

Input: ["a","b"]
Output: 0
Explanation: D = {}

Example 3:

Input: ["zyx","wvu","tsr"]
Output: 3
Explanation: D = {0, 1, 2}

Note:

  1 <= A.length <= 100
  1 <= A[i].length <= 1000
/*
  Submission Date: 2019-02-04
  Runtime: 44 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minDeletionSize(vector<string>& A) {
    int N = A[0].size();
    int res = 0;
    for (int c = 0; c < N; c++) {
      for (int i = 1; i < A.size(); i++) {
        if (A[i][c] < A[i - 1][c]) {
          res++;
          break;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
946. Validate Stack Sequences
Given two sequences pushed and popped with distinct values, return true if and
only if this could have been the result of a sequence of push and pop operations
on an initially empty stack.

Example 1:

Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

Example 2:

Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.

Note:

  0 <= pushed.length == popped.length <= 1000
  0 <= pushed[i], popped[i] < 1000
  pushed is a permutation of popped.
  pushed and popped have distinct values.
/*
  Submission Date: 2019-02-12
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  keep pushing everything into the stack and greedily pop off if we can.
  */
  bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> stk;
    int i = 0, N = pushed.size();
    for (const auto& p : pushed) {
      stk.push(p);
      while (!stk.empty() && i < N && popped[i] == stk.top()) {
        stk.pop();
        i++;
      }
    }
    return i == N;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
947. Most Stones Removed with Same Row or Column
On a 2D plane, we place stones at some integer coordinate points.  Each
coordinate point may have at most one stone.

Now, a move consists of removing a stone that shares a column or row with
another stone on the grid.

What is the largest possible number of moves we can make?

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5

Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3

Example 3:

Input: stones = [[0,0]]
Output: 0

Note:

  1 <= stones.length <= 1000
  0 <= stones[i][j] < 10000
/*
  Submission Date: 2019-02-16
  Runtime: 60 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct UnionFind {
  unordered_map<int, int> parent_, rank_;

  int FindHelper(int k) {
    if (parent_[k] != k) {
      parent_[k] = FindHelper(parent_[k]);
    }

    return parent_[k];
  }

  int Find(int k) {
    if (!parent_.count(k)) {
      parent_[k] = k;
      rank_[k] = 1;
    }

    return FindHelper(k);
  }

  void Union(int a, int b) {
    int a_root = Find(a);
    int b_root = Find(b);
    if (a_root == b_root) return;
    if (rank_[a_root] > rank_[b_root]) {
      parent_[b_root] = a_root;
    } else {
      parent_[a_root] = b_root;
      if (rank_[a_root] == rank_[b_root]) rank_[b_root]++;
    }
  }

  int NumberOfComponents() {
    int res = 0;
    for (const auto& kv : parent_) res += kv.first == kv.second;
    return res;
  }
};

class Solution {
 public:
  /*
  if a stone shares the same x or y coordinates then
  connect them in a graph. instead of connecting stones
  or indices, say that if two stones have the same x coordinates (same column)
  connect their y coordinates (the rows).
  connecting columns to rows can be done by having the key of columns
  be negative (x = -x-1 = ~x use -1 for zero to prevent collision) and the
  key for rows to be positive in union find.

  the result is the number of stones minus the number of islands
  this is because for each island we can remove all stones except one.
  this is done by doing a dfs and then removing those nodes in reverse
  similar to removing leaves from a tree.
  */
  int removeStones(vector<vector<int>>& stones) {
    UnionFind uf;
    int N = stones.size();
    for (const auto& s : stones) uf.Union(s[0], ~s[1]);
    return N - uf.NumberOfComponents();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
949. Largest Time for Given Digits
Given an array of 4 digits, return the largest 24 hour time that can be made.

The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from
00:00, a time is larger if more time has elapsed since midnight.

Return the answer as a string of length 5.  If no valid time can be made, return
an empty string.

Example 1:

Input: [1,2,3,4]
Output: "23:41"

Example 2:

Input: [5,5,5,5]
Output: ""

Note:

  A.length == 4
  0 <= A[i] <= 9
/*
  Submission Date: 2019-02-05
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string largestTimeFromDigits(vector<int>& A) {
    /*
    ab:cd
    a [0, 2]
    b a == 2 [0-3] else [0-9]
    c [0, 5]
    d [0, 9]
    */

    unordered_map<int, int> freq;
    for (const auto& e : A) freq[e]++;
    for (int i = 2; i >= 0; i--) {
      if (!freq.count(i)) continue;
      freq[i]--;

      int cap = (i == 2) ? 3 : 9;
      for (int j = cap; j >= 0; j--) {
        if (!freq.count(j) || freq[j] == 0) continue;
        freq[j]--;
        for (int k = 5; k >= 0; k--) {
          if (!freq.count(k) || freq[k] == 0) continue;
          freq[k]--;
          for (int l = 9; l >= 0; l--) {
            if (!freq.count(l) || freq[l] == 0) continue;
            return to_string(i) + to_string(j) + string(":") + to_string(k) +
                   to_string(l);
          }
          freq[k]++;
        }

        freq[j]++;
      }
      freq[i]++;
    }

    return "";
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
950. Reveal Cards In Increasing Order
In a deck of cards, every card has a unique integer.  You can order the deck
in any order you want.

Initially, all the cards start face down (unrevealed) in one deck.

Now, you do the following steps repeatedly, until all cards are revealed:

  Take the top card of the deck, reveal it, and take it out of the deck.
  If there are still cards in the deck, put the next top card of the deck at the
bottom of the deck.
  If there are still unrevealed cards, go back to step 1.  Otherwise, stop.

Return an ordering of the deck that would reveal the cards in increasing order.

The first entry in the answer is considered to be the top of the deck.

Example 1:

Input: [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation:
We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and
reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of
the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.

Note:

  1 <= A.length <= 1000
  1 <= A[i] <= 10^6
  A[i] != A[j] for all i != j
/*
  Submission Date: 2019-02-07
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  Find the order in which the cards are revealed (e.g. indices 0, 2, 4, ...).
  Place the sorted numbers into these indices.
  */
  vector<int> deckRevealedIncreasing(vector<int>& deck) {
    sort(deck.begin(), deck.end());
    int N = deck.size();
    deque<int> dq(N);
    for (int i = 0; i < N; i++) dq[i] = i;
    vector<int> order;
    while (!dq.empty()) {
      order.push_back(dq.front());
      dq.pop_front();
      if (!dq.empty()) {
        dq.push_back(dq.front());
        dq.pop_front();
      }
    }

    int i = 0;
    vector<int> res(N);
    for (const auto& o : order) {
      res[o] = deck[i++];
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
951. Flip Equivalent Binary Trees
For a binary tree T, we can define a flip operation as follows: choose any node,
and swap the left and right child subtrees.

A binary tree X is flip equivalent to a binary tree Y if and only if we can make
X equal to Y after some number of flip operations.

Write a function that determines whether two binary trees are flip equivalent. 
The trees are given by root nodes root1 and root2.

Example 1:

Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 =
[1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.

Note:

  Each tree will have at most 100 nodes.
  Each value in each tree will be a unique integer in the range [0, 99].
/*
  Submission Date: 2019-02-09
  Runtime: 8 ms
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
 public:
  bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    if (root1 && root2) {
      if (root1->val != root2->val) return false;
      return (flipEquiv(root1->left, root2->left) &&
              flipEquiv(root1->right, root2->right)) ||
             (flipEquiv(root1->left, root2->right) &&
              flipEquiv(root1->right, root2->left));
    } else {
      return root1 == nullptr && root2 == nullptr;
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
953. Verifying an Alien Dictionary
In an alien language, surprisingly they also use english lowercase letters, but
possibly in a different order. The order of the alphabet is some permutation of
lowercase letters.

Given a sequence of words written in the alien language, and the order of the
alphabet, return true if and only if the given words are sorted lexicographicaly
in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is
sorted.

Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1],
hence the sequence is unsorted.

Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is
shorter (in size.) According to lexicographical rules "apple" > "app", because
'l' > '∅', where '∅' is defined as the blank character which is less than any
other character (More info).

Note:

  1 <= words.length <= 100
  1 <= words[i].length <= 20
  order.length == 26
  All characters in words[i] and order are english lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool less(const string& s1, const string& s2,
            unordered_map<char, int>& rank) {
    int i = 0;
    while (i < min(s1.size(), s2.size()) && s1[i] == s2[i]) i++;
    int r1 = i == s1.size() ? INT_MIN : rank[s1[i]];
    int r2 = i == s2.size() ? INT_MIN : rank[s2[i]];
    return r1 <= r2;
  }

  bool isAlienSorted(vector<string>& words, string order) {
    unordered_map<char, int> rank;
    for (int i = 0; i < order.size(); i++) rank[order[i]] = i;

    for (int i = 1; i < words.size(); i++) {
      if (!less(words[i - 1], words[i], rank)) return false;
    }

    return true;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
958. Check Completeness of a Binary Tree
Given a binary tree, determine if it is a complete binary tree.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely
filled, and all nodes in the last level are as far left as possible. It can have
between 1 and 2h nodes inclusive at the last level h.

Example 1:

Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values
{1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as
possible.

Example 2:

Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.

Note:

  The tree will have between 1 and 100 nodes.
/*
  Submission Date: 2019-02-21
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  struct NodeInfo {
    int height;
    bool perfect;
  };
  /*
  perfect means every node other than the leaves has two children and all leaves
  are at the same level (e.g tree of height h should have 2^(h+1)-1 children)
  height == -1 when subtree isn't complete else it is 1 + max(height(left,
  right))

  if the left height equals the right height then the left should be perfect
  because there are nodes in the right subtree. For nodes to be furthest left
  then nodes in right subtree indicates all the nodes are filled in the left.
       x
    z     x
  z   z  y

  z should be perfect

  if the left height == right height + 1, then the right should be prefect
  because there are nodes in the left subtree at right height + 1 but none in
  the right subtree at that same level.
       x
    x     z
  y

  z should be perfect

  a node is perfect if the heights of left and right are equal and both left and
  right are perfect
  */
  NodeInfo helper(TreeNode* root) {
    if (!root) return {0, true};
    const auto& left = helper(root->left);
    const auto& right = helper(root->right);
    if (left.height == -1 || right.height == -1) return {-1, false};

    const int& diff = left.height - right.height;
    if ((diff == 0 && left.perfect) || (diff == 1 && right.perfect)) {
      return {1 + max(left.height, right.height),
              diff == 0 && left.perfect && right.perfect};
    } else {
      return {-1, false};
    }
  }

 public:
  bool isCompleteTree(TreeNode* root) { return helper(root).height != -1; }
};

class Solution2 {
 public:
  /* level order search
  expect that depth d should have 2^d nodes except the last one
  if a node has a right child it must have a left child
  if a null node is encounted in a level, all the rest of the nodes should be
  null.
  */
  bool isCompleteTree(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q{{root}};
    int expected_size = 2;
    bool found_not_equal = false;
    while (!q.empty()) {
      bool seen_null = false;
      for (int i = 0, q_size = q.size(); i < q_size; i++) {
        TreeNode* curr = q.front();
        q.pop();
        if ((seen_null && (curr->left || curr->right)) ||
            (curr->right && !curr->left))
          return false;
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
        seen_null = curr->left == nullptr || curr->right == nullptr;
      }

      if (found_not_equal) return q.empty();
      found_not_equal = expected_size != q.size();
      expected_size *= 2;
    }
    return true;
  }
};

int main() { return 0; }
