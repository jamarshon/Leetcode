
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
1026. Maximum Difference Between Node and Ancestor
Given the root of a binary tree, find the maximum value V for which there exists
different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.

(A node A is an ancestor of B if either: any child of A is equal to B, or any
child of A is an ancestor of B.)

Example 1:

Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| =
7.

Note:

  The number of nodes in the tree is between 2 and 5000.
  Each node will have value between 0 and 100000.
/*
  Submission Date: 2019-09-23
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <functional>
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
  int res = 0;

 public:
  void update(int x, pair<int, int> p) {
    if (p.first != -1) res = max(res, abs(x - p.first));
    if (p.second != -1) res = max(res, abs(x - p.second));
  }

  int get(vector<int> v, function<int(int, int)> compare) {
    int res = v[0];
    for (int i = 1; i < v.size(); i++) {
      if (v[i] != -1) res = compare(res, v[i]);
    }
    return res;
  }

  pair<int, int> solve(TreeNode* root) {
    if (!root) return {-1, -1};
    auto left = solve(root->left);
    auto right = solve(root->right);
    int x = root->val;
    update(x, left);
    update(x, right);
    int smallest = get(vector<int>{x, left.first, right.first},
                       [](int a, int b) { return min(a, b); });
    int largest = get(vector<int>{x, left.second, right.second},
                      [](int a, int b) { return max(a, b); });
    return {smallest, largest};
  }

  int maxAncestorDiff(TreeNode* root) {
    // compute the smallest and largest in the subtrees
    // then update and return the smalles/largest
    // see if abs(curr - smallest) || abs(curr - largest) is
    // greater than res
    solve(root);
    return res;
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
