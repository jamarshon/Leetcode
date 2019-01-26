
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
76. Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain
all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the
empty string "".

If there are multiple such windows, you are guaranteed that there will always be
only one unique minimum window in S.

/*
    Submission Date: 2017-06-23
    Runtime: 86 ms
    Difficulty: HARD
*/

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    list<int> l;
    unordered_map<char, list<list<int>::iterator>> m;
    unordered_map<char, int> dict;

    for (auto c : t) dict[c]++;

    int len = s.size();
    int target = t.size();
    string res = "";

    for (int i = 0; i < len; i++) {
      // check if current character is in t
      if (dict.count(s[i])) {
        auto it = m.find(s[i]);

        // check if there is a list for this letter
        if (it != m.end()) {
          list<list<int>::iterator>& list_of_list_it = it->second;
          // if there is a list and its size is same as the frequency we must
          // remove the first element from the list and the iterator from the
          // map
          if (list_of_list_it.size() == dict[s[i]]) {
            list<int>::iterator to_erase = list_of_list_it.front();
            l.erase(to_erase);
            list_of_list_it.pop_front();
          }
        }

        // add the index to the list and the iterator to the map
        l.push_back(i);

        list<int>::iterator l_it = l.end();
        m[s[i]].push_back(--l_it);

        // if there is enough letters (indices in the list) compare with result
        if (l.size() == target) {
          string sub = s.substr(l.front(), i - l.front() + 1);
          if (res.empty() || sub.size() < res.size()) res = sub;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
77. Combinations
Given two integers n and k, return all possible combinations of k numbers out of
1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

/*
    Submission Date: 2017-07-08
    Runtime: 73 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void combine(vector<int>& curr, vector<vector<int>>& res, int start, int n,
               int k) {
    if (curr.size() == k) {
      res.push_back(curr);
      return;
    }

    for (int i = start; i <= n; i++) {
      curr.push_back(i);
      combine(curr, res, i + 1, n, k);
      curr.pop_back();
    }
  }
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> curr;
    combine(curr, res, 1, n, k);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
78. Subsets
Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

/*
    Submission Date: 2017-07-08
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void subsets(vector<int>& curr, vector<int>& nums, vector<vector<int>>& res,
               int index) {
    res.push_back(curr);

    for (int i = index; i < nums.size(); i++) {
      curr.push_back(nums[i]);
      subsets(curr, nums, res, i + 1);
      curr.pop_back();
    }
  }
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> curr;
    vector<vector<int>> res;
    subsets(curr, nums, res, 0);
    return res;
  }
};
int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
79. Word Search
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
/*
    Submission Date: 2017-06-23
    Runtime: 119 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  bool exist(vector<vector<char>>& board, vector<pair<int, int>>& offset,
             string word, string curr, int row, int col, int M, int N) {
    if (curr == word) return true;
    char c = word[curr.size()];

    for (auto p : offset) {
      int new_row = row + p.first;
      int new_col = col + p.second;
      if (new_row >= 0 && new_row < M && new_col >= 0 && new_col < N) {
        if (board[new_row][new_col] == c) {
          board[new_row][new_col] = '\0';
          if (exist(board, offset, word, curr + c, new_row, new_col, M, N)) {
            board[new_row][new_col] = c;
            return true;
          }
          board[new_row][new_col] = c;
        }
      }
    }
    return false;
  }

 public:
  bool exist(vector<vector<char>>& board, string word) {
    int M = board.size();

    if (M == 0) return false;
    int N = board[0].size();

    vector<pair<int, int>> offset{{-1, 0}, {0, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (exist(board, offset, word, "", i, j, M, N)) return true;
      }
    }
    return false;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
80. Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums
being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int N = nums.size();

    if (N == 0) return 0;

    int write_idx = 0;
    for (int i = 0; i < N;) {
      int start = i;
      int start_el = nums[start];
      while (i < N && nums[start] == nums[i]) {
        i++;
      }

      int occurences = min(i - start, 2);
      while (occurences--) {
        nums[write_idx++] = start_el;
      }
    }

    return write_idx;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
81. Search in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

/*
    Submission Date: 2017-08-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (nums[mid] == target) return true;

      if (nums[low] < nums[mid]) {  // first half is sorted
        if (nums[low] <= target && target < nums[mid]) {
          high = mid - 1;
        } else {
          low = mid + 1;
        }
      } else if (nums[low] > nums[mid]) {  // second half is sorted
        if (nums[mid] < target && target <= nums[high]) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      } else {  // ambiguous (worst case is O(n))
        low++;
      }
    }
    return false;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
82. Remove Duplicates from Sorted List II
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

/*
    Submission Date: 2017-06-22
    Runtime: 9 ms
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
  ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL) return NULL;

    ListNode* dummy = new ListNode(-1);

    dummy->next = head;

    ListNode* prev = dummy;

    ListNode* current = head;
    ListNode* write_node = head;
    while (current) {
      while (current && current->val == write_node->val) {
        current = current->next;
      }

      if (write_node->next == current) {
        prev = write_node;
        write_node = write_node->next;
      } else {
        ListNode* temp;
        while (write_node != current) {
          temp = write_node;
          write_node = write_node->next;
          delete temp;
        }

        prev->next = current;
      }
    }

    ListNode* new_head = dummy->next;
    delete dummy;
    return new_head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
83. Remove Duplicates from Sorted List
Given a sorted linked list, delete all duplicates such that each element appear
only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

/*
    Submission Date: 2017-06-22
    Runtime: 9 ms
    Difficulty: EASY
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
  ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL) return NULL;

    ListNode* new_head = head;
    ListNode* current = head;
    ListNode* write_node = head;
    while (current) {
      while (current && current->val == write_node->val) {
        current = current->next;
      }

      if (current == NULL) {
        // delete remaining
        ListNode* to_delete = write_node->next;
        write_node->next = NULL;
        ListNode* temp;
        while (to_delete) {
          temp = to_delete;
          to_delete = to_delete->next;
          delete temp;
        }
      } else {
        write_node = write_node->next;
        write_node->val = current->val;
      }
    }

    return new_head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
84. Largest Rectangle in Histogram
Given n non-negative integers representing the histogram's bar height where the
width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

/*
    Submission Date: 2017-08-01
    Runtime: 19 ms
    Difficulty: HARD
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestRectangleArea2(vector<int>& heights) {
    stack<int> st;
    heights.push_back(0);
    int max_area = 0;
    // maintain increasing height stack
    // if current height (heights[i]) is less than last element in stack,
    // last element st[j] is bounded by heights[i] so the width is
    // i - 1 (right_boundary) - st[j-1] (left boundary) and area is
    // width*heights[st[j]] keep removing elements of stack until reach smaller
    // height which allows height[i] to be added to stack if stack is empty it
    // means st[j] is not bounded on the left (minimum of heights from 0 to
    // st[j]) so it is just i - 1 - (-1) which is i
    for (int i = 0, len = heights.size(); i < len; i++) {
      if (st.empty() || heights[i] >= heights[st.top()]) {
        st.push(i);
      } else {
        while (true) {
          int top_ind = st.top();
          st.pop();
          int curr_area = st.empty() ? i * heights[top_ind]
                                     : (i - st.top() - 1) * heights[top_ind];
          max_area = max(max_area, curr_area);
          if (st.empty() || heights[i] >= heights[st.top()]) {
            st.push(i);
            break;
          }
        }
      }
    }

    heights.pop_back();
    return max_area;
  }

  int largestRectangleArea(vector<int>& heights) {
    // at index i the area would be heights[i]*(the first index smaller than
    // heights[i] on the right - the first index smaller than heights[i] on the
    // left - 1) for example in {2,1,5,6,2,3} the area at index 2 would be
    // 5*(index of 2 - index of 1) 5*(4-1-1) = 10

    // to construct left and right in linear time we can take advantage of the
    // fact of jumps. for example 4, 200, 100, 10, 5 the left of 10 is 4 as it
    // is the first number smaller to it when moving left that is left[3] = 0
    // since 10 is greater than 5, we just need to compare 5 with elements
    // smaller than 10 so skip 100, 200 by using left array to find the first
    // number smaller than 10 which is 4
    int N = heights.size();
    vector<int> left(N), right(N);
    for (int i = 0; i < N; i++) {
      int index = i - 1;
      while (index >= 0 && heights[index] >= heights[i]) {
        index = left[index];
      }
      left[i] = index;
    }

    for (int i = N - 1; i >= 0; i--) {
      int index = i + 1;
      while (index < N && heights[index] >= heights[i]) {
        index = right[index];
      }
      right[i] = index;
    }

    int max_area = 0;
    for (int i = 0; i < N; i++) {
      max_area = max(max_area, heights[i] * (right[i] - left[i] - 1));
    }

    return max_area;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
85. Maximal Rectangle
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();

    int area = 0;
    int curr;
    vector<int> height(num_cols, 0);
    vector<int> left(num_cols, 0);
    vector<int> right(num_cols, num_cols);
    for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++) {
        if (matrix[i][j] == '1')
          height[j]++;
        else
          height[j] = 0;
      }

      // curr reprsent 1 + index of most recent zero seen from left
      curr = 0;
      for (int j = 0; j < num_cols; j++) {
        if (matrix[i][j] == '1')
          left[j] = max(curr, left[j]);
        else {
          curr = j + 1;
          left[j] = 0;
        }
      }

      // curr represents index of most recent zero seen from right
      curr = num_cols;
      for (int j = num_cols - 1; j >= 0; j--) {
        if (matrix[i][j] == '1')
          right[j] = min(curr, right[j]);
        else {
          curr = j;
          right[j] = num_cols;
        }
      }

      for (int j = 0; j < num_cols; j++) {
        area = max(area, (right[j] - left[j]) * height[j]);
      }
    }
    return area;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
86. Partition List
Given a linked list and a value x, partition it such that all nodes less than x
come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two
partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
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
  ListNode* partition(ListNode* head, int x) {
    ListNode less_head(-1);
    ListNode great_eq_head(-1);

    ListNode* less_curr = &less_head;
    ListNode* great_eq_curr = &great_eq_head;

    ListNode* curr = head;
    while (curr) {
      if (curr->val < x) {
        less_curr->next = curr;
        less_curr = less_curr->next;
      } else {
        great_eq_curr->next = curr;
        great_eq_curr = great_eq_curr->next;
      }
      curr = curr->next;
    }

    great_eq_curr->next = NULL;
    less_curr->next = great_eq_head.next;
    return less_head.next;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
87. Scramble String
Given a string s1, we may represent it as a binary tree by partitioning it to
two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two
children.

For example, if we choose the node "gr" and swap its two children, it produces a
scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it
produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled
string of s1.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

struct PairHash {
  size_t operator()(const pair<string, string>& p) const {
    hash<string> string_hash;
    return string_hash(p.first) ^ (string_hash(p.second) >> 1);
  }
};

class Solution {
  unordered_map<pair<string, string>, bool, PairHash> m;

 public:
  bool isScramble(string s1, string s2) {
    pair<string, string> p{s1, s2};

    if (m.count(p)) return m[p];

    int N = s1.size();
    int M = s2.size();

    assert(M == N);
    if (N == 0) return true;
    if (N == 1) return s1 == s2;

    int freq[26] = {0};
    for (int i = 0; i < N; i++) {
      freq[s1[i] - 'a']++;
      freq[s2[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
      if (freq[i] != 0) return m[p] = false;
    }

    for (int i = 0; i < N - 1; i++) {
      if (isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) &&
          isScramble(s1.substr(i + 1), s2.substr(i + 1))) {
        return m[p] = true;
      }
      if (isScramble(s1.substr(N - i - 1), s2.substr(0, i + 1)) &&
          isScramble(s1.substr(0, N - i - 1), s2.substr(i + 1))) {
        return m[p] = true;
      }
    }

    return m[p] = false;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
88. Merge Sorted Array
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one
sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m +
n) to hold additional elements from nums2. The number of elements initialized in
nums1 and nums2 are m and n respectively.

/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int write_idx = m + n - 1;

    while (i >= 0 && j >= 0) {
      if (nums1[i] > nums2[j]) {
        nums1[write_idx--] = nums1[i--];
      } else {
        nums1[write_idx--] = nums2[j--];
      }
    }

    while (j >= 0) {
      nums1[write_idx--] = nums2[j--];
    }
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
89. Gray Code

The gray code is a binary numeral system where two successive values differ in
only one bit.

Given a non-negative integer n representing the total number of bits in the
code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above
definition.

For now, the judge is able to judge based on one instance of gray code sequence.
Sorry about that.

/*
    Submission Date: 2017-06-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> grayCode(int n) {
    if (n == 0) return {0};

    vector<int> prev = grayCode(n - 1);

    for (int i = prev.size() - 1; i >= 0; i--) {
      prev.push_back(prev[i] + (1 << (n - 1)));
    }

    return prev;
  }
};

int main() {
  Solution s;
  vector<int> t = s.grayCode(2);
  for (auto e : t) cout << bitset<3>(e).to_string() << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all
possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

/*
    Submission Date: 2017-06-25
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void print(vector<T> v) {
  for (auto e : v) cout << e << ' ';
  cout << endl;
}

template <typename T>
void print2(vector<vector<T>> v) {
  for (auto v2 : v) print(v2);
}

class Solution {
 public:
  void subsetsWithDupHelper(vector<int>& nums, vector<int>& curr, int index,
                            vector<vector<int>>& res) {
    res.push_back(curr);

    for (int i = index; i < nums.size(); i++) {
      if (i == index || nums[i] != nums[i - 1]) {
        curr.push_back(nums[i]);
        subsetsWithDupHelper(nums, curr, i + 1, res);
        curr.pop_back();
      }
    }
  }
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> curr;
    sort(nums.begin(), nums.end());
    subsetsWithDupHelper(nums, curr, 0, res);
    return res;
  }
};

int main() {
  Solution s;
  vector<int> v;
  v = {1, 2, 2};
  vector<vector<int>> v2 = s.subsetsWithDup(v);
  print2(v2);
  return 0;
}