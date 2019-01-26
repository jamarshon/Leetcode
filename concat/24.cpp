
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
492. Construct the Rectangle
For a web developer, it is very important to know how to design a web page's
size. So, given a specific rectangular web page’s area, your job by now is to
design a rectangular web page, whose length L and width W satisfy the following
requirements:

1. The area of the rectangular web page you designed must equal to the given
target area.

2. The width W should not be larger than the length L, which means L >= W.

3. The difference between length L and width W should be as small as possible.
You need to output the length L and the width W of the web page you designed in
sequence. Example: Input: 4 Output: [2, 2] Explanation: The target area is 4,
and all the possible ways to construct it are [1,4], [2,2], [4,1]. But according
to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not
optimal compared to [2,2]. So the length L is 2, and the width W is 2. Note: The
given area won't exceed 10,000,000 and is a positive integer The web page's
width and length you designed must be positive integers.
/*
    Submission Date: 2018-06-07
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> constructRectangle(int area) {
    for (int i = sqrt(area); i >= 1; i--) {
      if (area % i == 0) return {area / i, i};
    }
    return {};
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
495. Teemo Attacking
In LOL world, there is a hero called Teemo and his attacking can make his enemy
Ashe be in poisoned condition. Now, given the Teemo's attacking ascending time
series towards Ashe and the poisoning time duration per Teemo's attacking, you
need to output the total time that Ashe is in poisoned condition.


You may assume that Teemo attacks at the very beginning of a specific time
point, and makes Ashe be in poisoned condition immediately.

Example 1:
Input: [1,4], 2
Output: 4
Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be
poisoned immediately. This poisoned status will last 2 seconds until the end of
time point 2. And at time point 4, Teemo attacks Ashe again, and causes Ashe to
be in poisoned status for another 2 seconds. So you finally need to output 4.




Example 2:
Input: [1,2], 2
Output: 3
Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be
poisoned. This poisoned status will last 2 seconds until the end of time point
2. However, at the beginning of time point 2, Teemo attacks Ashe again who is
already in poisoned status. Since the poisoned status won't add up together,
though the second poisoning attack will still work at time point 2, it will stop
at the end of time point 3. So you finally need to output 3.




Note:

You may assume the length of given time series array won't exceed 10000.
You may assume the numbers in the Teemo's attacking time series and his
poisoning time duration per attacking are non-negative integers, which won't
exceed 10,000,000.

/*
    Submission Date: 2018-07-01
    Runtime: 103 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findPoisonedDuration(vector<int>& timeSeries, int duration) {
    if (timeSeries.empty()) return 0;

    int N = timeSeries.size();

    int res = duration;
    for (int i = 1; i < N; i++) {
      res += min(duration, timeSeries[i] - timeSeries[i - 1]);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
496. Next Greater Element I
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s
elements are subset of nums2. Find all the next greater numbers for nums1's
elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to
its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for
it in the second array, so output -1. For number 1 in the first array, the next
greater number for it in the second array is 3. For number 2 in the first array,
there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the
second array is 3. For number 4 in the first array, there is no next greater
number for it in the second array, so output -1. Note: All elements in nums1 and
nums2 are unique. The length of both nums1 and nums2 would not exceed 1000.
/*
    Submission Date: 2018-06-02
    Runtime: 11 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      For a stack of decreasing number, if there is a number x encountered.
      All the numbers in the stack that x is greater than will have their return
     value to be x and x is placed in the stack. This means there is no number
     in the stack that is less than x eg [1,3,4,2,3]
       []     1 => [1]
       [1]    3 => [3]    update greater(1) = 3
       [3]    4 => [4]    update greater(3) = 4
       [4]    2 => [4,2]
       [4,2]  3 => [4,3]  update greater(2) = 3
  */
  vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
    if (nums.empty()) return {};

    int N = findNums.size();
    // decreasing numbers
    stack<int> stk;

    unordered_map<int, int> val_to_greater_val;
    for (const auto& x : nums) {
      while (!stk.empty() && stk.top() < x) {
        val_to_greater_val[stk.top()] = x;
        stk.pop();
      }

      stk.push(x);
    }

    vector<int> res;
    for (const auto& x : findNums) {
      res.push_back(val_to_greater_val.count(x) ? val_to_greater_val[x] : -1);
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
498. Diagonal Traverse
Given a matrix of M x N elements (M rows, N columns), return all elements of the
matrix in diagonal order as shown in the below image.


Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation:




Note:

The total number of elements of the given matrix will not exceed 10,000.

/*
    Submission Date: 2018-07-09
    Runtime: 52 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  all numbers in a diagonal indices add up to the same number (e.g i + j == x)
  the max is N-1 + M-1 = N - M - 2
  so for x = [0, N - M - 2], start from the top row go down i = [0, N) and see
  if x - i produces a j that is within the bounds [0, M). 0 <= x - i < M means
  x - M < i && i <= x
  0 <= i && i < N
  
  i > max(-1, x - M)
  i < min(N, x + 1)
  
  This creates all the diagonals going down.
  reverse the even diagonals and return
  */
  vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<int> res;

    for (int x = 0; x < N + M - 1; x++) {
      int sz = res.size();
      for (int i = max(0, x - M + 1); i < min(N, x + 1); i++) {
        res.push_back(matrix[i][x - i]);
      }
      if (x % 2 == 0) reverse(res.begin() + sz, res.end());
    }

    return res;
  }
};

class Solution2 {
  int d[2][2] = {{-1, 1}, {1, -1}};
  bool up = true;

 public:
  /*
  toggle between going up and down when hit out of bounds
  to find the new coordinate
      if going up:
          if hits the right boundary then can't keep going right so go down
          else keep going right
      if going down:
          if hits the bottom boundary then can't keep going down so go right
          else keep going down
  */
  vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<int> res;
    int x = 0, y = 0;
    for (int i = 0; i < N * M; i++) {
      res.push_back(matrix[y][x]);
      int new_x = x + d[up][0];
      int new_y = y + d[up][1];
      if (0 <= new_x && new_x < M && 0 <= new_y && new_y < N) {
        x = new_x;
        y = new_y;
      } else {
        if (up) {
          if (new_x == M)
            y++;
          else
            x++;
        } else {
          if (new_y == N)
            x++;
          else
            y++;
        }
        up ^= 1;
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
500. Keyboard Row
Given a List of words, return the words that can be typed using letters of
alphabet on only one row's of American keyboard like the image below.


American keyboard


Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
Note:
You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // Have a map of character to row. Loop through each string and check if all
  // the characters come from the same row.
  vector<string> findWords(vector<string>& words) {
    vector<string> v{"qwertyuiop", "asdfghjkl", "zxcvbnm"};
    unordered_map<char, int> m;

    for (int i = 0; i < v.size(); i++) {
      for (const auto& c : v[i]) m[c] = i;
    }

    vector<string> res;
    for (const auto& s : words) {
      int ind = -1;
      bool can_add = true;
      for (const auto& c : s) {
        if (ind == -1) ind = m[tolower(c)];
        if (m[tolower(c)] != ind) {
          can_add = false;
          break;
        }
      }

      if (can_add) res.push_back(s);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
501. Find Mode in Binary Search Tree
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most
frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to
the node's key. The right subtree of a node contains only nodes with keys
greater than or equal to the node's key. Both the left and right subtrees must
also be binary search trees. For example: Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the
implicit stack space incurred due to recursion does not count).
/*
    Submission Date: 2018-06-09
    Runtime: 15 ms
    Difficulty: EASY
*/
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
  typedef pair<int, int> pii;

  /*
  inorder traversal where if the current element is the same as the last then
  increase the frequency else reset it. if the frequency is greater than res
  frequency, then change res else if the frequency is the same than push back
  to res
  */
  void help(TreeNode* node, pii& curr, vector<pii>& res) {
    if (node == NULL) return;
    help(node->left, curr, res);

    if (curr.first == -1 || curr.second != node->val) {
      curr = {1, node->val};
    } else {
      curr.first++;
    }

    if (curr.first > res[0].first) {
      res = {curr};
    } else if (curr.first == res[0].first) {
      res.push_back(curr);
    }

    help(node->right, curr, res);
  }

  vector<int> findMode(TreeNode* root) {
    if (root == NULL) return {};

    vector<pii> res = {{0, INT_MIN}};
    pii curr = {-1, INT_MIN};
    help(root, curr, res);

    vector<int> v_i;
    v_i.reserve(res.size());
    for (const auto& p : res) v_i.push_back(p.second);
    return v_i;
  }
};
int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
503. Next Greater Element II
Given a circular array (the next element of the last element is the first
element of the array), print the Next Greater Number for every element. The Next
Greater Number of a number x is the first greater number to its traversing-order
next in the array, which means you could search circularly to find its next
greater number. If it doesn't exist, output -1 for this number.


Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; The number 2 can't find
next greater number; The second 1's next greater number needs to search
circularly, which is also 2.



Note:
The length of given array won't exceed 10000.

/*
    Submission Date: 2018-07-08
    Runtime: 68 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
   stack is in decreasing order, it represents an index which has
   not met an element greater than it. for all the elements that
   are smaller than the current element, make res[element] = current element
   then put current element in the stack
   
   if we ensure that the stack only has elements from 0 < N and traverse
   the array twice then after the first traversal, there will be a stack
   of elements that have nothing greater than it from [i, N) and in the
   second traversal it will try to find [0, i)
  */
  vector<int> nextGreaterElements(vector<int>& nums) {
    int N = nums.size();
    vector<int> res(N, -1);
    stack<int> stk;
    for (int i = 0; i < 2 * N; i++) {
      while (!stk.empty() && nums[stk.top()] < nums[i % N]) {
        res[stk.top()] = nums[i % N];
        stk.pop();
      }

      if (i < N) stk.push(i);
    }

    return res;
  }
};

class Solution2 {
 public:
  /*
  maintian a stack of increasing numbers similar to before but
  first prepopulate the stack by running through the array once
  then run through the array again, and if the back element in the
  stack is equal to the current element then remove it from the stk
  to preserve wraparound that does not exceed index i
  */
  vector<int> nextGreaterElements(vector<int>& nums) {
    int N = nums.size();
    list<int> stk;
    for (int i = N - 1; i >= 0; i--) {
      while (!stk.empty() && stk.front() <= nums[i]) {
        stk.pop_front();
      }
      stk.push_front(nums[i]);
    }

    vector<int> res(N, -1);
    for (int i = N - 1; i >= 0; i--) {
      if (!stk.empty() && stk.back() == nums[i]) {
        stk.pop_back();
      }

      while (!stk.empty() && stk.front() <= nums[i]) {
        stk.pop_front();
      }

      if (!stk.empty()) {
        res[i] = stk.front();
      }
      stk.push_front(nums[i]);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
504. Base 7
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].
/*
    Submission Date: 2018-06-08
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  string convertToBase7(int num) {
    if (num == 0) return "0";

    string sgn = num < 0 ? "-" : "";
    num = abs(num);

    string res = "";
    while (num) {
      res.push_back((num % 7) + '0');
      num /= 7;
    }

    reverse(res.begin(), res.end());
    return sgn + res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
506. Relative Ranks
Given scores of N athletes, find their relative ranks and the people with the
top three highest scores, who will be awarded medals: "Gold Medal", "Silver
Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they
got "Gold Medal", "Silver Medal" and "Bronze Medal". For the left two athletes,
you just need to output their relative ranks according to their scores. Note: N
is a positive integer and won't exceed 10,000. All the scores of athletes are
guaranteed to be unique.
/*
    Submission Date: 2018-06-08
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findRelativeRanks(vector<int>& nums) {
    map<int, int, greater<int>> m;
    for (int i = 0; i < nums.size(); i++) m[nums[i]] = i;

    vector<string> rep{"Gold Medal", "Silver Medal", "Bronze Medal"};

    vector<string> res(nums.size());
    int ind = 0;
    for (const auto& kv : m) {
      res[kv.second] = ind < 3 ? rep[ind] : to_string(ind + 1);
      ind++;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
507. Perfect Number
We define the Perfect Number is a positive integer that is equal to the sum of
all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect
number and false when it is not. Example: Input: 28 Output: True Explanation: 28
= 1 + 2 + 4 + 7 + 14 Note: The input number n will not exceed 100,000,000. (1e8)
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool checkPerfectNumber(int num) {
    if (num < 2) return false;
    int res = 1;
    for (int i = 2; i <= sqrt(num); i++) {
      if (num % i == 0) {
        res += i;
        res += num / i;
      }
    }

    return res == num;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
508. Most Frequent Subtree Sum
Given the root of a tree, you are asked to find the most frequent subtree sum.
The subtree sum of a node is defined as the sum of all the node values formed by
the subtree rooted at that node (including the node itself). So what is the most
frequent subtree sum value? If there is a tie, return all the values with the
highest frequency in any order.


Examples 1
Input:
  5
 /  \
2   -3

return [2, -3, 4], since all the values happen only once, return all of them in
any order.


Examples 2
Input:
  5
 /  \
2   -5

return [2], since 2 happens twice, however -5 only occur once.


Note:
You may assume the sum of values in any subtree is in the range of 32-bit signed
integer.

/*
    Submission Date: 2018-06-30
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
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
 public:
  int f(TreeNode* node, unordered_map<int, int>& sum_to_freq, int& max_freq) {
    if (node == NULL) return 0;

    int sum = node->val + f(node->left, sum_to_freq, max_freq) +
              f(node->right, sum_to_freq, max_freq);
    sum_to_freq[sum]++;
    max_freq = max(max_freq, sum_to_freq[sum]);
    return sum;
  }

  vector<int> findFrequentTreeSum(TreeNode* root) {
    unordered_map<int, int> sum_to_freq;
    int max_freq = 0;
    f(root, sum_to_freq, max_freq);
    vector<int> res;
    for (const auto& kv : sum_to_freq)
      if (kv.second == max_freq) res.push_back(kv.first);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
513. Find Bottom Left Tree Value
Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2:
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.
/*
    Submission Date: 2018-06-24
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int findBottomLeftValue(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);

    TreeNode* res = NULL;
    while (!q.empty()) {
      res = q.front();

      int level = q.size();
      for (int i = 0; i < level; i++) {
        TreeNode* node = q.front();
        q.pop();
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      }
    }

    return res->val;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

Example:
Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]

/*
    Submission Date: 2018-06-29
    Runtime: 15 ms
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
  vector<int> largestValues(TreeNode* root) {
    if (root == NULL) return {};
    vector<int> res;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      int n = q.size();
      int max_level = q.front()->val;
      for (int i = 0; i < n; i++) {
        TreeNode* curr = q.front();
        q.pop();
        max_level = max(max_level, curr->val);
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
      res.push_back(max_level);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
520. Detect Capital
Given a word, you need to judge whether the usage of capitals
in it is right or not.

We define the usage of capitals in a word to be right when one
of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than
one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a
right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase
and lowercase latin letters.

/*
    Submission Date: 2017-07-30
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool detectCapitalUse(string word) {
    int N = word.size();
    int capital_count = 0, lower_count = 0;
    for (auto c : word) {
      capital_count += isupper(c) != 0;
      lower_count += islower(c) != 0;
    }

    return capital_count == N || lower_count == N ||
           (capital_count == 1 && lower_count == N - 1 && isupper(word[0]));
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
521. Longest Uncommon Subsequence I
Given a group of two strings, you need to find the longest uncommon subsequence
of this group of two strings. The longest uncommon subsequence is defined as the
longest subsequence of one of these strings and this subsequence should not be
any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting
some characters without changing the order of the remaining elements. Trivially,
any string is a subsequence of itself and an empty string is a subsequence of
any string.

The input will be two strings, and the output needs to be the length of the
longest uncommon subsequence. If the longest uncommon subsequence doesn't exist,
return -1.

Example 1:
Input: "aba", "cdc"
Output: 3
Explanation: The longest uncommon subsequence is "aba" (or "cdc"),
because "aba" is a subsequence of "aba",
but not a subsequence of any other strings in the group of two strings.
Note:

Both strings' lengths will not exceed 100.
Only letters from a ~ z will appear in input strings.
/*
    Submission Date: 2018-06-02
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
    question is asking if for all subsequences of A (ss_A) and all subsequences
    of B (ss_B) what is the longest ss_A that is not ss_B and vice versa

    if A == B, then no matter what subsequence of A is made, it can be made in B
    so return -1 if len(A) > len(B) then removing letters from B will always be
    smaller than A so return A if len(A) < len(B) then removing letters from A
    will always be smaller than B  so return B if len(A) == len(B), since they
    are not the same if we arbitrarily choose A and start removing letters from
    B it will always be smaller than A, so return A. the samething can occur if
    choose B arbitrarily.
  */
  int findLUSlength(string a, string b) {
    if (a == b) return -1;
    return max(a.size(), b.size());
  }
};

int main() { return 0; }