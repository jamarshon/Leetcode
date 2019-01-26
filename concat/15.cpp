
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
241. Different Ways to Add Parentheses
Given a string of numbers and operators, return all possible results from
computing all the different possible ways to group numbers and operators. The
valid operators are +, - and *.

Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Element {
  bool is_operator;
  int value;
  Element(bool _is_operator, int _value)
      : is_operator(_is_operator), value(_value) {}
};

struct ETreeNode {
  Element e;
  ETreeNode *left, *right;
  ETreeNode(Element _e) : e(_e), left(NULL), right(NULL) {}
};

class SolutionTree {
 public:
  ETreeNode* cloneWithOffset(ETreeNode* curr, int offset) {
    if (curr == NULL) return NULL;
    Element offset_e = curr->e;
    offset_e.value += offset;

    ETreeNode* new_curr = new ETreeNode(offset_e);
    new_curr->left = cloneWithOffset(curr->left, offset);
    new_curr->right = cloneWithOffset(curr->right, offset);
    return new_curr;
  }

  void destroyTree(ETreeNode* root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
  }

  vector<ETreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    vector<vector<ETreeNode*>> dp(n + 1);
    dp[0] = {NULL};

    for (int len = 1; len <= n; len++) {
      for (int j = 0; j < len; j++) {
        vector<ETreeNode*> left_trees = dp[j], right_trees = dp[len - j - 1];
        for (auto left_tree : left_trees) {
          for (auto right_tree : right_trees) {
            ETreeNode* curr = new ETreeNode(Element{true, j});
            curr->left = cloneWithOffset(left_tree, 0);
            curr->right = cloneWithOffset(right_tree, j + 1);
            dp[len].push_back(curr);
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (auto tree : dp[i]) destroyTree(tree);
    }
    return dp[n];
  }

  void inorderPlaceValuesAndOperators(ETreeNode* root, vector<Element>& numbers,
                                      vector<Element> operators, int& i,
                                      int& j) {
    if (root == NULL) return;
    inorderPlaceValuesAndOperators(root->left, numbers, operators, i, j);
    root->e = operators[i++];
    if (root->left == NULL) {
      root->left = new ETreeNode(numbers[j++]);
    }

    if (root->right) {
      inorderPlaceValuesAndOperators(root->right, numbers, operators, i, j);
    } else {
      root->right = new ETreeNode(numbers[j++]);
    }
  }

  int evaluateTree(ETreeNode* root) {
    assert(root != NULL);  // should never happen as the numbers are the leafs
    if (root->e.is_operator) {
      if (root->e.value == '*') {
        return evaluateTree(root->left) * evaluateTree(root->right);
      } else if (root->e.value == '+') {
        return evaluateTree(root->left) + evaluateTree(root->right);
      } else if (root->e.value == '-') {
        return evaluateTree(root->left) - evaluateTree(root->right);
      } else {
        assert(false);
        return -1;
      }
    } else {
      return root->e.value;
    }
  }

  void preorder(ETreeNode* curr) {
    if (curr == NULL) {
      cout << "NULL ";
    } else {
      if (curr->e.is_operator)
        cout << char(curr->e.value) << ' ';
      else
        cout << (curr->e.value) << ' ';
      preorder(curr->left);
      preorder(curr->right);
    }
  }

  vector<int> diffWaysToCompute(string input) {
    int start = 0;
    int end = 0;
    int N = input.size();

    vector<Element> operators;
    vector<Element> numbers;
    while (end < N) {
      if (input[end] == '*' || input[end] == '-' || input[end] == '+') {
        string s = input.substr(start, end - start);
        if (!s.empty()) {
          numbers.emplace_back(false, stoi(s));
        }
        operators.emplace_back(true, input[end]);
        start = end + 1;
      }
      end++;
    }

    string s = input.substr(start, end - start);
    if (!s.empty()) {
      numbers.emplace_back(false, stoi(s));
    }

    vector<ETreeNode*> uniqueTrees = generateTrees(operators.size());
    vector<int> res;
    int i, j;
    for (auto tree : uniqueTrees) {
      i = j = 0;
      inorderPlaceValuesAndOperators(tree, numbers, operators, i, j);
      res.push_back(evaluateTree(tree));
    }
    return res;
  }
};

class SolutionDP {
  unordered_map<char, function<int(int, int)>> ops_m{
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
  };

 public:
  vector<int> diffWaysToCompute(string input) {
    vector<int> nums;  // nums will be size N and ops should be size N - 1 but
                       // extra added just for convenience
    vector<char> ops;

    int num;
    char op;
    stringstream ss(input + "+");

    while (ss >> num && ss >> op) {
      nums.push_back(num);
      ops.push_back(op);
    }

    int N = nums.size();
    if (N == 1) return nums;

    /**
        dp[i][j] is a vector of all possible values from operations from index i
       to j inclusive where indexes correspond with integers from the nums array
        e.g. "2*3-4*5" -> nums = [2,3,4,5] and ops = ['*', '-', '*'] dp[2][3] =
       {20} as 4*5 or ops[2](dp[2][2], dp[3][3])

        dp[i][i] would just be {nums[i]}
        dp[i][j] would be {op[k](dp[i][k], dp[k+1][j]), ... for all k from [i,
       j)} final result is just indexes 0 to N-1 or dp[0][N-1]
    */
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(N));

    for (int i = N - 1; i >= 0; i--) {
      for (int j = i; j < N; j++) {
        if (i == j) {
          dp[i][j] = {nums[i]};
        } else {
          for (int k = i; k < j; k++) {
            vector<int>& left = dp[i][k];
            vector<int>& right = dp[k + 1][j];
            function<int(int, int)> op = ops_m[ops[k]];
            for (auto left_el : left) {
              for (auto right_el : right) {
                dp[i][j].push_back(op(left_el, right_el));
              }
            }
          }
        }
      }
    }
    return dp[0][N - 1];
  }
};

class Solution {
  unordered_map<string, vector<int>> dp;
  unordered_map<char, function<int(int, int)>> ops_m{
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
  };

 public:
  vector<int> diffWaysToCompute(string input) {
    if (dp.count(input)) return dp[input];
    int N = input.size();
    vector<int> res;
    for (int i = 0; i < N; i++) {
      if (!isdigit(input[i])) {
        vector<int> left = diffWaysToCompute(input.substr(0, i));
        vector<int> right = diffWaysToCompute(input.substr(i + 1));
        function<int(int, int)> op = ops_m[input[i]];
        for (auto left_el : left) {
          for (auto right_el : right) {
            res.push_back(op(left_el, right_el));
          }
        }
      }
    }

    if (res.empty()) res.push_back(stoi(input));  // no operations left
    return dp[input] = res;
  }
};

int main() {
  Solution s;
  vector<int> v = s.diffWaysToCompute("2*3-4*5");
  for (auto e : v) cout << e << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
242. Valid Anagram
Given two strings s and t, write a function to determine if t is an anagram of
s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution
to such case?

/*
    Submission Date: 2017-08-06
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;

    unordered_map<char, int> s_freq, t_freq;
    for (int i = 0, len = s.size(); i < len; i++) {
      s_freq[s[i]]++;
      t_freq[t[i]]++;
    }

    if (s_freq.size() != t_freq.size()) return false;
    for (auto kv : s_freq) {
      if (t_freq.count(kv.first) && t_freq[kv.first] == kv.second) continue;
      return false;
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
257. Binary Tree Paths
Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
/*
    Submission Date: 2017-08-23
    Runtime: 79 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode *root) {
    if (root == NULL) return {};

    string curr = to_string(root->val);
    vector<string> res;

    vector<string> left = binaryTreePaths(root->left);
    for (auto str : left) res.push_back(curr + "->" + str);

    vector<string> right = binaryTreePaths(root->right);
    for (auto str : right) res.push_back(curr + "->" + str);

    if (left.empty() && right.empty()) res.push_back(curr);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
258. Add Digits
Given a non-negative integer num, repeatedly add all its
digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2.
Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?
/*
    Submission Date: 2017-08-25
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

/*
    digital root problem (single digit) value obtained by an iterative
    process of summing digits, on each iteration using the result from
    the previous iteration to compute a digit sum

    cyclic around 9
    ...                 10                  20                  30
    0 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4
    ...             40                  50                  60
    5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
    ...         70                  80                  90
    1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
*/
class Solution {
 public:
  int addDigits(int num) { return 1 + (num - 1) % 9; }
};

class Solution2 {
 public:
  int addDigits(int num) {
    if (num == 0) return 0;
    int num_digits = floor(log10(num)) + 1;
    if (num_digits == 1) return num;

    int x = 0;
    while (num) {
      x += num % 10;
      num /= 10;
    }

    return addDigits(x);
  }
};

int main() {
  Solution s;
  for (int i = 0; i < 100; i++) {
    cout << i << ' ' << s.addDigits(i) << endl;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
260. Single Number III
Given an array of numbers nums, in which exactly two elements
appear only once and all the other elements appear exactly twice.
Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example,
[5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you
implement it using only constant space complexity?
/*
    Submission Date: 2017-08-23
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> singleNumber(vector<int>& nums) {
    // 1, 2, 1, 3, 2, 5 -> 3 ^ 5 = 011 ^ 101 = 110
    int xor_all = 0;  // x ^ y
    for (auto num : nums) xor_all ^= num;

    // lsb of 110 is 010 so xor all number that has this bit set
    // 2 ^ 2 ^ 3 = 010 ^ 010 ^ 011 = 011
    int lsb = xor_all & ~(xor_all - 1);
    int xor_same_lsb = 0;
    for (auto num : nums) {
      if (num & lsb) xor_same_lsb ^= num;
    }

    // xor_same_lsb is x and xor_all ^ x = (x ^ y) ^ x = y
    int x = xor_same_lsb;
    int y = xor_all ^ x;
    return {x, y};
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
263. Ugly Number
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
For example, 6, 8 are ugly while 14 is not ugly since it includes another prime
factor 7.

Note that 1 is typically treated as an ugly number.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  bool isUgly2(int num) {
    if (num <= 0) return false;
    if (num == 1) return true;

    if (num % 2 == 0) return isUgly(num / 2);
    if (num % 3 == 0) return isUgly(num / 3);
    if (num % 5 == 0) return isUgly(num / 5);

    return false;
  }

  bool isUgly(int num) {
    if (num <= 0) return false;

    int primes[3] = {2, 3, 5};
    for (int i = 0; i < 3; i++) {
      while (num % primes[i] == 0) {
        num /= primes[i];
      }
    }

    return num == 1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
264. Ugly Number II
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only
include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12
is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n
does not exceed 1690.
/*
    Submission Date: 2017-08-23
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  int nthUglyNumber(int n) {
    typedef long long ll;
    typedef pair<ll, ll> pll;

    // pair where first is value and second is the minimum permissable
    // index for arr

    // we keep track of the smallest value using min heap and
    // remove the value to add smallest*arr[i] for i from index to 3
    // the index keeps track of allowable factors as 2*2*3 and
    // 3*2*2 is the same so by only keeping factors in increasing
    // order we can avoid duplicates
    // when n - 1 elements are removed then the top of the min heap
    // is the answer
    auto cmp = [](const pll& lhs, const pll& rhs) {
      return lhs.first == rhs.first ? lhs.second > rhs.second
                                    : lhs.first > rhs.first;
    };

    priority_queue<pll, vector<pll>, decltype(cmp)> pq(cmp);
    pq.emplace(1, 0);

    int removed = 0;
    ll arr[3] = {2, 3, 5};
    while (removed < n - 1) {
      pll top = pq.top();
      pq.pop();

      for (int i = top.second; i < 3; i++) {
        pq.emplace(top.first * arr[i], i);
      }
      removed++;
    }

    return pq.top().first;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
268. Missing Number
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement
it using only constant extra space complexity?

/*
    Submission Date: 2017-08-12
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    int res = 0;
    int N = nums.size();
    for (int i = 1; i <= N; i++) {
      res ^= i;
      res ^= nums[i - 1];
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
273. Integer to English Words
Convert a non-negative integer to its english words representation. Given input
is guaranteed to be less than 2^31 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
Seven"

/*
    Submission Date: 2017-08-12
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string numberToWords(int num) {
    if (num == 0) return "Zero";

    vector<pair<int, string>> val_to_str{
        {1e9, "Billion"}, {1e6, "Million"}, {1e3, "Thousand"}, {1e2, "Hundred"},
        {90, "Ninety"},   {80, "Eighty"},   {70, "Seventy"},   {60, "Sixty"},
        {50, "Fifty"},    {40, "Forty"},    {30, "Thirty"},    {20, "Twenty"},
        {19, "Nineteen"}, {18, "Eighteen"}, {17, "Seventeen"}, {16, "Sixteen"},
        {15, "Fifteen"},  {14, "Fourteen"}, {13, "Thirteen"},  {12, "Twelve"},
        {11, "Eleven"},   {10, "Ten"},      {9, "Nine"},       {8, "Eight"},
        {7, "Seven"},     {6, "Six"},       {5, "Five"},       {4, "Four"},
        {3, "Three"},     {2, "Two"},       {1, "One"}};

    string res = "";
    function<string(string, string)> add = [](const string& a,
                                              const string& b) {
      return a.empty() ? b : a + " " + b;
    };

    while (num) {
      for (auto p : val_to_str) {
        if (num == 0) break;
        if (num >= p.first) {
          int to_change = num / p.first;
          if (to_change == 1 && p.first < 1e2) {
            res = add(res, p.second);
            if (num == p.first) {
              num = 0;
              break;
            }
          } else {
            res = add(add(res, numberToWords(to_change)), p.second);
          }
          num %= p.first;
        }
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
274. H-Index
Given an array of citations (each citation is a non-negative integer)
of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has
index h if h of his/her N papers have at least h citations each, and
the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the
researcher has 5 papers in total and each of them had received
3, 0, 6, 1, 5 citations respectively. Since the researcher has
3 papers with at least 3 citations each and the remaining two
with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one
is taken as the h-index.
/*
    Submission Date: 2017-08-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
              i    0, 1, 2, 3, 4
            N - i  5, 4, 3, 2, 1
  h index is choose index from [0,n] such that
  h elements have citations >= h and N - h have citations < h

  Bucket sort
  bucket[i] for i = [0,n) indicates frequency of value i
  in citations. bucket[n] indications frequency of value >= n
  in citations.

  sum[i] shows how many element are greater than or equal to
  i so if sum[i] >= i then h = i as there are sum[i] elements
  greater than or equal to i and N - i elements smaller than
  i.

  3, 0, 6, 1, 5

  buckets
  0 1 2 3 4 5
  1 1 0 1 0 2

  sum   5 4 3 3 2 2
  index 0 1 2 3 4 5
  */
  int hIndex(vector<int>& citations) {
    int N = citations.size();

    vector<int> bucket(N + 1, 0);
    for (auto c : citations) {
      // if citation greater than N just use N
      // else increase bucket[c]
      bucket[min(c, N)]++;
    }

    int sum = 0;
    for (int i = N; i >= 0; i--) {
      sum += bucket[i];
      if (sum >= i) return i;
    }

    return 0;
  }
};

int main() {
  Solution s;
  vector<int> v{3, 0, 6, 1, 5};
  cout << s.hIndex(v) << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
275. H-Index II
Follow up for H-Index: What if the citations array is sorted in
ascending order? Could you optimize your algorithm?
/*
    Submission Date: 2017-08-30
    Runtime: 192 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
              i    0, 1, 2, 3, 4
            N - i  5, 4, 3, 2, 1
  h index is choose index from [0,n] such that
  h elements have citations >= h and N - h have citations < h

  sort and see if citations[i] >= N - i as N - i is the number
  of elements that are greater than or equal to this element
  from [i,N). Since it is sorted, i elements are less than citations[i].
  If citations[i] is greater than N - i, it means
  h = N - i as h elements [i, N) have citations[i] >= h
  and h elements [0, i) have citations[i] < h
  */
  int hIndex(vector<int>& citations) {
    int N = citations.size();
    for (int i = 0; i < N; i++) {
      if (citations[i] >= N - i) {
        return N - i;
      }
    }
    return 0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
278. First Bad Version
You are a product manager and currently leading a team to develop a new product.
Unfortunately, the latest version of your product fails the quality check.
Since each version is developed based on the previous version, all the
versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first
bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether
version is bad. Implement a function to find the first bad version. You should
minimize the number of calls to the API.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: EASY
*/

#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
 public:
  int firstBadVersion(int n) {
    int low = 1;
    int high = n;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (isBadVersion(mid)) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return low;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers
(for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13,
return 2 because 13 = 4 + 9.

/*
    Submission Date: 2017-08-12
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int numSquares(int n) {
    if (n == 0) return 0;
    int sq = sqrt(n);
    vector<int> dp(n + 1);

    iota(dp.begin(), dp.end(), 0);

    // dp[i][j] means minimum number using [0,i] squares for the number j
    // dp[i][j] = min(
    //              dp[i-1][j], // we don't use this square
    //              dp[i][j-i*i] // we use this square )
    // since we only use the previous row, just save space with 1d vector
    for (int i = 2; i <= sq; i++) {
      for (int j = 1; j <= n; j++) {
        int r = j - i * i;
        if (r >= 0) {
          dp[j] = min(dp[j], dp[r] + 1);
        }
      }
    }

    return dp[n];
  }
};

int main() { return 0; }