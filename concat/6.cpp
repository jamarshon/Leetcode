
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the
following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways
to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  unordered_map<string, int> m;

 public:
  int numDecodingsHelper(string s) {
    if (m.count(s)) return m[s];

    int len = s.size();
    if (len == 0) return 1;
    if (len == 1) return s[0] > '0';

    // length is at least 2
    int res = 0;
    if (s[0] > '0') {
      if (s[0] < '2' || (s[0] == '2' && s[1] <= '6')) {
        res += numDecodingsHelper(s.substr(2));
      }

      res += numDecodingsHelper(s.substr(1));
    }

    return m[s] = res;
  }

  int numDecodings(string s) {
    if (s.empty()) return 0;
    return numDecodingsHelper(s);
  }
};

int main() {
  Solution s;
  cout << s.numDecodings("12") << endl;    // 2
  cout << s.numDecodings("17") << endl;    // 2
  cout << s.numDecodings("1273") << endl;  // 2
  cout << s.numDecodings("0") << endl;     // 0
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

/*
    Submission Date: 2017-01-14
    Runtime: 3 ms
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
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (m == n) return head;

    ListNode* begin = head;
    bool reverseIncludeHead = m == 1;

    for (int i = 0; i < m - 2; i++) {
      begin = begin->next;
    }

    ListNode* end = begin->next;
    ListNode* A = reverseIncludeHead ? head : end;
    ListNode* B = A->next;
    ListNode* C = B == NULL ? NULL : B->next;

    for (int i = 0; i < n - m; i++) {
      B->next = A;
      A = B;
      B = C;
      if (C != NULL) C = C->next;
    }

    if (reverseIncludeHead) {
      head->next = B;
      head = A;
    } else {
      begin->next = A;
      end->next = B;
    }

    return head;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
93. Restore IP Addresses
Given a string containing only digits, restore it by returning all possible
valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void restoreIpAddressesHelper(string rem, string curr, int periods,
                                vector<string>& res) {
    if (periods == 4) {
      if (rem.empty()) {
        res.push_back(curr);
      }
      return;
    }

    int len = rem.size();

    if (len == 0) return;

    if (!curr.empty()) curr += '.';

    string first_substr = rem.substr(0, 1);
    restoreIpAddressesHelper(rem.substr(1), curr + first_substr, periods + 1,
                             res);

    if (len > 1) {
      string second_substr = rem.substr(0, 2);
      if (stoi(second_substr) >= 10) {
        restoreIpAddressesHelper(rem.substr(2), curr + second_substr,
                                 periods + 1, res);
      }
    }

    if (len > 2) {
      string third_substr = rem.substr(0, 3);
      if (stoi(third_substr) >= 100 && stoi(third_substr) <= 255) {
        restoreIpAddressesHelper(rem.substr(3), curr + third_substr,
                                 periods + 1, res);
      }
    }
  }

  vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    restoreIpAddressesHelper(s, "", 0, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <stack>
#include <unordered_set>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    unordered_set<TreeNode*> set;

    vector<int> result;
    s.push(root);

    while (!s.empty()) {
      TreeNode* top = s.top();
      s.pop();
      if (top == NULL) {
        continue;
      } else if (set.find(top) == set.end()) {
        s.push(top->right);
        s.push(top);
        s.push(top->left);
        set.insert(top);
      } else {
        result.push_back(top->val);
      }
    }

    return result;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
95. Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees)
that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-07-18
    Runtime: 16 ms
    Difficulty: MEDIUM
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
  void labelInorder(TreeNode* curr, int& count) {
    if (curr == NULL) return;

    labelInorder(curr->left, count);
    curr->val = count++;
    labelInorder(curr->right, count);
  }

  void getPreorderSequence(string s, vector<string>& res, int zeros, int ones,
                           int len) {
    if (ones > len / 2) return;

    if (s.size() == len) {
      res.push_back(s);
      return;
    }

    getPreorderSequence(s + '1', res, zeros, ones + 1, len);
    if (ones > zeros) {
      getPreorderSequence(s + '0', res, zeros + 1, ones, len);
    }
  }

  TreeNode* buildFromPreOrder(string seq, int& index) {
    if (seq[index] == '0') {
      index++;
      return NULL;
    }

    TreeNode* curr = new TreeNode(-1);
    index++;
    curr->left = buildFromPreOrder(seq, index);
    curr->right = buildFromPreOrder(seq, index);
    return curr;
  }

  vector<TreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    vector<string> pre_seq;
    getPreorderSequence("", pre_seq, 0, 0, n * 2);

    vector<TreeNode*> res(pre_seq.size());
    transform(pre_seq.begin(), pre_seq.end(), res.begin(),
              [this](const string s) {
                int temp = 0;
                TreeNode* root = buildFromPreOrder(s + "0", temp);
                temp = 1;
                labelInorder(root, temp);
                return root;
              });
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
96. Unique Binary Search Trees
Given n, how many structurally unique BST's (binary search trees) that store
values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-06-28
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  int numTrees(int n) {
    long long dp[n + 1];

    dp[0] = dp[1] = 1;

    for (long long i = 1; i < n; i++) {
      dp[(int)i + 1] = dp[i] * (2 * i + 2) * (2 * i + 1) / (i + 1) / (i + 2);
    }

    return dp[n];
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    int M = s1.size();
    int N = s2.size();
    if (M + N != s3.size()) return false;

    bool dp[M + 1][N + 1];

    for (int i = 0; i <= M; i++) {
      for (int j = 0; j <= N; j++) {
        if (i == 0 && j == 0)
          dp[i][j] = true;
        else if (i == 0)
          dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
        else if (j == 0)
          dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
        else
          dp[i][j] = (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]) ||
                     (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
      }
    }

    return dp[M][N];
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's
key. The right subtree of a node contains only nodes with keys greater than the
node's key. Both the left and right subtrees must also be binary search trees.

    2
   / \
  1   3

Binary tree [2,1,3], return true.

    1
   / \
  2   3

Binary tree [1,2,3], return false.

/*
    Submission Date: 2017-01-27
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool isValidBSTHelper(TreeNode* root, int* min, int* max) {
    if (root == NULL) return true;

    int rootVal = root->val;
    int* rootValPtr = &rootVal;

    if ((min && rootVal <= *min) || (max && rootVal >= *max)) return false;

    bool validLeftSubTree = isValidBSTHelper(root->left, min, rootValPtr);
    bool validRightSubTree = isValidBSTHelper(root->right, rootValPtr, max);

    return validLeftSubTree && validRightSubTree;
  }

  bool isValidBST(TreeNode* root) { return isValidBSTHelper(root, NULL, NULL); }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
99. Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a
constant space solution?

/*
    Submission Date: 2017-08-02
    Runtime: 32 ms
    Difficulty: HARD
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
 public:
  void findIllegals(TreeNode* root, TreeNode* minimum, TreeNode* maximum,
                    vector<tuple<TreeNode*, TreeNode*, bool>>& illegals) {
    if (root == NULL) return;

    int curr_val = root->val;
    bool is_less_than_minimum =
        minimum == NULL ? false : (curr_val < minimum->val);
    bool is_greater_than_maximum =
        maximum == NULL ? false : (curr_val > maximum->val);

    if (is_less_than_minimum || is_greater_than_maximum) {
      if (is_less_than_minimum) {
        illegals.emplace_back(minimum, root, true);
      } else {
        illegals.emplace_back(maximum, root, false);
      }
      return;
    }

    findIllegals(root->left, minimum, root, illegals);
    findIllegals(root->right, root, maximum, illegals);
  }

  void searchTree(TreeNode* root, TreeNode*& res,
                  function<bool(TreeNode*, TreeNode*)> criteria) {
    if (root == NULL) return;
    if (criteria(root, res)) {
      res = root;
    }

    searchTree(root->left, res, criteria);
    searchTree(root->right, res, criteria);
  }

  void recoverTree(TreeNode* root) {
    vector<tuple<TreeNode*, TreeNode*, bool>> illegals;
    findIllegals(root, NULL, NULL, illegals);

    int N = illegals.size();
    assert(N == 1 || N == 2);

    TreeNode *limit1, *violate1, *limit2, *violate2, *to_switch;
    bool violate1_is_smaller_than_limit, violate2_is_smaller_than_limit;

    limit1 = violate1 = limit2 = violate2 = to_switch = NULL;
    violate1_is_smaller_than_limit = violate2_is_smaller_than_limit = false;

    tie(limit1, violate1, violate1_is_smaller_than_limit) = illegals[0];
    if (N == 1) {
      // we have limit1 and a child node (violate1) which does not fit it's
      // boundaries if violate1_is_smaller_than_limit, limit1 is too large so we
      // find the smallest node from violate1 and replace limit1 with this node
      if (violate1_is_smaller_than_limit) {
        searchTree(violate1, to_switch,
                   [](const TreeNode* curr, const TreeNode* res) {
                     return res == NULL ? true : (res->val > curr->val);
                   });
      } else {
        searchTree(violate1, to_switch,
                   [](const TreeNode* a, const TreeNode* res) {
                     return res == NULL ? true : (res->val < a->val);
                   });
      }

      swap(limit1->val, to_switch->val);
    } else if (N == 2) {
      // we have two nodes that violate the limits meaning they are not on the
      // same path to the root (ie lca(a,b) != a or b) so we just swap violate1
      // and violate2 denote anc as lca(violate1, violate2) if violate1 is
      // smaller than its limit, it means it went from the left tree of anc into
      // right tree of anc and violate2 went from right tree to left. So
      // violate2 should be greater than its limit
      tie(limit2, violate2, violate2_is_smaller_than_limit) = illegals[1];
      swap(violate2->val, violate1->val);
      assert(violate1_is_smaller_than_limit != violate2_is_smaller_than_limit);
    }
  }
};

class Solution {
 private:
  TreeNode *first_, *second_, *prev_;

 public:
  void inorder(TreeNode* root) {
    if (root == NULL) return;

    inorder(root->left);

    bool prev_element_greater_than_current =
        prev_ == NULL ? false : (prev_->val > root->val);

    if (prev_element_greater_than_current) {
      if (first_ == NULL) first_ = prev_;
      second_ = root;
    }

    prev_ = root;
    inorder(root->right);
  }
  void recoverTree(TreeNode* root) {
    first_ = second_ = prev_ = NULL;
    inorder(root);
    swap(first_->val, second_->val);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
100. Same Tree
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the
nodes have the same value.

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
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
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == NULL && q == NULL) return true;
    if (p == NULL || q == NULL) return false;

    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric
around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
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
  bool isSymmetric(TreeNode* left, TreeNode* right) {
    if (left == NULL && right == NULL) return true;
    if (left == NULL || right == NULL) return false;
    if (left->val != right->val) return false;

    return isSymmetric(left->left, right->right) &&
           isSymmetric(left->right, right->left);
  }
  bool isSymmetric(TreeNode* root) {
    if (root) return isSymmetric(root->left, root->right);
    return true;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
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

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      int level_size = q.size();
      vector<int> temp;
      for (int i = 0; i < level_size; i++) {
        TreeNode* curr = q.front();
        if (curr) {
          temp.push_back(curr->val);
          q.push(curr->left);
          q.push(curr->right);
        }
        q.pop();
      }
      if (!temp.empty()) res.push_back(temp);
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
103. Binary Tree Zigzag Level Order Traversal
Given a binary tree, return the zigzag level order traversal of its nodes'
values. (ie, from left to right, then right to left for the next level and
alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
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

class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;

    bool forward = true;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      int level_size = q.size();
      vector<int> temp;
      for (int i = 0; i < level_size; i++) {
        TreeNode* curr = q.front();
        if (curr) {
          temp.push_back(curr->val);
          q.push(curr->left);
          q.push(curr->right);
        }
        q.pop();
      }

      if (!forward) {
        reverse(temp.begin(), temp.end());
      }

      if (!temp.empty()) res.push_back(temp);
      forward ^= true;
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
104. Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.
/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
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
  int maxDepth(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  unordered_map<int, int> inorder_val_to_index;

 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); i++) {
      inorder_val_to_index[inorder[i]] = i;
    }

    return buildTreeHelper(preorder, inorder, 0, preorder.size(), 0,
                           inorder.size());
  }
  TreeNode* buildTreeHelper(const vector<int>& preorder,
                            const vector<int>& inorder, int i, int j, int k,
                            int l) {
    assert(j - i == l - k);

    if (i == j) return NULL;

    TreeNode* root = new TreeNode(preorder[i]);
    int root_idx = inorder_val_to_index[preorder[i]];
    int left_size = root_idx - k;

    root->left = buildTreeHelper(preorder, inorder, i + 1, i + 1 + left_size, k,
                                 root_idx);
    root->right = buildTreeHelper(preorder, inorder, i + left_size + 1, j,
                                  root_idx + 1, l);
    return root;
  }
};

int main() {
  Solution s;
  return 0;
}