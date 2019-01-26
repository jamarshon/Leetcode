
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
136. Single Number
Given an array of integers, every element appears twice except for one. Find
that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

/*
    Submission Date: 2017-06-29
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto e : nums) res ^= e;
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
137. Single Number II
Given an array of integers, every element appears three times except for one,
which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

/*
    Submission Date: 2017-08-02
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int one = 0, two = 0;
    for (auto num : nums) {
      int common_with_one = one & num;
      int common_with_two = two & num;

      two &= ~common_with_two;
      two |= common_with_one;

      one |= num;
      one &= ~common_with_one;
      one &= ~common_with_two;
    }

    return one;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
138. Copy List with Random Pointer
A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.

/*
    Submission Date: 2017-07-16
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
 public:
  RandomListNode* copyRandomList(RandomListNode* head) {
    if (head == NULL) return NULL;

    RandomListNode* curr = head;

    // create duplicate node after the original one
    while (curr) {
      RandomListNode* next = curr->next;
      curr->next = new RandomListNode(curr->label);
      curr->next->next = next;
      curr = next;
    }

    // set all the random ones as the original node's random is adjacent
    // to the duplicate random node
    curr = head;
    while (curr) {
      RandomListNode* random = curr->random;
      curr->next->random = (random == NULL) ? NULL : random->next;
      curr = curr->next->next;
    }

    // remove originals
    RandomListNode* original_head = new RandomListNode(INT_MIN);
    RandomListNode* original_cur = original_head;

    RandomListNode* copy_head = new RandomListNode(INT_MIN);
    RandomListNode* copy_curr = copy_head;

    curr = head;
    while (curr) {
      original_cur->next = curr;
      original_cur = original_cur->next;

      copy_curr->next = curr->next;
      copy_curr = copy_curr->next;

      curr = curr->next->next;
    }

    original_cur->next = NULL;
    head = original_head->next;
    delete original_head;

    copy_curr->next = NULL;
    RandomListNode* root = copy_head->next;
    delete copy_head;

    return root;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
139. Word Break
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, determine if s can be segmented into a space-separated sequence
of one or more dictionary words. You may assume the dictionary does not contain
duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<string, bool> memo;

 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    if (s.empty()) return true;

    if (memo.count(s)) return memo[s];

    for (string word : wordDict) {
      int word_len = word.size();
      string prefix = s.substr(0, word_len);
      if (prefix == word) {
        // we can take this word
        if (wordBreak(s.substr(word_len), wordDict)) {
          return memo[s] = true;
        }
      }
    }

    return memo[s] = false;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
140. Word Break II
Given a non-empty string s and a dictionary wordDict containing a list of
non-empty words, add spaces in s to construct a sentence where each word is a
valid dictionary word. You may assume the dictionary does not contain duplicate
words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set
of strings). Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-20
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  void convertLenToStr(int i, string s, string curr, vector<vector<int>>& dp,
                       vector<string>& res) {
    if (i == s.size()) {
      res.push_back(curr);
      return;
    }

    for (const int word_size : dp[i]) {
      string word = s.substr(i, word_size);
      string new_curr = curr.empty() ? word : curr + " " + word;
      convertLenToStr(i + word_size, s, new_curr, dp, res);
    }
  }
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    int N = s.size();
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    set<int> word_sizes;

    for (const string word : dict) word_sizes.insert(word.size());

    vector<vector<int>> dp(N + 1, vector<int>{});
    dp[N].push_back(INT_MAX);

    for (int j = N; j >= 0; j--) {
      if (dp[j].empty()) continue;
      for (const int word_size : word_sizes) {
        if (j - word_size < 0) break;
        string word = s.substr(j - word_size, word_size);
        // we store at dp[j-word_size] the word_size if it is a valid word and
        // it ends at a valid index meaning dp[j] isn't empty
        if (dict.count(word)) {
          dp[j - word_size].push_back(word_size);
        }
      }
    }

    vector<string> res;
    convertLenToStr(0, s, "", dp, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
141. Linked List Cycle
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    ListNode *slow, *fast;
    slow = fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) return true;
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
142. Linked List Cycle II
Given a linked list, return the node where the cycle begins. If there is no
cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

/*
    Submission Date: 2017-08-02
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
  ListNode* detectCycle2(ListNode* head) {
    ListNode *slow, *fast;
    slow = fast = head;

    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) {
        break;
      }
    }

    if (!(fast && fast->next)) return NULL;
    ListNode* temp = slow;
    int cycle_len = 0;
    do {
      temp = temp->next;
      cycle_len++;
    } while (temp != slow);

    // if a cycle has a length n, then the start is the mth last node when
    // list is unravelled without including duplicates
    ListNode *backward, *forward;
    backward = forward = head;
    for (int i = 0; i < cycle_len; i++) {
      forward = forward->next;
    }

    while (backward != forward) {
      backward = backward->next;
      forward = forward->next;
    }

    return forward;
  }

  ListNode* detectCycle(ListNode* head) {
    ListNode *slow, *fast;
    slow = fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;

      // m - distance from start to cycle start
      // n - cycle len
      // k - distance from cycle start to where slow meets fast
      // if d is distance, then fast moved twice as much distance as slow
      // for some positive integers (p and q) slow moved d = m + k + p*n
      // fast moved 2*d = m + k + q*n where p*n and q*n represents number of
      // times it looped the cycle. 2*(m + k + p*n) = m + k + q*n -> m + k = (q
      // - 2*p)*n this means if you pick any node in the cycle and iterate m + k
      // steps, you will reach the same place and looped the cycle q - 2*p
      // times. if you have fast at where slow met fast (m + k) and have slow at
      // start and move both one at a time, they will meet at the cycle start
      // because slow will have traveled m while fast will have traveled
      // (q-2*p)*n - k from k which means it is k away from where fast started
      // which is the cycle start
      if (slow == fast) {
        slow = head;
        while (slow != fast) {
          slow = slow->next;
          fast = fast->next;
        }

        return slow;
      }
    }

    return NULL;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
143. Reorder List
Given a singly linked list L: L0?L1?…?Ln-1?Ln,
reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

/*
    Submission Date: 2017-07-18
    Runtime: 59 ms
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
  void reorderList(ListNode* head) {
    // find midpoint
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* last_slow = slow;
    while (fast && fast->next) {
      last_slow = slow;
      slow = slow->next;
      fast = fast->next->next;
    }

    if (slow == fast) return;

    last_slow->next = NULL;

    // reverse the second half
    ListNode* prev = NULL;
    ListNode* curr = slow;
    ListNode* new_curr = curr->next;
    while (curr) {
      curr->next = prev;
      prev = curr;
      curr = new_curr;
      if (new_curr) new_curr = new_curr->next;
    }

    // merge first half and second half
    curr = prev;
    ListNode* new_head = NULL;
    new_curr = NULL;
    while (head) {
      new_head = head->next;
      new_curr = curr->next;

      head->next = curr;
      if (new_head) {
        curr->next = new_head;
      } else if (new_curr) {
        curr->next = new_curr;
      }

      head = new_head;
      curr = new_curr;
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
144. Binary Tree Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-07-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
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
  vector<int> preorderTraversal(TreeNode* root) {
    stack<TreeNode*> st{{root}};
    vector<int> res;
    while (!st.empty()) {
      TreeNode* top = st.top();
      st.pop();

      if (top == NULL) continue;
      res.push_back(top->val);
      st.push(top->right);
      st.push(top->left);
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
145. Binary Tree Postorder Traversal
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-08-02
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <algorithm>
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
  void storeReverse(TreeNode* curr, vector<int>& res) {
    int i = res.size();
    while (curr) {
      res.push_back(curr->val);
      curr = curr->right;
    }
    reverse(res.begin() + i, res.end());
  }
  vector<int> postorderTraversal(TreeNode* root) {
    TreeNode* dummy = new TreeNode(-1);
    dummy->left = root;

    vector<int> res;
    TreeNode* curr = dummy;
    while (curr) {
      if (curr->left) {
        // left exists so find predecessor
        TreeNode* pre = curr->left;
        while (pre->right && pre->right != curr) {
          pre = pre->right;
        }

        if (pre->right == NULL) {
          // apply threading and go left
          pre->right = curr;
          curr = curr->left;
        } else {
          // restore, print reverse from curr -> left to pre and go right
          pre->right = NULL;
          storeReverse(curr->left, res);
          curr = curr->right;
        }
      } else {
        // no left go right
        curr = curr->right;
      }
    }

    dummy->left = NULL;
    delete dummy;
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It
should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists
in the cache, otherwise return -1. put(key, value) - Set or insert the value if
the key is not already present. When the cache reached its capacity, it should
invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

/*
    Submission Date: 2017-07-14
    Runtime: 95 ms
    Difficulty: HARD
*/

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

struct LRUElement {
  int key, value;
  LRUElement(int _key, int _value) : key(_key), value(_value) {}
};

class LRUCache {
  list<LRUElement> linked_list_;  // back is just inserted or used recently
  unordered_map<int, list<LRUElement>::iterator> hash_table_;
  int capacity_;

  void moveToBack(int key) {
    auto it = hash_table_[key];

    LRUElement temp = *it;
    linked_list_.erase(it);
    linked_list_.push_back(temp);

    hash_table_[key] = --linked_list_.end();
  }

 public:
  LRUCache(int capacity) { capacity_ = capacity; }

  int get(int key) {
    if (!hash_table_.count(key)) return -1;

    // update in the linked_list
    moveToBack(key);

    // for(auto e: linked_list_) cout << e.value << endl;
    return linked_list_.back().value;
  }

  void put(int key, int value) {
    if (hash_table_.count(key)) {
      moveToBack(key);
      linked_list_.back().value = value;
    } else {
      if (linked_list_.size() == capacity_) {
        hash_table_.erase(linked_list_.begin()->key);
        linked_list_.erase(linked_list_.begin());
      }
      linked_list_.emplace_back(key, value);
      hash_table_[key] = --linked_list_.end();
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
147. Insertion Sort List
Sort a linked list using insertion sort.

/*
    Submission Date: 2017-07-14
    Runtime: 59 ms
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
  ListNode* insertionSortList(ListNode* head) {
    ListNode* dummy = new ListNode(INT_MIN);

    ListNode* curr = head;
    ListNode* insert = NULL;
    while (curr) {
      insert = dummy;
      while (insert->next && insert->next->val < curr->val) {
        insert = insert->next;
      }

      ListNode* new_curr = curr->next;
      ListNode* next = insert->next;
      insert->next = curr;
      curr->next = next;
      curr = new_curr;
    }

    head = dummy->next;
    dummy->next = NULL;
    delete dummy;
    return head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

/*
    Submission Date: 2017-07-21
    Runtime: 52 ms
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
  ListNode* sortList(ListNode* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;

    ListNode *slow, *fast, *last;
    slow = fast = head;
    while (fast && fast->next) {
      last = slow;
      slow = slow->next;
      fast = fast->next->next;
    }

    ListNode* head1 = head;
    ListNode* head2 = last->next;
    last->next = NULL;

    ListNode* curr1 = sortList(head1);
    ListNode* curr2 = sortList(head2);

    ListNode* merged = new ListNode(INT_MIN);
    ListNode* merged_head = merged;

    while (curr1 && curr2) {
      if (curr1->val < curr2->val) {
        merged->next = curr1;
        merged = merged->next;
        curr1 = curr1->next;
      } else {
        merged->next = curr2;
        merged = merged->next;
        curr2 = curr2->next;
      }
    }

    while (curr1) {
      merged->next = curr1;
      merged = merged->next;
      curr1 = curr1->next;
    }

    while (curr2) {
      merged->next = curr2;
      merged = merged->next;
      curr2 = curr2->next;
    }

    merged->next = NULL;
    merged = merged_head;
    merged_head = merged_head->next;
    delete merged;

    return merged_head;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie on the
same straight line.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
    Difficulty: HARD
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  int maxPoints(vector<Point>& points) {
    int N = points.size();

    int max_points = 0;

    for (int i = 0; i < N; i++) {
      int same_count = 0;
      map<pair<int, int>, int> m;

      for (int j = i; j < N; j++) {
        if (points[i].x == points[j].x && points[i].y == points[j].y) {
          same_count++;
          continue;
        }

        int dx = points[j].x - points[i].x;
        int dy = points[j].y - points[i].y;

        int gcd_dx_dy = gcd(dx, dy);

        pair<int, int> p{dx / gcd_dx_dy, dy / gcd_dx_dy};
        m[p]++;
      }

      for (auto kv : m) max_points = max(kv.second + same_count, max_points);
      max_points = max(max_points, same_count);
    }

    return max_points;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
150. Evaluate Reverse Polish Notation
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another
expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

/*
    Submission Date: 2017-07-18
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  unordered_map<string, function<int(int, int)>> binop{
      {"*", [](const int& a, const int& b) { return a * b; }},
      {"+", [](const int& a, const int& b) { return a + b; }},
      {"-", [](const int& a, const int& b) { return a - b; }},
      {"/", [](const int& a, const int& b) { return a / b; }},
  };
  bool isNumber(string s) {
    return any_of(s.begin(), s.end(),
                  [](const char& c) -> bool { return isdigit(c); });
  }
  int evalRPN(vector<string>& tokens) {
    if (tokens.empty()) return 0;

    stack<int> st;
    int a, b;
    for (auto token : tokens) {
      if (isNumber(token)) {
        st.push(stoi(token));
      } else {
        b = st.top();
        st.pop();
        a = st.top();
        st.pop();
        st.push(binop[token](a, b));
      }
    }
    return st.top();
  }
};

int main() {
  Solution s;
  return 0;
}