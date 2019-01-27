
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
905. Sort Array By Parity
Given an array A of non-negative integers, return an array consisting of all the
even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 


Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.


 

Note:


  1 <= A.length <= 5000
  0 <= A[i] <= 5000
/*
  Submission Date: 2019-01-25
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortArrayByParity(vector<int>& A) {
    int even = 0;
    int odd = A.size() - 1;

    while (even < odd) {
      if (A[even] % 2 == 0) {
        even++;
      } else {
        swap(A[even], A[odd]);
        odd--;
      }
    }

    return A;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
908. Smallest Range I
Given an array A of integers, for each integer A[i] we may choose any x with -K
<= x <= K, and add x to A[i].

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the
minimum value of B.

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]

Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]

Example 3:

Input: A = [1,3,6], K = 3
Output: 0
Explanation: B = [3,3,3] or B = [4,4,4]

Note:

  1 <= A.length <= 10000
  0 <= A[i] <= 10000
  0 <= K <= 10000
/*
  Submission Date: 2019-01-26
  Runtime: 12 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int smallestRangeI(vector<int>& A, int K) {
    if (A.empty()) return 0;
    return max(0, *max_element(A.begin(), A.end()) -
                      *min_element(A.begin(), A.end()) - 2 * K);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
914. X of a Kind in a Deck of Cards
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to
split the entire deck into 1 or more groups of cards, where:

  Each group has exactly X cards.
  All the cards in each group have the same integer.

Example 1:

Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

Example 2:

Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Example 3:

Input: [1]
Output: false
Explanation: No possible partition.

Example 4:

Input: [1,1]
Output: true
Explanation: Possible partition [1,1]

Example 5:

Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:

  1 <= deck.length <= 10000
  0 <= deck[i] < 10000
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }
  /*
  gcd(a,b,c) = gcd(gcd(a,b), c)
  hence, if the gcd(freq[0], ... freq[n-1]) is the
  largest number which divides into all of them which
  is X (just check X >= 2)
  */
  bool hasGroupsSizeX(vector<int>& deck) {
    unordered_map<int, int> freq;
    for (auto& e : deck) {
      freq[e]++;
    }

    int res = 0;
    for (auto& kv : freq) res = gcd(res, kv.second);
    return res > 1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
917. Reverse Only Letters
Given a string S, return the "reversed" string where all characters that are not
a letter stay in the same place, and all letters reverse their positions.

Example 1:

Input: "ab-cd"
Output: "dc-ba"

Example 2:

Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"

Example 3:

Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"

Note:

  S.length <= 100
  33 <= S[i].ASCIIcode <= 122 
  S doesn't contain \ or "
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  string reverseOnlyLetters(string S) {
    int last_ind = S.size() - 1;
    for (int i = 0; i < last_ind; i++) {
      if (!isalpha(S[i])) continue;
      while (last_ind > i && !isalpha(S[last_ind])) last_ind--;
      swap(S[i], S[last_ind]);
      last_ind--;
    }
    return S;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
919. Complete Binary Tree Inserter
A complete binary tree is a binary tree in which every level, except possibly
the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary
tree and supports the following operations:

  CBTInserter(TreeNode root) initializes the data structure on a given tree with
head node root;
  CBTInserter.insert(int v) will insert a TreeNode into the tree with value
node.val = v so that the tree remains complete, and returns the value of the
parent of the inserted TreeNode;
  CBTInserter.get_root() will return the head node of the tree.

Example 1:

Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]

Example 2:

Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs =
[[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]

Note:

  The initial given tree is complete and contains between 1 and 1000 nodes.
  CBTInserter.insert is called at most 10000 times per test case.
  Every value of a given or inserted node is between 0 and 5000.
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class CBTInserter {
  vector<TreeNode*> nodes;

 public:
  CBTInserter(TreeNode* root) {
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
      TreeNode* front = q.front();
      q.pop();
      if (front->left) q.push(front->left);
      if (front->right) q.push(front->right);
      nodes.push_back(front);
    }
  }

  int insert(int v) {
    nodes.emplace_back(new TreeNode(v));
    int parent_ind = (nodes.size() - 2) / 2;
    if (nodes[parent_ind]->left == NULL)
      nodes[parent_ind]->left = nodes.back();
    else
      nodes[parent_ind]->right = nodes.back();
    return nodes[parent_ind]->val;
  }

  TreeNode* get_root() { return nodes[0]; }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter obj = new CBTInserter(root);
 * int param_1 = obj.insert(v);
 * TreeNode* param_2 = obj.get_root();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
921. Minimum Add to Make Parentheses Valid
Given a string S of '(' and ')' parentheses, we add the minimum number of
parentheses ( '(' or ')', and in any positions ) so that the resulting
parentheses string is valid.

Formally, a parentheses string is valid if and only if:

  It is the empty string, or
  It can be written as AB (A concatenated with B), where A and B are valid
strings, or
  It can be written as (A), where A is a valid string.

Given a parentheses string, return the minimum number of parentheses we must add
to make the resulting string valid.

Example 1:

Input: "())"
Output: 1

Example 2:

Input: "((("
Output: 3

Example 3:

Input: "()"
Output: 0

Example 4:

Input: "()))(("
Output: 4

Note:

  S.length <= 1000
  S only consists of '(' and ')' characters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int minAddToMakeValid(string s) {
    int open = 0;
    int res = 0;
    for (auto& c : s) {
      if (c == '(') {
        open++;
      } else {
        if (open > 0) {
          open--;
        } else {
          res++;
        }
      }
    }
    return res + open;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
922. Sort Array By Parity II
Given an array A of non-negative integers, half of the integers in A are odd,
and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is
even, i is even.

You may return any answer array that satisfies this condition.

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

Note:

  2 <= A.length <= 20000
  A.length % 2 == 0
  0 <= A[i] <= 1000
/*
  Submission Date: 2019-01-26
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortArrayByParityII(vector<int>& A) {
    int even_ind = 0;
    int odd_ind = 1;
    while (even_ind < A.size() && odd_ind < A.size()) {
      while (even_ind < A.size() && A[even_ind] % 2 == 0) {
        even_ind += 2;
      }

      while (odd_ind < A.size() && A[odd_ind] % 2 == 1) {
        odd_ind += 2;
      }

      int cnt = (even_ind < A.size()) + (odd_ind < A.size());

      if (cnt == 0) break;
      assert(cnt != 1);
      swap(A[even_ind], A[odd_ind]);
      even_ind += 2;
      odd_ind += 2;
    }

    return A;
  }
};

int main() { return 0; }

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
977. Squares of a Sorted Array
Given an array of integers A sorted in non-decreasing order, return an array of
the squares of each number, also in sorted non-decreasing order.

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:

  1 <= A.length <= 10000
  -10000 <= A[i] <= 10000
  A is sorted in non-decreasing order.
/*
  Submission Date: 2019-01-26
  Runtime: 132 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& A) {
    int N = A.size();
    vector<int> res(N);
    int i = 0;
    int j = N - 1;
    int wr = N - 1;

    while (i < j && A[i] < 0) {
      if (-A[i] > A[j]) {
        res[wr--] = A[i] * A[i];
        i++;
      } else {
        res[wr--] = A[j] * A[j];
        j--;
      }
    }

    while (j >= i) {
      res[wr--] = A[j] * A[j];
      j--;
    }

    return res;
  }
};

int main() { return 0; }
