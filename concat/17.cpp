
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
303. Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and
j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
/*
    Submission Date: 2017-03-11
    Runtime: 162 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
  vector<int> dp_;

 public:
  NumArray(vector<int> nums) {
    if (nums.empty()) return;

    int N = nums.size();
    dp_.resize(N);

    dp_[0] = nums[0];
    for (int i = 1; i < N; i++) {
      dp_[i] = dp_[i - 1] + nums[i];
    }
  }

  int sumRange(int i, int j) { return dp_[j] - (i - 1 >= 0 ? dp_[i - 1] : 0); }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
304. Range Sum Query 2D - Immutable
Given a 2D matrix matrix, find the sum of the elements inside the rectangle
defined by its upper left corner (row1, col1) and lower right corner (row2,
col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1)
and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
  int rows_, cols_;
  vector<vector<int>> dp_;

 public:
  NumMatrix(vector<vector<int>> matrix) {
    rows_ = matrix.size();
    cols_ = matrix.empty() ? 0 : matrix[0].size();

    dp_.assign(rows_, vector<int>(cols_));
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        dp_[i][j] = matrix[i][j];
        if (i > 0) dp_[i][j] += dp_[i - 1][j];
        if (i > 0 && j > 0) dp_[i][j] -= dp_[i - 1][j - 1];
        if (j > 0) dp_[i][j] += dp_[i][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int res = dp_[row2][col2];
    if (row1 > 0) res -= dp_[row1 - 1][col2];
    if (col1 > 0) res -= dp_[row2][col1 - 1];
    if (row1 > 0 && col1 > 0) res += dp_[row1 - 1][col1 - 1];
    return res;
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
306. Additive Number
Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers.
Except for the first two numbers, each subsequent number in the
sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an
additive sequence: 1, 1, 2, 3, 5, 8.

1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
"199100199" is also an additive number, the additive sequence is:
1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199
Note: Numbers in the additive sequence cannot have leading zeros,
so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9', write a function
to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?
/*
    Submission Date: 2017-08-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isAdditiveNumber(string num) {
    int N = num.size();

    long long o1 = 0;
    long long o2 = 0;

    // given a string, we extract o1 and o2 from it leaving (o3)xxxx and calling
    // the recursive function
    for (int i = 0; i < N; i++) {
      o1 = o1 * 10 + (num[i] - '0');
      o2 = 0;
      for (int j = i + 1; j < N; j++) {
        o2 = o2 * 10 + (num[j] - '0');
        if (isAdditiveNumber(num.substr(j + 1), o2, o1 + o2)) {
          return true;
        }
        if (o2 == 0) break;  // o2 begins with 0
      }

      if (o1 == 0) break;  // o1 begins with 0
    }

    return false;
  }

  // num should be (o3)xxxx if it is o3 then return true
  // else if it is (o3)xxxx then call the function on xxxx looking for o2 + o3
  // at the front and o3 becomes o2 f(num, o2, o3) -> f(num.substr(i), o3, o2 +
  // o3) where i the first index of x
  bool isAdditiveNumber(string num, long long o2, long long o3) {
    int N = num.size();
    if (N == 0) return false;
    if (num.front() == '0') return N == 1 && o3 == 0;  // o3 begins with zero

    long long curr = 0;
    for (int i = 0; i < N; i++) {
      curr = curr * 10 + (num[i] - '0');
      if (curr > o3) return false;
      if (curr == o3) {
        return i == N - 1 || isAdditiveNumber(num.substr(i + 1), o3, o2 + o3);
      }
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
307. Range Sum Query - Mutable
Given an integer array nums, find the sum of the elements between indices i and
j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to
val. Example: Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is
distributed evenly.
/*
    Submission Date: 2017-03-11
    Runtime: 83 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
  vector<int> tree;
  int N;

  int lsb(int x) { return x & ~(x - 1); }

  // [1,i]
  int query(int i) {
    int sum = 0;
    while (i != 0) {
      sum += tree[i];
      i -= lsb(i);
    }
    return sum;
  }

 public:
  NumArray(vector<int> nums) {
    N = nums.size();
    tree.resize(N + 1);

    tree[0] = 0;
    for (int i = 1; i <= N; i++) tree[i] = nums[i - 1];

    for (int i = 1; i <= N; i++) {
      int parent = i + lsb(i);
      if (parent <= N) tree[parent] += tree[i];
    }
  }

  void update(int i, int val) {
    int delta = val - sumRange(i, i);
    i++;
    while (i <= N) {
      tree[i] += delta;
      i += lsb(i);
    }
  }

  int sumRange(int i, int j) { return query(j + 1) - query(i); }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
309. Best Time to Buy and Sell Stock with Cooldown
Say you have an array for which the ith element is the price of a given stock on
day i.

Design an algorithm to find the maximum profit. You may complete as many
transactions as you like (ie, buy one and sell one share of the stock multiple
times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell
the stock before you buy again). After you sell your stock, you cannot buy stock
on next day. (ie, cooldown 1 day) Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int N = prices.size();
    if (N < 2) return 0;

    vector<int> dp(N);
    dp[N - 1] = 0;
    dp[N - 2] = max(0, prices[N - 1] - prices[N - 2]);

    int max_sold = max(prices[N - 1], prices[N - 2]);
    for (int i = N - 3; i >= 0; i--) {
      // buy now prices[i] and sell on day j then get dp[j+2]
      // -prices[i] + prices[j] + dp[j+2];
      dp[i] = max(dp[i + 1], -prices[i] + max_sold);
      max_sold = max(max_sold, prices[i] + dp[i + 2]);
    }

    return dp[0];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
310. Minimum Height Trees
For a undirected graph with tree characteristics, we can choose any
node as the root. The result graph is then a rooted tree. Among all
possible rooted trees, those with minimum height are called minimum
height trees (MHTs). Given such a graph, write a function to find all
the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will
be given the number n and a list of undirected edges (each edge is a
pair of labels).

You can assume that no duplicate edges will appear in edges. Since
all edges are undirected, [0, 1] is the same as [1, 0] and thus
will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

Note:

(1) According to the definition of tree on Wikipedia: “a tree is
an undirected graph in which any two vertices are connected by
exactly one path. In other words, any connected graph without
simple cycles is a tree.”

(2) The height of a rooted tree is the number of edges on the
longest downward path between the root and a leaf.
/*
    Submission Date: 2017-08-21
    Runtime: 76 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
    if (n == 1) return {0};  // one node so the root of mht is itself

    vector<unordered_set<int>> graph(n);
    for (auto p : edges) {
      graph[p.first].insert(p.second);
      graph[p.second].insert(p.first);
    }

    vector<int> leaves;
    for (int i = 0; i < n; i++) {
      // this node is connected to only one other node (parent) so it is a leaf
      if (graph[i].size() == 1) {
        leaves.push_back(i);
      }
    }

    // reverse BFS the idea is to select nodes that are only connected to one
    // other node these nodes are leafs and are removed. Update the new leafs by
    // keeping track of the number of children of each node. If it goes to 1, it
    // means it is only connected to its parent and is now a leaf when there are
    // only 2 or less leafs then it means these are the roots

    while (n > 2) {        // tree has more than 2 nodes
      n -= leaves.size();  // remove the leafs

      vector<int> new_leaves;
      for (auto leaf : leaves) {
        int parent = *graph[leaf].begin();
        graph[parent].erase(leaf);  // from the parent remove the leaf
        if (graph[parent].size() ==
            1) {  // if the parent has no children, it is now a new leaf
          new_leaves.push_back(parent);
        }
      }
      leaves = new_leaves;
    }

    return leaves;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
312. Burst Balloons
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number
on it represented by array nums. You are asked to burst all the balloons. If the
you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here
left and right are adjacent indices of i. After the burst, the left and right
then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not
burst them. 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100 Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
/*
    Submission Date: 2018-06-24
    Runtime: 14 ms
    Difficulty: HARD
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution2 {
 public:
  unordered_map<string, int> dp;
  int help(vector<int>& nums, int l, int r) {
    string key = to_string(l) + "," + to_string(r);
    if (dp.count(key)) return dp[key];
    int res = 0;
    for (int i = l + 1; i <= r - 1; i++) {
      res = max(res, nums[l] * nums[i] * nums[r] + help(nums, l, i) +
                         help(nums, i, r));
    }
    return dp[key] = res;
  }
  int maxCoins(vector<int>& nums) {
    vector<int> x;
    x.reserve(nums.size() + 2);
    x.push_back(1);
    for (auto e : nums) x.push_back(e);
    x.push_back(1);
    return help(x, 0, x.size() - 1);
  }
};

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    vector<int> x;
    x.reserve(nums.size() + 2);
    x.push_back(1);
    for (auto e : nums) x.push_back(e);
    x.push_back(1);

    int N = x.size();
    /*
    O(n^3)
    r-l < 2  gives 0 as needs at least 3 elements
    if l and r are adjacent and i is popped, it means no number between y =
    [l,i] can be adjacent to z = [i,r]. if y is adjacent to z, then i must have
    been popped to get y adjacent to z. the result would be finding what it
    takes to make l adjacent to i (dp[l][i]) and to make i adjacent to r
    (dp[i][r]) + value from popping i (x[l]*x[i]*x[r]).
    */
    vector<vector<int>> dp(N, vector<int>(N, 0));
    for (int gap = 2; gap < N; gap++) {
      for (int l = 0; l + gap < N; l++) {
        int r = l + gap;

        for (int i = l + 1; i <= r - 1; i++) {
          dp[l][r] = max(dp[l][r], x[l] * x[i] * x[r] + dp[l][i] + dp[i][r]);
        }
      }
    }

    return dp[0][N - 1];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given
prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26,
28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7,
13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution2 {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    set<int> res{1};
    vector<int> last_prime(K, 1);

    while (res.size() < n) {
      int min_j = 0;
      for (int j = 1; j < K; j++) {
        if (last_prime[j] * primes[j] < last_prime[min_j] * primes[min_j]) {
          min_j = j;
        }
      }

      res.insert(last_prime[min_j] * primes[min_j]);
      last_prime[min_j] = *res.upper_bound(last_prime[min_j]);
    }

    return *res.rbegin();
  }
};

class Solution3 {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    // idx[j] corresponds to the first element in dp which
    // primes[j]*dp[idx[j]] >= dp[i]
    vector<int> dp(n), idx(K, 0);
    dp[0] = 1;

    for (int i = 1; i < n; i++) {
      int best_j = 0;
      for (int j = 0; j < K; j++) {
        // avoid duplicates e.g 4*3 and 6*2
        if (dp[idx[j]] * primes[j] == dp[i - 1]) idx[j]++;
        if (dp[idx[j]] * primes[j] < dp[idx[best_j]] * primes[best_j]) {
          best_j = j;
        }
      }
      dp[i] = dp[idx[best_j]] * primes[best_j];
      idx[best_j]++;
    }

    return dp[n - 1];
  }
};

class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    vector<int> dp(n);
    dp[0] = 1;
    // pair<prime, index in dp>
    auto func = [&dp](const pair<int, int> lhs, const pair<int, int> rhs) {
      return lhs.first * dp[lhs.second] > rhs.first * dp[rhs.second];
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(func)> pq(
        func);

    for (int i = 0; i < K; i++) pq.push({primes[i], 0});

    for (int i = 1; i < n; i++) {
      pair<int, int> p;
      do {
        p = pq.top();
        pq.pop();
        dp[i] = p.first * dp[p.second];
        pq.emplace(p.first, p.second + 1);
      } while (p.first * dp[p.second] == dp[i - 1]);
    }

    return dp[n - 1];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
315. Count of Smaller Numbers After Self
You are given an integer array nums and you have to return a
new counts array. The counts array has the property where
counts[i] is the number of smaller elements to the right of
nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
/*
    Submission Date: 2017-08-26
    Runtime: 36 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
 public:
  /*
      nlogn using tree
      given arr A, traverse A from N-1 to 0 inserting value into tree
      tree is bst (right greater than root, left smaller than root) but it has
     properties of number of left children and number of duplicates this tree
     represents everything to the right of the current element when inserting,
     every right turn indicates that the current element is greater than this
     node so the number of elements this element is greater than is number of
     duplicates from this node and numbers of left children of this node as left
     tree <= node < current element

      e.g. [3, 2, 2, 6, 1]
          1(0, 1)
           \
           6(3, 1)
           /
         2(0, 2)
             \
              3(0, 1)
      adding 5 would put it to the right of 3 so 1(0,1), 2(0,2) and 3(0,1) are
     where it turned right (0 + 1) (0 + 2) + (0 + 1) = 4
  */
  struct Node {
    Node *left, *right;
    int num_left, num_dup;
    int val;
    Node(int _val)
        : val(_val), num_left(0), num_dup(1), left(NULL), right(NULL) {}
  };

  Node* insert(Node* root, int val, int& sum) {
    if (root == NULL) {
      return new Node(val);
    } else if (root->val == val) {
      // duplicate increases and sum increases by number of left children
      root->num_dup += 1;
      sum += root->num_left;
    } else if (root->val > val) {
      // go left so number of left children increases
      root->num_left += 1;
      root->left = insert(root->left, val, sum);
    } else {
      // go right so sum increases by number of duplicates and number of left
      // children
      sum += (root->num_dup) + (root->num_left);
      root->right = insert(root->right, val, sum);
    }

    return root;
  }

  vector<int> countSmaller(vector<int>& nums) {
    int N = nums.size();
    vector<int> res(N);
    Node* root = NULL;
    for (int i = N - 1; i >= 0; i--) {
      int sum = 0;
      root = insert(root, nums[i], sum);
      res[i] = sum;
    }
    return res;
  }
};

class Solution {
  typedef pair<int, int> pii;

 public:
  void mergeSort(vector<pii>& v, vector<pii>& sp, vector<int>& res, int start,
                 int end) {
    /* for a subarray of v for indices [start, end], there
    is a left subarray [start, mid] and a right subarray
    [mid + 1, end]. If an item in the left subarray (left[i])
    is less than an item in the right subarray (right[j]),
    then left[i] is the next element in the sorted sequence and
    there are j elements that are smaller than left[i] that is
    to the right of left[i] so res[indexof(left[i])] += j

    use <= because [0,j) should not include numbers that equal
    to left[i]
    */
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(v, sp, res, start, mid);
    mergeSort(v, sp, res, mid + 1, end);

    int idx = 0;
    int s1 = start, s2 = mid + 1;
    int e1 = mid + 1, e2 = end + 1;
    while (s1 < e1 || s2 < e2) {
      // left goes before right as right is empty (s2 >= e2)
      // or start of left is less than or equal to start of right
      if (s2 >= e2 || (s1 < e1 && v[s1].first <= v[s2].first)) {
        sp[idx++] = v[s1];
        res[v[s1].second] += s2 - mid - 1;
        s1++;
      } else {
        sp[idx++] = v[s2];
        s2++;
      }
    }

    for (int i = 0; i < idx; i++) v[i + start] = sp[i];
  }

  vector<int> countSmaller(vector<int>& nums) {
    int N = nums.size();

    vector<pii> v, sp(N);

    for (int i = 0; i < N; i++) {
      v.emplace_back(nums[i], i);
    }

    vector<int> res(N, 0);

    mergeSort(v, sp, res, 0, N - 1);
    return res;
  }
};

int main() {
  Solution s;
  vector<int> v{5, 2, 6, 1};
  v = s.countSmaller(v);
  for (auto e : v) cout << e << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
318. Maximum Product of Word Lengths
Given a string array words, find the maximum value of
length(word[i]) * length(word[j]) where the two words do not
share common letters. You may assume that each word will contain
only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
/*
    Submission Date: 2017-08-26
    Runtime: 42 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(vector<string>& words) {
    int res = 0;
    int N = words.size();

    // dp[i] is the bit representation of words[i] where bit at index i
    // corresponds with the ith letter of [a,b,c,...] that is in words[i] e.g
    // abcf would 0...100111

    vector<int> dp(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0, word_len = words[i].size(); j < word_len; j++) {
        dp[i] |= 1 << (words[i][j] - 'a');
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if ((dp[i] & dp[j]) == 0) {  // no intersection
          res = max(res, int(words[i].size() * words[j].size()));
        }
      }
    }

    return res;
  }
};

class Solution2 {
 public:
  int maxProduct(vector<string>& words) {
    int res = 0;
    int N = words.size();
    for (int i = 0; i < N; i++) {
      unordered_set<char> word_i(words[i].begin(), words[i].end());
      for (int j = i + 1; j < N; j++) {
        bool intersect = false;
        for (int k = 0; k < words[j].size(); k++) {
          if (word_i.count(words[j][k])) {
            intersect = true;
            break;
          }
        }

        if (intersect) continue;
        int pos_res = words[i].size() * words[j].size();
        res = max(res, pos_res);
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
319. Bulb Switcher
There are n bulbs that are initially off. You first turn on all the bulbs.
Then, you turn off every second bulb. On the third round, you toggle every
third bulb (turning on if it's off or turning off if it's on). For the ith
round, you toggle every i bulb. For the nth round, you only toggle the last
bulb. Find how many bulbs are on after n rounds.

Example:

Given n = 3.

At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off].

So you should return 1, because there is only one bulb is on.
/*
    Submission Date: 2017-09-10
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  int bulbSwitch(int N) { return sqrt(N); }
};

int main() { return 0; }