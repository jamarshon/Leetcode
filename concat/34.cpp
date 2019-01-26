
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
783. Minimum Distance Between BST Nodes
Given a Binary Search Tree (BST) with the root node root, return the minimum
difference between the values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \
    1   3

while the minimum difference in this tree is 1, it occurs between node 1 and
node 2, also between node 3 and node 2. Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value
is different.
/*
    Submission Date: 2018-06-08
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <climits>
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

  int minDiffInBST(TreeNode* root) {
    int res = INT_MAX, prev = INT_MAX;
    help(root, res, prev);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
784. Letter Case Permutation
Given a string S, we can transform every letter individually to be lowercase or
uppercase to create another string. Return a list of all possible strings we
could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length at most 12.
S will consist only of letters or digits.
/*
    Submission Date: 2018-06-03
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<string, vector<string>> dp_;

 public:
  /*
   find the first alphabetical letter. get the vector for the remaining string
   add prefix with the letter lower case and upper case to each element from the
   vector
  */
  vector<string> letterCasePermutation(string S) {
    if (dp_.count(S)) return dp_[S];

    int N = S.size();
    int i = 0;
    for (; i < N; i++) {
      if (isalpha(S[i])) break;
    }

    if (i >= N) return {S};
    vector<string> rem = letterCasePermutation(S.substr(i + 1));
    int M = rem.size();
    rem.reserve(2 * M);

    string s1 = S.substr(0, i) + string(1, toupper(S[i]));
    string s2 = S.substr(0, i) + string(1, tolower(S[i]));
    for (int j = 0; j < M; j++) {
      rem.push_back(s2 + rem[j]);
      rem[j] = s1 + rem[j];
    }
    return rem;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
788. Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees, we
get a valid number that is different from X. Each digit must be rotated - we
cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8
rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each
other, and the rest of the numbers do not rotate to any other number and become
invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation:
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after
rotating. Note:

N  will be in range [1, 10000].
/*
    Submission Date: 2018-06-04
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  dp[i] = -1 if i cannot be rotated else it equals the rotated number of i
  therefore dp[i] = dp[i/10] + rot[i % 10] as i/10 gets the rotated version i
  without the last number and rot[i % 10] gets the rotated version of the last
  number of i
  */
  int rotatedDigits(int N) {
    vector<int> dp(N + 1, -1);
    unordered_map<int, int> rot{{0, 0}, {1, 1}, {8, 8}, {2, 5},
                                {5, 2}, {6, 9}, {9, 6}};
    int res = 0;
    for (int i = 1; i <= N; i++) {
      if (!rot.count(i % 10)) continue;
      if (i < 10) {
        dp[i] = rot[i];
        res += dp[i] != i;
      } else {
        if (dp[i / 10] == -1) continue;
        dp[i] = dp[i / 10] * 10 + rot[i % 10];
        res += dp[i] != i;
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
789. Escape The Ghosts
You are playing a simplified Pacman game. You start at the point (0, 0), and
your destination is (target[0], target[1]). There are several ghosts on the map,
the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).

Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal
directions: north, east, west, or south, going from the previous point to a new
point 1 unit of distance away.

You escape if and only if you can reach the target before any ghost reaches you
(for any given moves the ghosts may take.)  If you reach any square (including
the target) at the same time as a ghost, it doesn't count as an escape.

Return True if and only if it is possible to escape.

Example 1:
Input:
ghosts = [[1, 0], [0, 3]]
target = [0, 1]
Output: true
Explanation:
You can directly reach the destination (0, 1) at time 1, while the ghosts
located at (1, 0) or (0, 3) have no way to catch up with you.


Example 2:
Input:
ghosts = [[1, 0]]
target = [2, 0]
Output: false
Explanation:
You need to reach the destination (2, 0), but the ghost at (1, 0) lies between
you and the destination.


Example 3:
Input:
ghosts = [[2, 0]]
target = [1, 0]
Output: false
Explanation:
The ghost can reach the target at the same time as you.


Note:


    All points have coordinates with absolute value <= 10000.
    The number of ghosts will not exceed 100.

/*
    Submission Date: 2018-07-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  if the manhattan distance (abs horizontal + abs vertical) of the target
  from the origin is less than or equal to the manhattan distance of the
  target with the ghost, then return false as the ghost can get there
  faster and just wait indefinitely.

  why ghost intercept is not good?
  if a ghost can intercept you, it means they can reach the target faster than
  you. the shortest path between two points is straight line so if ghost can
  take detour and intercept then it means if they just went straight, they
  would be there before you.
            if ghost gets here before you, they would already be at target
            x
  you --------------- target
            |         |
            |         |
  ghost--------------
  */
  bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
    int mine = abs(target[0]) + abs(target[1]);
    for (const auto& e : ghosts) {
      int dist = abs(e[0] - target[0]) + abs(e[1] - target[1]);
      if (dist <= mine) return false;
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
791. Custom Sort String
S and T are strings composed of lowercase letters. In S, no letter occurs more
than once.

S was sorted in some custom order previously. We want to permute the characters
of T so that they match the order that S was sorted. More specifically, if x
occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example :
Input:
S = "cba"
T = "abcd"
Output: "cbad"
Explanation:
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and
"a". Since "d" does not appear in S, it can be at any position in T. "dcba",
"cdba", "cbda" are also valid outputs.
 

Note:

S has length at most 26, and no character is repeated in S.
T has length at most 200.
S and T consist of lowercase letters only.
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string customSortString(string S, string T) {
    int N = S.size();

    vector<int> letter_to_ind(26, N);
    for (int i = 0; i < N; i++) letter_to_ind[S[i] - 'a'] = i;

    sort(T.begin(), T.end(),
         [&letter_to_ind](const char& lhs, const char& rhs) {
           return letter_to_ind[lhs - 'a'] < letter_to_ind[rhs - 'a'];
         });

    return T;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
796. Rotate String
We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to
the rightmost position. For example, if A = 'abcde', then it will be 'bcdea'
after one shift on A. Return True if and only if A can become B after some
number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
Note:

A and B will have length at most 100.
/*
    Submission Date: 2018-06-04
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool rotateString(string A, string B) {
    if (A.size() != B.size()) return false;
    string A2 = A + A;
    return A2.find(B) != string::npos;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
797. All Paths From Source to Target
Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0
to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.
graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []]
Output: [[0,1,3],[0,2,3]]
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of
nodes inside one path.
/*
    Submission Date: 2018-06-24
    Runtime: 103 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void dfs(int from, const vector<vector<int>>& graph, vector<int>& curr,
           vector<vector<int>>& res) {
    if (graph[from].empty()) {
      res.push_back(curr);
    } else {
      for (auto e : graph[from]) {
        curr.push_back(e);
        dfs(e, graph, curr, res);
        curr.pop_back();
      }
    }
  }

  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<int> curr{0};
    vector<vector<int>> res;
    dfs(0, graph, curr, res);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
804. Unique Morse Code Words
International Morse Code defines a standard encoding where each letter is mapped
to a series of dots and dashes, as follows: "a" maps to ".-", "b" maps to
"-...", "c" maps to "-.-.", and so on.

For convenience, the full table for the 26 letters of the English alphabet is
given below:

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
Now, given a list of words, each word can be written as a concatenation of the
Morse code of each letter. For example, "cab" can be written as "-.-.-....-",
(which is the concatenation "-.-." + "-..." + ".-"). We'll call such a
concatenation, the transformation of a word.

Return the number of different transformations among all words we have.

Example:
Input: words = ["gin", "zen", "gig", "msg"]
Output: 2
Explanation:
The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."

There are 2 different transformations, "--...-." and "--...--.".
 

Note:

The length of words will be at most 100.
Each words[i] will have length in range [1, 12].
words[i] will only consist of lowercase letters.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  vector<string> morse_{".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",
                        "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",
                        "---",  ".--.", "--.-", ".-.",  "...",  "-",    "..-",
                        "...-", ".--",  "-..-", "-.--", "--.."};

 public:
  int uniqueMorseRepresentations(vector<string>& words) {
    unordered_set<string> comb;
    for (const auto& s : words) {
      string curr = "";
      for (const auto& c : s) {
        curr += morse_[c - 'a'];
      }
      comb.insert(curr);
    }
    return comb.size();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
806. Number of Lines To Write String
We are to write the letters of a given string S, from left to right into lines.
Each line has maximum width 100 units, and if writing a letter would cause the
width of the line to exceed 100 units, it is written on the next line. We are
given an array widths, an array where widths[0] is the width of 'a', widths[1]
is the width of 'b', ..., and widths[25] is the width of 'z'.

Now answer two questions: how many lines have at least one character from S, and
what is the width used by the last such line? Return your answer as an integer
list of length 2.

Example :
Input:
widths =
[10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "abcdefghijklmnopqrstuvwxyz"
Output: [3, 60]
Explanation:
All letters have the same length of 10. To write all 26 letters,
we need two full lines and one line with 60 units.
Example :
Input:
widths =
[4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "bbbcccdddaaa"
Output: [2, 4]
Explanation:
All letters except 'a' have the same length of 10, and
"bbbcccdddaa" will cover 9 * 10 + 2 * 4 = 98 units.
For the last 'a', it is written on the second line because
there is only 2 units left in the first line.
So the answer is 2 lines, plus 4 units in the second line.
 
Note:

The length of S will be in the range [1, 1000].
S will only contain lowercase letters.
widths is an array of length 26.
widths[i] will be in the range of [2, 10].
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> numberOfLines(vector<int>& widths, string S) {
    int current_len = 0;
    int num_lines = 0;
    for (const auto& c : S) {
      if (current_len + widths[c - 'a'] > 100) {
        num_lines++;
        current_len = 0;
      }
      current_len += widths[c - 'a'];
    }
    return {num_lines + 1, current_len};
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
807. Max Increase to Keep City Skyline
In a 2 dimensional array grid, each value grid[i][j] represents the height of a
building located there. We are allowed to increase the height of any number of
buildings, by any amount (the amounts can be different for different buildings).
Height 0 is considered to be a building as well.

At the end, the "skyline" when viewed from all four directions of the grid, i.e.
top, bottom, left, and right, must be the same as the skyline of the original
grid. A city's skyline is the outer contour of the rectangles formed by all the
buildings when viewed from a distance. See the following example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation:
The grid is:
[ [3, 0, 8, 4],
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

Notes:

1 < grid.length = grid[0].length <= 50.
All heights grid[i][j] are in the range [0, 100].
All buildings in grid[i][j] occupy the entire grid cell: that is, they are a 1 x
1 x grid[i][j] rectangular prism.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int N = grid.size();
    int M = grid[0].size();
    vector<int> max_col(M, 0), max_row(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        max_col[j] = max(max_col[j], grid[i][j]);
        max_row[i] = max(max_row[i], grid[i][j]);
      }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        res += min(max_col[j], max_row[i]) - grid[i][j];
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
811. Subdomain Visit Count
A website domain like "discuss.leetcode.com" consists of various subdomains. At
the top level, we have "com", at the next level, we have "leetcode.com", and at
the lowest level, "discuss.leetcode.com". When we visit a domain like
"discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and
"com" implicitly.

Now, call a "count-paired domain" to be a count (representing the number of
visits this domain received), followed by a space, followed by the address. An
example of a count-paired domain might be "9001 discuss.leetcode.com".

We are given a list cpdomains of count-paired domains. We would like a list of
count-paired domains, (in the same format as the input, and in any order), that
explicitly counts the number of visits to each subdomain.

Example 1:
Input:
["9001 discuss.leetcode.com"]
Output:
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation:
We only have one website domain: "discuss.leetcode.com". As discussed above, the
subdomain "leetcode.com" and "com" will also be visited. So they will all be
visited 9001 times.

Example 2:
Input:
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output:
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1
intel.mail.com","951 com"] Explanation: We will visit "google.mail.com" 900
times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times. For
the subdomains, we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1
= 951 times, and "org" 5 times.

Notes:

The length of cpdomains will not exceed 100.
The length of each domain name will not exceed 100.
Each address will have either 1 or 2 "." characters.
The input count in any count-paired domain will not exceed 10000.
The answer output can be returned in any order.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> subdomainVisits(vector<string>& cpdomains) {
    unordered_map<string, int> domain_to_count;
    for (const auto& s : cpdomains) {
      int num = 0;
      int i = 0;
      while (i < s.size()) {
        if (isdigit(s[i])) {
          num = num * 10 + (s[i] - '0');
        } else {
          break;
        }
        i++;
      }

      string domain = s.substr(i + 1);
      while (domain.find('.') != string::npos) {
        domain_to_count[domain] += num;
        domain = domain.substr(domain.find('.') + 1);
      }

      domain_to_count[domain] += num;
    }

    vector<string> res;
    for (const auto& kv : domain_to_count) {
      res.push_back(to_string(kv.second) + " " + kv.first);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
812. Largest Triangle Area
You have a list of points in the plane. Return the area of the largest triangle
that can be formed by any 3 of the points.

Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation:
The five points are show in the figure below. The red triangle is the largest.

Notes:

3 <= points.length <= 50.
No points will be duplicated.
 -50 <= points[i][j] <= 50.
Answers within 10^-6 of the true value will be accepted as correct.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  double largestTriangleArea(vector<vector<int>>& points) {
    int res = 0;
    int N = points.size();
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        for (int k = j + 1; k < N; k++) {
          /*
          given points (a,b), (c,d), (e,f)
          vector A = (c-a, d-b, 0) and B = (e-a, f-b, 0)
          cross product of A and B is
          ((d-b)*0 - (f-b)*0, -((c-a)*0 - (e-a)*0), (c-a)*(f-b) - (e-a)*(d-b))
          (0, 0, (c-a)*(f-b) - (e-a)*(d-b))
          magnitude of A cross B is area of parallelogram so divide by half
          */
          int c_minus_a = points[j][0] - points[i][0];
          int d_minus_b = points[j][1] - points[i][1];
          int e_minus_a = points[k][0] - points[i][0];
          int f_minus_b = points[k][1] - points[i][1];

          res = max(res, abs(c_minus_a * f_minus_b - e_minus_a * d_minus_b));
        }
      }
    }
    return res / 2.0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
814. Binary Tree Pruning
We are given the head node root of a binary tree, where additionally every
node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1
has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant
of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
 
Explanation:
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.


Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]



Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]



Note:

The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.
/*
    Submission Date: 2018-06-24
    Runtime: 4 ms
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
  bool HasOne(TreeNode* root) {
    if (root == NULL) return false;
    bool l = HasOne(root->left);
    bool r = HasOne(root->right);

    if (!l) {
      delete root->left;
      root->left = NULL;
    }
    if (!r) {
      delete root->right;
      root->right = NULL;
    }

    return root->val == 1 || l || r;
  }

  TreeNode* pruneTree(TreeNode* root) {
    if (!HasOne(root)) {
      delete root;
      return NULL;
    }
    return root;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
817. Linked List Components
We are given head, the head node of a linked list containing unique integer
values.

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G, where two values are connected
if they appear consecutively in the linked list.

Example 1:

Input:
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation:
0 and 1 are connected, so [0, 1] and [3] are the two connected components.


Example 2:

Input:
head: 0->1->2->3->4
G = [0, 3, 1, 4]
Output: 2
Explanation:
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two
connected components.


Note:


    If N is the length of the linked list given by head, 1 <= N <= 10000.
    The value of each node in the linked list will be in the range [0, N - 1].
    1 <= G.length <= 10000.
    G is a subset of all values in the linked list.

/*
    Submission Date: 2018-07-02
    Runtime: 35 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  int numComponents(ListNode* head, vector<int>& G) {
    unordered_set<int> G_set(G.begin(), G.end());
    ListNode* curr = head;
    int res = 0;
    while (curr) {
      // looking for the start of a component
      while (curr && !G_set.count(curr->val)) {
        curr = curr->next;
      }

      if (curr) {
        res++;
        // looking for the end of a component
        while (curr && G_set.count(curr->val)) {
          curr = curr->next;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
