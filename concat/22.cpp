
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's
anagrams in s.

Strings consists of lowercase English letters only and the length of both
strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

/*
    Submission Date: 2017-08-06
    Runtime: 106 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  populate freq with frequency of letters in p.
  use sliding window and everytime a letter is added decrease
  its frequency in freq and remove it if it is zero.
  when a letter is removed, increase its frequency in freq
  and again remove it if it is zero.
  The idea is when freq is empty and since it only contains
  M letters than the original distribution of letters (p)
  must be in the current window.
  */
  vector<int> findAnagrams(string s, string p) {
    int N = s.size();
    int M = p.size();
    if (M > N) return {};
    vector<int> res;
    unordered_map<char, int> freq;
    for (const auto& c : p) freq[c]++;

    for (int i = 0; i < N; i++) {
      freq[s[i]]--;
      if (freq[s[i]] == 0) freq.erase(s[i]);
      if (i >= M) {
        freq[s[i - M]]++;
        if (freq[s[i - M]] == 0) freq.erase(s[i - M]);
      }

      if (freq.empty()) res.push_back(i - M + 1);
    }

    return res;
  }
};

class Solution2 {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    int M = s.size();
    int N = p.size();

    if (M < N) return res;
    unordered_map<char, int> freq, curr_freq;

    for (auto c : p) freq[c]++;

    for (int i = 0; i < N; i++) curr_freq[s[i]]++;

    int low = 0;
    int high = N;
    while (high <= M) {
      bool is_match = true;
      if (curr_freq.size() == freq.size()) {
        for (auto kv : freq) {
          if (curr_freq.count(kv.first) && curr_freq[kv.first] == kv.second)
            continue;
          is_match = false;
          break;
        }
      } else {
        is_match = false;
      }

      if (is_match) res.push_back(low);
      if (high == M) break;
      char to_erase = s[low++];
      curr_freq[s[high++]]++;
      if (curr_freq[to_erase] == 1)
        curr_freq.erase(to_erase);
      else
        curr_freq[to_erase]--;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
441. Arranging Coins
You have a total of n coins that you want to form in a staircase shape, where
every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed
integer.

Example 1:

n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.
Example 2:

n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.
/*
    Submission Date: 2018-06-09
    Runtime: 33 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  sum of 0 to x = x(x+1)/2
  x(x+1)/2 = n
  x^2 + x - 2n = 0

  quadratic formula: x = (-1 + sqrt(8n + 1))/2
  */
  int arrangeCoins(int n) { return (-1 + sqrt(8LL * n + 1)) / 2; }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
442. Find All Duplicates in an Array
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements
appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

/*
    Submission Date: 2017-08-06
    Runtime: 176 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findDuplicates(vector<int>& nums) {
    int N = nums.size();
    vector<int> res;
    for (int i = 0; i < N; i++) {
      while (nums[i] != nums[nums[i] - 1]) {
        swap(nums[i], nums[nums[i] - 1]);
      }
    }

    for (int i = 0; i < N; i++) {
      if (nums[i] != i + 1) {
        res.push_back(nums[i]);
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
443. String Compression
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the
original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of
the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be:
["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be:
["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is
replaced by "b12". Notice each digit has it's own entry in the array. Note: All
characters have an ASCII value in [35, 126]. 1 <= len(chars) <= 1000.
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  since length of 1 are not included the compressed string will always be less
  than the full string e.g a12 is smaller than aaa... hence it is safe to just
  overwrite existing string
  */
  int compress(vector<char>& s) {
    int write = 0;
    int N = s.size();
    for (int i = 0; i < N;) {
      int start = i;
      while (i < N && s[start] == s[i]) i++;
      string freq = to_string(i - start);
      s[write++] = s[start];
      if (i - start > 1)
        for (const auto& d : freq) s[write++] = d;
    }
    return write;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
445. Add Two Numbers II
You are given two non-empty linked lists representing two non-negative integers.
The most significant digit comes first and each of their nodes contain a single
digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists
is not allowed.



Example:
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

/*
    Submission Date: 2018-07-10
    Runtime: 28 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  int GetLength(ListNode* node) {
    int res = 0;
    while (node) {
      node = node->next;
      res++;
    }
    return res;
  }

  /*
  create list where head is lsb by traversing the nodes and adding up
  corresponding l1, l2 nodes. the list may have numbers >= 10. traverse the list
  from lsb to msb and move the carry through the list and at the same time
  reverse it.
  */
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int N = GetLength(l1);
    int M = GetLength(l2);

    ListNode* res = NULL;
    // assuming N > 0 && M > 0 initially, then they will both hit 0 at the same
    // time as the longer one keeps getting trimmed
    while (N > 0 && M > 0) {
      int sum = 0;
      // if N == M, both if will execute moving both pointers and adding both
      // sums if N > M, just the first will execute if N < M, just the second
      // will execute both these last condition will ensure the longer is
      // trimmed
      if (N >= M) {
        sum += l1->val;
        l1 = l1->next;
        N--;
      }

      if (N < M) {
        sum += l2->val;
        l2 = l2->next;
        M--;
      }

      ListNode* head = new ListNode(sum);
      head->next = res;
      res = head;
    }

    // need to reverse the list and do carry through
    int carry = 0;
    ListNode* prev = NULL;
    ListNode* temp;
    while (res) {
      res->val += carry;
      carry = res->val / 10;
      res->val %= 10;

      temp = res->next;
      res->next = prev;
      prev = res;
      res = temp;
    }

    if (carry) {
      ListNode* head = new ListNode(carry);
      head->next = prev;
      prev = head;
    }

    return prev;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
447. Number of Boomerangs
Given n points in the plane that are all pairwise distinct, a "boomerang" is a
tuple of points (i, j, k) such that the distance between i and j equals the
distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and
coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
/*
    Submission Date: 2018-06-08
    Runtime: 284 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numberOfBoomerangs(vector<pair<int, int>>& points) {
    int res = 0;
    int N = points.size();

    for (int i = 0; i < N; i++) {
      /*
      From this point find the distance of all points from this point.
      if there are m points that are at the same distance from this point,
      if m is less than 2 then it can't be used else it is permutation without
      repetition which is n!/(n-r)! = m!/(m-2)! = m*(m-1)
      */
      unordered_map<int, int> dist_sq_m;
      for (int j = 0; j < N; j++) {
        if (j == i) continue;
        int dist_sq = pow(points[i].first - points[j].first, 2) +
                      pow(points[i].second - points[j].second, 2);
        dist_sq_m[dist_sq]++;
      }

      for (const auto& kv : dist_sq_m) {
        if (kv.second < 2) continue;
        res += kv.second * (kv.second - 1);
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
448. Find All Numbers Disappeared in an Array
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements
appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the
returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
/*
    Submission Date: 2018-06-04
    Runtime: 155 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
      while (nums[nums[i] - 1] != nums[i]) swap(nums[nums[i] - 1], nums[i]);
    }

    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
      if (i + 1 != nums[i]) res.push_back(i + 1);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
449. Serialize and Deserialize BST
Serialization is the process of converting a data structure or object into a
sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in the
same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is
no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary search tree can be serialized to a string
and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your
serialize and deserialize algorithms should be stateless.
/*
  Submission Date: 2019-02-20
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
  /*
  normally store preorder with null but since its bst, a preorder
  without null is enough as the bst property determines whether
  a node is a left child or right child.
  */
  TreeNode* deserializeHelper(const string& data, int& i, const int& l,
                              const int& r) {
    size_t comma_ind = data.find(",", i);
    if (comma_ind == string::npos) return nullptr;
    int val = stoi(data.substr(i, comma_ind - i));
    // if outside bound, this node shouldn't be here
    if (val < l || val > r) return nullptr;
    i = comma_ind + 1;
    TreeNode* node = new TreeNode(val);
    node->left = deserializeHelper(data, i, l, val);
    node->right = deserializeHelper(data, i, val, r);
    return node;
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (!root) return "";
    return to_string(root->val) + "," + serialize(root->left) +
           serialize(root->right);
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int i = 0;
    return deserializeHelper(data, i, INT_MIN, INT_MAX);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
451. Sort Characters By Frequency
Given a string, sort it in decreasing order based on the frequency of
characters.

Example 1:
Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid
answer.



Example 2:
Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.



Example 3:
Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

/*
    Submission Date: 2018-06-30
    Runtime: 201 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string frequencySort(string s) {
    unordered_map<char, int> letter_to_freq;
    for (const auto& c : s) letter_to_freq[c]++;
    sort(s.begin(), s.end(),
         [&letter_to_freq](const char& lhs, const char& rhs) {
           return letter_to_freq[lhs] == letter_to_freq[rhs]
                      ? lhs > rhs
                      : letter_to_freq[lhs] > letter_to_freq[rhs];
         });
    return s;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
453. Minimum Moves to Equal Array Elements
Given a non-empty integer array of size n, find the minimum number of moves
required to make all array elements equal, where a move is incrementing n - 1
elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
/*
    Submission Date: 2018-06-07
    Runtime: 51 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  increasing everything besides a number is equivalent to decreasing the number
  by 1 so if all the numbers have to be decreased to equal the same value, then
  they should all be decreased until it reaches the smallest element in the
  array
  
  e.g 1 4 7
  the 4 needs to be decreased 3 times and the 7 decreased 6 times to get
  (4-1) + (7-1) = 9
  
  or
  
  let an array be A = {A[0], A[1], A[2], ... A[N]} and Z = {Z[0], Z[1], Z[2],
  Z[N]} where Z[i] means the number of rows where the element at i is zero then
  if x is the final value which all the elements equal to then
  
  A[0] + Z[1] + Z[2] + ... + Z[N] = x
  Z[0] + A[1] + Z[2] + ... + Z[N] = x
  Z[0] + Z[1] + A[2] + ... + Z[N] = x
  ...
  
  subtracting one row from another gets
  Z[0] - Z[1] + A[1] - A[0] = 0
  Z[1] - Z[0] = A[1] - A[0]
  
  let Z[0] = 0,
  Z[i] = A[i] - A[i-1] + Z[i-1]
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + Z[i-2])
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + Z[i-3]))
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + .... -A[1] + (A[1]
  - A[0] + Z[0])))
      ...
      = A[i] + (A[i-1] - A[i-1]) + (A[i-2] - A[i-2]) + .... (A[1] - A[1]) - A[0]
      = A[i] - A[0]
  
  The result is number of rows or sum Z[i] from i = [0, N]
  Z[i] must be >= 0 as number of rows can't be negative. to minimize then
  A[i] - A[0] should have A[0] as large as possible with having A[i] become < 0
  so A[0] should be the smallest in the array as A[min_ind] - A[min_ind] >= 0
  */
  int minMoves(vector<int>& nums) {
    if (nums.empty()) return 0;
    int min_el = *min_element(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      res += nums[i] - min_el;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
454. 4Sum II
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k,
l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤
500. All integers are in the range of -228 to 228 - 1 and the result is
guaranteed to be at most 231 - 1.

Example:
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

/*
    Submission Date: 2018-07-08
    Runtime: 104 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  O(n^2) generate all n^2 sums of A and B and put in hashmap of sum to frequency
  generate all n^2 sums of C and D and see if the sum exists in hashmap, if it
  does then res increases by the frequency as the frequency represents how many
  ways to get that sum
  */
  int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C,
                   vector<int>& D) {
    unordered_map<int, int> sum_A_B;
    for (const auto& a : A) {
      for (const auto& b : B) {
        sum_A_B[a + b]++;
      }
    }

    int res = 0;
    for (const auto& c : C) {
      for (const auto& d : D) {
        if (sum_A_B.count(-c - d)) {
          res += sum_A_B[-c - d];
        }
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
455. Assign Cookies
Assume you are an awesome parent and want to give your children some cookies.
But, you should give each child at most one cookie. Each child i has a greed
factor gi, which is the minimum size of a cookie that the child will be content
with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j
to the child i, and the child i will be content. Your goal is to maximize the
number of your content children and output the maximum number.

Note:
You may assume the greed factor is always positive.
You cannot assign more than one cookie to one child.

Example 1:
Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children
are 1, 2, 3. And even though you have 2 cookies, since their size is both 1, you
could only make the child whose greed factor is 1 content. You need to output 1.
Example 2:
Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children
are 1, 2. You have 3 cookies and their sizes are big enough to gratify all of
the children, You need to output 2.
/*
    Submission Date: 2018-06-08
    Runtime: 42 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    int res = 0;
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int j = 0;
    for (int i = 0; i < g.size(); i++) {
      while (j < s.size() && g[i] > s[j]) j++;
      if (j >= s.size()) break;
      j++;
      res++;
    }

    return res;
  }
};

int main() { return 0; }