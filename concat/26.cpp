
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
540. Single Element in a Sorted Array
Given a sorted array consisting of only integers where every element appears
twice except for one element which appears once. Find this single element that
appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNonDuplicate(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if ((mid % 2 == 0 && nums[mid] == nums[mid + 1]) ||
          (mid % 2 == 1 && nums[mid] == nums[mid - 1])) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return nums[low];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
541. Reverse String II
Given a string and an integer k, you need to reverse the first k characters for every 2k 
characters counting from the start of the string. If there are less than k characters left, 
reverse all of them. If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>

class Solution {
public:
    string reverseStr(string s, int k) {
        string finalStr = "";
        bool reverse = true;
        int i = 0, len = s.size();
        while(i < len) {
            string currentStr = string(1, s[i++]);
            while(i%k != 0 && i < len) {
                currentStr = reverse ? s[i] + currentStr : currentStr + s[i];
                i++;
            }
            finalStr += currentStr;
            reverse ^= true;
        }
        
        return finalStr;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
542. 01 Matrix
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each
cell.

The distance between two adjacent cells is 1.

Example 1:
Input:
0 0 0
0 1 0
0 0 0

Output:
0 0 0
0 1 0
0 0 0

Example 2:
Input:
0 0 0
0 1 0
1 1 1

Output:
0 0 0
0 1 0
1 2 1

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
/*
  Submission Date: 2019-02-10
  Runtime: 220 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int N = matrix.size();
    int M = matrix[0].size();

    vector<vector<int>> res(N, vector<int>(M, -1));
    // from the top left
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (matrix[i][j] == 0) {
          res[i][j] = 0;
        } else {
          if (i > 0 && res[i - 1][j] != -1) {
            int x = 1 + res[i - 1][j];
            res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
          }
          if (j > 0 && res[i][j - 1] != -1) {
            int x = 1 + res[i][j - 1];
            res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
          }
        }
      }
    }

    // from the bottom right
    for (int i = N - 1; i >= 0; i--) {
      for (int j = M - 1; j >= 0; j--) {
        if (i + 1 < N && res[i + 1][j] != -1) {
          int x = 1 + res[i + 1][j];
          res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
        }
        if (j + 1 < M && res[i][j + 1] != -1) {
          int x = 1 + res[i][j + 1];
          res[i][j] = (res[i][j] == -1) ? x : min(res[i][j], x);
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two
nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges
between them.
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
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
  /*
  returns the height of a node so height(root) = 1 + max(height(left),
  height(right)) res can be updated to 2 + height(left) + height(right) as the
  longest path in the left and right go through this node.
  */
  int help(TreeNode* root, int& res) {
    if (root == NULL) return -1;
    int left = help(root->left, res);
    int right = help(root->right, res);
    res = max(res, 2 + left + right);
    return 1 + max(left, right);
  }

  int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    help(root, res);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
547. Friend Circles
There are N students in a class. Some of them are friends, while some are not.
Their friendship is transitive in nature. For example, if A is a direct friend
of B, and B is a direct friend of C, then A is an indirect friend of C. And we
defined a friend circle is a group of students who are direct or indirect
friends.



Given a N*N matrix M representing the friend relationship between students in
the class. If M[i][j] = 1, then the ith and jth students are direct friends with
each other, otherwise not. And you have to output the total number of friend
circles among all the students.


Example 1:
Input:
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend
circle. The 2nd student himself is in a friend circle. So return 2.



Example 2:
Input:
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
students are direct friends, so the 0th and 2nd students are indirect friends.
All of them are in the same friend circle, so return 1.




Note:

N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.

/*
    Submission Date: 2018-07-05
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class UnionFind {
  // key is element, value is rank
  unordered_map<T, int> rank_;
  // key is element, value is parent
  unordered_map<T, T> parent_;

 public:
  bool IsWithinSet(T e) { return parent_.count(e); }

  void CreateSet(T e) {
    assert(!IsWithinSet(e));
    parent_[e] = e;
    rank_[e] = 0;
  }

  // finds the root of e
  T Find(T e) {
    if (parent_[e] != e) {
      // this is not a root (root has parent to be equal itself)
      // so find root and apply path compression along path
      parent_[e] = Find(parent_[e]);
    }
    return parent_[e];
  }

  // unions the sets of e1 and e2 if necessary
  // return whether an union took place
  bool Union(T e1, T e2) {
    T e1_root = Find(e1);
    T e2_root = Find(e2);

    if (e1_root == e2_root) return false;  // same root

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (rank_[e1_root] < rank_[e2_root]) {
      parent_[e1_root] = e2_root;
    } else {
      parent_[e2_root] = e1_root;
      if (rank_[e1_root] == rank_[e2_root]) {
        rank_[e1_root]++;
      }
    }

    return true;
  }
};

class Solution {
 public:
  /*
  basically find how many connected graphs there are
  so use union-find, for every edge from u to v, merge the sets u and v
  at the end find how many sets there are by finding the root of all
  the nodes and counting the distinct ones.
  
  O(N^2) as Union and Find are O(1)
  */
  int findCircleNum(vector<vector<int>>& M) {
    int N = M.size();
    UnionFind<int> uf;
    for (int i = 0; i < N; i++) uf.CreateSet(i);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (M[i][j] == 0) continue;
        uf.Union(i, j);
      }
    }

    unordered_set<int> roots;
    for (int i = 0; i < N; i++) roots.insert(uf.Find(i));
    return roots.size();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
551. Student Attendance Record I
You are given a string representing an attendance record for a student. The
record only contains the following three characters: 'A' : Absent. 'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than
one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his
attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False
/*
    Submission Date: 2018-06-08
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool checkRecord(string s) {
    int l_streak = 0;
    bool seen_absent = false;
    for (const auto& c : s) {
      if (c == 'L') {
        if (l_streak == 2) return false;
        l_streak++;
      } else {
        if (c == 'A') {
          if (seen_absent) return false;
          seen_absent = true;
        }  // c == 'P'

        l_streak = 0;
      }
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
553. Optimal Division
Given a list of positive integers, the adjacent integers will perform the float
division. For example, [2,3,4] -> 2 / 3 / 4.

However, you can add any number of parenthesis at any position to change the
priority of operations. You should find out how to add parenthesis to get the
maximum result, and return the corresponding expression in string format. Your
expression should NOT contain redundant parenthesis.

Example:
Input: [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant, since they
don't influence the operation priority. So you should return "1000/(100/10/2)".

Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2



Note:

The length of the input array is [1, 10].
Elements in the given array will be in range [2, 1000].
There is only one optimal division for each test case.

/*
    Submission Date: 2018-06-30
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  o(n) for a series of number dp_max[i] = nums[i]/dp_min[i+1]
  the minimum would be just divide all the numbers from [1,N)
  as they are all integers meaning its some number divide by all integers
  in the denominator which would be the smallest. if nums[i] had
  decimals than the smallest would not be dividing all the numbers as it could
  be equivalent to putting a integer number in the numerator
  
  so return nums[0] / (nums[1]/nums[2]/ .... /nums[N-1])
  */
  string optimalDivision(vector<int>& nums) {
    int N = nums.size();
    string res = to_string(nums[0]);
    if (N == 1) return res;
    if (N == 2) return res + "/" + to_string(nums[1]);

    res += "/(";
    for (int i = 1; i < N; i++) {
      res += to_string(nums[i]) + (i == N - 1 ? ")" : "/");
    }

    return res;
  }

  /*
  o(n^2) dp where dp_max[i] is the largest number created from [i, N) and
  dp_min[i] is the smallest then dp_max[i] is max(product of numbers between [i,
  j) /dp_min[j]) for j > i and dp_min[i] is min(product of numbers between [i,
  j) /dp_max[j]) for j > i
  
  strings in dp_max and dp_min are surrounded by parenthesis while product of
  numbers aren't
  
  return dp_max[0]
  */
  string optimalDivision2(vector<int>& nums) {
    int N = nums.size();
    vector<pair<string, double>> dp_max(N, {"", INT_MIN}),
        dp_min(N, {"", INT_MAX});
    dp_max[N - 1] = {to_string(nums[N - 1]), nums[N - 1]};
    dp_min[N - 1] = dp_max[N - 1];

    if (N == 1) return dp_max[0].first;

    for (int i = N - 2; i >= 0; i--) {
      string curr_s = to_string(nums[i]);
      double curr = nums[i];
      for (int j = i + 1; j < N; j++) {
        if (dp_max[i].second < curr / dp_min[j].second) {
          dp_max[i] = {"(" + curr_s + "/" + dp_min[j].first + ")",
                       curr / dp_min[j].second};
        }

        if (dp_min[i].second > curr / dp_max[j].second) {
          dp_min[i] = {"(" + curr_s + "/" + dp_max[j].first + ")",
                       curr / dp_max[j].second};
        }

        curr /= nums[j];
        curr_s += "/" + to_string(nums[j]);
      }
    }

    return dp_max[0].first.substr(1, dp_max[0].first.size() - 2);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
554. Brick Wall
There is a brick wall in front of you. The wall is rectangular and has several
rows of bricks. The bricks have the same height but different width. You want to
draw a vertical line from the top to the bottom and cross the least bricks.

The brick wall is represented by a list of rows. Each row is a list of integers
representing the width of each brick in this row from left to right.

If your line go through the edge of a brick, then the brick is not considered as
crossed. You need to find out how to draw the line to cross the least bricks and
return the number of crossed bricks.

You cannot draw a line just along one of the two vertical edges of the wall, in
which case the line will obviously cross no bricks.

Example:

Input: [[1,2,2,1],
        [3,1,2],
        [1,3,2],
        [2,4],
        [3,1,2],
        [1,3,1,1]]

Output: 2

Explanation:

Note:

  The width sum of bricks in different rows are the same and won't exceed
INT_MAX.
  The number of bricks in each row is in range [1,10,000]. The height of wall is
in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.
/*
  Submission Date: 2019-01-26
  Runtime: 44 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  put all the x boundaries into a hashmap. Since the x boundaries
  in a row will always be increasing, we dont need to worry about
  conflicts in a row. the most frequent x boundary is where we
  want to cut so the result is just the number of rows minus
  that.
  */
  int leastBricks(vector<vector<int>>& wall) {
    unordered_map<int, int> freq;
    int max_freq = 0;
    for (auto& row : wall) {
      int sum = 0;
      for (int i = 0; i < row.size(); i++) {
        sum += row[i];
        freq[sum]++;
        if (i != row.size() - 1) {
          max_freq = max(max_freq, freq[sum]);
        }
      }
    }

    return wall.size() - max_freq;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
557. Reverse Words in a String III
Given a string, you need to reverse the order of characters in each word within
a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not
be any extra space in the string.
/*
    Submission Date: 2018-05-31
    Runtime: 28 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  // from index 'start', find a space and reverse everything between start and
  // space. change start to space + 1.
  string reverseWords(string s) {
    int start = 0;
    while (s.find(' ', start) != string::npos) {
      int space_ind = s.find(' ', start);
      reverse(s.begin() + start, s.begin() + space_ind);
      start = space_ind + 1;
    }

    reverse(s.begin() + start, s.end());
    return s;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
558. Quad Tree Intersection
A quadtree is a tree data in which each internal node has exactly four children:
topLeft, topRight, bottomLeft and bottomRight. Quad trees are often used to
partition a two-dimensional space by recursively subdividing it into four
quadrants or regions.

We want to store True/False information in our quad tree. The quad tree is used
to represent a N * N boolean grid. For each node, it will be subdivided into
four children nodes until the values in the region it represents are all the
same. Each node has another two boolean attributes : isLeaf and val. isLeaf is
true if and only if the node is a leaf node. The val attribute for a leaf node
contains the value of the region it represents.

For example, below are two quad trees A and B:

A:
+-------+-------+   T: true
|       |       |   F: false
|   T   |   T   |
|       |       |
+-------+-------+
|       |       |
|   F   |   F   |
|       |       |
+-------+-------+
topLeft: T
topRight: T
bottomLeft: F
bottomRight: F

B:
+-------+---+---+
|       | F | F |
|   T   +---+---+
|       | T | T |
+-------+---+---+
|       |       |
|   T   |   F   |
|       |       |
+-------+-------+
topLeft: T
topRight:
     topLeft: F
     topRight: F
     bottomLeft: T
     bottomRight: T
bottomLeft: T
bottomRight: F

Your task is to implement a function that will take two quadtrees and return a
quadtree that represents the logical OR (or union) of the two trees.

A:                 B:                 C (A or B):
+-------+-------+  +-------+---+---+  +-------+-------+
|       |       |  |       | F | F |  |       |       |
|   T   |   T   |  |   T   +---+---+  |   T   |   T   |
|       |       |  |       | T | T |  |       |       |
+-------+-------+  +-------+---+---+  +-------+-------+
|       |       |  |       |       |  |       |       |
|   F   |   F   |  |   T   |   F   |  |   T   |   F   |
|       |       |  |       |       |  |       |       |
+-------+-------+  +-------+-------+  +-------+-------+

Note:

  Both A and B represent grids of size N * N.
  N is guaranteed to be a power of 2.
  If you want to know more about the quad tree, you can refer to its wiki.
  The logic OR operation is defined as this: "A or B" is true if A is true, or
if B is true, or if both A and B are true.
/*
  Submission Date: 2019-01-26
  Runtime: 212 ms
  Difficulty: EASY
*/
#include <cassert>
#include <iostream>

using namespace std;

class Node {
 public:
  bool val;
  bool isLeaf;
  Node* topLeft;
  Node* topRight;
  Node* bottomLeft;
  Node* bottomRight;

  Node() {}

  Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
       Node* _bottomLeft, Node* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

class Solution {
 public:
  bool isTrue(Node* node) { return node->isLeaf && node->val; }
  Node* intersect(Node* quadTree1, Node* quadTree2) {
    assert(quadTree1 != nullptr && quadTree2 != nullptr);

    if (isTrue(quadTree1) || isTrue(quadTree2))
      return new Node(true, true, nullptr, nullptr, nullptr, nullptr);

    if (quadTree1->isLeaf) return quadTree2;
    if (quadTree2->isLeaf) return quadTree1;

    Node* node = new Node();
    node->isLeaf = false;
    node->topLeft = intersect(quadTree1->topLeft, quadTree2->topLeft);
    node->topRight = intersect(quadTree1->topRight, quadTree2->topRight);
    node->bottomLeft = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
    node->bottomRight =
        intersect(quadTree1->bottomRight, quadTree2->bottomRight);

    if (isTrue(node->topLeft) && isTrue(node->topRight) &&
        isTrue(node->bottomLeft) && isTrue(node->bottomRight)) {
      return new Node(true, true, nullptr, nullptr, nullptr, nullptr);
    }
    return node;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
559. Maximum Depth of N-ary Tree
Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

For example, given a 3-ary tree:
 


 

We should return its max depth, which is 3.

Note:


    The depth of the tree is at most 1000.
    The total number of nodes is at most 5000.

/*
    Submission Date: 2018-07-13
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}

  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
 public:
  int maxDepth(Node* root) {
    if (!root) return 0;

    int res = 0;
    for (const auto& c : root->children) res = max(res, maxDepth(c));

    return res + 1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
561. Array Partition I
Given an array of 2n integers, your task is to group these integers into n pairs
of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi)
for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
/*
    Submission Date: 2018-05-31
    Runtime: 85 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
   for a pair ai and bi where bi is not used, it means bi should be the smallest
   element > ai in order to maximize the rest of the result
  */
  int arrayPairSum(vector<int>& nums) {
    int res = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i += 2) res += nums[i];
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
563. Binary Tree Tilt
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of
all left subtree node values and the sum of all right subtree node values. Null
node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input:
         1
       /   \
      2     3
Output: 1
Explanation:
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
/*
    Submission Date: 2018-06-08
    Runtime: 16 ms
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
  /*
  returns the sum of subtree with node as root
  */
  int help(TreeNode* node, int& res) {
    if (node == NULL) return 0;
    int left = help(node->left, res);
    int right = help(node->right, res);
    res += abs(left - right);
    return node->val + left + right;
  }

  int findTilt(TreeNode* root) {
    int res = 0;
    help(root, res);
    return res;
  }
};

int main() { return 0; }