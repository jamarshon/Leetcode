
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
16. 3Sum Closest
Given an array S of n integers, find three integers in S such that the sum is
closest to a given number, target. Return the sum of the three integers. You may
assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


/*
    Submission Date: 2017-06-18
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    int len = nums.size();
    sort(nums.begin(), nums.end());

    int closest = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < len; i++) {
      int low = i + 1;
      int high = len - 1;
      int curr_target = target - nums[i];
      while (low < high) {
        int curr_closest = nums[i] + nums[low] + nums[high];
        if (abs(target - curr_closest) < abs(target - closest)) {
          closest = curr_closest;
        }

        if (nums[low] + nums[high] == curr_target) {
          return target;
        } else if (nums[low] + nums[high] < curr_target) {
          low++;
        } else {
          high--;
        }
      }
    }
    return closest;
  }
};
int main() {
  Solution s;
  vector<int> v1{0, 0, 0};
  vector<int> v2{-1, 2, 1, -4};
  vector<int> v3{1, 2, 4, 8, 16, 32, 64, 128};
  vector<int> v4{-55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33};
  vector<int> v5{
      43,  75,  -90, 47,  -49, 72,  17,  -31, -68, -22, -21, -30, 65,  88,  -75,
      23,  97,  -61, 53,  87,  -3,  33,  20,  51,  -79, 43,  80,  -9,  34,  -89,
      -7,  93,  43,  55,  -94, 29,  -32, -49, 25,  72,  -6,  35,  53,  63,  6,
      -62, -96, -83, -73, 66,  -11, 96,  -90, -27, 78,  -51, 79,  35,  -63, 85,
      -82, -15, 100, -82, 1,   -4,  -41, -21, 11,  12,  12,  72,  -82, -22, 37,
      47,  -18, 61,  60,  55,  22,  -6,  26,  -60, -42, -92, 68,  45,  -1,  -26,
      5,   -56, -1,  73,  92,  -55, -20, -43, -56, -15, 7,   52,  35,  -90, 63,
      41,  -55, -58, 46,  -84, -92, 17,  -66, -23, 96,  -19, -44, 77,  67,  -47,
      -48, 99,  51,  -25, 19,  0,   -13, -88, -10, -67, 14,  7,   89,  -69, -83,
      86,  -70, -66, -38, -50, 66,  0,   -67, -91, -65, 83,  42,  70,  -6,  52,
      -21, -86, -87, -44, 8,   49,  -76, 86,  -3,  87,  -32, 81,  -58, 37,  -55,
      19,  -26, 66,  -89, -70, -69, 37,  0,   19,  -65, 38,  7,   3,   1,   -96,
      96,  -65, -52, 66,  5,   -3,  -87, -16, -96, 57,  -74, 91,  46,  -79, 0,
      -69, 55,  49,  -96, 80,  83,  73,  56,  22,  58,  -44, -40, -45, 95,  99,
      -97, -22, -33, -92, -51, 62,  20,  70,  90};
  cout << s.threeSumClosest(v1, 1) << endl;
  cout << s.threeSumClosest(v2, 1) << endl;
  cout << s.threeSumClosest(v3, 82) << endl;
  cout << s.threeSumClosest(v4, 0) << endl;
  cout << s.threeSumClosest(v5, 284) << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
17. Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number
could represent.

A mapping of digit to letters (just like on the telephone buttons) is given
below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

/*
    Submission Date: 2016-11-29
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;

#include <unordered_map>
#include <vector>

class Solution {
 private:
  unordered_map<char, vector<char>> LETTER_DIGIT_MAP = {
      {'2', {'a', 'b', 'c'}}, {'3', {'d', 'e', 'f'}},
      {'4', {'g', 'h', 'i'}}, {'5', {'j', 'k', 'l'}},
      {'6', {'m', 'n', 'o'}}, {'7', {'p', 'q', 'r', 's'}},
      {'8', {'t', 'u', 'v'}}, {'9', {'w', 'x', 'y', 'z'}}};

 public:
  vector<string> letterCombinations(string digits) {
    if (digits == "") {
      return {};
    }
    vector<string> result = {""};
    for (char digit : digits) {
      vector<char> letters = LETTER_DIGIT_MAP[digit];
      vector<string> temp = {};
      for (char letter : letters) {
        for (string str : result) {
          temp.push_back(str + letter);
        }
      }
      result = temp;
    }
    return result;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
18. 4Sum
Given an array S of n integers, are there elements a, b, c, and d in S such that
a + b + c + d = target? Find all unique quadruplets in the array which gives the
sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

/*
    Submission Date: 2017-06-19
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());

    int len = nums.size();
    vector<vector<int>> res;

    for (int i = 0; i < len; i++) {
      if (nums[i] > 0 && nums[i] > target) break;
      if (i != 0 && nums[i] == nums[i - 1]) continue;
      for (int j = i + 1; j < len; j++) {
        if (j != i + 1 && nums[j] == nums[j - 1]) continue;
        int low = j + 1;
        int high = len - 1;
        int curr_target = target - nums[i] - nums[j];
        while (low < high) {
          if (nums[low] + nums[high] == curr_target) {
            res.push_back({nums[i], nums[j], nums[low], nums[high]});
            while (++low < high && nums[low] == nums[low - 1]) {
            }
          } else if (nums[low] + nums[high] > curr_target) {
            high--;
          } else {
            low++;
          }
        }
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
19. Remove Nth Node From End of List
Given a linked list, remove the nth node from the end of list and return its
head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes
1->2->3->5. Note: Given n will always be valid. Try to do this in one pass.

/*
    Submission Date: 2017-05-20
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* current = head;
    ListNode* forward = head;
    for (int i = 0; i < n + 1; i++) {
      // Delete head
      if (forward == NULL) {
        ListNode* new_head = head->next;
        delete head;
        return new_head;
      }
      forward = forward->next;
    }

    // We assume deleted node is not the head
    while (forward != NULL) {
      current = current->next;
      forward = forward->next;
    }

    // Delete node at current
    ListNode* next_next_node = current->next->next;
    delete current->next;
    current->next = next_next_node;
    return head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
20. Valid Parentheses
Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid
but "(]" and "([)]" are not.

/*
    Submission Date: 2017-01-20
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <stack>
#include <unordered_map>

class Solution {
 public:
  unordered_map<char, char> MAP = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  bool isValid(string s) {
    stack<char> st;
    char topChar;
    for (char c : s) {
      if (c == ')' || c == '}' || c == ']') {
        if (st.empty()) return false;
        topChar = st.top();
        st.pop();
        if (MAP[topChar] != c) return false;
      } else {
        st.push(c);
      }
    }

    return st.empty();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
21. Merge Two Sorted Lists
Merge two sorted linked lists and return it as a new list. The new list should
be made by splicing together the nodes of the first two lists.

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
*/
using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* head = new ListNode(-1);
    ListNode* tail = head;
    while (l1 != NULL && l2 != NULL) {
      if (l1->val > l2->val) {
        tail->next = l2;
        l2 = l2->next;
      } else {
        tail->next = l1;
        l1 = l1->next;
      }
      tail = tail->next;
    }

    tail->next = (l1 != NULL) ? l1 : l2;

    return head->next;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>

class Solution {
 private:
  void generateParenthesis(const int& n, const int& left, const int& right,
                           const string& current, vector<string>& result) {
    if (left == n && right == n) {
      result.push_back(current);
      return;
    }
    if (right > left) return;
    if (left > n || right > n) return;
    generateParenthesis(n, left + 1, right, current + "(", result);
    generateParenthesis(n, left, right + 1, current + ")", result);
  }

 public:
  vector<string> generateParenthesis(int n) {
    vector<string> result;
    generateParenthesis(n, 0, 0, "", result);
    return result;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
23. Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list. Analyze and
describe its complexity.
/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  // O(KN) where K is the number of lists and N is the maximum number of
  // elements in a list
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* dummy = new ListNode(-1);
    ListNode* current = dummy;

    while (true) {
      int min_node_ind = -1;
      for (int i = 0, K = lists.size(); i < K; i++) {
        if (lists[i] == NULL) continue;
        if (min_node_ind == -1) {
          min_node_ind = i;
        } else if (lists[min_node_ind]->val > lists[i]->val) {
          min_node_ind = i;
        }
      }

      if (min_node_ind == -1) break;

      current->next = lists[min_node_ind];
      lists[min_node_ind] = lists[min_node_ind]->next;

      if (lists[min_node_ind] == NULL)
        lists.erase(lists.begin() + min_node_ind);

      current = current->next;
      current->next = NULL;
    }

    ListNode* head = dummy->next;
    delete dummy;
    return head;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
24. Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in
the list, only nodes itself can be changed.

/*
    Submission Date: 2017-07-21
    Runtime: 3 ms
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
  ListNode* swapPairs(ListNode* head) {
    ListNode* a = head;
    ListNode* b;
    ListNode* newHead = new ListNode(-1);
    ListNode* prev = newHead;
    prev->next = a;

    while (a != NULL && a->next != NULL) {
      b = a->next;
      prev->next = b;
      prev = a;
      a->next = b->next;
      b->next = a;
      a = a->next;
    }

    return newHead->next;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
25. Reverse Nodes in k-Group
Given a linked list, reverse the nodes of a linked list k at a time and return
its modified list.

k is a positive integer and is less than or equal to the length of the linked
list. If the number of nodes is not a multiple of k then left-out nodes in the
end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

/*
    Submission Date: 2017-01-08
    Runtime: 22 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  void incrementalReverse(ListNode*& A, ListNode*& B, ListNode*& C) {
    B->next = A;
    A = B;
    B = C;
    if (C != NULL) {
      C = C->next;
    }
  }

  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k < 0 || head == NULL) return NULL;
    if (k == 1) return head;

    ListNode* newHead = NULL;
    ListNode* A = NULL;
    ListNode* B = head;
    ListNode* C = head->next;
    ListNode* lastInterval = head;
    ListNode* nextInterval = head;

    int i = k;

    while (i--) {
      if (nextInterval == NULL) {
        return head;
      }
      nextInterval = nextInterval->next;
    }

    while (true) {
      while (B != nextInterval) incrementalReverse(A, B, C);
      if (newHead == NULL) newHead = A;

      A = nextInterval;
      B = (A == NULL) ? NULL : A->next;
      C = (B == NULL) ? NULL : B->next;

      i = k;
      while (i--) {
        if (nextInterval == NULL) {
          lastInterval->next = A;
          return newHead;
        } else {
          if (i == 0) lastInterval->next = nextInterval;
          nextInterval = nextInterval->next;
        }
      }

      lastInterval = A;
      lastInterval->next = NULL;
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
26. Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element
appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with
constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums
being 1 and 2 respectively. It doesn't matter what you leave beyond the new
length.

/*
    Submission Date: 2017-01-22
    Runtime: 48 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int i = 0, j = 1, len = nums.size();
    if (len == 0) return 0;

    while (true) {
      while (j < len && nums[i] == nums[j]) j++;
      if (j == len) return i + 1;
      swap(nums[++i], nums[j++]);
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
27. Remove Element
Given an array and a value, remove all instances of that value in place and
return the new length.

Do not allocate extra space for another array, you must do this in place with
constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond
the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums
being 2.

/*
    Submission Date: 2017-01-25
    Runtime: 6 ms
    Difficulty: EASY
*/

using namespace std;
#include <vector>

class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    int len = nums.size();
    int low = 0;
    int high = len - 1;

    while (low < high) {
      if (nums[low] == val) {
        swap(nums[low], nums[high]);
        high--;
      } else {
        low++;
      }
    }

    int i = 0, result = 0;
    while (i < len && nums[i++] != val) result++;
    return result;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
28. Implement strStr()
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle
is not part of haystack.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int strStr(string haystack, string needle) {
    int hLen = haystack.size();
    int nLen = needle.size();
    if (nLen == 0) return 0;
    if (nLen == hLen) return haystack == needle ? 0 : -1;
    if (nLen > hLen) return -1;

    vector<int> start;
    int i = 0, j = 0;

    while (i < hLen) {
      if (haystack[i] == needle[0]) start.push_back(i);
      i++;
    }

    for (int index : start) {
      i = index;
      j = 0;
      while (i < hLen && j < nLen) {
        if (haystack[i] != needle[j]) break;
        i++;
        j++;
      }
      if (j == nLen) {
        return index;
      }
    }

    return -1;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
29. Divide Two Integers
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

/*
    Submission Date: 2017-06-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <climits>
#include <iostream>

using namespace std;

class Solution {
 public:
  int divide(int dividend, int divisor) {
    if (dividend == 0) return 0;
    if (divisor == 0) return INT_MAX;
    if (dividend == INT_MIN && divisor == -1)
      return INT_MAX;  // INT_MIN/-1 overflow

    int sign = ((divisor < 0) ^ (dividend < 0)) ? -1 : 1;

    // make both negative as range is larger
    if (divisor > 0) divisor = -divisor;
    if (dividend > 0) dividend = -dividend;
    if (divisor < dividend) return 0;

    int count = 0;
    for (int i = 31; i >= 0; i--) {
      // maintain (divisor << i) >= INT_MIN
      if (divisor >= INT_MIN >> i) {
        int divisor_shift = divisor << i;
        // check if (divisor << (i+1)) < dividend < (divisor << i)  then i can
        // be used in the result
        if (divisor_shift >= dividend) {
          count += 1 << i;
          dividend -= divisor_shift;
          if (dividend == 0) {
            break;
          }
        }
      }
    }

    return sign * count;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
30. Substring with Concatenation of All Words
You are given a string, s, and a list of words, words, that are all of the same
length. Find all starting indices of substring(s) in s that is a concatenation
of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: HARD
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    int num_words = words.size();
    int K = words.front().size();
    int N = s.size();
    int target_count = words.size();

    unordered_map<string, int> freq;
    map<int, string> m;

    // store frequency of the words
    for (string word : words) {
      freq[word]++;
    }

    // associate substrings with each index
    for (int i = 0; i < N - K + 1; i++) {
      string sub = s.substr(i, K);
      if (freq.count(sub)) {
        m[i] = sub;
      }
    }

    vector<int> res;
    for (int i = 0; i < K; i++) {
      // hop K from i keep track of longest
      int start = i;
      int curr = i;
      int count = 0;
      unordered_map<string, int> not_seen(freq);

      while (curr < N) {
        // no string from words is at this index
        if (m.find(curr) == m.end()) {
          not_seen = freq;
          while (curr < N && m.find(curr) == m.end()) {
            curr += K;
          }
          count = 0;
          start = curr;
        }

        if (curr >= N) break;

        string s = m.find(curr)->second;

        // the word occured more times than needed so keep removing from start
        while (not_seen[s] == 0 && start < min(N, curr)) {
          string next = m.find(start)->second;
          not_seen[next]++;
          count--;
          start += K;
        }

        // increase the longest length if the frequency of the word is greater
        // than zero
        if (not_seen[s] > 0) {
          not_seen[s]--;
          count++;
          if (count == target_count) {
            res.push_back(start);
          }
        }

        curr += K;
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
31. Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically
next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible
order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding
outputs are in the right-hand column. 1,2,3 → 1,3,2 3,2,1 → 1,2,3 1,1,5 → 1,5,1

/*
    Submission Date: 2017-01-24
    Runtime: 13 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int len = nums.size();
    if (len <= 1) return;

    // starting from the right find any elements that are after it that are
    // larger than it if there is, swap them and sort in descending order all
    // the elements after it
    int i = len - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) i--;

    int offset;
    if (i == -1) {
      offset = 0;
    } else {
      int j = len - 1;
      while (nums[i] >= nums[j]) j--;
      swap(nums[i], nums[j]);
      offset = i + 1;
    }

    reverse(nums.begin() + offset, nums.end());
  }
};

int main() {
  Solution s;
  vector<int> v{1, 5, 1};
  s.nextPermutation(v);
  return 0;
}