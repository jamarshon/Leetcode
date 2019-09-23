
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
919. Complete Binary Tree Inserter
A complete binary tree is a binary tree in which every level, except possibly
the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary
tree and supports the following operations:

  CBTInserter(TreeNode root) initializes the data structure on a given tree with
head node root;
  CBTInserter.insert(int v) will insert a TreeNode into the tree with value
node.val = v so that the tree remains complete, and returns the value of the
parent of the inserted TreeNode;
  CBTInserter.get_root() will return the head node of the tree.

Example 1:

Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]

Example 2:

Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs =
[[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]

Note:

  The initial given tree is complete and contains between 1 and 1000 nodes.
  CBTInserter.insert is called at most 10000 times per test case.
  Every value of a given or inserted node is between 0 and 5000.
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: MEDIUM
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

class CBTInserter {
  vector<TreeNode*> nodes;

 public:
  CBTInserter(TreeNode* root) {
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
      TreeNode* front = q.front();
      q.pop();
      if (front->left) q.push(front->left);
      if (front->right) q.push(front->right);
      nodes.push_back(front);
    }
  }

  int insert(int v) {
    nodes.emplace_back(new TreeNode(v));
    int parent_ind = (nodes.size() - 2) / 2;
    if (nodes[parent_ind]->left == NULL)
      nodes[parent_ind]->left = nodes.back();
    else
      nodes[parent_ind]->right = nodes.back();
    return nodes[parent_ind]->val;
  }

  TreeNode* get_root() { return nodes[0]; }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter obj = new CBTInserter(root);
 * int param_1 = obj.insert(v);
 * TreeNode* param_2 = obj.get_root();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
921. Minimum Add to Make Parentheses Valid
Given a string S of '(' and ')' parentheses, we add the minimum number of
parentheses ( '(' or ')', and in any positions ) so that the resulting
parentheses string is valid.

Formally, a parentheses string is valid if and only if:

  It is the empty string, or
  It can be written as AB (A concatenated with B), where A and B are valid
strings, or
  It can be written as (A), where A is a valid string.

Given a parentheses string, return the minimum number of parentheses we must add
to make the resulting string valid.

Example 1:

Input: "())"
Output: 1

Example 2:

Input: "((("
Output: 3

Example 3:

Input: "()"
Output: 0

Example 4:

Input: "()))(("
Output: 4

Note:

  S.length <= 1000
  S only consists of '(' and ')' characters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int minAddToMakeValid(string s) {
    int open = 0;
    int res = 0;
    for (auto& c : s) {
      if (c == '(') {
        open++;
      } else {
        if (open > 0) {
          open--;
        } else {
          res++;
        }
      }
    }
    return res + open;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
922. Sort Array By Parity II
Given an array A of non-negative integers, half of the integers in A are odd,
and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is
even, i is even.

You may return any answer array that satisfies this condition.

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

Note:

  2 <= A.length <= 20000
  A.length % 2 == 0
  0 <= A[i] <= 1000
/*
  Submission Date: 2019-01-26
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortArrayByParityII(vector<int>& A) {
    int even_ind = 0;
    int odd_ind = 1;
    while (even_ind < A.size() && odd_ind < A.size()) {
      while (even_ind < A.size() && A[even_ind] % 2 == 0) {
        even_ind += 2;
      }

      while (odd_ind < A.size() && A[odd_ind] % 2 == 1) {
        odd_ind += 2;
      }

      int cnt = (even_ind < A.size()) + (odd_ind < A.size());

      if (cnt == 0) break;
      assert(cnt != 1);
      swap(A[even_ind], A[odd_ind]);
      even_ind += 2;
      odd_ind += 2;
    }

    return A;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
924. Minimize Malware Spread
In a network of nodes, each node i is directly connected to another node j if
and only if graph[i][j] = 1.

Some nodes initial are initially infected by malware.  Whenever two nodes are
directly connected and at least one of those two nodes is infected by malware,
both nodes will be infected by malware.  This spread of malware will continue
until no more nodes can be infected in this manner.

Suppose M(initial) is the final number of nodes infected with malware in the
entire network, after the spread of malware stops.

We will remove one node from the initial list.  Return the node that if removed,
would minimize M(initial).  If multiple nodes could be removed to minimize
M(initial), return such a node with the smallest index.

Note that if a node was removed from the initial list of infected nodes, it may
still be infected later as a result of the malware spread.

Example 1:

Input: graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
Output: 0

Example 2:

Input: graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
Output: 0

Example 3:

Input: graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
Output: 1

Note:

  1 < graph.length = graph[0].length <= 300
  0 <= graph[i][j] == graph[j][i] <= 1
  graph[i][i] = 1
  1 <= initial.length < graph.length
  0 <= initial[i] < graph.length
/*
  Submission Date: 2019-02-04
  Runtime: 168 ms
  Difficulty: HARD
*/
#include <cassert>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T>
class UnionFind {
  unordered_map<T, int> rank_, size_;
  unordered_map<T, T> parent_;

 public:
  bool IsWithinSet(T e) { return parent_.count(e); }

  void CreateSet(T e) {
    assert(!IsWithinSet(e));
    parent_[e] = e;
    rank_[e] = 0;
    size_[e] = 1;
  }

  T Find(T e) {
    if (parent_[e] != e) {
      parent_[e] = Find(parent_[e]);
    }
    return parent_[e];
  }
  int GetSize(T e) { return size_[Find(e)]; }

  bool Union(T e1, T e2) {
    T e1_root = Find(e1);
    T e2_root = Find(e2);

    if (e1_root == e2_root) return false;  // same root

    if (rank_[e1_root] < rank_[e2_root]) {
      parent_[e1_root] = e2_root;
      size_[e2_root] += size_[e1_root];
    } else {
      parent_[e2_root] = e1_root;
      size_[e1_root] += size_[e2_root];
      if (rank_[e1_root] == rank_[e2_root]) {
        rank_[e1_root]++;
      }
    }

    return true;
  }
};

class Solution {
 public:
  int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int N = graph.size();
    UnionFind<int> uf;
    for (int i = 0; i < N; i++) uf.CreateSet(i);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (graph[i][j]) uf.Union(i, j);
      }
    }

    unordered_map<int, vector<int>> parent_to_children;
    int min_m = INT_MAX;
    for (const auto& m : initial) {
      parent_to_children[uf.Find(m)].push_back(m);
      min_m = min(min_m, m);
    }

    int largest_machine = -1;
    for (const auto& kv : parent_to_children) {
      // for connected components that with more than one initial machine, they
      // should be discarded
      if (kv.second.size() != 1) continue;
      int m = kv.second.front();
      if (largest_machine == -1) {
        largest_machine = m;
        continue;
      }

      // this component only has one machine, so removing it would result in
      // uf.GetSize(m) number of machines saved.
      int max_size = uf.GetSize(largest_machine);
      int curr_size = uf.GetSize(m);
      if (curr_size == max_size) {
        largest_machine = min(largest_machine, m);
      } else if (curr_size > max_size) {
        largest_machine = m;
      }
    }

    return (largest_machine == -1) ? min_m : largest_machine;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
925. Long Pressed Name
Your friend is typing his name into a keyboard.  Sometimes, when typing a
character c, the key might get long pressed, and the character will be typed 1
or more times.

You examine the typed characters of the keyboard.  Return True if it is possible
that it was your friends name, with some characters (possibly none) being long
pressed.

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.

Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed
output.

Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true

Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.

Note:

  name.length <= 1000
  typed.length <= 1000
  The characters of name and typed are lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isLongPressedName(string name, string typed) {
    int n = name.size();
    int m = typed.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
      if (name[i] != typed[j]) return false;
      int new_i = i;
      int new_j = j;
      while (new_i < n && name[i] == name[new_i]) new_i++;
      while (new_j < m && typed[j] == typed[new_j]) new_j++;

      int name_cnt = new_i - i + 1;
      int typed_cnt = new_j - j + 1;

      if (typed_cnt < name_cnt) return false;
      i = new_i;
      j = new_j;
    }

    return i == n && j == m;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
926. Flip String to Monotone Increasing
A string of '0's and '1's is monotone increasing if it consists of some number
of '0's (possibly 0), followed by some number of '1's (also possibly 0.)

We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a
'1' to a '0'.

Return the minimum number of flips to make S monotone increasing.

Example 1:

Input: "00110"
Output: 1
Explanation: We flip the last digit to get 00111.

Example 2:

Input: "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.

Example 3:

Input: "00011000"
Output: 2
Explanation: We flip to get 00000000.

Note:

  1 <= S.length <= 20000
  S only consists of '0' and '1' characters.
/*
  Submission Date: 2019-02-21
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  for index i if we have number of ones from [0, i) ones_left
  and number of ones from [i,N) ones_right then the cost
  of partitioning at i would be number of ones on left +
  number of zeros on right
  */
  int minFlipsMonoIncr(string S) {
    int N = S.size();
    int ones_right = 0;
    for (const auto& c : S) ones_right += c == '1';

    int res = min(ones_right, N - ones_right);
    int ones_left = 0;
    for (int i = 0; i < N; i++) {
      res = min(res, ones_left + N - i - ones_right);
      if (S[i] == '1') {
        ones_left++;
        ones_right--;
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
929. Unique Email Addresses
Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is
the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an
email address, mail sent there will be forwarded to the same address without
dots in the local name.  For example, "alice.z@leetcode.com" and
"alicez@leetcode.com" forward to the same email address.  (Note that this rule
does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign
will be ignored. This allows certain emails to be filtered, for
example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule
does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many
different addresses actually receive mails? 

Example 1:

Input:
["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually
receive mails

Note:

  1 <= emails[i].length <= 100
  1 <= emails.length <= 100
  Each emails[i] contains exactly one '@' character.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> uniq_emails;

    for (const auto& email : emails) {
      size_t at_ind = email.find('@');
      if (at_ind == string::npos) return -1;
      string res = "";
      for (int i = 0; i < at_ind; i++) {
        if (email[i] == '.') continue;
        if (email[i] == '+') break;
        res.push_back(email[i]);
      }

      for (int i = at_ind + 1; i < email.size(); i++) {
        res.push_back(email[i]);
      }

      uniq_emails.insert(res);
    }

    return uniq_emails.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
931. Minimum Falling Path Sum
Given a square array of integers A, we want the minimum sum of a falling path
through A.

A falling path starts at any element in the first row, and chooses one element
from each row.  The next row's choice must be in a column that is different from
the previous row's column by at most one.

Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: 12
Explanation:
The possible falling paths are:

  [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
  [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
  [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]

The falling path with the smallest sum is [1,4,7], so the answer is 12.

Note:

  1 <= A.length == A[0].length <= 100
  -100 <= A[i][j] <= 100
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();

    for (int i = n - 2; i >= 0; i--) {  // skip last row
      for (int j = 0; j < m; j++) {
        int to_add = INT_MAX;
        for (int k = -1; k <= 1; k++) {
          if (j + k >= 0 && j + k < m) {
            to_add = min(to_add, A[i + 1][j + k]);
          }
        }

        A[i][j] += to_add;
      }
    }
    return *min_element(A[0].begin(), A[0].end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
932. Beautiful Array
For some fixed N, an array A is beautiful if it is a permutation of the integers
1, 2, ..., N, such that:

For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].

Given N, return any beautiful array A.  (It is guaranteed that one exists.)

Example 1:

Input: 4
Output: [2,1,4,3]

Example 2:

Input: 5
Output: [3,1,2,5,4]

Note:

  1 <= N <= 1000
/*
  Submission Date: 2019-02-19
  Runtime: 12 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  generate all the odd numbers followed by the even
  this partition helps because if even_a + even_b = x and odd_a + odd_b = y
  then if x is 2*odd number or y is 2*even number, it will never violate
  the beautiful condition due to the partition

  even_a + odd_a is always odd so concatenate an array of odd numbers and
  even numbers is still beautiful

  given a beautiful array A of size N, the operations are supported
  1) remove element
  -removing element will never violate condition as it relaxes the criteria
  2) multiplication
  since beautiful A[k]*2 != A[i] + A[j], if all elements multiplied by x
  # (A[k]*x)*2
  ## (A[i]*x) + (A[j]*x)
  divide # and ## by x and get A[k]*2 and A[i] + A[j] which are not equal so
  still beautiful

  3) addition
  add x to each element
  # (A[k]+x)*2 = A[k]*2 + 2x
  ## (A[i]+x) + (A[j]+x) = A[i] + A[j] + 2x
  subtract 2x from # and ## and get A[k]*2 and A[i] + A[j] which are not equal
  so still beautiful

  so start with the base case of A = {1} for size 1 and build it recursively
  to size N by multiply, add and remove elements that are too large

  odd = A[i]*2-1 for all i (generates all odd from 1 to 2*N-1)
  even = A[i]*2 for all i (generates all even from 0 to 2*N)
  new_A = concat odd and even (size of 2*N)
  */
  vector<int> beautifulArray(int N) {
    vector<int> res{1};
    res.reserve(N);
    while (res.size() < N) {
      vector<int> tmp;
      for (const auto& i : res)
        if (2 * i - 1 <= N) tmp.push_back(2 * i - 1);
      for (const auto& i : res)
        if (2 * i <= N) tmp.push_back(2 * i);
      res = tmp;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
933. Number of Recent Calls
Write a class RecentCounter to count recent requests.

It has only one method: ping(int t), where t represents some time in
milliseconds.

Return the number of pings that have been made from 3000 milliseconds ago until
now.

Any ping with time in [t - 3000, t] will count, including the current ping.

It is guaranteed that every call to ping uses a strictly larger value of t than
before.

Example 1:

Input: inputs = ["RecentCounter","ping","ping","ping","ping"], inputs =
[[],[1],[100],[3001],[3002]]
Output: [null,1,2,3,3]

Note:

  Each test case will have at most 10000 calls to ping.
  Each test case will call ping with strictly increasing values of t.
  Each call to ping will have 1 <= t <= 10^9.
/*
  Submission Date: 2019-01-26
  Runtime: 252 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;
class RecentCounter {
  MinHeap heap;

 public:
  RecentCounter() {}

  int ping(int t) {
    while (!heap.empty() && heap.top() < t - 3000) {
      heap.pop();
    }
    heap.push(t);
    return heap.size();
  }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
937. Reorder Log Files
You have an array of logs.  Each log is a space delimited string of words.

For each log, the first word in each log is an alphanumeric identifier.  Then,
either:

  Each word after the identifier will consist only of lowercase letters, or;
  Each word after the identifier will consist only of digits.

We will call these two varieties of logs letter-logs and digit-logs.  It is
guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.  The
letter-logs are ordered lexicographically ignoring identifier, with the
identifier used in case of ties.  The digit-logs should be put in their original
order.

Return the final order of the logs.

Example 1:

Input: ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]

Note:

  0 <= logs.length <= 100
  3 <= logs[i].length <= 100
  logs[i] is guaranteed to have an identifier, and a word after the identifier.
/*
  Submission Date: 2019-02-05
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    // move digit logs to the back
    int i = logs.size() - 1;
    for (int j = logs.size() - 1; j >= 0; j--) {
      size_t first_space_ind = logs[j].find(' ');
      if (isdigit(logs[j][first_space_ind + 1])) {
        swap(logs[i--], logs[j]);
      }
    }

    // sort the letter logs
    sort(logs.begin(), logs.begin() + i + 1,
         [](const string& lhs, const string& rhs) {
           size_t lhs_ind = lhs.find(' ');
           size_t rhs_ind = rhs.find(' ');
           string lhs_sub = lhs.substr(lhs_ind + 1);
           string rhs_sub = rhs.substr(rhs_ind + 1);
           if (lhs_sub == rhs_sub)
             return lhs.substr(0, lhs_ind) < rhs.substr(0, rhs_ind);
           return lhs_sub < rhs_sub;
         });
    return logs;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
938. Range Sum of BST
Given the root node of a binary search tree, return the sum of values of all
nodes with value between L and R (inclusive).

The binary search tree is guaranteed to have unique values.

Example 1:

Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32

Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23

Note:

  The number of nodes in the tree is at most 10000.
  The final answer is guaranteed to be less than 2^31.
/*
  Submission Date: 2019-02-06
  Runtime: 156 ms
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
  int rangeSumBST(TreeNode *root, int L, int R) {
    if (root == nullptr) return 0;
    int sum = 0;
    if (L <= root->val && root->val <= R) sum += root->val;
    // tree has unique values. if root->val < L, then don't need to search left
    // tree and root->val > R, then don't need to search right tree.
    if (L < root->val) sum += rangeSumBST(root->left, L, R);
    if (root->val < R) sum += rangeSumBST(root->right, L, R);
    return sum;
  }
};

int main() { return 0; }
