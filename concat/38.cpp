
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
877. Stone Game
Alex and Lee play a game with piles of stones.  There are an even number
of piles arranged in a row, and each pile has a positive integer number of
stones piles[i].

The objective of the game is to end with the most stones.  The total number of
stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes
the entire pile of stones from either the beginning or the end of the row.  This
continues until there are no more piles left, at which point the person with the
most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the
game.

Example 1:

Input: [5,3,4,5]
Output: true
Explanation:
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10
points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with
9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we
return true.

Note:

  2 <= piles.length <= 500
  piles.length is even.
  1 <= piles[i] <= 500
  sum(piles) is odd.
/*
  Submission Date: 2019-01-26
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int N;

 public:
  int get(const vector<vector<int>>& dp, int i, int j) {
    if (i <= j && i >= 0 && i < N && j >= 0 && j < N) {
      return dp[i][j];
    }
    return 0;
  }
  bool stoneGame(vector<int>& piles) {
    N = piles.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    for (int gap = 0; gap < N; gap++) {
      for (int i = 0; i + gap < N; i++) {
        int j = gap;
        dp[i][j] =
            max(piles[i] + min(get(dp, i + 1, j - 1), get(dp, i + 2, j)),
                piles[j] + min(get(dp, i, j - 2), get(dp, i + 1, j - 1)));
      }
    }

    return get(dp, 0, N - 1) > get(dp, 1, N - 1) ||
           get(dp, 0, N - 1) > get(dp, 0, N - 2);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
883. Projection Area of 3D Shapes
On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x,
y, and z axes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid
cell (i, j).

Now we view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3 dimensional figure to a 2
dimensional plane. 

Here, we are viewing the "shadow" when looking at the cubes from the top, the
front, and the side.

Return the total area of all three projections.

Example 1:

Input: [[2]]
Output: 5

Example 2:

Input: [[1,2],[3,4]]
Output: 17
Explanation:
Here are the three projections ("shadows") of the shape made with each
axis-aligned plane.

Example 3:

Input: [[1,0],[0,2]]
Output: 8

Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 14

Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 21

Note:

  1 <= grid.length = grid[0].length <= 50
  0 <= grid[i][j] <= 50
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int projectionArea(vector<vector<int>>& grid) {
    int res = 0;
    int N = grid.size();

    vector<int> row(N, 0), col(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (grid[i][j] > 0) res++;
        row[i] = max(row[i], grid[i][j]);
        col[j] = max(col[j], grid[i][j]);
      }
    }

    for (int i = 0; i < N; i++) {
      res += row[i] + col[i];
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
884. Uncommon Words from Two Sentences
We are given two sentences A and B.  (A sentence is a string of space separated
words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does
not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]

Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]

Note:

  0 <= A.length <= 200
  0 <= B.length <= 200
  A and B both contain only spaces and lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> uncommonFromSentences(string A, string B) {
    unordered_map<string, int> freq;
    stringstream ssA(A), ssB(B);
    string temp;

    while (ssA >> temp) freq[temp]++;
    while (ssB >> temp) freq[temp]++;

    vector<string> res;
    for (const auto& kv : freq)
      if (kv.second == 1) res.push_back(kv.first);

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
885. Spiral Matrix III
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing
east.

Here, the north-west corner of the grid is at the first row and column, and the
south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk
outside the grid (but may return to the grid boundary later.) 

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order
they were visited.

Example 1:

Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]

Example 2:

Input: R = 5, C = 6, r0 = 1, c0 = 4
Output:
[[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

Note:

  1 <= R <= 100
  1 <= C <= 100
  0 <= r0 < R
  0 <= c0 < C
/*
  Submission Date: 2019-01-26
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int key(int i, int j, int R, int C) { return i * C + j; }
  vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
    unordered_set<int> visited;

    vector<vector<int>> res;
    res.push_back({r0, c0});
    visited.insert(key(r0, c0, R, C));

    int i = r0, j = c0;
    int dx = 1;
    int dy = 0;
    while (visited.size() != R * C) {
      if (!(0 <= i + dy && i + dy < R) || !(0 <= j + dx && j + dx < C)) {
        // will go out of bounds so change direction
        swap(dx, dy);
        dx *= -1;
      } else {
        i += dy;
        j += dx;
        if (visited.count(key(i, j, R, C))) {
          continue;
        } else {
          // an unvisited cell so push it to result
          res.push_back({i, j});
          visited.insert(key(i, j, R, C));

          // if node to the right isn't visited or if it is out of bounds change
          // directions
          int rot_dx = -dy;
          int rot_dy = dx;

          if (!(0 <= i + rot_dy && i + rot_dy < R) ||
              !(0 <= j + rot_dx && j + rot_dx < C) ||
              !visited.count(key(i + rot_dy, j + rot_dx, R, C))) {
            swap(dx, dy);
            dx *= -1;
          }
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
888. Fair Candy Swap
Alice and Bob have candy bars of different sizes: A[i] is the size of the i-th
bar of candy that Alice has, and B[j] is the size of the j-th bar of candy that
Bob has.

Since they are friends, they would like to exchange one candy bar each so that
after the exchange, they both have the same total amount of candy.  (The total
amount of candy a person has is the sum of the sizes of candy bars they have.)

Return an integer array ans where ans[0] is the size of the candy bar that Alice
must exchange, and ans[1] is the size of the candy bar that Bob must exchange.

If there are multiple answers, you may return any one of them.  It is guaranteed
an answer exists.

Example 1:

Input: A = [1,1], B = [2,2]
Output: [1,2]

Example 2:

Input: A = [1,2], B = [2,3]
Output: [1,2]

Example 3:

Input: A = [2], B = [1,3]
Output: [2,3]

Example 4:

Input: A = [1,2,5], B = [2,4]
Output: [5,4]

Note:

  1 <= A.length <= 10000
  1 <= B.length <= 10000
  1 <= A[i] <= 100000
  1 <= B[i] <= 100000
  It is guaranteed that Alice and Bob have different total amounts of candy.
  It is guaranteed there exists an answer.
/*
  Submission Date: 2019-01-26
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  /*sum_A + (B[j] - A[i]) == sum_B == (A[i] - B[j])
  sum_A = sum_B + 2*A[i] - 2*B[j]
  */
  vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
    int sum_A = 0;
    int sum_B = 0;
    for (auto& e : A) sum_A += e;
    for (auto& e : B) sum_B += e;

    unordered_set<int> B_set(B.begin(), B.end());
    for (auto& e : A) {
      int B_j = (sum_A - sum_B - 2 * e) / -2;
      if (B_set.count(B_j)) return {e, B_j};
    }

    return {};
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
889. Construct Binary Tree from Preorder and Postorder Traversal
Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Note:

  1 <= pre.length == post.length <= 30
  pre[] and post[] are both permutations of 1, 2, ..., pre.length.
  It is guaranteed an answer exists. If there exists multiple answers, you can
return any of them.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
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
  /* traverse pre and create nodes from there. the stk represents
  the current path of the tree (ie. from root to node). when the
  stk last value is equal to post[j], it means the tree is done
  so pop stk and increment j until it is no longer so. add the
  pre[i] is either the left or right of the stack depending on
  which is available.
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    vector<TreeNode*> stk;
    stk.emplace_back(new TreeNode(pre[0]));
    for (int i = 1, j = 0; i < pre.size(); i++) {
      while (stk.back()->val == post[j]) {
        j++;
        stk.pop_back();
      }

      TreeNode* curr = new TreeNode(pre[i]);
      if (stk.back()->left == NULL)
        stk.back()->left = curr;
      else
        stk.back()->right = curr;
      stk.emplace_back(curr);
    }

    return stk.front();
  }
};

class Solution2 {
 public:
  TreeNode* f(vector<int>& pre, int a, int b, vector<int>& post, int c, int d,
              unordered_map<int, int>& val_to_post_ind) {
    if (a > b || c > d) return NULL;
    assert(b - a == d - c);

    TreeNode* root = new TreeNode(pre[a]);

    int furthest = -1;
    for (int i = a + 1; i <= b; i++) {
      int ind = val_to_post_ind[pre[i]];
      furthest = max(furthest, ind);
      if (furthest - c == i - (a + 1)) {
        root->left = f(pre, a + 1, i, post, c, furthest, val_to_post_ind);
        root->right =
            f(pre, i + 1, b, post, furthest + 1, d - 1, val_to_post_ind);
        break;
      }
    }

    return root;
  }

  /*
  we traverse from pre i = 1 to N looking for where pre[i] is in post, say it is
  at j. it means every element from 0 to j must be in the tree so keep going
  until the furthest j contains as many elements as i-1. These range must be the
  left sub tree so partition both the pre and post from [1,i] [i+1, N] and [0,
  furthest_j] [furthest_j + 1, N-1]
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    unordered_map<int, int> val_to_post_ind;
    for (int i = 0; i < post.size(); i++) val_to_post_ind[post[i]] = i;
    return f(pre, 0, pre.size() - 1, post, 0, pre.size() - 1, val_to_post_ind);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
890. Find and Replace Pattern
You have a list of words and a pattern, and you want to know which words in
words matches the pattern.

A word matches the pattern if there exists a permutation of letters p so that
after replacing every letter x in the pattern with p(x), we get the desired
word.

(Recall that a permutation of letters is a bijection from letters to letters:
every letter maps to another letter, and no two letters map to the same letter.)

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 


Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b
-> e, ...}.
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a
permutation,
since a and b map to the same letter.

 

Note:


  1 <= words.length <= 50
  1 <= pattern.length = words[i].length <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> res;
    for (const auto& w : words) {
      if (w.size() != pattern.size()) continue;
      unordered_map<char, char> p;

      unordered_set<char> used;
      bool can_insert = true;
      for (int i = 0; i < w.size(); i++) {
        if (p.count(w[i])) {
          if (p[w[i]] != pattern[i]) {
            can_insert = false;
            break;
          }
        } else {
          if (used.count(pattern[i])) {
            can_insert = false;
            break;
          } else {
            p[w[i]] = pattern[i];
            used.insert(pattern[i]);
          }
        }
      }

      if (can_insert) res.push_back(w);
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
892. Surface Area of 3D Shapes
On a N * N grid, we place some 1 * 1 * 1 cubes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid
cell (i, j).

Return the total surface area of the resulting shapes.

Example 1:

Input: [[2]]
Output: 10

Example 2:

Input: [[1,2],[3,4]]
Output: 34

Example 3:

Input: [[1,0],[0,2]]
Output: 16

Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 32

Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 46

Note:

  1 <= N <= 50
  0 <= grid[i][j] <= 50
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int di[2] = {-1, 0};
  int dj[2] = {0, -1};

 public:
  int surfaceArea(vector<vector<int>>& grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == 0) continue;
        res += 4 * grid[i][j] + 2;
        for (int k = 0; k < 2; k++) {
          int n_i = i + di[k];
          int n_j = j + dj[k];
          if (0 <= n_i && n_i < grid.size() && 0 <= n_j &&
              n_j < grid[j].size()) {
            res -= 2 * min(grid[i][j], grid[n_i][n_j]);
          }
        }
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
893. Groups of Special-Equivalent Strings
You are given an array A of strings.

Two strings S and T are special-equivalent if after any number of moves, S == T.

A move consists of choosing two indices i and j with i % 2 == j % 2, and
swapping S[i] with S[j].

Now, a group of special-equivalent strings from A is a non-empty subset S of
A such that any string not in S is not special-equivalent with any string in S.

Return the number of groups of special-equivalent strings from A.

Example 1:

Input: ["a","b","c","a","c","c"]
Output: 3
Explanation: 3 groups ["a","a"], ["b"], ["c","c","c"]

Example 2:

Input: ["aa","bb","ab","ba"]
Output: 4
Explanation: 4 groups ["aa"], ["bb"], ["ab"], ["ba"]

Example 3:

Input: ["abc","acb","bac","bca","cab","cba"]
Output: 3
Explanation: 3 groups ["abc","cba"], ["acb","bca"], ["bac","cab"]

Example 4:

Input: ["abcd","cdab","adcb","cbad"]
Output: 1
Explanation: 1 group ["abcd","cdab","adcb","cbad"]

Note:

  1 <= A.length <= 1000
  1 <= A[i].length <= 20
  All A[i] have the same length.
  All A[i] consist of only lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numSpecialEquivGroups(vector<string>& A) {
    unordered_map<string, int> freq;

    for (const auto& s : A) {
      string even = "";
      string odd = "";
      for (int i = 0; i < s.size(); i++) {
        if (i % 2 == 0) {
          even.push_back(s[i]);
        } else {
          odd.push_back(s[i]);
        }
      }

      sort(even.begin(), even.end());
      sort(odd.begin(), odd.end());

      freq[even + odd]++;
    }

    return freq.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
894. All Possible Full Binary Trees
A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.  Each element of
the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.

You may return the final list of trees in any order.

 

Example 1:

Input: 7
Output:
[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:



 

Note:


  1 <= N <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 68 ms
  Difficulty: MEDIUM
*/
#include <iostream>
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
  vector<TreeNode*> allPossibleFBT(int N) {
    if (N == 0) return {};

    vector<vector<TreeNode*>> dp(N + 1);
    dp[1] = {new TreeNode(0)};

    for (int i = 1; i <= N; i += 2) {
      for (int j = 1; j < i; j += 2) {
        for (const auto& l : dp[j]) {
          for (const auto& r : dp[i - 1 - j]) {
            TreeNode* node = new TreeNode(0);
            node->left = l;
            node->right = r;
            dp[i].push_back(node);
          }
        }
      }
    }

    return dp[N];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
896. Monotonic Array
An array is monotonic if it is either monotone increasing or monotone
decreasing.

An array A is monotone increasing if for all i <= j, A[i] <= A[j].  An array A
is monotone decreasing if for all i <= j, A[i] >= A[j].

Return true if and only if the given array A is monotonic.

Example 1:

Input: [1,2,2,3]
Output: true

Example 2:

Input: [6,5,4,4]
Output: true

Example 3:

Input: [1,3,2]
Output: false

Example 4:

Input: [1,2,4,5]
Output: true

Example 5:

Input: [1,1,1]
Output: true

Note:

  1 <= A.length <= 50000
  -100000 <= A[i] <= 100000
/*
  Submission Date: 2019-01-26
  Runtime: 96 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isMonotonic(vector<int>& A) {
    int inc_cnt = 1;
    int dec_cnt = 1;
    for (int i = 1; i < A.size(); i++) {
      inc_cnt += A[i] >= A[i - 1];
      dec_cnt += A[i] <= A[i - 1];
    }

    return inc_cnt == A.size() || dec_cnt == A.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
897. Increasing Order Search Tree
Given a tree, rearrange the tree in in-order so that the leftmost node in the
tree is now the root of the tree, and every node has no left child and only 1
right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9

Note:

  The number of nodes in the given tree will be between 1 and 100.
  Each node will have a unique integer value from 0 to 1000.
/*
  Submission Date: 2019-01-26
  Runtime: 72 ms
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
  void inorder(TreeNode* curr, TreeNode** last, TreeNode** res) {
    if (curr) {
      inorder(curr->left, last, res);
      if (*last) {
        (*last)->right = curr;
      }

      *last = curr;
      if (*res == NULL) {
        *res = curr;
      }

      curr->left = NULL;
      inorder(curr->right, last, res);
    }
  }
  TreeNode* increasingBST(TreeNode* root) {
    TreeNode *res = NULL, *last = NULL;
    inorder(root, &last, &res);
    return res;
  }
};

int main() { return 0; }
