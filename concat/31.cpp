
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
665. Non-decreasing Array
Given an array with n integers, your task is to check if it could become
non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every
i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].
/*
    Submission Date: 2018-06-09
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  for the first number where nums[i] < nums[i-1] where nums[i] = c
  a b c d
  
  then a <= b and c < b.
  the condition must hold c <= d as if c < d then it will be a a c (c-x)
  or 10 10 7 6 where c has to be fixed and d as well
  
  if problem_ind == -1 means the array is already sorted in increasing order
  if it is 1 then just update nums[0] to equal nums[1]
  
  if a <= c then it is true as well as a <= b, a <= c and c <= d (from before)
  so a <= b <= c <= d
  
  if d does not exist or b <= d as a <= b and b <= d so replace c with any
  number between [b,d] to get a b b d
  */
  bool checkPossibility(vector<int>& nums) {
    int problem_ind = -1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] < nums[i - 1]) {
        if (problem_ind != -1) return false;
        problem_ind = i;
      }
    }

    return problem_ind < 2 || nums[problem_ind - 2] <= nums[problem_ind] ||
           (problem_ind + 1 == nums.size() ||
            nums[problem_ind - 1] <= nums[problem_ind + 1]);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
667. Beautiful Arrangement II
Given two integers n and k, you need to construct a list which contains n
different positive integers ranging from 1 to n and obeys the following
requirement:

Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 -
a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.



If there are multiple answers, print any of them.


Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1
to 3, and the [1, 1] has exactly 1 distinct integer: 1.



Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1
to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.



Note:

The n and k are in the range 1 <= k < n <= 104.

/*
    Submission Date: 2018-07-02
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  place elements [1, n-k] in array then keep adding to the back numbers from
  [k, 1] alterating the sign (+, -) starting with +
  */
  vector<int> constructArray(int n, int k) {
    vector<int> res;
    res.reserve(n);
    for (int i = 1; i + k <= n; i++) res.push_back(i);
    for (int i = 0; i < k; i++) {
      res.push_back(res.back() + (i % 2 == 0 ? 1 : -1) * (k - i));
    }

    return res;
  }
};

class Solution2 {
 public:
  /*
  have two pointers i and j where i starts at 1 and j starts at n
  interweave i and j for the first k elements then just keep increasing i until
  reaches j e.g n = 5, k = 3
  
  weaves 3 2 1
  res    1 5 2 3 4
  diff    4 3 1 1
  */
  vector<int> constructArray(int n, int k) {
    vector<int> res;
    res.reserve(n);
    int j = n;
    for (int i = 1; i <= j;) {
      if (k > 1) {
        res.push_back(k-- % 2 ? i++ : j--);
      } else {
        res.push_back(i++);
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
669. Trim a Binary Search Tree
Given a binary search tree and the lowest and highest boundaries as L and R,
trim the tree so that all its elements lies in [L, R] (R >= L). You might need
to change the root of the tree, so the result should return the new root of the
trimmed binary search tree.

Example 1:
Input:
    1
   / \
  0   2

  L = 1
  R = 2

Output:
    1
      \
       2
Example 2:
Input:
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output:
      3
     /
   2
  /
 1
/*
    Submission Date: 2018-05-31
    Runtime: 18 ms
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
  /*
  if node val is within bounds, than return node with left and right subtrees
  trimmed if node val is > R that means all the element in the right subtree
  will also be bigger so return the trimmed left subtree if node val is < L that
  means all the element in the left subtree will also be smaller so return the
  trimmed right subtree
  */
  TreeNode* trimBST(TreeNode* root, int L, int R) {
    if (root == NULL) return NULL;
    if (root->val > R) {
      return trimBST(root->left, L, R);
    } else if (root->val < L) {
      return trimBST(root->right, L, R);
    } else {
      root->left = trimBST(root->left, L, R);
      root->right = trimBST(root->right, L, R);
      return root;
    }
  }
};
int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
671. Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative
value, where each node in this tree has exactly two or zero sub-node. If the
node has two sub-nodes, then this node's value is the smaller value among its
two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set
made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
/*
    Submission Date: 2018-06-08
    Runtime: 3 ms
    Difficulty: EASY
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
 public:
  /*
  bfs that once reaches a different node->val than root->val will stop putting
  that node's children. result is the minimum of all these first encountered
  different node-> val
  */
  int findSecondMinimumValue(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = INT_MAX;
    bool seen_others = false;

    while (!q.empty()) {
      TreeNode* node = q.front();
      q.pop();
      if (node->val == root->val) {
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      } else {
        // found node that does not equal root->val, no need to go deeper as
        // they will be >= node->val
        res = min(res, node->val);
        seen_others = true;
      }
    }

    return seen_others ? res : -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
672. Bulb Switcher II
There is a room with n lights which are turned on initially and 4 buttons on the
wall. After performing exactly m unknown operations towards buttons, you need to
return how many different kinds of status of the n lights could be.



Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4
buttons are given below:


Flip all the lights.
Flip lights with even numbers.
Flip lights with odd numbers.
Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...




Example 1:
Input: n = 1, m = 1.
Output: 2
Explanation: Status can be: [on], [off]




Example 2:
Input: n = 2, m = 1.
Output: 3
Explanation: Status can be: [on, off], [off, on], [off, off]




Example 3:
Input: n = 3, m = 1.
Output: 4
Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off],
[off, on, on].



Note:
n and m both fit in range [0, 1000].

/*
    Submission Date: 2018-07-07
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  8 states:
  All_on, 1, 2, 3, 4, 1+4, 2+4, 3+4
  
  m == 0: All_on (no possible moves) => 1
  m > 0:
      n == 1: All_on (3 apply odd which doesnt affect anything) or 1 => 2
      n == 2:
          m == 1: 1, 2, 3 => 3
          m >= 2: All_on (1 1), 1 (2 3), 2 (1 3), 3 (1 2) => 4
      n >= 3:
          m == 1: 1, 2, 3, 4 => 4
          m == 2: All_on (1 1), 1 (2 3), 2 (1 3), 3 (1 2), 1+4, 2+4, 3+4 => 7
          m > 2: All_on (1 2 3), 1 (1 1 1), 2 (1 1 2), 3 (1 1 2), 4 (1 1 4),
                  1+4 (2 3 4), 2+4 (1 3 4), 3+4 (1 2 4) => 8
      
  */
  int flipLights(int n, int m) {
    if (m == 0) return 1;
    if (n == 1) return 2;
    if (n == 2) {
      if (m == 1) return 3;
      return 4;
    } else {
      if (m == 1) return 4;
      if (m == 2) return 7;
      return 8;
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
674. Longest Continuous Increasing Subsequence
Given an unsorted array of integers, find the length of longest continuous
increasing subsequence (subarray).

Example 1:
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its
length is 3. Even though [1,3,5,7] is also an increasing subsequence, it's not a
continuous one where 5 and 7 are separated by 4. Example 2: Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length
is 1. Note: Length of the array will not exceed 10,000.
/*
    Submission Date: 2018-06-08
    Runtime: 14 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findLengthOfLCIS(vector<int>& nums) {
    if (nums.empty()) return 0;

    int res = 1;
    int pos_res = 1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] > nums[i - 1]) {
        pos_res++;
      } else {
        pos_res = 1;
      }
      res = max(res, pos_res);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
676. Implement Magic Dictionary

Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to
build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify
exactly one character into another character in this word, the modified word is
in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about
highly efficient algorithm after the contest. Please remember to RESET your
class variables declared in class MagicDictionary, as static/class variables are
persisted across multiple test cases. Please see here for more details.
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class MagicDictionary {
 public:
  /** Initialize your data structure here. */
  unordered_map<string, vector<pair<char, int>>> m_;
  MagicDictionary() {}

  /** Build a dictionary through a list of words */
  void buildDict(vector<string> dict) {
    /*
        N words of size K O(Nk^2)
        hello -> [ello, [h, 0]], [hllo, [e, 1]], [helo, l, 2]], [helo, [l, 3]],
       [hell, [o, 4]]
    */
    m_.clear();
    for (const auto& s : dict) {
      for (int i = 0; i < s.size(); i++) {
        m_[s.substr(0, i) + s.substr(i + 1)].emplace_back(s[i], i);
      }
    }
  }

  /** Returns if there is any word in the trie that equals to the given word
   * after modifying exactly one character */
  bool search(string s) {
    // O(k^2*M) where M is size of vector for a key in m_
    for (int i = 0; i < s.size(); i++) {
      const auto& key = s.substr(0, i) + s.substr(i + 1);
      if (!m_.count(key)) continue;
      for (const auto& p : m_[key]) {
        // looking for same index different letter
        if (p.second == i && p.first != s[i]) return true;
      }
    }
    return false;
  }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
677. Map Sum Pairs
Implement a MapSum class with insert, and sum methods.



For the method insert, you'll be given a pair of (string, integer). The string
represents the key and the integer represents the value. If the key already
existed, then the original key-value pair will be overridden to the new one.



For the method sum, you'll be given a string representing the prefix, and you
need to return the sum of all the pairs' value whose key starts with the prefix.


Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5

/*
    Submission Date: 2018-07-02
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

struct TrieNode {
  int sum;
  TrieNode* children[26];
  TrieNode() {
    sum = 0;
    for (int i = 0; i < 26; i++) children[i] = NULL;
  }
};

class MapSum {
  unordered_map<string, int> m;
  TrieNode* root;

 public:
  /** Have a trie and unordered_map. the unordered_map keeps track of key and
   val the trie can find prefix easily. each node has sum which is the sum of
   all...l with each node visited getting the to_add added to their sum.
  */
  MapSum() { root = new TrieNode(); }

  void insert(string key, int val) {
    int to_add = m.count(key) ? val - m[key] : val;
    m[key] = val;
    TrieNode* curr = root;
    curr->sum += to_add;

    for (const auto& c : key) {
      if (curr->children[c - 'a'] == NULL)
        curr->children[c - 'a'] = new TrieNode();
      curr = curr->children[c - 'a'];
      curr->sum += to_add;
    }
  }

  int sum(string prefix) {
    TrieNode* curr = root;
    for (const auto& c : prefix) {
      if (curr->children[c - 'a'] == NULL) return 0;
      curr = curr->children[c - 'a'];
    }

    return curr->sum;
  }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
680. Valid Palindrome II
Given a non-empty string s, you may delete at most one character. Judge whether
you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z. The maximum length of the
string is 50000.
/*
    Submission Date: 2018-06-24
    Runtime: 129 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
 public:
  /*
  dp[i][j] represents number of deletes to make a palindrome for string [i, j]
  */
  bool validPalindrome(string s) {
    int N = s.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));
    for (int gap = 1; gap < N; gap++) {
      for (int i = 0; i + gap < N; i++) {
        int j = i + gap;
        dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1]
                                : 1 + min(dp[i + 1][j], dp[i][j - 1]);
      }
    }

    return dp[0][N - 1] <= 1;
  }
};

class Solution {
 public:
  bool IsPalindrome(const string& s, int l, int r) {
    while (l < r) {
      if (s[l] == s[r]) {
        l++;
        r--;
      } else {
        return false;
      }
    }
    return true;
  }

  /*
  loop l and r until they do not match then check either if skipping l
  IsPalindrome(s, l+1, r) or skipping r IsPalindrome(s, l, r-1) will result in a
  palindrome
  */
  bool validPalindrome(string s) {
    int l = 0;
    int r = s.size() - 1;
    while (l < r) {
      if (s[l] == s[r]) {
        l++;
        r--;
      } else {
        return IsPalindrome(s, l + 1, r) || IsPalindrome(s, l, r - 1);
      }
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
682. Baseball Game
You're now a baseball game point recorder.

Given a list of strings, each string can be one of the 4 following types:

Integer (one round's score): Directly represents the number of points you get in
this round.
"+" (one round's score): Represents that the points you get in this round are
the sum of the last two valid round's points. "D" (one round's score):
Represents that the points you get in this round are the doubled data of the
last valid round's points. "C" (an operation, which isn't a round's score):
Represents the last valid round's points you get were invalid and should be
removed. Each round's operation is permanent and could have an impact on the
round before and the round after.

You need to return the sum of the points you could get in all the rounds.

Example 1:
Input: ["5","2","C","D","+"]
Output: 30
Explanation:
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get 2 points. The sum is: 7.
Operation 1: The round 2's data was invalid. The sum is: 5.
Round 3: You could get 10 points (the round 2's data has been removed). The sum
is: 15. Round 4: You could get 5 + 10 = 15 points. The sum is: 30. Example 2:
Input: ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation:
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get -2 points. The sum is: 3.
Round 3: You could get 4 points. The sum is: 7.
Operation 1: The round 3's data is invalid. The sum is: 3.
Round 4: You could get -4 points (the round 3's data has been removed). The sum
is: -1. Round 5: You could get 9 points. The sum is: 8. Round 6: You could get
-4 + 9 = 5 points. The sum is 13. Round 7: You could get 9 + 5 = 14 points. The
sum is 27. Note: The size of the input list will be between 1 and 1000. Every
integer represented in the list will be between -30000 and 30000.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  let stk be all the valid round points. if it is a number just add it as a
  round and increment res by the amount if it is a "+", take the last two rounds
  add add them up. put the sum as a round and increment res by the amount if it
  is a "D", take the last round, multiply it by two and add it as a around and
  increment res by the amount if it is a "C", take the last round and decrease
  res by the amount as well as pop that round off.
  */
  int calPoints(vector<string>& ops) {
    int res = 0;
    vector<int> stk;
    for (const auto& s : ops) {
      int stk_size = stk.size();
      if (s == "+") {
        assert(stk_size >= 2);
        stk.push_back(stk[stk_size - 1] + stk[stk_size - 2]);
        res += stk.back();
      } else if (s == "D") {
        assert(stk_size >= 1);
        stk.push_back(stk[stk_size - 1] * 2);
        res += stk.back();
      } else if (s == "C") {
        res -= stk.back();
        stk.pop_back();
      } else {  // a number
        stk.push_back(stoi(s));
        res += stk.back();
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
684. Redundant Connection
In this problem, a tree is an undirected graph that is connected and has no
cycles.

The given input is a graph that started as a tree with N nodes (with distinct
values 1, 2, ..., N), with one additional edge added.  The added edge has two
different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges.  Each element of edges is a
pair [u, v] with u < v, that represents an undirected edge connecting nodes u
and v.

Return an edge that can be removed so that the resulting graph is a tree of N
nodes.  If there are multiple answers, return the answer that occurs last in the
given 2D-array.  The answer edge [u, v] should be in the same format, with u <
v.
Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3


Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3


Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is
the size of the input array.





Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly
the graph is an undirected graph. For the directed graph follow up please see
Redundant Connection II). We apologize for any inconvenience caused.

/*
    Submission Date: 2018-07-11
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class UnionFind {
  // key is element, value is rank
  unordered_map<T, int> rank_;
  // key is element, value is parent
  unordered_map<T, T> parent_;

 public:
  bool IsWithinSet(T e) { return parent_.count(e); }

  void CreateSet(T e) {
    assert(!IsWithinSet(e));
    parent_[e] = e;
    rank_[e] = 0;
  }

  // finds the root of e
  T Find(T e) {
    if (parent_[e] != e) {
      // this is not a root (root has parent to be equal itself)
      // so find root and apply path compression along path
      parent_[e] = Find(parent_[e]);
    }
    return parent_[e];
  }

  // unions the sets of e1 and e2 if necessary
  // return whether an union took place
  bool Union(T e1, T e2) {
    T e1_root = Find(e1);
    T e2_root = Find(e2);

    if (e1_root == e2_root) return false;  // same root

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (rank_[e1_root] < rank_[e2_root]) {
      parent_[e1_root] = e2_root;
    } else {
      parent_[e2_root] = e1_root;
      if (rank_[e1_root] == rank_[e2_root]) {
        rank_[e1_root]++;
      }
    }

    return true;
  }
};

class Solution {
 public:
  /*
  union find
  for each node uv, find if u and v are seperate sets. if they are, union the
  sets else they are in the same set and already connected so return uv
  */
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    UnionFind<int> uf;
    for (const auto& uv : edges) {
      if (!uf.IsWithinSet(uv[0])) uf.CreateSet(uv[0]);
      if (!uf.IsWithinSet(uv[1])) uf.CreateSet(uv[1]);
      if (!uf.Union(uv[0], uv[1])) {  // no union occured as same set already
        return uv;
      }
    }

    return {};
  }
};

class Solution2 {
  vector<int> path;
  int u = -1;

 public:
  bool dfs(int from, unordered_map<int, vector<int>>& adj,
           unordered_set<int>& visited, int parent) {
    for (const auto& to : adj[from]) {
      if (to == parent) continue;
      if (visited.count(to)) {
        u = to;
        return true;
      }

      visited.insert(to);

      path.push_back(to);
      if (dfs(to, adj, visited, from)) {
        return true;
      }
      path.pop_back();
    }

    return false;
  }

  /*
  do dfs and keep track of path. for nodes that are not in cycle the popback
  will remove them the result is path is vector of nodes that go into a cycle
  and u marks where the cycle begins now traverse the cycle (ie path) and find
  the edge that has highest index
  */
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> adj;

    unordered_map<int, unordered_map<int, int>> priority;
    int i = 0;
    for (const auto& uv : edges) {
      adj[uv[1]].push_back(uv[0]);
      adj[uv[0]].push_back(uv[1]);
      priority[uv[0]][uv[1]] = i++;
    }

    unordered_set<int> visited;

    // no disjoint so can just start at one node and will traverse everything
    visited.insert(1);
    path.push_back(1);

    bool cycle = dfs(1, adj, visited, -1);
    assert(cycle);
    i = 0;
    while (path[i] != u) i++;

    int start = i;
    int pos_u = -1;
    int pos_v = -1;
    int N = path.size();
    for (int j = i; j < N; j++) cout << path[j] << ' ';
    cout << endl;
    for (; i < N; i++) {
      auto p = minmax(path[i], i + 1 < N ? path[i + 1] : path[start]);
      if (pos_u == -1 || priority[p.first][p.second] > priority[pos_u][pos_v]) {
        pos_u = p.first;
        pos_v = p.second;
      }
    }

    return {pos_u, pos_v};
  }
};

int main() { return 0; }
