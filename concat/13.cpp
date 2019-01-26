
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
220. Contains Duplicate III
Given an array of integers, find out whether there are two distinct indices
i and j in the array such that the absolute difference between nums[i] and
nums[j] is at most t and the absolute difference between i and j is at most k.

/*
    Submission Date: 2017-08-07
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution2 {
 public:
  // O(nlogk) maintain window of k and do range search on it
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if (k < 0 || t < 0) return false;

    map<int, int> m;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      int above = (nums[i] > INT_MAX - t) ? INT_MAX : nums[i] + t;
      int below = (nums[i] < INT_MIN + t) ? INT_MIN : nums[i] - t;

      if (above < below) swap(above, below);

      auto below_it = m.lower_bound(below);
      auto above_it = m.upper_bound(above);

      while (below_it != above_it) {
        if (below_it->second > 0) return true;
        below_it++;
      }

      m[nums[i]]++;
      if (i >= k) {
        m[nums[i - k]]--;
      }
    }
    return false;
  }
};

class Solution1 {
 public:
  // nlogn + check if adjacent numbers are close enough in index
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if (k < 0 || t < 0) return false;

    int N = nums.size();
    vector<pair<int, int>> v;
    for (int i = 0; i < N; i++) {
      v.emplace_back(nums[i], i);
    }

    sort(v.begin(), v.end(),
         [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
           return lhs.first < rhs.first;
         });

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if (v[i].first < 0 && v[j].first > INT_MAX + v[i].first) break;

        int diff = v[j].first - v[i].first;
        int idx_diff = abs(v[j].second - v[i].second);
        if (diff > t) break;
        if (idx_diff <= k) return true;
      }
    }
    return false;
  }
};

class Solution {
 public:
  // numbers 0,1,2 and bucket of 3 they all get put into bucket[1]
  // since negative numbers are allowed we remap to nums[i] - INT_MIN as bucket
  // 0 should include INT_MIN, we check adjacent bucket to see if across bucket
  // values work
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if (k < 1 || t < 0) return false;

    unordered_map<long, long> m;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      long remapped_num = (long)nums[i] - INT_MIN;
      long bucket = remapped_num / ((long)t + 1);

      bool another_el_same_bucket = m.count(bucket);
      bool bucket_below_close_enough =
          m.count(bucket - 1) && remapped_num - m[bucket - 1] <= t;
      bool bucket_above_close_enough =
          m.count(bucket + 1) && m[bucket + 1] - remapped_num <= t;
      if (another_el_same_bucket || bucket_below_close_enough ||
          bucket_above_close_enough) {
        return true;
      }

      if (m.size() >= k) {
        long last_bucket = ((long)nums[i - k] - INT_MIN) / ((long)t + 1);
        m.erase(last_bucket);
      }

      m[bucket] = remapped_num;
    }
    return false;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
221. Maximal Square
Given a 2D binary matrix filled with 0's and 1's, find the largest square
containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

/*
    Submission Date: 2017-08-03
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int M = matrix.size();
    if (M == 0) return 0;
    int N = matrix[0].size();
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

    int res = 0;
    for (int i = M - 1; i >= 0; i--) {
      for (int j = N - 1; j >= 0; j--) {
        if (matrix[i][j] == '0') continue;
        dp[i][j] = 1 + min(min(dp[i + 1][j], dp[i + 1][j + 1]), dp[i][j + 1]);
        res = max(res, dp[i][j]);
      }
    }

    return res * res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
222. Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely
filled, and all nodes in the last level are as far left as possible. It can have
between 1 and 2h nodes inclusive at the last level h.

/*
    Submission Date: 2017-08-03
    Runtime: 72 ms
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
  int countNodes(TreeNode* root) {
    if (root == NULL) return 0;

    TreeNode* curr = root;
    int l_depth = 0, r_depth = 0;
    while (curr) {
      curr = curr->left;
      l_depth++;
    }

    curr = root;
    while (curr) {
      curr = curr->right;
      r_depth++;
    }

    if (l_depth == r_depth) {  // filled tree
      return (1 << l_depth) - 1;
    } else {  // not completely filled get the count of left and right with this
              // node
      return 1 + countNodes(root->left) + countNodes(root->right);
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
223. Rectangle Area
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as
shown in the figure. Assume that the total area is never beyond the maximum
possible value of int.
    ----- (C,D)
    |   |
    |   |
    -----
(A,B)

    ----- (G,H)
    |   |
    |   |
    -----
(E,F)


/*
    Submission Date: 2017-08-07
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution2 {
 public:
  // A----C and E---G represents intervals say close_x is A---C meaning C <= G
  // if C < E width is 0 as no intersect
  // else width = C - max(A,E)
  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    pair<int, int> close_x{A, C}, far_x{E, G};
    if (C > G) swap(close_x, far_x);
    int width = 0;
    if (far_x.first < close_x.second) {  // check if two intervals intersect
      width = close_x.second - max(close_x.first, far_x.first);
    }

    pair<int, int> close_y{B, D}, far_y{F, H};
    if (D > H) swap(close_y, far_y);
    int height = 0;
    if (far_y.first < close_y.second) {  // check if two intervals intersect
      height = close_y.second - max(close_y.first, far_y.first);
    }

    int intersect_area = height * width;
    int total_area = (C - A) * (D - B) + (G - E) * (H - F);
    return total_area - intersect_area;
  }
};

class Solution {
 public:
  // for A---C and E--G it is just min(C,G) - max(A,E) if this is negative
  // ie no intersection min(C,G) < max(A,E) just make right = left so width is
  // zero
  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int left = max(A, E), right = max(min(C, G), left);
    int bottom = max(B, F), top = max(min(D, H), bottom);

    int intersect_area = (top - bottom) * (right - left);
    int total_area = (C - A) * (D - B) + (G - E) * (H - F);

    return total_area - intersect_area;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
224. Basic Calculator
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus +
or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
Note: Do not use the eval built-in library function.

/*
    Submission Date: 2017-08-07
    Runtime: 26 ms
    Difficulty: HARD
*/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <functional>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution2 {
  unordered_map<char, function<int(int, int)>> ops_m{
      {'+', [](const int a, const int b) { return a + b; }},
      {'-', [](const int a, const int b) { return a - b; }},
  };

  unordered_map<char, char> toggle{{'+', '-'}, {'-', '+'}};

 public:
  int calculate(string s) {
    for (int i = 0, len = s.size(); i < len; i++) {
      if (i > 0 && s[i - 1] == '-' && s[i] == '(') {
        // the idea is to keep track of "-(" and "("
        // if we get to a ")" we pop. Maintain "-(" count in the stack
        // if it is odd then toggle all '-' and '+' we come across
        stack<char> stk;
        int minus_open_count = 1;
        stk.push('-');
        while (!stk.empty() && ++i < len) {
          if (isspace(s[i]) || isdigit(s[i])) continue;
          if (s[i] == ')') {
            if (stk.top() == '-') minus_open_count--;
            stk.pop();
          } else if (s[i] == '(') {
            stk.push(')');
          } else if (s[i] == '+' || s[i] == '-') {
            bool should_push = s[i] == '-' && s[i + 1] == '(';
            if (minus_open_count % 2 == 1) {
              s[i] = toggle[s[i]];
            }
            if (should_push) {
              stk.push('-');
              minus_open_count++;
              i++;
            }
          } else {
            assert(false);
          }
        }
      }
    }

    s.erase(remove_if(s.begin(), s.end(),
                      [](const char& c) {
                        return isspace(c) || c == '(' || c == ')';
                      }),
            s.end());

    int N = s.size();
    if (N == 0) return 0;

    int res = 0;

    function<int(int, int)> op = ops_m['+'];

    for (int i = 0; i < N; i++) {
      int start = i;
      while (i < N && isdigit(s[i])) {
        i++;
      }

      int val = stoi(s.substr(start, i - start));

      res = op(res, val);
      if (i < N) {
        op = ops_m[s[i]];
      }
    }

    return res;
  }
};

class Solution {
 public:
  int calculate(string s) {
    stack<string> stk;
    int N = s.size();

    for (int i = 0; i < N; i++) {
      // space continue
      if (isspace(s[i])) continue;
      // '(', '+', '-' push to stack
      if (s[i] == '(' || s[i] == '+' || s[i] == '-') {
        stk.push(string(1, s[i]));
      } else if (isdigit(s[i])) {
        // number so get the whole number and push to stack
        int start = i;
        while (i < N && isdigit(s[i])) i++;
        string val = s.substr(start, i - start);
        stk.push(val);
        i--;
      } else if (s[i] == ')') {
        // closing bracket keep popping until one "(" is removed
        // keep evaluating the expression, check if number is preceded by
        // a negative
        int curr = 0;
        while (!stk.empty()) {
          string top = stk.top();
          stk.pop();
          if (top == "(") break;
          int val = stoi(top);
          if (!stk.empty()) {
            if (stk.top() == "-") {
              val *= -1;
              stk.pop();
            } else {
              if (stk.top() == "+") {
                stk.pop();
              } else {
                assert(stk.top() == "(");
              }
            }
          }
          curr += val;
        }
        stk.push(to_string(curr));
      } else {
        assert(false);
      }
    }

    // evaluate remaining stack
    int res = 0;
    while (!stk.empty()) {
      int val = stoi(stk.top());
      stk.pop();
      if (!stk.empty()) {
        if (stk.top() == "-") {
          val *= -1;
        } else {
          assert(stk.top() == "+");
        }
        stk.pop();
      }
      res += val;
    }

    return res;
  }
};

int main() {
  Solution s;
  cout << s.calculate("1 + 1") << ' ' << 2 << endl;
  cout << s.calculate(" 2-1 + 2 ") << ' ' << 3 << endl;
  cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << ' ' << 23 << endl;
  cout << s.calculate("2-(5-6)") << ' ' << 3 << endl;
  cout << s.calculate("(3-(2-(5-(9-(4)))))") << ' ' << 1 << endl;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
225. Implement Stack using Queues
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to
back, peek/pop from front, size, and is empty operations are valid. Depending on
your language, queue may not be supported natively. You may simulate a queue by
using a list or deque (double-ended queue), as long as you use only standard
operations of a queue. You may assume that all operations are valid (for
example, no pop or top operations will be called on an empty stack).

/*
    Submission Date: 2017-08-12
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <queue>

using namespace std;

// one queue - pop efficient, reverse queue everytime push
// push item to queue and take the 0 to N-1 elements before it and place it
// behind it so 1,2,3,4,5 becomes 5,4,3,2,1 through rotating the queue
// 1
// 1,2 -> 2 -> 2,1
// 2,1,3 -> 1,3,2 -> 3,2,1
// 3,2,1,4 -> 2,1,4,3 -> 1,4,3,2 - > 4,3,2,1
// 4,3,2,1,5 -> 3,2,1,5,4 -> 2,1,5,4,3 -> 1,5,4,3,2 -> 5,4,3,2,1
// push - O(n), top/pop/empty O(1)
class MyStack {
  queue<int> q_;

 public:
  MyStack() {}

  void push(int x) {
    q_.push(x);
    for (int i = 0, N = q_.size(); i < N - 1; i++) {
      q_.push(q_.front());
      q_.pop();
    }
  }

  int pop() {
    int front_el = q_.front();
    q_.pop();
    return front_el;
  }

  int top() { return q_.front(); }

  bool empty() { return q_.empty(); }
};

// two queues - pop efficient, same as above 1 queue except instead use
// additional queue to rotate push - o(n), pop/top/empty - o(1) for pop/top just
// choose the non empty queue and return front and pop if necessary empty check
// if both queues are empty push choose the empty queue (any queue if both are
// empty) and push the value to it. Move all items in the other queue into this
// queue this maintains one empty queue and one queue that has all its elements
// reversed e.g insert 1,2,3,4,5 should result in a queue with 5,4,3,2,1 and an
// empty queue
// /* push 1 to A */ [1]        []
// /* push 2 to B */ [1]        [2]         -> []           [2,1]       /*
// remove 1 from A and move to B */
// /* push 3 to A */ [3]        [2,1]       -> [3,2,1]      []          /*
// remove 2,1 from B and move to A */
// /* push 4 to B */ [3,2,1]    [4]         ->  []          [4,3,2,1]   /*
// remove 3,2,1 from A and move to B */
// /* push 5 to A */ [5]        [4,3,2,1]   ->  [5,4,3,2,1] []          /*
// remove 4,3,2,1 from B and move to A */

class MyStack2 {
  queue<int> q1_, q2_;

 public:
  MyStack2() {}

  void push(int x) {
    if (q1_.empty()) {
      q1_.push(x);
      while (!q2_.empty()) {
        q1_.push(q2_.front());
        q2_.pop();
      }
    } else {
      q2_.push(x);
      while (!q1_.empty()) {
        q2_.push(q1_.front());
        q1_.pop();
      }
    }
  }

  int pop() {
    int top_el = top();
    if (q2_.empty()) {
      q1_.pop();
    } else {
      q2_.pop();
    }
    return top_el;
  }

  int top() { return q2_.empty() ? q1_.front() : q2_.front(); }

  bool empty() { return q1_.empty() && q2_.empty(); }
};

// one queue - push efficient
// pop/top - o(n), push/empty - o(1)
class MyStack3 {
  queue<int> q_;

 public:
  MyStack3() {}

  void push(int x) { q_.push(x); }

  int pop() {
    for (int i = 0, N = q_.size(); i < N - 1; i++) {
      q_.push(q_.front());
      q_.pop();
    }
    int last_el = q_.front();
    q_.pop();
    return last_el;
  }

  int top() {
    int last_el = pop();
    push(last_el);
    return last_el;
  }

  bool empty() { return q_.empty(); }
};

// two queues - push efficient
// pop/top - o(n), push/empty - o(1)
// push to non empty queue
// pop by taking everything except the last element in the non empty queue and
// put it in the empty queue take the only element in the empty queue
class MyStack4 {
  queue<int> q1_, q2_;

 public:
  MyStack4() {}

  void push(int x) {
    if (!q1_.empty()) {
      q1_.push(x);
    } else {
      q2_.push(x);
    }
  }

  int popHelper(queue<int>& empty_q, queue<int>& non_empty_q) {
    for (int i = 0, N = non_empty_q.size(); i < N - 1; i++) {
      empty_q.push(non_empty_q.front());
      non_empty_q.pop();
    }

    int last_el = non_empty_q.front();
    non_empty_q.pop();

    return last_el;
  }

  int pop() {
    int last_el = q1_.empty() ? popHelper(q1_, q2_) : popHelper(q2_, q1_);
    return last_el;
  }

  int top() {
    int last_el = pop();
    push(last_el);
    return last_el;
  }

  bool empty() { return q1_.empty() && q2_.empty(); }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
226. Invert Binary Tree
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1

/*
    Submission Date: 2017-07-30
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
  TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) return NULL;
    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
227. Basic Calculator II
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators
and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Note: Do not use the eval built-in library function.

/*
    Submission Date: 2017-08-12
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int getNumber(const string& s, int& i, const int& N) {
    int num = 0;
    bool seen_digit = false;
    while (i < N) {
      if (isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        seen_digit = true;
      } else if (seen_digit) {  // have seen a digit but current is not a digit
                                // meaning end of sequence
        break;
      }
      i++;
    }

    return num;
  }

  int calculate(string s) {
    s = "+" + s + "+";
    int N = s.size();
    int total = 0, prev_val = 0, temp;
    for (int i = 0; i < N;) {
      if (isspace(s[i])) {
        i++;
      } else if (s[i] == '+' || s[i] == '-') {
        total += prev_val;

        bool is_neg = s[i] == '-';
        prev_val = getNumber(s, i, N);
        if (is_neg) prev_val *= -1;
      } else if (s[i] == '*' || s[i] == '/') {
        bool is_multply = s[i] == '*';
        temp = getNumber(s, i, N);

        if (is_multply)
          prev_val *= temp;
        else
          prev_val /= temp;
      } else {
        assert(false);
      }
    }
    return total;
  }
};

class Solution2 {
  unordered_map<char, function<int(int, int)>> ops_m_{
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'/', [](const int& a, const int& b) { return a / b; }},
  };

 public:
  int getNumber(const string& s, int& i, const int N) {
    int num = 0;
    while (i < N && isdigit(s[i])) num = num * 10 + (s[i++] - '0');
    i--;
    return num;
  }

  int evaluate(const vector<int>& nums, const vector<char>& ops) {
    assert(nums.size() == ops.size() + 1);
    int num = nums.front();
    for (int i = 0; i < ops.size(); i++) {
      num = ops_m_[ops[i]](num, nums[i + 1]);
    }
    return num;
  }

  int calculate(string s) {
    int N = s.size();
    vector<int> to_add_nums, to_mul_nums;
    vector<char> to_add_ops, to_mul_ops;
    for (int i = 0; i < N; i++) {
      if (isspace(s[i])) continue;
      if (isdigit(s[i])) {
        int num = getNumber(s, i, N);
        to_mul_nums.push_back(num);
      } else if (s[i] == '+' || s[i] == '-') {
        // once we get to a '+' or '-' it is safe
        // to evaluate whatever multiplication/divide/subtract/add
        // that appears before this
        int num = evaluate(to_mul_nums, to_mul_ops);
        to_mul_nums.clear();
        to_mul_ops.clear();
        to_add_nums.push_back(num);
        to_add_ops.push_back(s[i]);
      } else if (s[i] == '*' || s[i] == '/') {
        to_mul_ops.push_back(s[i]);
      }
    }

    // if it ends on a multiplication
    if (!to_mul_nums.empty()) {
      int num = evaluate(to_mul_nums, to_mul_ops);
      to_add_nums.push_back(num);
    }

    // evaluate the whole stack
    int res = 0;
    if (!to_add_nums.empty()) {
      res = evaluate(to_add_nums, to_add_ops);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
228. Summary Ranges
Given a sorted integer array without duplicates, return the summary of its
ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

/*
    Submission Date: 2017-08-06
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int N = nums.size();
    for (int i = 0; i < N;) {
      int start, prev;
      start = prev = nums[i++];
      while (i < N && nums[i] == prev + 1) {
        prev++;
        i++;
      }
      if (start == prev) {
        res.push_back(to_string(start));
      } else {
        res.push_back(to_string(start) + "->" + to_string(prev));
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
229. Majority Element II
Given an integer array of size n, find all elements that appear more than
⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
/*
    Submission Date: 2017-08-22
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    /*
    Moore’s Voting Algorithm
    using two variables. Candidate search followed by verification step
    */
    // if(nums.empty()) return {};

    int c1 = 0, c2 = 1;
    int c1_count = 0, c2_count = 0;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      if (nums[i] == c1) {
        c1_count++;
      } else if (nums[i] == c2) {
        c2_count++;
      } else if (c1_count == 0) {
        c1 = nums[i];
        c1_count = 1;
      } else if (c2_count == 0) {
        c2 = nums[i];
        c2_count = 1;
      } else {
        c1_count--;
        c2_count--;
      }
    }

    c1_count = 0, c2_count = 0;
    for (int i = 0; i < N; i++) {
      c1_count += nums[i] == c1;
      c2_count += nums[i] == c2;
    }

    vector<int> res;
    if (c1_count > N / 3) res.push_back(c1);
    if (c2_count > N / 3) res.push_back(c2);

    return res;
  }
};

int main() {
  Solution s;
  return 0;
}