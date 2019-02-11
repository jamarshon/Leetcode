
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
706. Design HashMap
Design a HashMap without using any built-in hash table libraries.

To be specific, your design should include these functions:

  put(key, value) : Insert a (key, value) pair into the HashMap. If the value
already exists in the HashMap, update the value.
  get(key): Returns the value to which the specified key is mapped, or -1 if
this map contains no mapping for the key. remove(key) : Remove the mapping for
the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);          
hashMap.put(2, 2);        
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found)

Note:

  All keys and values will be in the range of [0, 1000000].
  The number of operations will be in the range of [1, 10000].
  Please do not use the built-in HashMap library.
/*
  Submission Date: 2019-02-06
  Runtime: 160 ms
  Difficulty: EASY
*/
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
struct Data {
  hash<int> h;
  int capacity;
  int size = 0;
  vector<list<pii>> arr;
  int GetHash(int key) { return h(key) % capacity; }

  Data(int cap) : capacity(cap) { arr.resize(capacity); }
};

class MyHashMap {
  const double load_factor_ = 0.75;
  int capacity_ = 10;
  Data* data_;

  list<pii>::iterator Get(int key) {
    auto& l = data_->arr[data_->GetHash(key)];
    for (auto it = l.begin(); it != l.end(); it++) {
      if (it->first == key) return it;
    }
    return l.end();
  }

 public:
  /** Initialize your data structure here. */
  MyHashMap() { data_ = new Data(capacity_); }

  /** value will always be non-negative. */
  void put(int key, int value) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];

    if (it == l.end()) {
      // insert
      l.emplace_back(key, value);
      data_->size++;

      if (data_->size > load_factor_ * capacity_) {
        Data* old = data_;
        capacity_ *= 2;
        data_ = new Data(capacity_);
        for (const auto& bucket : old->arr) {
          for (const pii& p : bucket) {
            put(p.first, p.second);
          }
        }

        delete old;
      }
    } else {
      it->second = value;
    }
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map
   * contains no mapping for the key */
  int get(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    return it == l.end() ? -1 : it->second;
  }

  /** Removes the mapping of the specified value key if this map contains a
   * mapping for the key */
  void remove(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    if (it != l.end()) {
      l.erase(it);
      data_->size--;
    }
  }
};

int main() {
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
707. Design Linked List
Design your implementation of the linked list. You can choose to use the singly
linked list or the doubly linked list. A node in a singly linked list should
have two attributes: val and next. val is the value of the current node, and
next is a pointer/reference to the next node. If you want to use the doubly
linked list, you will need one more attribute prev to indicate the previous node
in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement these functions in your linked list class:


    get(index) : Get the value of the index-th node in the linked list. If the
index is invalid, return -1.
    addAtHead(val) : Add a node of value val before the first element of the
linked list. After the insertion, the new node will be the first node of the
linked list. addAtTail(val) : Append a node of value val to the last element of
the linked list. addAtIndex(index, val) : Add a node of value val before the
index-th node in the linked list. If index equals to the length of linked list,
the node will be appended to the end of linked list. If index is greater than
the length, the node will not be inserted. deleteAtIndex(index) : Delete the
index-th node in the linked list, if the index is valid.


Example:

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3


Note:


    All values will be in the range of [1, 1000].
    The number of operations will be in the range of [1, 1000].
    Please do not use the built-in LinkedList library.
/*
    Submission Date: 2018-07-15
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int _val) : val(_val), next(NULL) {}
};

class MyLinkedList {
  ListNode* head = NULL;
  ListNode* tail = NULL;
  int size = 0;

 public:
  /** Initialize your data structure here. */
  MyLinkedList() {}

  /** Get the value of the index-th node in the linked list. If the index is
   * invalid, return -1. */
  /* o(n) */

  ListNode* getNode(int index) {
    if (index >= size) return NULL;

    ListNode* curr = head;
    for (int i = 0; i < index && curr; i++) {
      curr = curr->next;
    }
    return curr;
  }

  int get(int index) {
    ListNode* curr = getNode(index);
    return curr ? curr->val : -1;
  }

  /** Add a node of value val before the first element of the linked list. After
   * the insertion, the new node will be the first node of the linked list. */
  /* o(1) */
  void addAtHead(int val) {
    ListNode* add = new ListNode(val);
    add->next = head;
    head = add;
    if (tail == NULL) tail = head;
    size++;
  }

  /** Append a node of value val to the last element of the linked list. */
  /* o(1) */
  void addAtTail(int val) {
    ListNode* add = new ListNode(val);
    if (tail == NULL) {
      head = add;
    } else {
      tail->next = add;
    }
    tail = add;
    size++;
  }

  /** Add a node of value val before the index-th node in the linked list. If
   * index equals to the length of linked list, the node will be appended to the
   * end of linked list. If index is greater than the length, the node will not
   * be inserted. */
  /* o(n) */
  void addAtIndex(int index, int val) {
    if (index > size) return;
    if (index == 0) {
      addAtHead(val);
    } else if (index == size) {
      addAtTail(val);
    } else {  // index [1, size-1]
      ListNode* curr = getNode(index - 1);
      ListNode* next = curr->next;
      curr->next = new ListNode(val);
      curr->next->next = next;
      size++;
    }
  }

  /** Delete the index-th node in the linked list, if the index is valid. */
  /* o(n) */
  void deleteAtIndex(int index) {
    if (index >= size) return;
    if (index == 0) {
      ListNode* temp = head;
      head = head->next;
      delete temp;
    } else {  // index [1, size-1]
      ListNode* curr = getNode(index - 1);
      ListNode* temp = curr->next;
      if (temp == tail) {
        tail = curr;
      }
      curr->next = temp->next;
      delete temp;
    }

    size--;
  }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList obj = new MyLinkedList();
 * int param_1 = obj.get(index);
 * obj.addAtHead(val);
 * obj.addAtTail(val);
 * obj.addAtIndex(index,val);
 * obj.deleteAtIndex(index);
 */

int main() { return 0; }
