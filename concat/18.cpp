
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
321. Create Maximum Number
Given two arrays of length m and n with digits 0-9 representing two numbers.
Create the maximum number of length k <= m + n from digits of the two. The
relative order of the digits from the same array must be preserved. Return an
array of the k digits. You should try to optimize your time and space
complexity.

Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]

Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]

Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
/*
    Submission Date: 2018-05-02
    Runtime: 72 ms
    Difficulty: HARD
*/
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      Take i numbers from first array and k - i numbers from second array.
      Merge to find the largest possible string and store the largest for all i.
      O(k^3)
  */
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    string s1, s2;
    int m = nums1.size(), n = nums2.size();

    s1.reserve(m);
    s2.reserve(n);

    for (auto e : nums1) s1.push_back(e + '0');
    for (auto e : nums2) s2.push_back(e + '0');

    string res = "";
    // need to maintain k-i >= 0, i <= m
    for (int i = 0; i <= min(m, k); i++) {
      if (k - i > n)
        continue;  // s2 is too short to produce k-i elements needed
      string tmp = Merge(MaxArray(s1, i), MaxArray(s2, k - i), m, n);
      res = max(res, tmp);
    }

    vector<int> out(k);
    for (int i = 0; i < k; i++) out[i] = res[i] - '0';
    return out;
  }

  // O(m + n) merge of two substrings of size m and n by choosing letters to
  // make the largest possible.
  string Merge(const string& s1, const string& s2, int m, int n) {
    int i = 0, j = 0;
    string res;
    while (i < s1.size() || j < s2.size()) {
      if (s1.substr(min(i, m)) > s2.substr(min(j, n))) {
        res.push_back(s1[i++]);
      } else {
        res.push_back(s2[j++]);
      }
    }

    return res;
  }

  // maximum subsequence of s with size n, if s.size() <= n return s. O(n)
  string MaxArray(const string& s, int n) {
    string stk = "";
    for (int i = 0; i < s.size(); i++) {
      // if remaining elements and stack have more than enough elements
      // then keep removing from the stack while it is smaller than the current
      // element
      while (s.size() - i + stk.size() > n && !stk.empty() && stk.back() < s[i])
        stk.pop_back();
      // if the stk is already size n, no need to push
      if (stk.size() < n) stk.push_back(s[i]);
    }
    return stk;
  }
};

class Solution2 {
 public:
  /*
      dp[i][j][k] represents the largest number created from nums1 from [0,i)
      and nums2 [0, j) of size k.

      dp[i][j][k] = max (
          dp[i-1][j][k-1] + nums1[i-1]    take a number from nums1
          dp[i-1][j][k]                   do not take a number
          dp[i][j-1][k-1] + nums2[j-1]    take a number forom nums2
          dp[i][j-1][k]                   do not take a number
          )
  */
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int kk) {
    string s1, s2;
    for (auto e : nums1) s1.push_back(e + '0');
    for (auto e : nums2) s2.push_back(e + '0');
    vector<vector<vector<string>>> dp(
        s1.size() + 1,
        vector<vector<string>>(s2.size() + 1, vector<string>(kk + 1)));

    for (int k = 1; k <= kk; k++) {
      for (int i = 0; i <= s1.size(); i++) {
        for (int j = 0; j <= s2.size(); j++) {
          if (i > 0) {
            dp[i][j][k] =
                max(dp[i][j][k], dp[i - 1][j][k - 1] + string(1, s1[i - 1]));
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
          }
          if (j > 0) {
            dp[i][j][k] =
                max(dp[i][j][k], dp[i][j - 1][k - 1] + string(1, s2[j - 1]));
            dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
          }
        }
      }
    }

    vector<int> res;
    for (const auto& e : dp[s1.size()][s2.size()][kk]) res.push_back(e - '0');
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
322. Coin Change
You are given coins of different denominations and a total amount of money
amount. Write a function to compute the fewest number of coins that you need to
make up that amount. If that amount of money cannot be made up by any
combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
/*
    Submission Date: 2017-03-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    int N = coins.size();
    vector<int> dp(amount + 1, INT_MAX);

    dp[0] = 0;

    for (int i = 1; i <= N; i++) {
      for (int j = 0; j <= amount; j++) {
        if (j - coins[i - 1] >= 0 &&
            dp[j - coins[i - 1]] != INT_MAX) {  // we can take this coin
          dp[j] = min(dp[j - coins[i - 1]] + 1, dp[j]);
        }
      }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?
/*
    Submission Date: 2018-05-02
    Runtime: 80 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isPowerOfThree(int n) {
    // 1162261467 largest power of 3 that can be represented by int and all it's
    // factors are powers of 3. a = nq + r where n < r means a % n = r 3^19 % y
    // => 3^19 = n*y + r if y == 3^x, then this only true if r == 0 and n ==
    // 3^(19-x)
    return n > 0 && 1162261467 % n == 0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
328. Odd Even Linked List
Given a singly linked list, group all odd nodes together followed by the even
nodes. Please note here we are talking about the node number and not the value
in the nodes.

You should try to do it in place. The program should run in O(1) space
complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was
in the input. The first node is considered odd, the second node even and so on
...
/*
    Submission Date: 2018-05-02
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* oddEvenList(ListNode* head) {
    ListNode *first_odd, *first_even;
    first_odd = first_even = NULL;
    vector<ListNode*> arr{NULL, NULL};

    int index = 0;
    while (head) {
      ListNode* temp = head;
      head = head->next;
      temp->next = NULL;

      if (index == 0 && first_odd == NULL) {
        first_odd = temp;
      } else if (index == 1 && first_even == NULL) {
        first_even = temp;
      }

      if (arr[index] == NULL)
        arr[index] = temp;
      else {
        arr[index]->next = temp;
        arr[index] = temp;
      }

      index ^= 1;
    }

    if (arr[0]) {
      arr[0]->next = first_even;
    }
    return first_odd;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
329. Longest Increasing Path in a Matrix
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down.
You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is
not allowed).

Example 1:

Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is
not allowed.
/*
    Submission Date: 2018-05-26
    Runtime: 112 ms
    Difficulty: HARD
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  vector<int> dx_{1, -1, 0, 0};
  vector<int> dy_{0, 0, 1, -1};

  unordered_map<int, int> dp_;

 public:
  int id(const int& i, const int& j, const int& M) { return i * M + j; }

  /*
       graph has vertex being a cell and the edges to cells strictly greater
     than it (directed graph) do a dfs on all the neighbors and take the max of
     this to return use memoization as the longest path for a cell is the same
     once computed.
  */
  int dfs(int curr, const unordered_map<int, vector<int>>& graph) {
    if (dp_.count(curr)) return dp_[curr];

    const auto& it = graph.find(curr);
    if (it == graph.cend()) return dp_[curr] = 1;

    int res = 0;

    for (const auto& n : it->second) {
      res = max(res, dfs(n, graph));
    }

    return dp_[curr] = res + 1;
  }

  int longestIncreasingPath(vector<vector<int>>& A) {
    if (A.empty()) return 0;

    int N = A.size();
    int M = A[0].size();
    unordered_map<int, vector<int>> graph;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < 4; k++) {
          if ((0 <= dy_[k] + i && dy_[k] + i < N) &&
              (0 <= dx_[k] + j && dx_[k] + j < M) &&
              A[i][j] < A[i + dy_[k]][j + dx_[k]])
            graph[id(i, j, M)].push_back(id(i + dy_[k], j + dx_[k], M));
        }
      }
    }

    int res = 1;
    for (const auto& kv : graph) {
      res = max(res, dfs(kv.first, graph));
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
330. Patching Array
Given a sorted positive integer array nums and an integer n, add/patch elements
to the array such that any number in range [1, n] inclusive can be formed by the
sum of some elements in the array. Return the minimum number of patches
required.

Example 1:

Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3],
[2,3], [1,2,3]. Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range
[1, 6]. So we only need 1 patch. Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
/*
    Submission Date: 2018-05-30
    Runtime: 9 ms
    Difficulty: HARD
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      suppose furthest is the sum of all elements before nums[i], then
      if furthest >= nums[i] - 1, it means we can include this element and
     furthest += nums[i] else furthest is too small so we can add furthest + 1
     (res increases as element is added) meaning furthest = 2*furthest + 1 and
     keep doing this until furthest >= nums[i] - 1
  */
  int minPatches(vector<int>& nums, int n) {
    int res = 0;
    int furthest = 0;
    for (const auto& x : nums) {
      if (furthest >= n) break;
      while (x > furthest + 1 && furthest < n) {
        furthest = (furthest <= (INT_MAX - 1) / 2) ? furthest * 2 + 1 : INT_MAX;
        res++;
      }
      furthest += x;
    }

    while (n > furthest) {
      furthest = (furthest <= (INT_MAX - 1) / 2) ? furthest * 2 + 1 : INT_MAX;
      res++;
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
331. Verify Preorder Serialization of a Binary Tree
One way to serialize a binary tree is to use pre-order traversal. When we
encounter a non-null node, we record the node's value. If it is a null node, we
record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string
"9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct
preorder traversal serialization of a binary tree. Find an algorithm without
reconstructing the tree.

Each comma separated value in the string must be either an integer or a
character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never
contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
 public:
  bool isValidSerialization(string preorder) {
    int count = 0;
    stringstream ss(preorder);
    string temp;
    while (getline(ss, temp, ',')) {
      if (count < 0) return false;
      if (temp == "#") {
        count--;
      } else {
        count++;
      }
    }

    return count == -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
332. Reconstruct Itinerary
Given a list of airline tickets represented by pairs of departure and arrival
airports [from, to], reconstruct the itinerary in order. All of the tickets
belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that
has the smallest lexical order when read as a single string. For example, the
itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"]. All
airports are represented by three capital letters (IATA code). You may assume
all tickets form at least one valid itinerary. Example 1: tickets = [["MUC",
"LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]] Return ["JFK", "MUC",
"LHR", "SFO", "SJC"]. Example 2: tickets =
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]] Return
["JFK","ATL","JFK","SFO","ATL","SFO"]. Another possible reconstruction is
["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
/*
    Submission Date: 2018-05-02
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // m is unordered key of 'from' with value of ordered key of 'to' with value
  // frequency
  void recurse(unordered_map<string, map<string, int>>& m, string from,
               const int& tickets_to_use, vector<string>& curr,
               vector<string>& res) {
    if (tickets_to_use == 0) {
      assert(res.empty());
      res = curr;
    } else {
      if (!m.count(from)) return;

      for (auto& kv : m[from]) {
        if (kv.second > 0) {
          // there is a to for from so try to use it
          kv.second--;
          curr.push_back(kv.first);
          recurse(m, kv.first, tickets_to_use - 1, curr, res);
          // if res isn't empty, then a path was found and return it
          curr.pop_back();
          if (!res.empty()) return;
          kv.second++;
        }
      }
    }
  }

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    unordered_map<string, map<string, int>> m;
    for (auto p : tickets) m[p.first][p.second]++;
    vector<string> res, curr;
    curr.push_back("JFK");
    recurse(m, curr.front(), tickets.size(), curr, res);
    return res;
  }
};

class Solution2 {
 public:
  /*
  Eulerian path using Hierholzer's algorithm
  Starting from a vertex, do a dfs. put the vertex in the stack and then loop
  back outward.
  */
  void recurse(unordered_map<string, multiset<string>>& m, string from,
               vector<string>& stk) {
    while (!m[from].empty()) {
      const string& to = *(m[from].begin());
      m[from].erase(m[from].begin());
      recurse(m, to, stk);
    }

    stk.push_back(from);
  }

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    unordered_map<string, multiset<string>> m;
    for (auto p : tickets) m[p.first].insert(p.second);
    vector<string> stk;
    recurse(m, "JFK", stk);
    reverse(stk.begin(), stk.end());
    return stk;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of
length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else
return false.
Your algorithm should run in O(n) time complexity and O(1) space
complexity.

Examples:
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
/*
    Submission Date: 2017-08-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      we have a vector of size 3 where smallest[i] indicates
      the smallest last element of a sequence of size i

      similar to LIS

      for example if smallest is {1, _, _} and a 2 is found
      it becomes {1, 2, _} but if a 0 is found it becomes
      {0, 2, _}. Notice how it stops replacing as soon as finds
      a smallest[i] <= num. this is to prevent replacing multiple
      values.
  */
  bool increasingTriplet(vector<int>& nums) {
    vector<int> smallest(3, 0);
    int size = 0;

    for (auto num : nums) {
      bool found_replace = false;
      for (int i = 0; i < size; i++) {
        if (num <= smallest[i]) {
          smallest[i] = num;
          found_replace = true;
          break;
        }
      }

      if (found_replace) continue;

      if (size == 0 || smallest[size - 1] < num) {
        smallest[size++] = num;
      }

      if (size == 3) return true;
    }

    return false;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
336. Palindrome Pairs
Given a list of unique words, find all pairs of distinct indices (i, j) in the
given list, so that the concatenation of the two words, i.e. words[i] + words[j]
is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
/*
    Submission Date: 2018-05-28
    Runtime: 525 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  vector<int> palindrome_suffix;
  int index = -1;
  vector<Node*> child = vector<Node*>(26, NULL);
};

class Solution {
 public:
  /*
      is_pal O(n)
      insert O(k^2)
      traverse O(k^2)

      For each word[i] in words, place the word in a trie. if the node is the
     end of the word, set node->index = i for each j from [0, words[i].size()),
     check if a suffix of [j, words[i].size()) is a palindrome. if it is then
     store i as palindrome_suffix for that node.

      For each word[i] in words, reverse it and traverse the trie. If the
     current node is end of a word then check if a suffix of rev(words[i]) is a
     palindrome.

      'bat' 'abatab'
      reverse 'abatab', 'bataba' we find 'bat' then check if suffix 'aba' is a
     palindrome to see 'bat' + 'abatab'

      if rev(words[i]) has a letter not in trie then return
      once rev(words[i]) has completely been traversed it means either the
     current node is end of word

      'bat' 'tab'
      reverse 'tab', 'bat' we find 'bat' return 'bat' + 'tab'

      or there are palindrome suffix

      'bataba' 'tab'
      'batdd' 'tab'
      The palindrome suffix of 'aba' and 'dd' means there is 'bataba' + 'tab'
     and 'batdd' + 'tab'
  */
  unordered_map<string, bool> dp_;

  bool is_pal(const string& s) {
    if (dp_.count(s)) return dp_[s];
    int N = s.size();
    for (int i = 0; i < N / 2; i++) {
      if (s[i] != s[N - i - 1]) return dp_[s] = false;
    }

    return dp_[s] = true;
  }

  void insert(Node* root, const string& s, const int& index) {
    Node* curr = root;
    for (int i = 0; i < s.size(); i++) {
      if (is_pal(s.substr(i))) curr->palindrome_suffix.push_back(index);
      if (curr->child[s[i] - 'a'] == NULL) curr->child[s[i] - 'a'] = new Node();
      curr = curr->child[s[i] - 'a'];
    }
    curr->index = index;
  }

  void traverse(Node* root, const string& s, const int& index,
                vector<vector<int>>& res) {
    Node* curr = root;
    for (int i = 0; i < s.size(); i++) {
      if (curr->index != -1 && is_pal(s.substr(i))) {
        res.push_back({curr->index, index});
      }
      if (curr->child[s[i] - 'a'] == NULL) {
        return;
      }
      curr = curr->child[s[i] - 'a'];
    }

    if (curr->index != -1 && index != curr->index)
      res.push_back({index, curr->index});

    for (const auto& e : curr->palindrome_suffix) {
      if (index == e) continue;
      res.push_back({e, index});
    }
  }

  vector<vector<int>> palindromePairs(vector<string>& words) {
    Node* root = new Node();

    for (int i = 0; i < words.size(); i++) {
      insert(root, words[i], i);
    }

    vector<vector<int>> res;
    for (int i = 0; i < words.size(); i++) {
      string s = words[i];
      reverse(s.begin(), s.end());
      traverse(root, s, i, res);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
337. House Robber III
The thief has found himself a new place for his thievery again. There is only
one entrance to this area, called the "root." Besides the root, each house has
one and only one parent house. After a tour, the smart thief realized that "all
houses in this place forms a binary tree". It will automatically contact the
police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting
the police.

Example 1:
     3
    / \
   2   3
    \   \
     3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
     3
    / \
   4   5
  / \   \
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.
/*
    Submission Date: 2018-05-30
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

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
      if we use the node, then the maximium value is node's val +
     rob(root->left's children) + rob(root->right's children) if we dont use the
     node, then maximum value is rob(root->left) + rob(root->right) Take the max
     of use node and not using node
  */
  unordered_map<TreeNode*, int> dp_;
  int rob(TreeNode* root) {
    if (root == NULL) return 0;
    if (dp_.count(root)) return dp_[root];

    int use_node = root->val;
    int not_use_node = 0;

    if (root->left) {
      use_node += rob(root->left->left) + rob(root->left->right);
      not_use_node += rob(root->left);
    }

    if (root->right) {
      use_node += rob(root->right->left) + rob(root->right->right);
      not_use_node += rob(root->right);
    }

    return dp_[root] = max(use_node, not_use_node);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
338. Counting Bits
Given a non negative integer number num. For every numbers i in the range 0 ≤ i
≤ num calculate the number of 1's in their binary representation and return them
as an array.

Example:
For num = 5 you should return [0,1,1,2,1,2].

Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)).
But can you do it in linear time O(n) /possibly in a single pass? Space
complexity should be O(n). Can you do it like a boss? Do it without using any
builtin function like
__builtin_popcount in c++ or in any other language.
/*
    Submission Date: 2017-03-11
    Runtime: 69 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> countBits(int num) {
    vector<int> res(num + 1, 0);

    for (int i = 1; i <= num; i++) {
      res[i] = res[i / 2] + (i % 2);
    }

    return res;
  }
};

int main() { return 0; }