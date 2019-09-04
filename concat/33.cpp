
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
733. Flood Fill
An image is represented by a 2-D array of integers, each integer representing
the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of
the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels
connected 4-directionally to the starting pixel of the same color as the
starting pixel, plus any pixels connected 4-directionally to those pixels (also
with the same color as the starting pixel), and so on. Replace the color of all
of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels
connected by a path of the same color as the starting pixel are colored with the
new color. Note the bottom corner is not colored 2, because it is not
4-directionally connected to the starting pixel. Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc <
image[0].length. The value of each color in image[i][j] and newColor will be an
integer in [0, 65535].
/*
    Submission Date: 2018-06-08
    Runtime: 57 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

 public:
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int newColor) {
    if (image.empty()) return {};
    queue<pair<int, int>> q;
    unordered_set<string> visited;

    int N = image.size();
    int M = image[0].size();
    int original_color = image[sr][sc];

    q.emplace(sr, sc);
    visited.insert(to_string(sr) + "," + to_string(sc));
    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();
      image[p.first][p.second] = newColor;

      for (int k = 0; k < 4; k++) {
        int new_row = p.first + dy[k];
        int new_col = p.second + dx[k];
        if (0 <= new_row && new_row < N && 0 <= new_col && new_col < M &&
            image[new_row][new_col] == original_color) {
          string key = to_string(new_row) + "," + to_string(new_col);
          if (!visited.count(key)) {
            q.emplace(new_row, new_col);
            visited.insert(key);
          }
        }
      }
    }

    return image;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
739. Daily Temperatures
Given a list of daily temperatures, produce a list that, for each day in the
input, tells you how many days you would have to wait until a warmer
temperature.  If there is no future day for which this is possible, put 0
instead.

For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73],
your output should be [1, 1, 4, 2, 1, 1, 0, 0].


Note:
The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].

/*
    Submission Date: 2018-06-30
    Runtime: 250 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  stk keeps an increasing temperatures to the right (represented as indices)
  while stk isn't emtpy and the current element is greater than the smallest
  element (ie stk top) pop the stk, basically it means this element replaces all
  the smaller elements as it will be closer to the next element while still
  being greater
  */
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> stk;
    int N = temperatures.size();
    vector<int> res(N, 0);
    for (int i = N - 1; i >= 0; i--) {
      while (!stk.empty() && temperatures[stk.top()] <= temperatures[i])
        stk.pop();
      res[i] = stk.empty() ? 0 : stk.top() - i;
      stk.push(i);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
743. Network Delay Time
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w),
where u is the source node, v is the target node, and w is the time it takes for
a signal to travel from source to target.

Now, we send a signal from a certain node K.  How long will it take for all
nodes to receive the signal?  If it is impossible, return -1.

Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
 public:
  typedef pair<int, int> pii;
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    vector<vector<pii>> edges(N);
    K--;
    for (auto& v : times) {
      edges[v[0] - 1].emplace_back(v[2], v[1] - 1);
    }

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, K);
    vector<int> dist(N, INT_MAX);
    dist[K] = 0;
    int cnt = 0;
    while (cnt < N && !q.empty()) {
      int weight, node;

      tie(weight, node) = q.top();
      q.pop();

      if (dist[node] == INT_MAX) break;
      if (dist[node] < weight) continue;
      cnt++;

      for (pii& n : edges[node]) {
        if (dist[n.second] == INT_MAX ||
            dist[node] + n.first < dist[n.second]) {
          dist[n.second] = dist[node] + n.first;
          q.emplace(dist[n.second], n.second);
        }
      }
    }
    int res = *max_element(dist.begin(), dist.end());
    return res == INT_MAX ? -1 : res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
744. Find Smallest Letter Greater Than Target
Given a list of sorted characters letters containing only lowercase letters, and
given a target letter target, find the smallest element in the list that is
larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters
= ['a', 'b'], the answer is 'a'.

Examples:
Input:
letters = ["c", "f", "j"]
target = "a"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "c"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "d"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "g"
Output: "j"

Input:
letters = ["c", "f", "j"]
target = "j"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "k"
Output: "c"
Note:
letters has a length in range [2, 10000].
letters consists of lowercase letters, and contains at least 2 unique letters.
target is a lowercase letter.
/*
    Submission Date: 2018-06-08
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  char nextGreatestLetter(vector<char>& letters, char target) {
    int low = 0;
    int high = letters.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (letters[mid] > target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    if (low == letters.size()) return letters[0];
    return letters[low];
  }
};

int main() { return 0; }