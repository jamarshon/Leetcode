
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1008. Construct Binary Search Tree from Preorder Traversal
Return the root node of a binary search tree that matches the given preorder
traversal.

(Recall that a binary search tree is a binary tree where for every node, any
descendant of node.left has a value < node.val, and any descendant of node.right
has a value > node.val.  Also recall that a preorder traversal displays the
value of the node first, then traverses node.left, then traverses node.right.)

Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Note: 

  1 <= preorder.length <= 100
  The values of preorder are distinct.
/*
  Submission Date: 2019-09-21
  Runtime: 8 ms
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
  int index = 0;

 public:
  TreeNode* f(vector<int>& preorder, int low, int high) {
    /*
    recursive create tree, if current value in preorder fits
    in [low, high] then create a node else backtrack
    */
    int N = preorder.size();
    if (index >= N) return nullptr;
    if (preorder[index] < low || preorder[index] > high) return nullptr;
    TreeNode* curr = new TreeNode(preorder[index++]);
    curr->left = f(preorder, low, curr->val);
    curr->right = f(preorder, curr->val, high);
    return curr;
  }
  TreeNode* bstFromPreorder(vector<int>& preorder) {
    return f(preorder, INT_MIN, INT_MAX);
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
1010. Pairs of Songs With Total Durations Divisible by 60
In a list of songs, the i-th song has a duration of time[i] seconds. 

Return the number of pairs of songs for which their total duration in seconds is
divisible by 60.  Formally, we want the number of indices i < j with (time[i] +
time[j]) % 60 == 0.

Example 1:

Input: [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60

Example 2:

Input: [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by
60.

Note:

  1 <= time.length <= 60000
  1 <= time[i] <= 500
/*
  Submission Date: 2019-09-23
  Runtime: 48 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numPairsDivisibleBy60(vector<int>& time) {
    /*
    similar to two sum using a hashmap except
    we are looking for the modulo of the complement
    */
    unordered_map<int, int> seen;
    int res = 0;
    for (const auto& e : time) {
      int ee = e % 60;
      int complement = (60 - ee) % 60;
      if (seen.count(complement)) {
        res += seen[complement];
      }
      seen[ee]++;
    }
    return res;
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
1018. Binary Prefix Divisible By 5
Given an array A of 0s and 1s, consider N_i: the i-th subarray from A[0] to
A[i] interpreted as a binary number (from most-significant-bit to
least-significant-bit.)

Return a list of booleans answer, where answer[i] is true if and only if N_i is
divisible by 5.

Example 1:

Input: [0,1,1]
Output: [true,false,false]
Explanation:
The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
Only the first number is divisible by 5, so answer[0] is true.

Example 2:

Input: [1,1,1]
Output: [false,false,false]

Example 3:

Input: [0,1,1,1,1,1]
Output: [true,false,false,false,true,false]

Example 4:

Input: [1,1,1,0,1]
Output: [false,false,false,false,false]

Note:

  1 <= A.length <= 30000
  A[i] is 0 or 1
/*
  Submission Date: 2019-09-23
  Runtime: 12 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<bool> prefixesDivBy5(vector<int>& A) {
    /*
    prove (a + b) % n == a % n + b % n
    (cn + d + en + f) % n == ((c + e)n + (d + f)) % n == d + f
    same thing with multiplication so it is good to modulo the
    intermediate results to prevent overflow
    */
    int curr = 0;
    vector<bool> res;
    for (const auto& e : A) {
      curr = ((curr * 2) % 5 + (e % 5)) % 5;
      res.push_back(curr == 0);
    }
    return res;
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1030. Matrix Cells in Distance Order
We are given a matrix with R rows and C columns has cells with integer
coordinates (r, c), where 0 <= r < R and 0 <= c < C.

Additionally, we are given a cell in that matrix with coordinates (r0, c0).

Return the coordinates of all cells in the matrix, sorted by their distance from
(r0, c0) from smallest distance to largest distance.  Here, the distance between
two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 -
c2|.  (You may return the answer in any order that satisfies this condition.)

Example 1:

Input: R = 1, C = 2, r0 = 0, c0 = 0
Output: [[0,0],[0,1]]
Explanation: The distances from (r0, c0) to other cells are: [0,1]

Example 2:

Input: R = 2, C = 2, r0 = 0, c0 = 1
Output: [[0,1],[0,0],[1,1],[1,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2]
The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

Example 3:

Input: R = 2, C = 3, r0 = 1, c0 = 2
Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2,2,3]
There are other answers that would also be accepted as correct, such as
[[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].

Note:

  1 <= R <= 100
  1 <= C <= 100
  0 <= r0 < R
  0 <= c0 < C
/*
  Submission Date: 2019-09-07
  Runtime: 220 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  string GetKey(int x, int y) { return to_string(x) + '-' + to_string(y); }

 public:
  // bfs
  vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
    queue<pair<int, int>> q{{{r0, c0}}};
    unordered_set<string> seen{GetKey(r0, c0)};
    vector<vector<int>> res;
    while (!q.empty()) {
      auto p = q.front();
      res.push_back({p.first, p.second});
      q.pop();
      for (int i = 0; i < 4; i++) {
        int x = dx[i] + p.first;
        int y = dy[i] + p.second;
        if (0 <= x && x < R && 0 <= y && y < C) {
          string key = GetKey(x, y);
          if (!seen.count(key)) {
            seen.insert(key);
            q.emplace(x, y);
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
