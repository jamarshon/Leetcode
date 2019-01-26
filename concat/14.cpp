
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
230. Kth Smallest Element in a BST
Given a binary search tree, write a function kthSmallest to find the kth
smallest element in it.

Note:
You may assume k is always valid, 1 ? k ? BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you
need to find the kth smallest frequently? How would you optimize the
kthSmallest routine?

/*
    Submission Date: 2017-08-14
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  bool inorder(TreeNode* root, int& count, int k, int& res) {
    if (root == NULL) return false;

    if (inorder(root->left, count, k, res)) return true;
    count++;
    if (count == k) {
      res = root->val;
      return true;
    }

    if (inorder(root->right, count, k, res)) return true;
    return false;
  }
  int kthSmallest(TreeNode* root, int k) {
    int count = 0, res = 0;
    inorder(root, count, k, res);
    return res;
  }
};

class Solution2 {
 public:
  int updateMap(unordered_map<TreeNode*, int>& node_to_num_children,
                TreeNode* root) {
    if (node_to_num_children.count(root)) return node_to_num_children[root];
    int res = 1;
    res += updateMap(node_to_num_children, root->left);
    res += updateMap(node_to_num_children, root->right);
    return node_to_num_children[root] = res;
  }

  int traverse(TreeNode* root, int k,
               unordered_map<TreeNode*, int>& node_to_num_children) {
    assert(root != NULL);
    int left_num = node_to_num_children[root->left];

    if (left_num == k - 1) return root->val;

    if (left_num >= k) {
      return traverse(root->left, k, node_to_num_children);
    } else {
      return traverse(root->right, k - 1 - left_num, node_to_num_children);
    }
  }
  int kthSmallest(TreeNode* root, int k) {
    unordered_map<TreeNode*, int> node_to_num_children{{NULL, 0}};
    updateMap(node_to_num_children, root);
    return traverse(root, k, node_to_num_children);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
231. Power of Two
Given an integer, write a function to determine if it is a power of two.

/*
    Submission Date: 2017-07-30
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
 public:
  bool isPowerOfTwo(int n) { return n > 0 ? (n & (n - 1)) == 0 : false; }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
232. Implement Queue using Stacks
Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:
You must use only standard operations of a stack -- which means
only push to top, peek/pop from top, size, and is empty operations
are valid.
Depending on your language, stack may not be supported natively. You
may simulate a stack by using a list or deque (double-ended queue), as
long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or
peek operations will be called on an empty queue).
/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
  stack<int> input_, output_;

 public:
  MyQueue() {}

  void push(int x) { input_.push(x); }

  int pop() {
    int output_top = peek();
    output_.pop();
    return output_top;
  }

  int peek() {
    if (output_.empty()) {
      // reverse input_ stack by taking the top and making it at the bottom of
      // output_
      while (!input_.empty()) {
        int input_top = input_.top();
        output_.push(input_top);
        input_.pop();
      }
    }

    return output_.top();
  }

  bool empty() { return input_.empty() && output_.empty(); }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
233. Number of Digit One
Given an integer n, count the total number of digit 1
appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers:
1, 10, 11, 12, 13.

/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution2 {
 public:
  // low is the form of 10^n where 10^n <= high < 10^(n+1) meaning low and high
  // have same number of digits
  int countDigitOne(int low, int high) {
    while (low > high)
      low /= 10;  // 100 and 002 we need to make them the same so 10 and 2

    if (low == 0) return 0;
    if (low == 1) return 1;

    int res = 0;
    int diff = min(high - low + 1, low);  // 461-100 -> 100 or 120-100 -> 20

    res += diff;

    int high_first_digit = high / low;

    // high_first_digit = 461/100 = 4
    // we consider 0-99 100-199 200-299, 300-399, 400-461
    // there are high_first_digit - 1 full intervals countDigitOne(10, 99)
    // there is one incomplete interval countDigitOne(10,61)
    int full_interval = countDigitOne(low / 10, low - 1);
    for (int i = 0; i < high_first_digit; i++) {
      res += full_interval;
    }

    res += countDigitOne(low / 10, high % low);
    return res;
  }

  int countDigitOne(int x) {
    if (x < 0) return 0;

    int n = floor(log10(x));
    int low = round(pow(10, n));
    return countDigitOne(low, x);
  }
};

class Solution {
 public:
  int countDigitOne(int n) {
    typedef long long ll;
    ll res = 0;

    /*
        Given a number xxxxyzzz where indices are 76543210 and k=3 which is
       where y appears we want to count how many times y is one. xxxx would be
       numbers 0000 to xxxx so they appear xxxx - 0000 + 1 times or (xxxx + 1)
        if y >= 2 then it means for the (xxxx+1) times, there is 10^k occurences
       that y is 1 so it is just (xxxx+1)*10^k if y == 1 then for the (xxxx+1)
       times, there is (xxxx+1)-1 full intervals of 10^k that has y equal to 1
       and there is one partial interval for the numbers zzz which occur zzz -
       000 + 1 times or (zzz+1) so it is xxxx*10^k + zzz+1 if y == 0 then the
       (xxxx+1) complete intervals do not include the last one as y is not
       greater than one so it is xxxx*10^k

        e.g (y >= 2) 4(3)zz there is x + 1 = 5 times x(1)zz can occur 0(1)zz,
       1(1)zz, 2(1)zz, 3(1)zz, 4(1)zz y >= 2 meaning the last interval 4(1)zz is
       considered complete (4100 to 4199) is included by 4(3)zz so it is 5*10^2

            (y == 1) 4(1)zz the last interval 4(1)zz is not considered complete
       but for 0(1)zz, 1(1)zz, 2(1)zz, 3(1)zz there are 4*10^2 ones. The partial
       interval of 4(1)zz has zz + 1 number of ones as 4(1)00 to 4(1)zz include
       zz + 1 elements for a total of 4*10^2 + (zz + 1)
            
            (y == 0) 4(0)zz the last interval 4(1)zz is not complete so there is
       4*10^2 for 0(1)zz, 1(1)zz, 2(1)zz, 3(1)zz and the zz + 1 elements do not
       count towards the total as y is not one so just 4*10^2
    */
    for (ll i = 1; i <= n; i *= 10) {  // i is 10^k
      // denote xxxxy as temp, xxxx as prefix, y as digit, and zz as suffix
      ll temp = n / i;
      ll prefix = temp / 10;
      ll digit = temp % 10;
      ll suffix = n % i;

      if (digit >= 2) {
        res += (prefix + 1) * i;  // (xxxx+1)*10^k
      } else if (digit == 1) {
        res += (prefix)*i + (suffix + 1);  // xxxx*10^k + zzz+1
      } else {                             // digit == 0
        res += (prefix)*i;                 // xxxx*10^k
      }
    }
    return res;
  }
};

int main() {
  Solution s;
  cout << s.countDigitOne(13) << endl;          // 6
  cout << s.countDigitOne(100) << endl;         // 21
  cout << s.countDigitOne(101) << endl;         // 23
  cout << s.countDigitOne(102) << endl;         // 24
  cout << s.countDigitOne(1410065408) << endl;  // 1737167499
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
234. Palindrome Linked List
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

/*
    Submission Date: 2017-08-06
    Runtime: 28 ms
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
  ListNode* reverse(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    ListNode* next = curr->next;

    while (curr) {
      curr->next = prev;
      prev = curr;
      curr = next;
      if (next != NULL) next = curr->next;
    }

    return prev;
  }

  bool isEqual(ListNode* a, ListNode* b) {
    while (a && b) {
      if (a->val != b->val) return false;
      a = a->next;
      b = b->next;
    }
    return a == NULL && b == NULL;
  }

  bool isPalindrome(ListNode* head) {
    ListNode *slow, *fast, *last_slow;
    last_slow = NULL;
    slow = fast = head;

    while (fast && fast->next) {
      fast = fast->next->next;
      last_slow = slow;
      slow = slow->next;
    }

    if (slow == head) return true;

    last_slow->next = NULL;

    bool is_even_length = fast == NULL;
    // marker is where to start reversing if even and it's next is where to
    // start reversing if odd e.g marker is 1 in 0 -> 1 -> 2 -> 3 and marker is
    // 2 in 0 -> 1 -> 2 -> 3 -> 4
    ListNode* marker = slow;

    ListNode* rev_head = is_even_length
                             ? reverse(marker)
                             : reverse(marker->next);  // reverse last half
    bool res = isEqual(
        head,
        rev_head);  // check if first half and reversed second half is the same
    ListNode* rev_tail = reverse(rev_head);  // undo the reverse
    if (is_even_length) {
      last_slow->next = rev_tail;
    } else {
      last_slow->next = marker;  // place the marker back in between the first
                                 // half and second half for odd length
      marker->next = rev_tail;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
235. Lowest Common Ancestor of a Binary Search Tree
Given a binary search tree (BST), find the lowest common ancestor
(LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest
common ancestor is defined between two nodes v and w as the
lowest node in T that has both v and w as descendants (where
we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6.
Another example is LCA of nodes 2 and 4 is 2, since a node can be a
descendant of itself according to the LCA definition.

/*
    Submission Date: 2017-08-21
    Runtime: 29 ms
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
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) return NULL;
    if (p == NULL || q == NULL) return p ? p : q;

    int p_val = p->val, q_val = q->val, root_val = root->val;

    if (root_val > p_val && root_val > q_val) {
      return lowestCommonAncestor(root->left, p, q);
    } else if (root_val < p_val && root_val < q_val) {
      return lowestCommonAncestor(root->right, p, q);
    } else {
      return root;
    }
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
236. Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes v and w as the lowest node in T that has both v and w
as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another
example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of
itself according to the LCA definition.

/*
    Submission Date: 2017-08-14
    Runtime: 16 ms
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

class Solution2 {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;

    auto* left = lowestCommonAncestor(root->left, p, q);
    auto* right = lowestCommonAncestor(root->right, p, q);

    if (left && right)
      return root;
    else if (left)
      return left;
    else
      return right;
  }
};

class Solution {
 public:
  int lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q,
                           TreeNode*& res) {
    if (root == NULL) return 0;

    int count = 0;
    if (root == p) count++;
    if (root == q) count++;

    if (count == 2) {  // root == p == q so root is lca
      res = root;
      return 2;
    }

    int left_count = lowestCommonAncestor(root->left, p, q, res);
    if (left_count == 2) return 2;  // found p and q in root -> left
    count += left_count;

    // root is either p or q and the other is in the left tree so root is lca
    if (count == 2) {
      res = root;
      return 2;
    }

    int right_count = lowestCommonAncestor(root->right, p, q, res);
    if (right_count == 2) return 2;  // found p and q in root -> right
    count += right_count;

    // root and left_tree has either p or q and the other is in the right tree
    // so root is lca
    if (count == 2) {
      res = root;
      return 2;
    }

    return count;
  }

  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* res = NULL;
    lowestCommonAncestor(root, p, q, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
237. Delete Node in a Linked List
Write a function to delete a node (except the tail) in a singly linked list,
given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node
with value 3, the linked list should become 1 -> 2 -> 4 after calling your
function.

/*
    Submission Date: 2017-07-21
    Runtime: 16 ms
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
  void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
238. Product of Array Except Self
Given an array of n integers where n > 1, nums, return an array output such that
output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

/*
    Submission Date: 2017-07-30
    Runtime: 68 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int N = nums.size();
    vector<int> dp(N);

    // forwards sweep
    int product = 1;
    for (int i = 0; i < N; i++) {
      dp[i] = product;
      product *= nums[i];
    }

    // backward sweep
    int back_product = 1;
    for (int i = N - 1; i >= 0; i--) {
      dp[i] *= back_product;
      back_product *= nums[i];
    }

    return dp;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is
moving from the very left of the array to the very right. You can
only see the k numbers in the window. Each time the sliding window
moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's
size for non-empty array.

Follow up:
Could you solve it in linear time?
/*
    Submission Date: 2017-08-21
    Runtime: 69 ms
    Difficulty: HARD
*/
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    typedef pair<int, int> pii;
    list<pii> ls;

    int N = nums.size();
    vector<int> res;
    for (int i = 0; i < N; i++) {
      while (!ls.empty() && ls.front().second <= i - k) {
        ls.pop_front();
      }

      while (!ls.empty() && ls.back().first < nums[i]) {
        ls.pop_back();
      }

      ls.emplace_back(nums[i], i);
      if (i >= k - 1) res.push_back(ls.front().first);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix.
This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
/*
    Submission Date: 2017-08-22
    Runtime: 79 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int M = matrix.size();
    int N = matrix.front().size();

    int i = 0;
    int j = N - 1;
    while (i < M && j >= 0) {
      if (matrix[i][j] == target) return true;
      if (matrix[i][j] > target) {  // smaller than everything in this column
        j--;
      } else if (matrix[i][j] < target) {  // bigger than everything in this row
        i++;
      }
    }

    return false;
  }
};

int main() {
  Solution s;
  return 0;
}