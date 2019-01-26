
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
686. Repeated String Match
Given two strings A and B, find the minimum number of times A has to be repeated
such that B is a substring of it. If no such solution, return -1.


For example, with A = "abcd" and B = "cdabcdab".


Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring
of it; and B is not a substring of A repeated two times ("abcdabcd").


Note:
The length of A and B will be between 1 and 10000.
/*
    Submission Date: 2018-06-24
    Runtime: 716 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  if A is already in B, return 1
  else it is a suffix of A + A repeated n times + prefix of A
  so return n + 2
  for all suffix of A, check if it is a prefix of B. if it is then see how many
  times A repeats if it does repeat n times and the prefix of A is a suffix of
  B, then the answer is just n + 2.
  */
  int repeatedStringMatch(string A, string B) {
    if (A.find(B) != string::npos) return 1;
    for (int i = 0; i < A.size(); i++) {
      bool got_suffix = true;
      for (int j = 0; j < A.size() - i; j++) {
        if (B[j] != A[i + j]) {
          got_suffix = false;
          break;
        }
      }

      if (!got_suffix) continue;
      int res = 1;
      int A_ind = 0;
      for (int j = A.size() - i; j < B.size(); j++) {
        if (A_ind == 0) res++;

        if (B[j] != A[A_ind]) {
          res = -1;
          break;
        }

        A_ind = (A_ind + 1) % A.size();
      }

      if (res == -1) continue;
      return res;
    }

    return -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
687. Longest Univalue Path
Given a binary tree, find the length of the longest path where each node in the
path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges
between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the
tree is not more than 1000.
/*
    Submission Date: 2018-05-24
    Runtime: 112 ms
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
      N by returning the longest path that starts from this node where a path is
     straight down where all the nodes have the same value. This is 1 +
     max(f(left), f(right)) if left and right have the same value as this node.
      Variable that is passed by reference is the result where it can be 1 +
     f(left) + f(right) if left and right have the same value as this node as it
     means there is a path for the left and a path for the right which creates a
     upside down v shape.
  */
  int solve(TreeNode* root, int& res) {
    if (!root) return 0;
    vector<int> longest_path_starting_at_child{solve(root->left, res),
                                               solve(root->right, res)};
    int pos_res = 1;
    int longest_path_starting_at_node = 0;

    if (root->left && root->left->val == root->val) {
      pos_res += longest_path_starting_at_child[0];
      longest_path_starting_at_node = longest_path_starting_at_child[0];
    }
    if (root->right && root->right->val == root->val) {
      pos_res += longest_path_starting_at_child[1];
      longest_path_starting_at_node =
          max(longest_path_starting_at_node, longest_path_starting_at_child[1]);
    }

    res = max(res, pos_res);
    return 1 + longest_path_starting_at_node;
  }

  int longestUnivaluePath(TreeNode* root) {
    int res = 1;
    solve(root, res);
    return res - 1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
690. Employee Importance
You are given a data structure of employee information, which includes the
employee's unique id, his importance value and his direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the
leader of employee 3. They have importance value 15, 10 and 5, respectively.
Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has [2,
10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a
subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, you need to
return the total importance value of this employee and all his subordinates.

Example 1:
Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee
2 and employee 3. They both have importance value 3. So the total importance
value of employee 1 is 5 + 3 + 3 = 11. Note: One employee has at most one direct
leader and may have several subordinates. The maximum number of employees won't
exceed 2000.
/*
    Submission Date: 2018-06-04
    Runtime: 135 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Employee {
 public:
  // It's the unique ID of each node.
  // unique id of this employee
  int id;
  // the importance value of this employee
  int importance;
  // the id of direct subordinates
  vector<int> subordinates;
};

class Solution {
 public:
  int dfs(int id, unordered_map<int, int> id_to_ind,
          const vector<Employee*>& employees) {
    int res = employees[id_to_ind[id]]->importance;
    for (const auto& e : employees[id_to_ind[id]]->subordinates)
      res += dfs(e, id_to_ind, employees);
    return res;
  }

  int getImportance(vector<Employee*> employees, int id) {
    unordered_map<int, int> id_to_ind;
    for (int i = 0; i < employees.size(); i++) id_to_ind[employees[i]->id] = i;

    return dfs(id, id_to_ind, employees);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
692. Top K Frequent Words
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words
have the same frequency, then the word with the lower alphabetical order comes
first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"],
k = 4 Output: ["the", "is", "sunny", "day"] Explanation: "the", "is", "sunny"
and "day" are the four most frequent words, with the number of occurrence being
4, 3, 2 and 1 respectively. Note: You may assume k is always valid, 1 ≤ k ≤
number of unique elements. Input words contain only lowercase letters. Follow
up: Try to solve it in O(n log k) time and O(n) extra space.
/*
    Submission Date: 2018-05-24
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> freq_map;
    for (auto e : words) freq_map[e]++;

    map<int, vector<string>> grouped_map;
    for (auto kv : freq_map) grouped_map[kv.second].push_back(kv.first);

    vector<string> res;
    for (auto it = grouped_map.rbegin(); it != grouped_map.rend(); it++) {
      sort(it->second.begin(), it->second.end());
      for (auto e : it->second) {
        res.push_back(e);
        if (res.size() == k) break;
      }
      if (res.size() == k) break;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
693. Binary Number with Alternating Bits
Given a positive integer, check whether it has alternating bits: namely, if two
adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
/*
    Submission Date: 2018-06-02
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution2 {
 public:
  // 0x5555555555555555 checks if any of the even bits are set as 5 is 0101
  bool IsPowerOfFour(long long x) {
    return (x & ~(x - 1)) == x && (x & 0x5555555555555555);
  }

  // 0xaaaaaaaaaaaaaaaa checks if any of the odd bits are set as a is 1010
  bool IsPowerOfFourTimesTwo(long long x) {
    return (x & ~(x - 1)) == x && (x & 0xaaaaaaaaaaaaaaaa);
  }
  /*
      sum of geometric series is (1-r^n)/(1-r) so sum 2^(2i) and sum 2^(2i+1)
     becomes sum(2^(2i)) = sum(4^i) = (1-4^n)/(1-4) = (4^n-1)/3 sum(2^(2i+1)) =
     2*sum(4^i) = 2*(1-4^n)/(1-4) = (2*4^n-2)/3 so check if the number x =
     (4^n-1)/3 or x = (2*4^n-2)/3 works
  */
  bool hasAlternatingBits(long long n) {
    return IsPowerOfFour(3 * n + 1) || IsPowerOfFourTimesTwo(n * 3 + 2);
  }
};

class Solution {
 public:
  /*
      shift number by two bits and xor it with itself. only the leading one
     should remeain first operation gives one if x[i] != x[i+2] so if they are
     all zero it means x[0] = x[2] = x[4] = ... x[2*n] and x[1] = x[3] = x[5] =
     ... x[2*n+1]

      x[0] and x[1] can give 4 combinations 00, 01, 10, 11 so checking that
     there is just a leading one ensures there is only one 1 and one 0 that
     propogate correctly to the rest of the numbers.
  */
  bool hasAlternatingBits(int n) {
    int x = ((n >> 2) ^ n);
    return (x & ~(x - 1)) == x;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
695. Max Area of Island
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no
island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island
must be connected 4-directionally. Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.
/*
    Submission Date: 2018-06-03
    Runtime: 32 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

 public:
  int dfs(vector<vector<int>>& grid, int i, int j, int N, int M) {
    grid[i][j] = 0;

    int res = 1;
    for (int k = 0; k < 4; k++) {
      int new_x = j + dx[k];
      int new_y = i + dy[k];
      if ((0 <= new_x && new_x < M) && (0 <= new_y && new_y < N) &&
          grid[new_y][new_x] == 1) {
        res += dfs(grid, new_y, new_x, N, M);
      }
    }
    return res;
  }

  int maxAreaOfIsland(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int N = grid.size();
    int M = grid[0].size();
    int res = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] == 1) {
          res = max(res, dfs(grid, i, j, N, M));
        }
      }
    }
    return res;
  }
};

int main() { return 0; }