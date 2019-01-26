
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for
the multiples of five output “Buzz”. For numbers which are multiples of both
three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
/*
    Submission Date: 2018-05-31
    Runtime: 5 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> fizzBuzz(int n) {
    vector<string> res;
    for (int i = 1; i <= n; i++) {
      string s = "";
      if (i % 3 == 0) s += "Fizz";
      if (i % 5 == 0) s += "Buzz";
      if (s.empty()) s = to_string(i);
      res.push_back(s);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
413. Arithmetic Slices
A sequence of number is called arithmetic if it consists of at least three
elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9

The following sequence is not arithmetic. 1, 1, 2, 5, 7


A zero-indexed array A consisting of N numbers is given. A slice of that array
is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
    A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means
that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:
A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4]
itself.

/*
    Submission Date: 2018-06-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  find the length of sequence where A[i+1] - A[i] is the same for all numbers in
  the sequence let this length be called len, then there are len - 2 subarrays
  of size 3, len - 3 subarrays of size 4 and so on. so the sum of 0 to len - 2
  is just n*(n+1)/2 or (len - 2)*(len - 1)/2
  */
  int numberOfArithmeticSlices(vector<int>& A) {
    int res = 0;
    int N = A.size();
    for (int i = 0; i + 1 < N;) {
      int diff = A[i + 1] - A[i];
      int start = i;
      while (i + 1 < N && A[i + 1] - A[i] == diff) i++;
      int len = i - start + 1;
      if (len >= 3) {
        res += (len - 2) * (len - 1) / 2;
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
414. Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this
array. If it does not exist, return the maximum number. The time complexity must
be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned
instead. Example 3: Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct
number. Both numbers with value 2 are both considered as second maximum.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int thirdMax(vector<int>& nums) {
    priority_queue<int, vector<int>, greater<int>> min_heap;
    unordered_set<int> distinct;
    int max_item = nums.front();
    for (auto num : nums) {
      max_item = max(max_item, num);
      if (distinct.count(num)) continue;
      min_heap.push(num);
      distinct.insert(num);
      if (min_heap.size() > 3) {
        int to_delete = min_heap.top();
        distinct.erase(to_delete);
        min_heap.pop();
      }
    }

    return min_heap.size() == 3 ? min_heap.top() : max_item;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
415. Add Strings
Given two non-negative integers num1 and num2 represented as string, return the
sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to
integer directly.
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  string addStrings(string num1, string num2) {
    string res = "";
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
      int x = carry;
      if (i >= 0) x += (num1[i] - '0');
      if (j >= 0) x += (num2[j] - '0');

      carry = x / 10;
      res.push_back((x % 10) + '0');

      i--;
      j--;
    }

    if (carry > 0) res.push_back('1');
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
419. Battleships in a Board
Given an 2D board, count how many battleships are in it. The battleships are
represented with 'X's, empty slots are represented with '.'s. You may assume the
following rules: You receive a valid board, made of only battleships or empty
slots. Battleships can only be placed horizontally or vertically. In other
words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows,
1 column), where N can be of any size. At least one horizontal or vertical cell
separates between two battleships - there are no adjacent battleships. Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always
have a cell separating between them. Follow up: Could you do it in one-pass,
using only O(1) extra memory and without modifying the value of the board?
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
    N by checking if the element to the left and to the top of board[i][j] isn't
   a 'X'. If there is one then it means it is continuing a ship so it should not
   be counted.
*/
class Solution {
 public:
  int countBattleships(vector<vector<char>>& board) {
    if (board.empty()) return 0;
    int res = 0;
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[0].size(); j++) {
        if (board[i][j] == 'X' && (j == 0 || board[i][j - 1] != 'X') &&
            (i == 0 || board[i - 1][j] != 'X')) {
          res++;
        }
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
421. Maximum XOR of Two Numbers in an Array
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:
Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.

/*
    Submission Date: 2018-07-01
    Runtime: 47 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
  TrieNode* children[2];
  TrieNode() { children[0] = children[1] = NULL; }
};

class Solution {
 public:
  int findMaximumXOR(vector<int>& nums) {
    TrieNode* root = new TrieNode();
    // insert all numbers in trie in bit representation with msb near root
    for (const auto& n : nums) {
      TrieNode* curr = root;
      for (int i = 31; i >= 0; i--) {
        bool bit = n & (1 << i);
        if (curr->children[bit] == NULL) curr->children[bit] = new TrieNode();
        curr = curr->children[bit];
      }
    }

    // for each number search for the complementary if it exists, else take
    // other path
    int res = 0;
    for (const auto& n : nums) {
      TrieNode* curr = root;
      int max_value = 0;
      for (int i = 31; i >= 0; i--) {
        bool bit = n & (1 << i);
        bool comp_bit = !bit;
        if (curr->children[comp_bit] == NULL) {
          // take other path and since same number nothing is added
          curr = curr->children[bit];
        } else {
          // take complentary path and since a different number is added, add to
          // the max_value
          max_value += (1 << i);
          curr = curr->children[comp_bit];
        }
      }
      res = max(res, max_value);
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
423. Reconstruct Original Digits from English
Given a non-empty string containing an out-of-order English representation of
digits 0-9, output the digits in ascending order.

Note:

Input contains only lowercase English letters.
Input is guaranteed to be valid and can be transformed to its original digits.
That means invalid inputs such as "abc" or "zerone" are not permitted.
Input length is less than 50,000.



Example 1:
Input: "owoztneoer"

Output: "012"



Example 2:
Input: "fviefuro"

Output: "45"

/*
    Submission Date: 2018-07-13
    Runtime: 28 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<char, string> first_pass{
      {'z', "zero"}, {'w', "two"}, {'u', "four"}, {'x', "six"}, {'g', "eight"}};
  unordered_map<char, string> second_pass{
      {'o', "one"}, {'h', "three"}, {'f', "five"}, {'s', "seven"}};
  unordered_map<char, string> last_pass{{'i', "nine"}};

  vector<unordered_map<char, string>> v{first_pass, second_pass, last_pass};

  vector<string> rep{"zero", "one", "two",   "three", "four",
                     "five", "six", "seven", "eight", "nine"};

 public:
  /*
  have 3 passes where an unique number distinguishes between the numbers and
  only occurs once in that number get a frequency map of the string, for each
  pass see how many times that unique character occurs. if it is greater than
  zero, then it is part of the result so subtract occurence*(occurence in the
  number string) e.g 'h' appeared 3 times in s and 'e' appears 2 times in
  "three" so subtract 3*2. add the integer representation to the result occrence
  number of times. sort the result and return it.
  
  first unique
  zero => z
  two => w
  four => u
  six => x
  eight => g
  
  second unique
  one => o
  three => h
  five => f
  seven => s
  
  remaining
  nine => i
  */

  string originalDigits(string s) {
    unordered_map<string, char> rep_m;
    for (int i = 0; i < 10; i++) rep_m[rep[i]] = i + '0';

    unordered_map<char, int> freq;
    for (const auto& c : s) freq[c]++;  // o(n)

    string res;
    for (const auto& m : v) {  // occurs 3 times
      if (freq.empty()) break;
      for (const auto& kv : m) {  // occurs max 5 times
        if (freq.empty()) break;

        if (freq.count(kv.first)) {
          int occurences = freq[kv.first];
          for (int i = 0; i < occurences; i++) res.push_back(rep_m[kv.second]);

          unordered_map<char, int> distribution;
          for (const auto& c : kv.second)
            distribution[c]++;  // occurs max 5 time

          for (const auto& kv2 : distribution) {  // occurs max 5 time
            int to_remove = occurences * kv2.second;
            assert(freq.count(kv2.first));
            assert(freq[kv2.first] >= to_remove);
            if (freq[kv2.first] == to_remove)
              freq.erase(kv2.first);
            else
              freq[kv2.first] -= to_remove;
          }
        }
      }
    }

    sort(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
424. Longest Repeating Character Replacement
Given a string that consists of only uppercase English letters, you can replace
any letter in the string with another letter at most k times. Find the length of
a longest substring containing all repeating letters you can get after
performing the above operations.

Note:
Both the string's length and k will not exceed 104.



Example 1:
Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.




Example 2:
Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
/*
    Submission Date: 2018-07-15
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  /*
  find the longest substring where there are k characters that are not the main
  character use sliding window and keep track of frequency of characters in
  window, end - start + 1 - max_occurence > k means too many characters that are
  not the main character so shift start and end by 1. this keeps the size of the
  window always increasing as looking at smaller windows will not change the
  result.
  
  max_occurence will also always increase as suppose max_occurence is > actual
  max_occurence in the window then this window will not be part of the result as
  the number of not main characters will actually be higher than calculated.
  only when max_occurence updates can the window be extended/result updated.
  */
  int characterReplacement(string s, int k) {
    unordered_map<char, int> freq;
    int start = 0;
    int max_occurence = 0;
    for (int end = 0; end < s.size(); end++) {
      max_occurence = max(max_occurence, ++freq[s[end] - 'A']);
      if (end - start + 1 - max_occurence > k) {
        freq[s[start++] - 'A']--;
      }
    }

    return s.size() - start;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
427. Construct Quad Tree
We want to use quad trees to store an N x N boolean grid. Each cell in the grid
can only be true or false. The root node represents the whole grid. For each
node, it will be subdivided into four children nodes until the values in the
region it represents are all the same.

Each node has another two boolean attributes : isLeaf and val. isLeaf is true if
and only if the node is a leaf node. The val attribute for a leaf node contains
the value of the region it represents.

Your task is to use a quad tree to represent a given grid. The following example
may help you understand the problem better:

Given the 8 x 8 grid below, we want to construct the corresponding quad tree:



It can be divided according to the definition above:



 

The corresponding quad tree should be as following, where each node is
represented as a (isLeaf, val) pair.

For the non-leaf nodes, val can be arbitrary, so it is represented as *.



Note:


    N is less than 1000 and guaranteened to be a power of 2.
    If you want to know more about the quad tree, you can refer to its wiki.

/*
    Submission Date: 2018-07-13
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Node {
 public:
  bool val;
  bool isLeaf;
  Node* topLeft;
  Node* topRight;
  Node* bottomLeft;
  Node* bottomRight;

  Node() {}

  Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
       Node* _bottomLeft, Node* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

class Solution {
 public:
  /*
  cell of size 1 is a leaf and its value is just the grid cell
  else get the 4 quadrants
  they all have to be leafs and their values have to be the same for this to be
  merged else just put a parent node over the 4 quadrants
  */
  Node* help(const vector<vector<int>>& grid, int x, int y, int N) {
    if (N == 1) return new Node(grid[y][x], true, NULL, NULL, NULL, NULL);
    Node* top_left = help(grid, x, y, N / 2);
    Node* top_right = help(grid, x + N / 2, y, N / 2);
    Node* bottom_left = help(grid, x, y + N / 2, N / 2);
    Node* bottom_right = help(grid, x + N / 2, y + N / 2, N / 2);
    vector<Node*> v{top_left, top_right, bottom_left, bottom_right};
    bool all_same = v[0]->isLeaf;
    for (int i = 1; i < 4; i++) {
      if (!v[i]->isLeaf || v[i]->val != v[0]->val) {
        all_same = false;
        break;
      }
    }

    if (all_same)
      return new Node(v[0]->val, true, NULL, NULL, NULL, NULL);
    else
      return new Node(-1, false, top_left, top_right, bottom_left,
                      bottom_right);
  }

  Node* construct(vector<vector<int>>& grid) {
    int N = grid.size();
    if (N == 0) return NULL;
    return help(grid, 0, 0, N);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
429. N-ary Tree Level Order Traversal
Given an n-ary tree, return the level order traversal of its nodes' values. (ie,
from left to right, level by level).

For example, given a 3-ary tree:
 


 

We should return its level order traversal:

 

 

[
     [1],
     [3,2,4],
     [5,6]
]


 

Note:


    The depth of the tree is at most 1000.
    The total number of nodes is at most 5000.

/*
    Submission Date: 2018-07-13
    Runtime: 44 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
 public:
  int val = NULL;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    if (root == NULL) return {};
    vector<vector<int>> res;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
      int q_size = q.size();
      res.push_back({});
      for (int i = 0; i < q_size; i++) {
        Node* curr = q.front();
        q.pop();
        res.back().push_back(curr->val);
        for (const auto& c : curr->children) {
          if (c) q.push(c);
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
433. Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices
from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to
"end"), where ONE mutation is defined as ONE single character changed in the
gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations.
A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the
minimum number of mutations needed to mutate from "start" to "end". If there is
no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be
valid. You may assume start and end string is not the same. Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  bool isConnect(string s1, string s2) {
    int diff_count = 0;
    for (int i = 0, len = s1.size(); i < len; i++) {
      diff_count += s1[i] != s2[i];
    }
    return diff_count == 1;
  }

 public:
  int minMutation(string start, string end, vector<string>& bank) {
    unordered_map<string, vector<string>> graph;

    bank.push_back(start);
    int N = bank.size();
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if (isConnect(bank[i], bank[j])) {
          graph[bank[i]].push_back(bank[j]);
          graph[bank[j]].push_back(bank[i]);
        }
      }
    }

    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.emplace(start, 0);
    visited.insert(start);

    string curr;
    int dist;
    while (!q.empty()) {
      tie(curr, dist) = q.front();
      // cout << curr << ' ' << dist << endl;
      q.pop();
      if (curr == end) return dist;
      for (auto neighbor : graph[curr]) {
        if (visited.count(neighbor)) continue;
        q.emplace(neighbor, dist + 1);
        visited.insert(neighbor);
      }
    }
    return -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
434. Number of Segments in a String
Count the number of segments in a string, where a segment is defined to be a
contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5
/*
    Submission Date: 2018-06-09
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  int countSegments(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
      if (!isspace(s[i]) && (i == 0 || isspace(s[i - 1]))) {
        res++;
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
437. Path Sum III
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go
downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000
to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
/*
    Submission Date: 2018-06-09
    Runtime: 28 ms
    Difficulty: EASY
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
  /*
  returns path sums from this root down (not necessarily reach leaf)
  this is {root->val,
          root->val + l for all l from f(root->left),
          root->val + r for all r from f(root->left),
          }
  first one meets terminate the path here, second one means this extends a left
  path and the last one extends a right path check if any of the new paths equal
  sum to increase res
  */
  vector<int> help(TreeNode* root, int sum, int& res) {
    if (root == NULL) return {};
    vector<int> left = help(root->left, sum, res);
    vector<int> right = help(root->right, sum, res);

    if (root->val == sum) res++;

    vector<int> paths;
    paths.reserve(1 + left.size() + right.size());
    paths.push_back(root->val);

    for (const auto& l : left) {
      paths.push_back(root->val + l);
      if (paths.back() == sum) res++;
    }

    for (const auto& r : right) {
      paths.push_back(root->val + r);
      if (paths.back() == sum) res++;
    }

    return paths;
  }

  int pathSum(TreeNode* root, int sum) {
    int res = 0;
    help(root, sum, res);
    return res;
  }
};

int main() { return 0; }