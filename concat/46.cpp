
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1103. Distribute Candies to People
We distribute some number of candies, to a row of n = num_people people in the
following way:

We then give 1 candy to the first person, 2 candies to the second person, and so
on until we give n candies to the last person.

Then, we go back to the start of the row, giving n + 1 candies to the first
person, n + 2 candies to the second person, and so on until we give 2 *
n candies to the last person.

This process repeats (with us giving one more candy each time, and moving to the
start of the row after we reach the end) until we run out of candies.  The last
person will receive all of our remaining candies (not necessarily one more than
the previous gift).

Return an array (of length num_people and sum candies) that represents the final
distribution of candies.

Example 1:

Input: candies = 7, num_people = 4
Output: [1,2,3,1]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0,0].
On the third turn, ans[2] += 3, and the array is [1,2,3,0].
On the fourth turn, ans[3] += 1 (because there is only one candy left), and the
final array is [1,2,3,1].

Example 2:

Input: candies = 10, num_people = 3
Output: [5,2,3]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0].
On the third turn, ans[2] += 3, and the array is [1,2,3].
On the fourth turn, ans[0] += 4, and the final array is [5,2,3].

Constraints:

  1 <= candies <= 10^9
  1 <= num_people <= 1000
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> distributeCandies(int candies, int num_people) {
    int i = 1, j = 0;
    vector<int> res(num_people, 0);
    while (candies) {
      i = min(candies, i);
      candies -= i;
      res[j] += i;
      i++;
      j = (j + 1) % num_people;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1104. Path In Zigzag Labelled Binary Tree
In an infinite binary tree where every node has two children, the nodes are
labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is
left to right, while in the even numbered rows (second, fourth, sixth,...), the
labelling is right to left.

Given the label of a node in this tree, return the labels in the path from the
root of the tree to the node with that label.

Example 1:

Input: label = 14
Output: [1,3,4,14]

Example 2:

Input: label = 26
Output: [1,2,6,10,26]

Constraints:

  1 <= label <= 10^6
/*
  Submission Date: 2019-09-22
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> pathInZigZagTree(int label) {
    /*
    get the current level, reverse the level and
    divide by two to get the parent
    to reverse a number y around x do 2x-y
    now for level i in a tree [2^i, 2^(i+1)-1] the
    center is (2^i + 2^(i+1)-1)/2 so to reverse a level
    just reverse around the center
    */
    int level = log2(label);
    vector<int> res;
    while (level >= 0) {
      res.push_back(label);
      int flipped = (1 << level) + (1 << (level + 1)) - 1 - label;
      level--;
      label = flipped / 2;
    }
    reverse(res.begin(), res.end());
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
1110. Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest
(a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the
result in any order.

Example 1:

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Constraints:

  The number of nodes in the given tree is at most 1000.
  Each node has a distinct value between 1 and 1000.
  to_delete.length <= 1000
  to_delete contains distinct values between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 20 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  vector<TreeNode*> res;

 public:
  /*
  return the tree without the deleted nodes
  when a node is deleted, put the pruned left/right (if non null) into the
  forest also add the root if it is not deleted
  */
  TreeNode* helper(TreeNode* root, const unordered_set<int>& delete_set) {
    if (!root) return nullptr;
    auto left = helper(root->left, delete_set);
    auto right = helper(root->right, delete_set);
    if (delete_set.count(root->val)) {
      if (left) res.push_back(left);
      if (right) res.push_back(right);
      return nullptr;
    } else {
      root->left = left;
      root->right = right;
      return root;
    }
  }

  vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    unordered_set<int> delete_set(to_delete.begin(), to_delete.end());
    if (!delete_set.count(root->val)) res.push_back(root);
    helper(root, delete_set);
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1111. Maximum Nesting Depth of Two Valid Parentheses Strings
A string is a valid parentheses string (denoted VPS) if and only if it consists
of "(" and ")" characters only, and:

  It is the empty string, or
  It can be written as AB (A concatenated with B), where A and B are VPS's, or
  It can be written as (A), where A is a VPS.

We can similarly define the nesting depth depth(S) of any VPS S as follows:

  depth("") = 0
  depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
  depth("(" + A + ")") = 1 + depth(A), where A is a VPS.

For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1,
and 2), and ")(" and "(()" are not VPS's.

Given a VPS seq, split it into two disjoint subsequences A and B, such that A
and B are VPS's (and A.length + B.length = seq.length).

Now choose any such A and B such that max(depth(A), depth(B)) is the minimum
possible value.

Return an answer array (of length seq.length) that encodes such a choice of A
and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note that
even though multiple answers may exist, you may return any of them.

Example 1:

Input: seq = "(()())"
Output: [0,1,1,1,1,0]

Example 2:

Input: seq = "()(())()"
Output: [0,0,0,1,1,0,1,1]

Constraints:

  1 <= seq.size <= 10000
/*
  Submission Date: 2019-09-22
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxDepthAfterSplit(string seq) {
    // put all the even '(' in one area with all the
    // odd ')'
    vector<int> res;
    for (int i = 0; i < seq.size(); i++) res.push_back(i & 1 ^ (seq[i] == '('));
    return res;
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
1123. Lowest Common Ancestor of Deepest Leaves
Given a rooted binary tree, return the lowest common ancestor of its deepest
leaves.

Recall that:

  The node of a binary tree is a leaf if and only if it has no children
  The depth of the root of the tree is 0, and if the depth of a node is d, the
depth of each of its children is d+1.
  The lowest common ancestor of a set S of nodes is the node A with the largest
depth such that every node in S is in the subtree with root A.

Example 1:

Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization
"[1,2,3]".

Example 2:

Input: root = [1,2,3,4]
Output: [4]

Example 3:

Input: root = [1,2,3,4,5]
Output: [2,4,5]

Constraints:

  The given tree will have between 1 and 1000 nodes.
  Each node of the tree will have a distinct value between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
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
  // return lca, depth
  pair<TreeNode*, int> helper(TreeNode* curr) {
    if (!curr) return {nullptr, 0};
    auto left = helper(curr->left);
    auto right = helper(curr->right);
    // same depth means this is the lca
    if (left.second == right.second) return {curr, left.second + 1};
    // the left lca is the lca of all the deepest leaves so
    // return that upward
    else if (left.second > right.second)
      return {left.first, left.second + 1};
    // same as before but its the right lca
    else
      return {right.first, right.second + 1};
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) { return helper(root).first; }
};

class Solution3 {
  unordered_map<int, unordered_set<TreeNode*>> depth_to_node;

 public:
  pair<TreeNode*, int> lca(TreeNode* curr,
                           const unordered_set<TreeNode*>& leaves) {
    if (!curr) return {nullptr, 0};
    int N = leaves.size();
    auto left = lca(curr->left, leaves);
    if (left.second == N) return left;
    auto right = lca(curr->right, leaves);
    if (right.second == N) return right;
    int total = left.second + right.second + leaves.count(curr);
    return {curr, total};
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].insert(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    return lca(root, depth_to_node[max_depth]).first;
  }
};

class Solution2 {
  unordered_map<int, vector<TreeNode*>> depth_to_node;

 public:
  TreeNode* lca(TreeNode* curr, TreeNode* a, TreeNode* b) {
    if (!curr || curr == a || curr == b) return curr;
    auto left = lca(curr->left, a, b);
    auto right = lca(curr->right, a, b);
    if (left && right)
      return curr;
    else if (left)
      return left;
    else
      return right;
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].push_back(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    auto v = depth_to_node[max_depth];
    TreeNode* prev = nullptr;
    for (auto e : v) prev = lca(root, prev, e);
    return prev;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1128. Number of Equivalent Domino Pairs
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] =
[c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one
domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length,
and dominoes[i] is equivalent to dominoes[j].

Example 1:
Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1

Constraints:

  1 <= dominoes.length <= 40000
  1 <= dominoes[i][j] <= 9
/*
  Submission Date: 2019-09-23
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    unordered_map<string, int> freq;
    int res = 0;
    for (const auto& d : dominoes) {
      auto p = minmax(d[0], d[1]);
      string key = to_string(p.first) + ',' + to_string(p.second);
      res += freq[key];
      freq[key]++;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1137. N-th Tribonacci Number
The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:

Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:

Input: n = 25
Output: 1389537

Constraints:

  0 <= n <= 37
  The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 -
1.
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int tribonacci(int n) {
    if (n <= 1) return n;
    int T0 = 0, T1 = 1, T2 = 1;
    for (int i = 2; i < n; i++) {
      int T3 = T0 + T1 + T2;
      T0 = T1;
      T1 = T2;
      T2 = T3;
    }

    return T2;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1154. Day of the Year
Given a string date representing a Gregorian calendar date formatted as
YYYY-MM-DD, return the day number of the year.

Example 1:

Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.

Example 2:

Input: date = "2019-02-10"
Output: 41

Example 3:

Input: date = "2003-03-01"
Output: 60

Example 4:

Input: date = "2004-03-01"
Output: 61

Constraints:

  date.length == 10
  date[4] == date[7] == '-', and all other date[i]'s are digits
  date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
/*
  Submission Date: 2019-09-23
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  }
  int dayOfYear(string date) {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8));
    bool is_leap_year = isLeapYear(year);
    int res = 0;
    for (int i = 0; i < month - 1; i++) {
      res += days_in_month[i];
    }
    return res + day + (is_leap_year && month > 2);
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1161. Maximum Level Sum of a Binary Tree
Given the root of a binary tree, the level of its root is 1, the level of its
children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at
level X is maximal.

Example 1:

Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Note:

  The number of nodes in the given tree is between 1 and 10^4.
  -10^5 <= node.val <= 10^5
/*
  Submission Date: 2019-09-21
  Runtime: 208 ms
  Difficulty: MEDIUM
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
  int maxLevelSum(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int max_level = -1;
    int max_sum = INT_MIN;
    int level = 1;
    while (!q.empty()) {
      int sum = 0;
      for (int i = 0, N = q.size(); i < N; i++) {
        TreeNode* curr = q.front();
        sum += curr->val;
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
      if (max_level == -1 || sum > max_sum) {
        max_level = level;
        max_sum = sum;
      }
      level++;
    }
    return max_level;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1170. Compare Strings by Frequency of the Smallest Character
Let's define a function f(s) over a non-empty string s, which calculates the
frequency of the smallest character in s. For example, if s = "dcce" then f(s) =
2 because the smallest character is "c" and its frequency is 2.

Now, given string arrays queries and words, return an integer array answer,
where each answer[i] is the number of words such that f(queries[i]) < f(W),
where W is a word in words.

Example 1:

Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd")
< f("zaaaz").

Example 2:

Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query
both f("aaa") and f("aaaa") are both > f("cc").

Constraints:

  1 <= queries.length <= 2000
  1 <= words.length <= 2000
  1 <= queries[i].length, words[i].length <= 10
  queries[i][j], words[i][j] are English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  // linear finds the smallest character and its frequency
  int f(const string& s) {
    char smallest = 'z' + 1;
    for (const auto& c : s) smallest = min(smallest, c);
    int freq = 0;
    for (const auto& c : s) freq += c == smallest;
    return freq;
  }

 public:
  vector<int> numSmallerByFrequency(vector<string>& queries,
                                    vector<string>& words) {
    int w_size = words.size();

    // compute all the f of words and sort them
    vector<int> f_ws(w_size);
    for (int i = 0; i < w_size; i++) f_ws[i] = f(words[i]);
    sort(f_ws.begin(), f_ws.end());

    int q_size = queries.size();
    vector<int> res(q_size);
    for (int i = 0; i < q_size; i++) {
      int f_q = f(queries[i]);
      // find the f of a query and binary search the first
      // f of a word larger than it. return the number
      // of elements further right/greater than the iterator
      // (e.g. > f_q)
      auto it = upper_bound(f_ws.begin(), f_ws.end(), f_q);
      res[i] = f_ws.end() - it;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1175. Prime Arrangements
Return the number of permutations of 1 to n so that prime numbers are at prime
indices (1-indexed.)

(Recall that an integer is prime if and only if it is greater than 1, and cannot
be written as a product of two positive integers both smaller than it.)

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is
not because the prime number 5 is at index 1.

Example 2:

Input: n = 100
Output: 682289015

Constraints:

  1 <= n <= 100
/*
  Submission Date: 2019-09-21
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int mod = 1e9 + 7;

  // get the number of primes from [2, n]
  int sieve(int n) {
    int cnt = 0;
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= sqrt(n); i++) {
      if (is_prime[i]) {
        cnt++;
        for (int j = i * i; j <= n; j += i) {
          is_prime[j] = false;
        }
      }
    }
    for (int i = sqrt(n) + 1; i <= n; i++) cnt += is_prime[i];
    return cnt;
  }

  long long factorial(int n) {
    long long res = 1;
    for (int i = 1; i <= n; i++) res = (res * i) % mod;
    return res;
  }

  int numPrimeArrangements(int n) {
    /*
    return num_primes! * (n - num_primes)!
    because there are num_primes! ways to organize the primes
    and (n - num_primes)! ways to organize the composites
    */
    int num_primes = sieve(n);
    int num_composites = n - sieve(n);
    return (factorial(num_primes) * factorial(num_composites)) % mod;
  }
};

int main() { return 0; }
