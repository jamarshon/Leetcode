
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
925. Long Pressed Name
Your friend is typing his name into a keyboard.  Sometimes, when typing a
character c, the key might get long pressed, and the character will be typed 1
or more times.

You examine the typed characters of the keyboard.  Return True if it is possible
that it was your friends name, with some characters (possibly none) being long
pressed.

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.

Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed
output.

Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true

Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.

Note:

  name.length <= 1000
  typed.length <= 1000
  The characters of name and typed are lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isLongPressedName(string name, string typed) {
    int n = name.size();
    int m = typed.size();
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
      if (name[i] != typed[j]) return false;
      int new_i = i;
      int new_j = j;
      while (new_i < n && name[i] == name[new_i]) new_i++;
      while (new_j < m && typed[j] == typed[new_j]) new_j++;

      int name_cnt = new_i - i + 1;
      int typed_cnt = new_j - j + 1;

      if (typed_cnt < name_cnt) return false;
      i = new_i;
      j = new_j;
    }

    return i == n && j == m;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
929. Unique Email Addresses
Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is
the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an
email address, mail sent there will be forwarded to the same address without
dots in the local name.  For example, "alice.z@leetcode.com" and
"alicez@leetcode.com" forward to the same email address.  (Note that this rule
does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign
will be ignored. This allows certain emails to be filtered, for
example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule
does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many
different addresses actually receive mails? 

Example 1:

Input:
["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually
receive mails

Note:

  1 <= emails[i].length <= 100
  1 <= emails.length <= 100
  Each emails[i] contains exactly one '@' character.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> uniq_emails;

    for (const auto& email : emails) {
      size_t at_ind = email.find('@');
      if (at_ind == string::npos) return -1;
      string res = "";
      for (int i = 0; i < at_ind; i++) {
        if (email[i] == '.') continue;
        if (email[i] == '+') break;
        res.push_back(email[i]);
      }

      for (int i = at_ind + 1; i < email.size(); i++) {
        res.push_back(email[i]);
      }

      uniq_emails.insert(res);
    }

    return uniq_emails.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
931. Minimum Falling Path Sum
Given a square array of integers A, we want the minimum sum of a falling path
through A.

A falling path starts at any element in the first row, and chooses one element
from each row.  The next row's choice must be in a column that is different from
the previous row's column by at most one.

Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: 12
Explanation:
The possible falling paths are:

  [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
  [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
  [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]

The falling path with the smallest sum is [1,4,7], so the answer is 12.

Note:

  1 <= A.length == A[0].length <= 100
  -100 <= A[i][j] <= 100
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();

    for (int i = n - 2; i >= 0; i--) {  // skip last row
      for (int j = 0; j < m; j++) {
        int to_add = INT_MAX;
        for (int k = -1; k <= 1; k++) {
          if (j + k >= 0 && j + k < m) {
            to_add = min(to_add, A[i + 1][j + k]);
          }
        }

        A[i][j] += to_add;
      }
    }
    return *min_element(A[0].begin(), A[0].end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
933. Number of Recent Calls
Write a class RecentCounter to count recent requests.

It has only one method: ping(int t), where t represents some time in
milliseconds.

Return the number of pings that have been made from 3000 milliseconds ago until
now.

Any ping with time in [t - 3000, t] will count, including the current ping.

It is guaranteed that every call to ping uses a strictly larger value of t than
before.

Example 1:

Input: inputs = ["RecentCounter","ping","ping","ping","ping"], inputs =
[[],[1],[100],[3001],[3002]]
Output: [null,1,2,3,3]

Note:

  Each test case will have at most 10000 calls to ping.
  Each test case will call ping with strictly increasing values of t.
  Each call to ping will have 1 <= t <= 10^9.
/*
  Submission Date: 2019-01-26
  Runtime: 252 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;
class RecentCounter {
  MinHeap heap;

 public:
  RecentCounter() {}

  int ping(int t) {
    while (!heap.empty() && heap.top() < t - 3000) {
      heap.pop();
    }
    heap.push(t);
    return heap.size();
  }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
937. Reorder Log Files
You have an array of logs.  Each log is a space delimited string of words.

For each log, the first word in each log is an alphanumeric identifier.  Then,
either:

  Each word after the identifier will consist only of lowercase letters, or;
  Each word after the identifier will consist only of digits.

We will call these two varieties of logs letter-logs and digit-logs.  It is
guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.  The
letter-logs are ordered lexicographically ignoring identifier, with the
identifier used in case of ties.  The digit-logs should be put in their original
order.

Return the final order of the logs.

Example 1:

Input: ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]

Note:

  0 <= logs.length <= 100
  3 <= logs[i].length <= 100
  logs[i] is guaranteed to have an identifier, and a word after the identifier.
/*
  Submission Date: 2019-02-05
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    // move digit logs to the back
    int i = logs.size() - 1;
    for (int j = logs.size() - 1; j >= 0; j--) {
      size_t first_space_ind = logs[j].find(' ');
      if (isdigit(logs[j][first_space_ind + 1])) {
        swap(logs[i--], logs[j]);
      }
    }

    // sort the letter logs
    sort(logs.begin(), logs.begin() + i + 1,
         [](const string& lhs, const string& rhs) {
           size_t lhs_ind = lhs.find(' ');
           size_t rhs_ind = rhs.find(' ');
           string lhs_sub = lhs.substr(lhs_ind + 1);
           string rhs_sub = rhs.substr(rhs_ind + 1);
           if (lhs_sub == rhs_sub)
             return lhs.substr(0, lhs_ind) < rhs.substr(0, rhs_ind);
           return lhs_sub < rhs_sub;
         });
    return logs;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
938. Range Sum of BST
Given the root node of a binary search tree, return the sum of values of all
nodes with value between L and R (inclusive).

The binary search tree is guaranteed to have unique values.

Example 1:

Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32

Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23

Note:

  The number of nodes in the tree is at most 10000.
  The final answer is guaranteed to be less than 2^31.
/*
  Submission Date: 2019-02-06
  Runtime: 156 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int rangeSumBST(TreeNode *root, int L, int R) {
    if (root == nullptr) return 0;
    int sum = 0;
    if (L <= root->val && root->val <= R) sum += root->val;
    // tree has unique values. if root->val < L, then don't need to search left
    // tree and root->val > R, then don't need to search right tree.
    if (L < root->val) sum += rangeSumBST(root->left, L, R);
    if (root->val < R) sum += rangeSumBST(root->right, L, R);
    return sum;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
941. Valid Mountain Array
Given an array A of integers, return true if and only if it is a valid mountain
array.

Recall that A is a mountain array if and only if:

  A.length >= 3
  There exists some i with 0 < i < A.length - 1 such that:

    A[0] < A[1] < ... A[i-1] < A[i]
    A[i] > A[i+1] > ... > A[B.length - 1]

Example 1:

Input: [2,1]
Output: false

Example 2:

Input: [3,5,5]
Output: false

Example 3:

Input: [0,3,2,1]
Output: true

Note:

  0 <= A.length <= 10000
  0 <= A[i] <= 10000
/*
  Submission Date: 2019-02-05
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool validMountainArray(vector<int>& A) {
    int N = A.size();
    if (N < 3) return false;
    // increasing
    int i = 1;
    for (; i < N && A[i - 1] < A[i]; i++) {
    }

    if (i == 1 || i == N) return false;

    for (; i < N && A[i - 1] > A[i]; i++) {
    }
    return i == N;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
942. DI String Match
Given a string S that only contains "I" (increase) or "D" (decrease), let N =
S.length.

Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:

  If S[i] == "I", then A[i] < A[i+1]
  If S[i] == "D", then A[i] > A[i+1]

Example 1:

Input: "IDID"
Output: [0,4,1,3,2]

Example 2:

Input: "III"
Output: [0,1,2,3]

Example 3:

Input: "DDI"
Output: [3,2,0,1]

Note:

  1 <= S.length <= 10000
  S only contains characters "I" or "D".
/*
  Submission Date: 2019-02-04
  Runtime: 28 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  if S[i] is 'I', putting the smallest available number here works
  because all other numbers will be larger.
  else putting the largest available number here works.
  */
  vector<int> diStringMatch(string S) {
    int N = S.size();
    vector<int> res(N + 1);
    int low = 0;
    int high = N;
    for (int i = 0; i < N; i++) {
      if (S[i] == 'I')
        res[i] = low++;
      else
        res[i] = high--;
    }

    res[N] = low;
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
944. Delete Columns to Make Sorted
We are given an array A of N lowercase letter strings, all of the same length.

Now, we may choose any set of deletion indices, and for each string, we delete
all the characters in those indices.

For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices
{0, 2, 3}, then the final array after deletions is ["bef", "vyz"], and the
remaining columns of A are ["b","v"], ["e","y"], and ["f","z"].  (Formally, the
c-th column is [A[0][c], A[1][c], ..., A[A.length-1][c]].)

Suppose we chose a set of deletion indices D such that after deletions, each
remaining column in A is in non-decreasing sorted order.

Return the minimum possible value of D.length.

Example 1:

Input: ["cba","daf","ghi"]
Output: 1
Explanation:
After choosing D = {1}, each column ["c","d","g"] and ["a","f","i"] are in
non-decreasing sorted order.
If we chose D = {}, then a column ["b","a","h"] would not be in non-decreasing
sorted order.

Example 2:

Input: ["a","b"]
Output: 0
Explanation: D = {}

Example 3:

Input: ["zyx","wvu","tsr"]
Output: 3
Explanation: D = {0, 1, 2}

Note:

  1 <= A.length <= 100
  1 <= A[i].length <= 1000
/*
  Submission Date: 2019-02-04
  Runtime: 44 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minDeletionSize(vector<string>& A) {
    int N = A[0].size();
    int res = 0;
    for (int c = 0; c < N; c++) {
      for (int i = 1; i < A.size(); i++) {
        if (A[i][c] < A[i - 1][c]) {
          res++;
          break;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
949. Largest Time for Given Digits
Given an array of 4 digits, return the largest 24 hour time that can be made.

The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from
00:00, a time is larger if more time has elapsed since midnight.

Return the answer as a string of length 5.  If no valid time can be made, return
an empty string.

Example 1:

Input: [1,2,3,4]
Output: "23:41"

Example 2:

Input: [5,5,5,5]
Output: ""

Note:

  A.length == 4
  0 <= A[i] <= 9
/*
  Submission Date: 2019-02-05
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string largestTimeFromDigits(vector<int>& A) {
    /*
    ab:cd
    a [0, 2]
    b a == 2 [0-3] else [0-9]
    c [0, 5]
    d [0, 9]
    */

    unordered_map<int, int> freq;
    for (const auto& e : A) freq[e]++;
    for (int i = 2; i >= 0; i--) {
      if (!freq.count(i)) continue;
      freq[i]--;

      int cap = (i == 2) ? 3 : 9;
      for (int j = cap; j >= 0; j--) {
        if (!freq.count(j) || freq[j] == 0) continue;
        freq[j]--;
        for (int k = 5; k >= 0; k--) {
          if (!freq.count(k) || freq[k] == 0) continue;
          freq[k]--;
          for (int l = 9; l >= 0; l--) {
            if (!freq.count(l) || freq[l] == 0) continue;
            return to_string(i) + to_string(j) + string(":") + to_string(k) +
                   to_string(l);
          }
          freq[k]++;
        }

        freq[j]++;
      }
      freq[i]++;
    }

    return "";
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
950. Reveal Cards In Increasing Order
In a deck of cards, every card has a unique integer.  You can order the deck
in any order you want.

Initially, all the cards start face down (unrevealed) in one deck.

Now, you do the following steps repeatedly, until all cards are revealed:

  Take the top card of the deck, reveal it, and take it out of the deck.
  If there are still cards in the deck, put the next top card of the deck at the
bottom of the deck.
  If there are still unrevealed cards, go back to step 1.  Otherwise, stop.

Return an ordering of the deck that would reveal the cards in increasing order.

The first entry in the answer is considered to be the top of the deck.

Example 1:

Input: [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation:
We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and
reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of
the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.

Note:

  1 <= A.length <= 1000
  1 <= A[i] <= 10^6
  A[i] != A[j] for all i != j
/*
  Submission Date: 2019-02-07
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  Find the order in which the cards are revealed (e.g. indices 0, 2, 4, ...).
  Place the sorted numbers into these indices.
  */
  vector<int> deckRevealedIncreasing(vector<int>& deck) {
    sort(deck.begin(), deck.end());
    int N = deck.size();
    deque<int> dq(N);
    for (int i = 0; i < N; i++) dq[i] = i;
    vector<int> order;
    while (!dq.empty()) {
      order.push_back(dq.front());
      dq.pop_front();
      if (!dq.empty()) {
        dq.push_back(dq.front());
        dq.pop_front();
      }
    }

    int i = 0;
    vector<int> res(N);
    for (const auto& o : order) {
      res[o] = deck[i++];
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
951. Flip Equivalent Binary Trees
For a binary tree T, we can define a flip operation as follows: choose any node,
and swap the left and right child subtrees.

A binary tree X is flip equivalent to a binary tree Y if and only if we can make
X equal to Y after some number of flip operations.

Write a function that determines whether two binary trees are flip equivalent. 
The trees are given by root nodes root1 and root2.

Example 1:

Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 =
[1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.

Note:

  Each tree will have at most 100 nodes.
  Each value in each tree will be a unique integer in the range [0, 99].
/*
  Submission Date: 2019-02-09
  Runtime: 8 ms
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
  bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    if (root1 && root2) {
      if (root1->val != root2->val) return false;
      return (flipEquiv(root1->left, root2->left) &&
              flipEquiv(root1->right, root2->right)) ||
             (flipEquiv(root1->left, root2->right) &&
              flipEquiv(root1->right, root2->left));
    } else {
      return root1 == nullptr && root2 == nullptr;
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
953. Verifying an Alien Dictionary
In an alien language, surprisingly they also use english lowercase letters, but
possibly in a different order. The order of the alphabet is some permutation of
lowercase letters.

Given a sequence of words written in the alien language, and the order of the
alphabet, return true if and only if the given words are sorted lexicographicaly
in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is
sorted.

Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1],
hence the sequence is unsorted.

Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is
shorter (in size.) According to lexicographical rules "apple" > "app", because
'l' > '∅', where '∅' is defined as the blank character which is less than any
other character (More info).

Note:

  1 <= words.length <= 100
  1 <= words[i].length <= 20
  order.length == 26
  All characters in words[i] and order are english lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool less(const string& s1, const string& s2,
            unordered_map<char, int>& rank) {
    int i = 0;
    while (i < min(s1.size(), s2.size()) && s1[i] == s2[i]) i++;
    int r1 = i == s1.size() ? INT_MIN : rank[s1[i]];
    int r2 = i == s2.size() ? INT_MIN : rank[s2[i]];
    return r1 <= r2;
  }

  bool isAlienSorted(vector<string>& words, string order) {
    unordered_map<char, int> rank;
    for (int i = 0; i < order.size(); i++) rank[order[i]] = i;

    for (int i = 1; i < words.size(); i++) {
      if (!less(words[i - 1], words[i], rank)) return false;
    }

    return true;
  }
};

int main() { return 0; }
