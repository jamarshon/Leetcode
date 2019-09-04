
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
1108. Defanging an IP Address
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

Example 1:
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"

Constraints:

  The given address is a valid IPv4 address.
/*
  Submission Date: 2019-08-25
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
 public:
  string defangIPaddr(string address) {
    istringstream ss(address);
    string res, token;
    string splitter = "[.]";
    while (getline(ss, token, '.')) {
      res += token + splitter;
    }
    return res.substr(0, res.size() - 3);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1122. Relative Sort Array
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all
elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are
the same as in arr2.  Elements that don't appear in arr2 should be placed at the
end of arr1 in ascending order.

Example 1:
Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]

Constraints:

  arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  Each arr2[i] is distinct.
  Each arr2[i] is in arr1.
/*
  Submission Date: 2019-09-03
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
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int, int> arr2_to_ind;
    for (int i = 0; i < arr2.size(); i++) {
      arr2_to_ind[arr2[i]] = i;
    }

    auto end_it = arr2_to_ind.end();

    sort(arr1.begin(), arr1.end(),
         [&arr2_to_ind, &end_it](const int& left, const int& right) {
           auto left_it = arr2_to_ind.find(left);
           auto right_it = arr2_to_ind.find(right);
           if (left_it == end_it && right_it == end_it) {
             // ascending order
             return left < right;
           } else if (left_it == end_it) {
             // put the right in front as the left is not defined
             return false;
           } else if (right_it == end_it) {
             // put the left in front as the right is not defined
             return true;
           } else {
             // return the relative order of left, right
             return left_it->second < right_it->second;
           }
         });

    return arr1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1160. Find Words That Can Be Formed by Characters
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each
character can only be used once).

Return the sum of lengths of all good strings in words.

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation:
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.

Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation:
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 =
10.

Note:

  1 <= words.length <= 1000
  1 <= words[i].length, chars.length <= 100
  All strings contain lowercase English letters only.
/*
  Submission Date: 2019-08-25
  Runtime: 172 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // count the frequency of letters in chars and
  // make sure the string has at most that many letters
  // and no unknown letters
  int countCharacters(vector<string>& words, string chars) {
    unordered_map<char, int> freqs;
    for (const auto& e : chars) freqs[e]++;
    int res = 0;
    for (const auto& s : words) {
      unordered_map<char, int> freqs_copy = freqs;
      bool ok = true;
      for (const auto& e : s) {
        if (!freqs_copy.count(e)) {
          ok = false;
          break;
        }
        freqs_copy[e]--;
        if (freqs_copy[e] == 0) freqs_copy.erase(e);
      }
      if (ok) res += s.size();
    }
    return res;
  }
};

int main() { return 0; }
