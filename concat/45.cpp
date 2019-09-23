
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1047. Remove All Adjacent Duplicates In String
Given a string S of lowercase letters, a duplicate removal consists of choosing
two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is
guaranteed the answer is unique.

Example 1:

Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and
equal, and this is the only possible move.  The result of this move is that the
string is "aaca", of which only "aa" is possible, so the final string is "ca".

Note:

  1 <= S.length <= 20000
  S consists only of English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeDuplicates(string S) {
    // using a stack if we encounter a character
    // that was previously seen then we can pop from
    // the stack and not add the current character.
    // this exposes a previous character in the string
    // which can match with the next character as needed.
    vector<char> stk;
    for (int i = 0; i < S.size(); i++) {
      if (!stk.empty() && stk.back() == S[i])
        stk.pop_back();
      else
        stk.push_back(S[i]);
    }

    return string(stk.begin(), stk.end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1051. Height Checker
Students are asked to stand in non-decreasing order of heights for an annual
photo.

Return the minimum number of students not standing in the right positions. 
(This is the number of students that must move in order for all students to be
standing in non-decreasing order of height.)

Example 1:

Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right
positions.

Note:

  1 <= heights.length <= 100
  1 <= heights[i] <= 100
/*
  Submission Date: 2019-08-25
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // sort the list and see compare elmentwise between
  // the two lists to see how many elements are out of place
  int heightChecker(vector<int>& heights) {
    int res = 0;
    vector<int> v = heights;
    sort(v.begin(), v.end());
    for (int i = 0; i < heights.size(); i++) res += v[i] != heights[i];
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1071. Greatest Common Divisor of Strings
For strings S and T, we say "T divides S" if and only if S = T + ... + T  (T
concatenated with itself 1 or more times)

Return the largest string X such that X divides str1 and X divides str2.

Example 1:

Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

Example 2:

Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

Example 3:

Input: str1 = "LEET", str2 = "CODE"
Output: ""

Note:

  1 <= str1.length <= 1000
  1 <= str2.length <= 1000
  str1[i] and str2[i] are English uppercase letters.
/*
  Submission Date: 2019-09-21
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  string gcdOfStrings(string str1, string str2) {
    /*
    Lyndon and Schützenberger states that A+B=B+A
    (commutative concatenation) iff A and B consist of a
    substring C where  C^i = C+...+C = A and C^j = C+...+C = B
    ie both strings are the powers of the same
    string
    */
    return str1 + str2 == str2 + str1
               ? str1.substr(0, gcd(str1.size(), str2.size()))
               : "";
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1078. Occurrences After Bigram
Given words first and second, consider occurrences in some text of the form
"first second third", where second comes immediately after first, and third
comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second
= "good"
Output: ["girl","student"]

Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]

Note:

  1 <= text.length <= 1000
  text consists of space separated words, where each word consists of lowercase
English letters.
  1 <= first.length, second.length <= 10
  first and second consist of lowercase English letters.
/*
  Submission Date: 2019-09-04
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  // store the last two words and return the current word
  // if the last two words match `first`, `second`
  vector<string> findOcurrences(string text, string first, string second) {
    vector<string> res;
    stringstream ss(text);
    string token;
    string last, lastlast;
    while (ss >> token) {
      if (lastlast.empty()) {
        lastlast = token;
      } else if (last.empty()) {
        last = token;
      } else {
        if (lastlast == first && last == second) {
          res.push_back(token);
        }
        lastlast = last;
        last = token;
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1079. Letter Tile Possibilities
You have a set of tiles, where each tile has one letter tiles[i] printed on it. 
Return the number of possible non-empty sequences of letters you can make.

Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
"ABA", "BAA".

Example 2:

Input: "AAABBC"
Output: 188

Note:

  1 <= tiles.length <= 7
  tiles consists of uppercase English letters.
/*
  Submission Date: 2019-09-21
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int f(vector<int>& count) {
    int sum = 0;
    for (int i = 0; i < 26; i++) {
      // no letters here
      if (count[i] == 0) continue;
      // use this letter
      sum++;
      count[i]--;
      sum += f(count);
      count[i]++;
    }
    return sum;
  }
  int numTilePossibilities(string tiles) {
    vector<int> count(26, 0);
    for (const auto& c : tiles) count[c - 'A']++;
    return f(count);
  }
};

class Solution2 {
 public:
  void f(const string& tiles, const int& index, const string& curr,
         unordered_set<string>& comb) {
    if (!curr.empty()) {
      comb.insert(curr);
    }
    if (index >= tiles.size()) return;

    // use this letter by putting it any of the positions of curr
    for (int i = 0; i <= curr.size(); i++) {
      f(tiles, index + 1, curr.substr(0, i) + tiles[index] + curr.substr(i),
        comb);
    }
    // ignore this letter
    f(tiles, index + 1, curr, comb);
  }
  int numTilePossibilities(string tiles) {
    unordered_set<string> comb;
    f(tiles, 0, "", comb);
    // for(auto e: comb) cout << e << endl;
    return comb.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1089. Duplicate Zeros
Given a fixed length array arr of integers, duplicate each occurrence of zero,
shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything
from your function.

Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,0,0,2,3,0,0,4]

Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,2,3]

Note:

  1 <= arr.length <= 10000
  0 <= arr[i] <= 9
/*
  Submission Date: 2019-09-17
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    /*
    two passes where i is the original arr index
    and j is the new arr index. stop when j >= N
    then go backwards and fill
    */
    int N = arr.size();
    int i = 0, j = 0;
    for (; i < N && j < N; i++) {
      j += (arr[i] == 0) ? 2 : 1;
    }

    while (i >= 0 && j >= 0) {
      i--;
      if (i >= 0) {
        if (arr[i] == 0) {
          if (j - 1 < N) arr[j - 1] = 0;
          if (j - 2 < N) arr[j - 2] = 0;
          j -= 2;
        } else {
          arr[j - 1] = arr[i];
          j--;
        }
      }
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1103. Distribute Candies to People
We distribute some number of candies, to a row of n = num_people people in the
following way:

We then give 1 candy to the first person, 2 candies to the second person, and so
on until we give n candies to the last person.

Then, we go back to the start of the row, giving n + 1 candies to the first
person, n + 2 candies to the second person, and so on until we give 2 *
n candies to the last person.

This process repeats (with us giving one more candy each time, and moving to the
start of the row after we reach the end) until we run out of candies.  The last
person will receive all of our remaining candies (not necessarily one more than
the previous gift).

Return an array (of length num_people and sum candies) that represents the final
distribution of candies.

Example 1:

Input: candies = 7, num_people = 4
Output: [1,2,3,1]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0,0].
On the third turn, ans[2] += 3, and the array is [1,2,3,0].
On the fourth turn, ans[3] += 1 (because there is only one candy left), and the
final array is [1,2,3,1].

Example 2:

Input: candies = 10, num_people = 3
Output: [5,2,3]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0].
On the third turn, ans[2] += 3, and the array is [1,2,3].
On the fourth turn, ans[0] += 4, and the final array is [5,2,3].

Constraints:

  1 <= candies <= 10^9
  1 <= num_people <= 1000
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> distributeCandies(int candies, int num_people) {
    int i = 1, j = 0;
    vector<int> res(num_people, 0);
    while (candies) {
      i = min(candies, i);
      candies -= i;
      res[j] += i;
      i++;
      j = (j + 1) % num_people;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1104. Path In Zigzag Labelled Binary Tree
In an infinite binary tree where every node has two children, the nodes are
labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is
left to right, while in the even numbered rows (second, fourth, sixth,...), the
labelling is right to left.

Given the label of a node in this tree, return the labels in the path from the
root of the tree to the node with that label.

Example 1:

Input: label = 14
Output: [1,3,4,14]

Example 2:

Input: label = 26
Output: [1,2,6,10,26]

Constraints:

  1 <= label <= 10^6
/*
  Submission Date: 2019-09-22
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> pathInZigZagTree(int label) {
    /*
    get the current level, reverse the level and
    divide by two to get the parent
    to reverse a number y around x do 2x-y
    now for level i in a tree [2^i, 2^(i+1)-1] the
    center is (2^i + 2^(i+1)-1)/2 so to reverse a level
    just reverse around the center
    */
    int level = log2(label);
    vector<int> res;
    while (level >= 0) {
      res.push_back(label);
      int flipped = (1 << level) + (1 << (level + 1)) - 1 - label;
      level--;
      label = flipped / 2;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1108. Defanging an IP Address
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

Example 1:
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"

Constraints:

  The given address is a valid IPv4 address.
/*
  Submission Date: 2019-08-25
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
 public:
  string defangIPaddr(string address) {
    istringstream ss(address);
    string res, token;
    string splitter = "[.]";
    while (getline(ss, token, '.')) {
      res += token + splitter;
    }
    return res.substr(0, res.size() - 3);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1110. Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest
(a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the
result in any order.

Example 1:

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Constraints:

  The number of nodes in the given tree is at most 1000.
  Each node has a distinct value between 1 and 1000.
  to_delete.length <= 1000
  to_delete contains distinct values between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 20 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  vector<TreeNode*> res;

 public:
  /*
  return the tree without the deleted nodes
  when a node is deleted, put the pruned left/right (if non null) into the
  forest also add the root if it is not deleted
  */
  TreeNode* helper(TreeNode* root, const unordered_set<int>& delete_set) {
    if (!root) return nullptr;
    auto left = helper(root->left, delete_set);
    auto right = helper(root->right, delete_set);
    if (delete_set.count(root->val)) {
      if (left) res.push_back(left);
      if (right) res.push_back(right);
      return nullptr;
    } else {
      root->left = left;
      root->right = right;
      return root;
    }
  }

  vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    unordered_set<int> delete_set(to_delete.begin(), to_delete.end());
    if (!delete_set.count(root->val)) res.push_back(root);
    helper(root, delete_set);
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1111. Maximum Nesting Depth of Two Valid Parentheses Strings
A string is a valid parentheses string (denoted VPS) if and only if it consists
of "(" and ")" characters only, and:

  It is the empty string, or
  It can be written as AB (A concatenated with B), where A and B are VPS's, or
  It can be written as (A), where A is a VPS.

We can similarly define the nesting depth depth(S) of any VPS S as follows:

  depth("") = 0
  depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
  depth("(" + A + ")") = 1 + depth(A), where A is a VPS.

For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1,
and 2), and ")(" and "(()" are not VPS's.

Given a VPS seq, split it into two disjoint subsequences A and B, such that A
and B are VPS's (and A.length + B.length = seq.length).

Now choose any such A and B such that max(depth(A), depth(B)) is the minimum
possible value.

Return an answer array (of length seq.length) that encodes such a choice of A
and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note that
even though multiple answers may exist, you may return any of them.

Example 1:

Input: seq = "(()())"
Output: [0,1,1,1,1,0]

Example 2:

Input: seq = "()(())()"
Output: [0,0,0,1,1,0,1,1]

Constraints:

  1 <= seq.size <= 10000
/*
  Submission Date: 2019-09-22
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxDepthAfterSplit(string seq) {
    // put all the even '(' in one area with all the
    // odd ')'
    vector<int> res;
    for (int i = 0; i < seq.size(); i++) res.push_back(i & 1 ^ (seq[i] == '('));
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1122. Relative Sort Array
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all
elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are
the same as in arr2.  Elements that don't appear in arr2 should be placed at the
end of arr1 in ascending order.

Example 1:
Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]

Constraints:

  arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  Each arr2[i] is distinct.
  Each arr2[i] is in arr1.
/*
  Submission Date: 2019-09-03
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int, int> arr2_to_ind;
    for (int i = 0; i < arr2.size(); i++) {
      arr2_to_ind[arr2[i]] = i;
    }

    auto end_it = arr2_to_ind.end();

    sort(arr1.begin(), arr1.end(),
         [&arr2_to_ind, &end_it](const int& left, const int& right) {
           auto left_it = arr2_to_ind.find(left);
           auto right_it = arr2_to_ind.find(right);
           if (left_it == end_it && right_it == end_it) {
             // ascending order
             return left < right;
           } else if (left_it == end_it) {
             // put the right in front as the left is not defined
             return false;
           } else if (right_it == end_it) {
             // put the left in front as the right is not defined
             return true;
           } else {
             // return the relative order of left, right
             return left_it->second < right_it->second;
           }
         });

    return arr1;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1123. Lowest Common Ancestor of Deepest Leaves
Given a rooted binary tree, return the lowest common ancestor of its deepest
leaves.

Recall that:

  The node of a binary tree is a leaf if and only if it has no children
  The depth of the root of the tree is 0, and if the depth of a node is d, the
depth of each of its children is d+1.
  The lowest common ancestor of a set S of nodes is the node A with the largest
depth such that every node in S is in the subtree with root A.

Example 1:

Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization
"[1,2,3]".

Example 2:

Input: root = [1,2,3,4]
Output: [4]

Example 3:

Input: root = [1,2,3,4,5]
Output: [2,4,5]

Constraints:

  The given tree will have between 1 and 1000 nodes.
  Each node of the tree will have a distinct value between 1 and 1000.
/*
  Submission Date: 2019-09-23
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
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
  // return lca, depth
  pair<TreeNode*, int> helper(TreeNode* curr) {
    if (!curr) return {nullptr, 0};
    auto left = helper(curr->left);
    auto right = helper(curr->right);
    // same depth means this is the lca
    if (left.second == right.second) return {curr, left.second + 1};
    // the left lca is the lca of all the deepest leaves so
    // return that upward
    else if (left.second > right.second)
      return {left.first, left.second + 1};
    // same as before but its the right lca
    else
      return {right.first, right.second + 1};
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) { return helper(root).first; }
};

class Solution3 {
  unordered_map<int, unordered_set<TreeNode*>> depth_to_node;

 public:
  pair<TreeNode*, int> lca(TreeNode* curr,
                           const unordered_set<TreeNode*>& leaves) {
    if (!curr) return {nullptr, 0};
    int N = leaves.size();
    auto left = lca(curr->left, leaves);
    if (left.second == N) return left;
    auto right = lca(curr->right, leaves);
    if (right.second == N) return right;
    int total = left.second + right.second + leaves.count(curr);
    return {curr, total};
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].insert(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    return lca(root, depth_to_node[max_depth]).first;
  }
};

class Solution2 {
  unordered_map<int, vector<TreeNode*>> depth_to_node;

 public:
  TreeNode* lca(TreeNode* curr, TreeNode* a, TreeNode* b) {
    if (!curr || curr == a || curr == b) return curr;
    auto left = lca(curr->left, a, b);
    auto right = lca(curr->right, a, b);
    if (left && right)
      return curr;
    else if (left)
      return left;
    else
      return right;
  }

  void search(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    depth_to_node[depth].push_back(root);
    search(root->left, depth + 1);
    search(root->right, depth + 1);
  }

  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    /*
    get all the nodes with the maximum depth, then do pairwise lca
    through all of them
    */
    search(root);
    int max_depth = -1;
    for (auto kv : depth_to_node) max_depth = max(max_depth, kv.first);
    auto v = depth_to_node[max_depth];
    TreeNode* prev = nullptr;
    for (auto e : v) prev = lca(root, prev, e);
    return prev;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1128. Number of Equivalent Domino Pairs
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] =
[c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one
domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length,
and dominoes[i] is equivalent to dominoes[j].

Example 1:
Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1

Constraints:

  1 <= dominoes.length <= 40000
  1 <= dominoes[i][j] <= 9
/*
  Submission Date: 2019-09-23
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    unordered_map<string, int> freq;
    int res = 0;
    for (const auto& d : dominoes) {
      auto p = minmax(d[0], d[1]);
      string key = to_string(p.first) + ',' + to_string(p.second);
      res += freq[key];
      freq[key]++;
    }
    return res;
  }
};

int main() { return 0; }
