
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
696. Count Binary Substrings
Give a string s, count the number of non-empty (contiguous) substrings that have
the same number of 0's and 1's, and all the 0's and all the 1's in these
substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's
and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times
they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not
grouped together. Example 2: Input: "10101" Output: 4 Explanation: There are 4
substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and
0's. Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.
/*
    Submission Date: 2018-05-24
    Runtime: 45 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      suppose there is prev_cnt which is the number of repeated characters
     before index i that is different than s[i]. Find how many s[i] repeats e.g.
     if it repeats from [i,j) The number of times s[i] repeats (j-i) and the
     number of times previous character repeated (prev_cnt) and the minimum
     between these two is the number of times that the substrings can have the
     same number of characters from both characters. e.g 3 4 000 1111 min(3,4) =
     3 000 111, 00 11, 0 1
  */
  int countBinarySubstrings(string s) {
    int res = 0;
    int N = s.size();
    int prev_cnt = 0;
    for (int i = 0; i < N;) {
      int start = i;
      while (i < N && s[i] == s[start]) i++;
      res += min(prev_cnt, i - start);
      prev_cnt = i - start;
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
697. Degree of an Array
Given a non-empty array of non-negative integers nums, the degree of this array
is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of
nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation:
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
/*
    Submission Date: 2018-05-24
    Runtime: 59 ms
    Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      Find the maximum frequency, loop through and if the number occurs as many
     times as max frequency then store the first seen and last seen index. Loop
     through the first seen and last seen indicies to find the shortest one.
  */
  int findShortestSubArray(vector<int>& nums) {
    unordered_map<int, int> val_to_freq;
    int max_freq = 0;
    for (const auto& n : nums) {
      val_to_freq[n]++;
      max_freq = max(max_freq, val_to_freq[n]);
    }

    unordered_map<int, pair<int, int>> val_to_seen_boundaries;
    for (int i = 0; i < nums.size(); i++) {
      if (val_to_freq[nums[i]] != max_freq) continue;
      if (!val_to_seen_boundaries.count(nums[i]))
        val_to_seen_boundaries[nums[i]] = {i, i};
      val_to_seen_boundaries[nums[i]].second = i;
    }

    int res = INT_MAX;
    for (const auto& kv : val_to_seen_boundaries)
      res = min(res, kv.second.second - kv.second.first);
    return res + 1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
700. Search in a Binary Search Tree
Given the root node of a binary search tree (BST) and a value. You need to find
the node in the BST that the node's value equals the given value. Return the
subtree rooted with that node. If such node doesn't exist, you should return
NULL.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3

And the value to search: 2


You should return this subtree:

      2
     / \
    1   3


In the example above, if we want to search the value 5, since there is no node
with value 5, we should return NULL.

/*
    Submission Date: 2018-07-13
    Runtime: 24 ms
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
  TreeNode* searchBST(TreeNode* root, int val) {
    if (root == NULL || root->val == val) return root;
    if (root->val > val)
      return searchBST(root->left, val);
    else
      return searchBST(root->right, val);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
701. Insert into a Binary Search Tree
Given the root node of a binary search tree (BST) and a value to be inserted
into the tree, insert the value into the BST. Return the root node of the BST
after the insertion. It is guaranteed that the new value does not exist in the
original BST.

Note that there may exist multiple valid ways for the insertion, as long as the
tree remains a BST after insertion. You can return any of them.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3
And the value to insert: 5


You can return this binary search tree:

         4
       /   \
      2     7
     / \   /
    1   3 5


This tree is also valid:

         5
       /   \
      2     7
     / \
    1   3
         \
          4
/*
  Submission Date: 2019-01-25
  Runtime: 108 ms
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

class Solution {
 public:
  TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) {
      return new TreeNode(val);
    }

    if (root->val < val) {
      root->right = insert(root->right, val);
    } else {
      root->left = insert(root->left, val);
    }

    return root;
  }

  TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == NULL) return new TreeNode(val);
    insert(root, val);
    return root;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
703. Kth Largest Element in a Stream
Design a class to find the kth largest element in a stream. Note that it is the
kth largest element in the sorted order, not the kth distinct element.

Your KthLargest class will have a constructor which accepts an integer k and an
integer array nums, which contains initial elements from the stream. For each
call to the method KthLargest.add, return the element representing the kth
largest element in the stream.

Example:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8

Note:
You may assume that nums' length ≥ k-1 and k ≥ 1.
/*
  Submission Date: 2019-01-26
  Runtime: 28 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
  priority_queue<int, vector<int>, greater<int>> pq_;
  int k_;

 public:
  KthLargest(int k, vector<int> nums) {
    k_ = k;
    for (auto& e : nums) add(e);
  }

  int add(int val) {
    pq_.push(val);
    if (pq_.size() > k_) {
      pq_.pop();
    }

    if (pq_.size() == k_) {
      return pq_.top();
    } else {
      return -1;
    }
  }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest obj = new KthLargest(k, nums);
 * int param_1 = obj.add(val);
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
704. Binary Search
Given a sorted (in ascending order) integer array nums of n elements and a
target value, write a function to search target in nums. If target exists, then
return its index, otherwise return -1.


Example 1:

Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4



Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1


 

Note:


    You may assume that all elements in nums are unique.
    n will be in the range [1, 10000].
    The value of each element in nums will be in the range [-9999, 9999].

/*
    Submission Date: 2018-07-13
    Runtime: 32 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (nums[mid] == target)
        return mid;
      else if (nums[mid] > target)
        high = mid - 1;
      else
        low = mid + 1;
    }

    return -1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
705. Design HashSet
Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

  add(value): Insert a value into the HashSet. 
  contains(value) : Return whether the value exists in the HashSet or not.
  remove(value): Remove a value in the HashSet. If the value does not exist in
the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);        
hashSet.add(2);        
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);          
hashSet.contains(2);    // returns true
hashSet.remove(2);          
hashSet.contains(2);    // returns false (already removed)

Note:

  All values will be in the range of [0, 1000000].
  The number of operations will be in the range of [1, 10000].
  Please do not use the built-in HashSet library.
/*
  Submission Date: 2019-02-06
  Runtime: 140 ms
  Difficulty: EASY
*/
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Data {
  hash<int> h;
  int capacity;
  int size = 0;
  vector<list<int>> arr;
  int GetHash(int key) { return h(key) % capacity; }

  Data(int cap) : capacity(cap) { arr.resize(capacity); }
};

class MyHashSet {
  const double load_factor_ = 0.75;
  int capacity_ = 10;
  Data* data_;

  list<int>::iterator Get(int key) {
    auto& l = data_->arr[data_->GetHash(key)];
    for (auto it = l.begin(); it != l.end(); it++) {
      if (*it == key) return it;
    }
    return l.end();
  }

 public:
  /** Initialize your data structure here. */
  MyHashSet() { data_ = new Data(capacity_); }

  void add(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];

    if (it == l.end()) {
      // insert
      l.emplace_back(key);
      data_->size++;

      if (data_->size > load_factor_ * capacity_) {
        Data* old = data_;
        capacity_ *= 2;
        data_ = new Data(capacity_);
        for (const auto& bucket : old->arr) {
          for (const int& k : bucket) {
            add(k);
          }
        }

        delete old;
      }
    }
  }

  void remove(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    if (it != l.end()) {
      l.erase(it);
      data_->size--;
    }
  }

  /** Returns true if this set contains the specified element */
  bool contains(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    return it != l.end();
  }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * bool param_3 = obj.contains(key);
 */

int main() {
  return 0;
}
