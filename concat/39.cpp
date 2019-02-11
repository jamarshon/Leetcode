
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
905. Sort Array By Parity
Given an array A of non-negative integers, return an array consisting of all the
even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 


Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.


 

Note:


  1 <= A.length <= 5000
  0 <= A[i] <= 5000
/*
  Submission Date: 2019-01-25
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortArrayByParity(vector<int>& A) {
    int even = 0;
    int odd = A.size() - 1;

    while (even < odd) {
      if (A[even] % 2 == 0) {
        even++;
      } else {
        swap(A[even], A[odd]);
        odd--;
      }
    }

    return A;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
908. Smallest Range I
Given an array A of integers, for each integer A[i] we may choose any x with -K
<= x <= K, and add x to A[i].

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the
minimum value of B.

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]

Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]

Example 3:

Input: A = [1,3,6], K = 3
Output: 0
Explanation: B = [3,3,3] or B = [4,4,4]

Note:

  1 <= A.length <= 10000
  0 <= A[i] <= 10000
  0 <= K <= 10000
/*
  Submission Date: 2019-01-26
  Runtime: 12 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int smallestRangeI(vector<int>& A, int K) {
    if (A.empty()) return 0;
    return max(0, *max_element(A.begin(), A.end()) -
                      *min_element(A.begin(), A.end()) - 2 * K);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
914. X of a Kind in a Deck of Cards
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to
split the entire deck into 1 or more groups of cards, where:

  Each group has exactly X cards.
  All the cards in each group have the same integer.

Example 1:

Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

Example 2:

Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Example 3:

Input: [1]
Output: false
Explanation: No possible partition.

Example 4:

Input: [1,1]
Output: true
Explanation: Possible partition [1,1]

Example 5:

Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:

  1 <= deck.length <= 10000
  0 <= deck[i] < 10000
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }
  /*
  gcd(a,b,c) = gcd(gcd(a,b), c)
  hence, if the gcd(freq[0], ... freq[n-1]) is the
  largest number which divides into all of them which
  is X (just check X >= 2)
  */
  bool hasGroupsSizeX(vector<int>& deck) {
    unordered_map<int, int> freq;
    for (auto& e : deck) {
      freq[e]++;
    }

    int res = 0;
    for (auto& kv : freq) res = gcd(res, kv.second);
    return res > 1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
917. Reverse Only Letters
Given a string S, return the "reversed" string where all characters that are not
a letter stay in the same place, and all letters reverse their positions.

Example 1:

Input: "ab-cd"
Output: "dc-ba"

Example 2:

Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"

Example 3:

Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"

Note:

  S.length <= 100
  33 <= S[i].ASCIIcode <= 122 
  S doesn't contain \ or "
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  string reverseOnlyLetters(string S) {
    int last_ind = S.size() - 1;
    for (int i = 0; i < last_ind; i++) {
      if (!isalpha(S[i])) continue;
      while (last_ind > i && !isalpha(S[last_ind])) last_ind--;
      swap(S[i], S[last_ind]);
      last_ind--;
    }
    return S;
  }
};

int main() { return 0; }

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
