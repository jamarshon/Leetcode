
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
709. To Lower Case
Implement function ToLowerCase() that has a string parameter str, and returns
the same string in lowercase.

/*
    Submission Date: 2018-07-12
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string toLowerCase(string str) {
    for (auto& c : str) c = tolower(c);
    return str;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
712. Minimum ASCII Delete Sum for Two Strings
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to
make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the
sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum
possible to achieve this.



Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to
the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 =
403.
If instead we turned both strings into "lee" or "eet", we would get answers of
433 or 417, which are higher.



Note:
0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].

/*
    Submission Date: 2018-07-01
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  dp[i][j] is minimum cost for s1[0, i) s2[0, j)
  dp[0][0] = 0
  dp[0][j] = s2[j-1] + dp[i][j-1] // sum of ascii of s2[0, j)
  dp[i][0] = s1[i-1] + dp[i-1][j] // sum of ascii of s1[0, i)
  
  if s1[i-1] == s2[j-1]
      dp[i][j] = dp[i-1][j-1] // this character does not to be deleted so
                              // it is just excluding the two end characters
  else
      dp[i][j] = min(
          s1[i-1] + dp[i-1][j], // the cost of the end character of s1 + cost of
  not using that character s2[j-1] + dp[i][j-1] // cost of the end character of
  s2 + cost of not using that character
      )
  */
  int minimumDeleteSum(string s1, string s2) {
    int N = s1.size(), M = s2.size();
    int dp[N + 1][M + 1];
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= M; j++) {
        if (i == 0 && j == 0) {
          dp[i][j] = 0;
        } else if (i == 0) {
          dp[i][j] = s2[j - 1] + dp[i][j - 1];
        } else if (j == 0) {
          dp[i][j] = s1[i - 1] + dp[i - 1][j];
        } else if (s1[i - 1] == s2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = min(s1[i - 1] + dp[i - 1][j], s2[j - 1] + dp[i][j - 1]);
        }
      }
    }

    return dp[N][M];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
717. 1-bit and 2-bit Characters
We have two special characters. The first character can be represented by one
bit 0. The second character can be represented by two bits (10 or 11).

Now given a string represented by several bits. Return whether the last
character must be a one-bit character or not. The given string will always end
with a zero.

Example 1:
Input:
bits = [1, 0, 0]
Output: True
Explanation:
The only way to decode it is two-bit character and one-bit character. So the
last character is one-bit character. Example 2: Input: bits = [1, 1, 1, 0]
Output: False
Explanation:
The only way to decode it is two-bit character and two-bit character. So the
last character is NOT one-bit character. Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
/*
    Submission Date: 2018-06-07
    Runtime: 7 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isOneBitCharacter(vector<int>& bits) {
    int N = bits.size();
    vector<bool> dp(N, false);
    dp[N - 1] = true;

    for (int i = N - 2; i >= 0; i--) {
      if (bits[i] == 0) {
        dp[i] = dp[i + 1];
      } else {
        if (i + 2 < N) dp[i] = dp[i + 2];
      }
    }

    return dp[0];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
720. Longest Word in Dictionary
Given a list of strings words representing an English Dictionary, find the
longest word in words that can be built one character at a time by other words
in words. If there is more than one possible answer, return the longest word
with the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input:
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation:
The word "world" can be built one character at a time by "w", "wo", "wor", and
"worl". Example 2: Input: words = ["a", "banana", "app", "appl", "ap", "apply",
"apple"] Output: "apple" Explanation: Both "apply" and "apple" can be built from
other words in the dictionary. However, "apple" is lexicographically smaller
than "apply". Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].
/*
    Submission Date: 2018-05-24
    Runtime: 56 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
  bool is_word;
  TrieNode* child[26];
  TrieNode() {
    is_word = false;
    for (int i = 0; i < 26; i++) child[i] = NULL;
  }
};

class Trie {
 public:
  TrieNode* root_;

  /** Initialize your data structure here. */
  Trie() { root_ = new TrieNode(); }

  /** Inserts a word into the trie. */
  void insert(string word) {
    TrieNode* curr = root_;
    for (auto c : word) {
      if (curr->child[c - 'a'] == NULL) curr->child[c - 'a'] = new TrieNode();
      curr = curr->child[c - 'a'];
    }
    curr->is_word = true;
  }
};

class Solution {
 public:
  string dfs(TrieNode* node, string letter) {
    if (node == NULL || !node->is_word) return "";
    string max_child = "";
    for (int i = 0; i < 26; i++) {
      string child = dfs(node->child[i], string(1, 'a' + i));
      if (child.size() > max_child.size()) {
        max_child = child;
      }
    }

    return letter + max_child;
  }
  string longestWord(vector<string>& words) {
    Trie trie;
    for (const auto& s : words) trie.insert(s);
    trie.root_->is_word = true;
    return dfs(trie.root_, "");
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
724. Find Pivot Index
Given an array of integers nums, write a method that returns the "pivot" index
of this array.

We define the pivot index as the index where the sum of the numbers to the left
of the index is equal to the sum of the numbers to the right of the index.

If no such index exists, we should return -1. If there are multiple pivot
indexes, you should return the left-most pivot index.

Example 1:
Input:
nums = [1, 7, 3, 6, 5, 6]
Output: 3
Explanation:
The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the sum
of numbers to the right of index 3. Also, 3 is the first index where this
occurs. Example 2: Input: nums = [1, 2, 3] Output: -1 Explanation: There is no
index that satisfies the conditions in the problem statement. Note:

The length of nums will be in the range [0, 10000].
Each element nums[i] will be an integer in the range [-1000, 1000].
/*
    Submission Date: 2018-06-09
    Runtime: 45 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  make right = sum of all array then at each index i decrease nums[i]
  have left = 0 and increase it by nums[i] to compare if
  the left sum == right sum
  */
  int pivotIndex(vector<int>& nums) {
    int right = 0;
    for (const auto& e : nums) right += e;

    int left = 0;
    for (int i = 0; i < nums.size(); i++) {
      right -= nums[i];
      if (left == right) return i;
      left += nums[i];
    }

    return -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
728. Self Dividing Numbers
A self-dividing number is a number that is divisible by every digit it contains.

For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0,
and 128 % 8 == 0.

Also, a self-dividing number is not allowed to contain the digit zero.

Given a lower and upper number bound, output a list of every possible self
dividing number, including the bounds if possible.

Example 1:
Input:
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
Note:

The boundaries of each input argument are 1 <= left <= right <= 10000.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> selfDividingNumbers(int left, int right) {
    vector<int> res;

    for (int i = left; i <= right; i++) {
      int x = i;
      bool can_use = true;
      while (x) {
        if (x % 10 == 0 || i % (x % 10) != 0) {
          can_use = false;
          break;
        }
        x /= 10;
      }

      if (can_use) res.push_back(i);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
732. My Calendar III
Implement a MyCalendarThree class to store your events. A new event can always
be added.

Your class will have one method, book(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A K-booking happens when K events have some non-empty intersection (ie., there
is some time that is common to all K events.)

For each call to the method MyCalendar.book, return an integer K representing
the largest integer such that there exists a K-booking in the calendar.
Your class will be called like this: MyCalendarThree cal = new
MyCalendarThree(); MyCalendarThree.book(start, end)

Example 1:

MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
Explanation:
The first two events can be booked and are disjoint, so the maximum K-booking is
a 1-booking.
The third event [10, 40) intersects the first event, and the maximum K-booking
is a 2-booking.
The remaining events cause the maximum K-booking to be only a 3-booking.
Note that the last event locally causes a 2-booking, but the answer is still 3
because
eg. [10, 20), [10, 40), and [5, 15) are still triple booked.

Note:

  The number of calls to MyCalendarThree.book per test case will be at most 400.
  In calls to MyCalendarThree.book(start, end), start and end are integers in
the range [0, 10^9].
/*
  Submission Date: 2019-01-26
  Runtime: 128 ms
  Difficulty: HARD
*/
#include <iostream>
#include <map>

using namespace std;

class MyCalendarThree {
  map<int, int> m;

 public:
  MyCalendarThree() {}

  /*
  have a timeline like an array where an event [start, end) means a +1 at
  start and a -1 at end then when summing acrossing the timeline you
  can see how many events are at that specfic time.

  use a map to save space (still process time sequentially).
  k is just the maximum of the ongoing sum.

  */
  int book(int start, int end) {
    m[start]++;
    m[end]--;

    int k = 0, ongoing = 0;
    for (auto& p : m) {
      k = max(k, ongoing += p.second);
    }
    return k;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */

int main() { return 0; }
