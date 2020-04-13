
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
888. Fair Candy Swap
Alice and Bob have candy bars of different sizes: A[i] is the size of the i-th
bar of candy that Alice has, and B[j] is the size of the j-th bar of candy that
Bob has.

Since they are friends, they would like to exchange one candy bar each so that
after the exchange, they both have the same total amount of candy.  (The total
amount of candy a person has is the sum of the sizes of candy bars they have.)

Return an integer array ans where ans[0] is the size of the candy bar that Alice
must exchange, and ans[1] is the size of the candy bar that Bob must exchange.

If there are multiple answers, you may return any one of them.  It is guaranteed
an answer exists.

Example 1:

Input: A = [1,1], B = [2,2]
Output: [1,2]

Example 2:

Input: A = [1,2], B = [2,3]
Output: [1,2]

Example 3:

Input: A = [2], B = [1,3]
Output: [2,3]

Example 4:

Input: A = [1,2,5], B = [2,4]
Output: [5,4]

Note:

  1 <= A.length <= 10000
  1 <= B.length <= 10000
  1 <= A[i] <= 100000
  1 <= B[i] <= 100000
  It is guaranteed that Alice and Bob have different total amounts of candy.
  It is guaranteed there exists an answer.
/*
  Submission Date: 2019-01-26
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  /*sum_A + (B[j] - A[i]) == sum_B == (A[i] - B[j])
  sum_A = sum_B + 2*A[i] - 2*B[j]
  */
  vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
    int sum_A = 0;
    int sum_B = 0;
    for (auto& e : A) sum_A += e;
    for (auto& e : B) sum_B += e;

    unordered_set<int> B_set(B.begin(), B.end());
    for (auto& e : A) {
      int B_j = (sum_A - sum_B - 2 * e) / -2;
      if (B_set.count(B_j)) return {e, B_j};
    }

    return {};
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
889. Construct Binary Tree from Preorder and Postorder Traversal
Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Note:

  1 <= pre.length == post.length <= 30
  pre[] and post[] are both permutations of 1, 2, ..., pre.length.
  It is guaranteed an answer exists. If there exists multiple answers, you can
return any of them.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
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
  /* traverse pre and create nodes from there. the stk represents
  the current path of the tree (ie. from root to node). when the
  stk last value is equal to post[j], it means the tree is done
  so pop stk and increment j until it is no longer so. add the
  pre[i] is either the left or right of the stack depending on
  which is available.
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    vector<TreeNode*> stk;
    stk.emplace_back(new TreeNode(pre[0]));
    for (int i = 1, j = 0; i < pre.size(); i++) {
      while (stk.back()->val == post[j]) {
        j++;
        stk.pop_back();
      }

      TreeNode* curr = new TreeNode(pre[i]);
      if (stk.back()->left == NULL)
        stk.back()->left = curr;
      else
        stk.back()->right = curr;
      stk.emplace_back(curr);
    }

    return stk.front();
  }
};

class Solution2 {
 public:
  TreeNode* f(vector<int>& pre, int a, int b, vector<int>& post, int c, int d,
              unordered_map<int, int>& val_to_post_ind) {
    if (a > b || c > d) return NULL;
    assert(b - a == d - c);

    TreeNode* root = new TreeNode(pre[a]);

    int furthest = -1;
    for (int i = a + 1; i <= b; i++) {
      int ind = val_to_post_ind[pre[i]];
      furthest = max(furthest, ind);
      if (furthest - c == i - (a + 1)) {
        root->left = f(pre, a + 1, i, post, c, furthest, val_to_post_ind);
        root->right =
            f(pre, i + 1, b, post, furthest + 1, d - 1, val_to_post_ind);
        break;
      }
    }

    return root;
  }

  /*
  we traverse from pre i = 1 to N looking for where pre[i] is in post, say it is
  at j. it means every element from 0 to j must be in the tree so keep going
  until the furthest j contains as many elements as i-1. These range must be the
  left sub tree so partition both the pre and post from [1,i] [i+1, N] and [0,
  furthest_j] [furthest_j + 1, N-1]
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    unordered_map<int, int> val_to_post_ind;
    for (int i = 0; i < post.size(); i++) val_to_post_ind[post[i]] = i;
    return f(pre, 0, pre.size() - 1, post, 0, pre.size() - 1, val_to_post_ind);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
890. Find and Replace Pattern
You have a list of words and a pattern, and you want to know which words in
words matches the pattern.

A word matches the pattern if there exists a permutation of letters p so that
after replacing every letter x in the pattern with p(x), we get the desired
word.

(Recall that a permutation of letters is a bijection from letters to letters:
every letter maps to another letter, and no two letters map to the same letter.)

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 


Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b
-> e, ...}.
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a
permutation,
since a and b map to the same letter.

 

Note:


  1 <= words.length <= 50
  1 <= pattern.length = words[i].length <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> res;
    for (const auto& w : words) {
      if (w.size() != pattern.size()) continue;
      unordered_map<char, char> p;

      unordered_set<char> used;
      bool can_insert = true;
      for (int i = 0; i < w.size(); i++) {
        if (p.count(w[i])) {
          if (p[w[i]] != pattern[i]) {
            can_insert = false;
            break;
          }
        } else {
          if (used.count(pattern[i])) {
            can_insert = false;
            break;
          } else {
            p[w[i]] = pattern[i];
            used.insert(pattern[i]);
          }
        }
      }

      if (can_insert) res.push_back(w);
    }

    return res;
  }
};

int main() { return 0; }

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
904. Fruit Into Baskets
In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following
steps:

  Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
  Move to the next tree to the right of the current tree.  If there is no tree
to the right, stop.

Note that you do not have any choice after the initial choice of starting
tree: you must perform step 1, then step 2, then back to step 1, then step 2,
and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you
want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

Example 1:

Input: [1,2,1]
Output: 3
Explanation: We can collect [1,2,1].

Example 2:

Input: [0,1,2,2]
Output: 3
Explanation: We can collect [1,2,2].
If we started at the first tree, we would only collect [0, 1].

Example 3:

Input: [1,2,3,2,2]
Output: 4
Explanation: We can collect [2,3,2,2].
If we started at the first tree, we would only collect [1, 2].

Example 4:

Input: [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can collect [1,2,1,1,2].
If we started at the first tree or the eighth tree, we would only collect 4
fruits.

Note:

  1 <= tree.length <= 40000
  0 <= tree[i] < tree.length
/*
  Submission Date: 2019-09-24
  Runtime: 192 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int totalFruit(vector<int>& tree) {
    unordered_map<int, int> seen;
    int sum = 0;
    int res = 0;
    int front = 0;
    for (int i = 0, N = tree.size(); i < N; i++) {
      seen[tree[i]]++;
      sum++;
      while (seen.size() > 2) {
        int to_remove = tree[front++];
        seen[to_remove]--;
        if (seen[to_remove] == 0) {
          seen.erase(to_remove);
        }
        sum--;
      }
      res = max(res, sum);
    }
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
912. Sort an Array
Given an array of integers nums, sort the array in ascending order.

Example 1:

Input: [5,2,3,1]
Output: [1,2,3,5]

Example 2:

Input: [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]

Note:

  1 <= A.length <= 10000
  -50000 <= A[i] <= 50000
/*
  Submission Date: 2019-09-23
  Runtime: 84 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void sort(vector<int>& nums, int l, int r) {
    if (l < r) {
      int mid = l + (r - l) / 2;
      int pivot = nums[mid];
      swap(nums[mid], nums[l]);
      int j = l + 1;
      for (int i = l + 1; i <= r; i++) {
        if (nums[i] < pivot) {
          swap(nums[i], nums[j]);
          j++;
        }
      }
      swap(nums[j - 1], nums[l]);
      sort(nums, l, j - 2);
      sort(nums, j, r);
    }
  }
  vector<int> sortArray(vector<int>& nums) {
    // quick sort
    sort(nums, 0, nums.size() - 1);
    return nums;
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
