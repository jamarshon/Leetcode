
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
747. Largest Number At Least Twice of Others
In a given integer array nums, there is always exactly one largest element.

Find whether the largest element in the array is at least twice as much as every
other number in the array.

If it is, return the index of the largest element, otherwise return -1.

Example 1:

Input: nums = [3, 6, 1, 0]
Output: 1
Explanation: 6 is the largest integer, and for every other number in the array
x, 6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
 

Example 2:

Input: nums = [1, 2, 3, 4]
Output: -1
Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.
 

Note:

nums will have a length in the range [1, 50].
Every nums[i] will be an integer in the range [0, 99].
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  priority queue minheap to get the 2 largest element along with their index
  compare if the largest element is > second largest element * 2 then return
  index of largest element else -1
  */
  typedef pair<int, int> pii;
  int dominantIndex(vector<int>& nums) {
    if (nums.empty()) return -1;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < nums.size(); i++) {
      pq.emplace(nums[i], i);
      if (pq.size() > 2) pq.pop();
    }

    int top_ind = pq.top().second;
    pq.pop();

    if (pq.empty()) return top_ind;

    return nums[top_ind] > nums[pq.top().second] / 2 ? -1 : pq.top().second;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
748. Shortest Completing Word
Find the minimum length word from a given dictionary words, which has all the
letters from the string licensePlate. Such a word is said to complete the given
string licensePlate

Here, for letters we ignore case. For example, "P" on the licensePlate still
matches "p" on the word.

It is guaranteed an answer exists. If there are multiple answers, return the one
that occurs first in the array.

The license plate might have the same letter occurring multiple times. For
example, given a licensePlate of "PP", the word "pair" does not complete the
licensePlate, but the word "supper" does.

Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S",
and "T". Note that the answer is not "step", because the letter "s" must occur
in the word twice. Also note that we ignored case for the purposes of comparing
whether a letter exists in the word. Example 2: Input: licensePlate = "1s3 456",
words = ["looks", "pest", "stew", "show"] Output: "pest" Explanation: There are
3 smallest length words that contains the letters "s". We return the one that
occurred first. Note: licensePlate will be a string with length in range [1, 7].
licensePlate will contain digits, spaces, or letters (uppercase or lowercase).
words will have a length in the range [10, 1000].
Every words[i] will consist of lowercase letters, and have length in range [1,
15].
/*
    Submission Date: 2018-06-30
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  licensePlate size M, words size N, words[i] size k
  
  generate a frequency of character for licensePlate O(M)
  for each word, loop through character and decrease frequency of character if
  it exists if the frequency is zero, remove it and if the hashmap is empty than
  all the characters are needed in this string so update res if it is shorter
  O(N*k)
  
  O(N*k + M)
  */
  string shortestCompletingWord(string licensePlate, vector<string>& words) {
    unordered_map<char, int> letters;
    for (const auto& c : licensePlate)
      if (isalpha(c)) letters[tolower(c)]++;

    string res = "";
    for (const auto& word : words) {
      unordered_map<char, int> letters_copy = letters;
      for (const auto& c : word) {
        if (letters_copy.count(c)) {
          letters_copy[c]--;
          if (letters_copy[c] == 0) {
            letters_copy.erase(c);
            if (letters_copy.empty()) break;
          }
        }
      }

      if (letters_copy.empty() && (res.empty() || word.size() < res.size())) {
        res = word;
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
756. Pyramid Transition Matrix
We are stacking blocks to form a pyramid.  Each block has a color which is a one

For every block of color `C` we place not in the bottom row, we are placing it
on top of a left block of color `A` and right block of color `B`.  We are

We start with a bottom row of bottom, represented as a single string.  We also
start with a list of allowed triples allowed.  Each allowed triple is

Return true if we can build the pyramid all the way to the top, otherwise false.


Example 1:
Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  D   E
 / \ / \
X   Y   Z

This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are



Example 2:
Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.



Note:

bottom will be a string with length in range [2, 8].
allowed will have length in range [0, 200].
Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E',
/*
    Submission Date: 2018-07-09
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
  TrieNode* children[7];
  TrieNode() {
    for (int i = 0; i < 7; i++) {
      children[i] = NULL;
    }
  }
};

class Solution {
 public:
  /*
  loop through s from i = [1,N) and seeing if s[i-1] + s[i] exists
  if it does then try all combinations of s[i-1] + s[i] + _ where _ is
  determined from the Trie. base case is when s is just a single letter.
  
  building.size() always == i-1 so if building.size() == N-1 (building row is
  one less than previous row) then i-1 == N-1 or i == N which terminates
  */
  bool f(string s, int i, string building, TrieNode* root) {
    int N = s.size();
    if (N == 1) return true;

    if (building.size() == N - 1) {
      return f(building, 1, "", root);  // swap building and create a new row
    }

    // checking trie if AB exists
    TrieNode* curr = root;
    for (int j = 0; j < 2; j++) {
      if (curr->children[s[i - 1 + j] - 'A'] == NULL) return false;
      curr = curr->children[s[i - 1 + j] - 'A'];
    }

    // useing all combinations of AB_ to see if _ can work as the character for
    // the building row
    for (int j = 0; j < 7; j++) {
      if (curr->children[j] == NULL) continue;
      if (f(s, i + 1, building + char('A' + j), root)) return true;
    }

    return false;
  }

  bool pyramidTransition(string bottom, vector<string>& allowed) {
    TrieNode* root = new TrieNode();
    for (const auto& s : allowed) {
      TrieNode* curr = root;
      for (const auto& c : s) {
        if (curr->children[c - 'A'] == NULL)
          curr->children[c - 'A'] = new TrieNode();
        curr = curr->children[c - 'A'];
      }
    }

    return f(bottom, 1, "", root);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
762. Prime Number of Set Bits in Binary Representation
Given two integers L and R, find the count of numbers in the range [L, R]
(inclusive) having a prime number of set bits in their binary representation.

(Recall that the number of set bits an integer has is the number of 1s present
when written in binary. For example, 21 written in binary is 10101 which has 3
set bits. Also, 1 is not a prime.)

Example 1:

Input: L = 6, R = 10
Output: 4
Explanation:
6 -> 110 (2 set bits, 2 is prime)
7 -> 111 (3 set bits, 3 is prime)
9 -> 1001 (2 set bits , 2 is prime)
10->1010 (2 set bits , 2 is prime)
Example 2:

Input: L = 10, R = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
Note:

L, R will be integers L <= R in the range [1, 10^6].
R - L will be at most 10000.
/*
    Submission Date: 2018-06-02
    Runtime: 105 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
  int numbits(int x) {
    int res = 0;
    while (x) {
      x &= (x - 1);
      res++;
    }
    return res;
  }

 public:
  /*
      the number of bits for a number i = number of bits for i/2 + the last bit
     of i e.g 10101 = number of bits for 1010 + last bit which is 1
  */
  int countPrimeSetBits(int L, int R) {
    unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    unordered_map<int, int> n_to_bits;
    int res = 0;
    for (int i = L; i <= R; i++) {
      int bits;
      if (n_to_bits.count(i)) {
        bits = n_to_bits[i / 2] + (i % 2);
      } else {
        bits = numbits(i);
      }
      n_to_bits[i] = bits;
      res += primes.count(bits);
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
763. Partition Labels
A string S of lowercase letters is given. We want to partition this string into
as many parts as possible so that each letter appears in at most one part, and
return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits
S into less parts. Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  everytime a letter is visited, update right to be max right and
  the index of the furthest right of this character
  if i == right it means all the caharacters between i and the previous pushed
  number contains letters that do not appear in any other part of the string.
  */
  vector<int> partitionLabels(string S) {
    unordered_map<char, int> last_seen;
    int N = S.size();
    for (int i = 0; i < N; i++) last_seen[S[i]] = i;
    int right = 0;

    vector<int> res;
    for (int i = 0; i < N; i++) {
      right = max(right, last_seen[S[i]]);
      if (i == right) res.push_back(i + 1);
    }

    for (int i = res.size() - 1; i >= 1; i--) res[i] -= res[i - 1];
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
766. Toeplitz Matrix
A matrix is Toeplitz if every diagonal from top-left to bottom-right has the
same element.

Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

Example 1:

Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: True
Explanation:
1234
5123
9512

In the above grid, the diagonals are "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]",
"[3, 3]", "[4]", and in each diagonal all elements are the same, so the answer
is True. Example 2:

Input: matrix = [[1,2],[2,2]]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.
Note:

matrix will be a 2D array of integers.
matrix will have a number of rows and columns in range [1, 20].
matrix[i][j] will be integers in range [0, 99].
/*
    Submission Date: 2018-05-31
    Runtime: 22 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isToeplitzMatrix(vector<vector<int>>& matrix) {
    if (matrix.empty()) return true;
    int N = matrix.size();
    int M = matrix[0].size();

    for (int i = 1; i < N; i++) {
      for (int j = 1; j < M; j++) {
        if (matrix[i][j] != matrix[i - 1][j - 1]) return false;
      }
    }

    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
769. Max Chunks To Make Sorted
Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we
split the array into some number of "chunks" (partitions), and individually sort

What is the most number of chunks we could have made?

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2],


Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks


Note:


    arr will have length in range [1, 10].
    arr[i] will be a permutation of [0, 1, ..., arr.length - 1].
/*
    Submission Date: 2018-07-08
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  nums[i] must be moved to the index nums[i] so keep track of right
  boundary, once i > right boundary it means all the number from the previous
  right boundary this right boundary can be sorted such that nums[i] == i
  so increase res by 1
  
  proof that nums[i] will never get sorted to a number of a previous boundary
  all numbers from [0, i) all smaller than i as i was the previous boundary
  hence nums[i] must be >= i (ie you won't find any smaller number outside
  of the boundary as all of them are already in boundary since there are
  exactly i numbers < i)
  */
  int maxChunksToSorted(vector<int>& arr) {
    int right = 0;
    int N = arr.size();
    int res = 1;
    for (int i = 0; i < N; i++) {
      if (i > right) {
        res++;
      }
      right = max(right, arr[i]);
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
771. Jewels and Stones
You're given strings J representing the types of stones that are jewels, and S
representing the stones you have. Each character in S is a type of stone you
have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are
letters. Letters are case sensitive, so "a" is considered a different type of
stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.
/*
    Submission Date: 2018-05-31
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  int numJewelsInStones(string J, string S) {
    unordered_set<char> jewels(J.begin(), J.end());
    int res = 0;
    for (const auto& stone : S) res += jewels.count(stone);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
781. Rabbits in Forest
In a forest, each rabbit has some color. Some subset of rabbits (possibly all of
them) tell you how many other rabbits have the same color as them. Those answers

Return the minimum number of rabbits that could be in the forest.

Examples:
Input: answers = [1, 1, 2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit than answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into
The smallest possible number of rabbits in the forest is therefore 5: 3 that

Input: answers = [10, 10, 10]
Output: 11

Input: answers = []
Output: 0


Note:


    answers will have length at most 1000.
    Each answers[i] will be an integer in the range [0, 999].
/*
    Submission Date: 2018-07-02
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  convert numbers to frequency.
  if x occurs y times it means each group of size x+1 in y could refer to the
  same rabbits so find how many x+1 groups are in y and multiply by x+1 to get
  the total number of rabbits e.g 1 1 1 1 1 1 1 x = 1 y = 7 groups of 2 (1 1) (1
  1) (1 1) (1) there are 4 groups of two and multiply this by 1+1 = 8 the groups
  are referring to only rabbits in their own group.
  */
  int numRabbits(vector<int>& answers) {
    unordered_map<int, int> freq;
    for (const auto& n : answers) freq[n]++;
    int res = 0;
    for (const auto& kv : freq) {
      res += ceil((float)kv.second / (kv.first + 1)) * (kv.first + 1);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
783. Minimum Distance Between BST Nodes
Given a Binary Search Tree (BST) with the root node root, return the minimum
difference between the values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \
    1   3

while the minimum difference in this tree is 1, it occurs between node 1 and
node 2, also between node 3 and node 2. Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value
is different.
/*
    Submission Date: 2018-06-08
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <climits>
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
  inorder traversal keeping tracking of prev
  */
  void help(TreeNode* root, int& res, int& prev) {
    if (root == NULL) return;
    help(root->left, res, prev);
    if (prev != INT_MAX) {
      res = min(res, root->val - prev);
    }

    prev = root->val;
    help(root->right, res, prev);
  }

  int minDiffInBST(TreeNode* root) {
    int res = INT_MAX, prev = INT_MAX;
    help(root, res, prev);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
784. Letter Case Permutation
Given a string S, we can transform every letter individually to be lowercase or
uppercase to create another string. Return a list of all possible strings we
could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length at most 12.
S will consist only of letters or digits.
/*
    Submission Date: 2018-06-03
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<string, vector<string>> dp_;

 public:
  /*
   find the first alphabetical letter. get the vector for the remaining string
   add prefix with the letter lower case and upper case to each element from the
   vector
  */
  vector<string> letterCasePermutation(string S) {
    if (dp_.count(S)) return dp_[S];

    int N = S.size();
    int i = 0;
    for (; i < N; i++) {
      if (isalpha(S[i])) break;
    }

    if (i >= N) return {S};
    vector<string> rem = letterCasePermutation(S.substr(i + 1));
    int M = rem.size();
    rem.reserve(2 * M);

    string s1 = S.substr(0, i) + string(1, toupper(S[i]));
    string s2 = S.substr(0, i) + string(1, tolower(S[i]));
    for (int j = 0; j < M; j++) {
      rem.push_back(s2 + rem[j]);
      rem[j] = s1 + rem[j];
    }
    return rem;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
788. Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees, we
get a valid number that is different from X. Each digit must be rotated - we
cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8
rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each
other, and the rest of the numbers do not rotate to any other number and become
invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation:
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after
rotating. Note:

N  will be in range [1, 10000].
/*
    Submission Date: 2018-06-04
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  dp[i] = -1 if i cannot be rotated else it equals the rotated number of i
  therefore dp[i] = dp[i/10] + rot[i % 10] as i/10 gets the rotated version i
  without the last number and rot[i % 10] gets the rotated version of the last
  number of i
  */
  int rotatedDigits(int N) {
    vector<int> dp(N + 1, -1);
    unordered_map<int, int> rot{{0, 0}, {1, 1}, {8, 8}, {2, 5},
                                {5, 2}, {6, 9}, {9, 6}};
    int res = 0;
    for (int i = 1; i <= N; i++) {
      if (!rot.count(i % 10)) continue;
      if (i < 10) {
        dp[i] = rot[i];
        res += dp[i] != i;
      } else {
        if (dp[i / 10] == -1) continue;
        dp[i] = dp[i / 10] * 10 + rot[i % 10];
        res += dp[i] != i;
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
789. Escape The Ghosts
You are playing a simplified Pacman game. You start at the point (0, 0), and
your destination is (target[0], target[1]). There are several ghosts on the map,
the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).

Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal
directions: north, east, west, or south, going from the previous point to a new
point 1 unit of distance away.

You escape if and only if you can reach the target before any ghost reaches you
(for any given moves the ghosts may take.)  If you reach any square (including
the target) at the same time as a ghost, it doesn't count as an escape.

Return True if and only if it is possible to escape.

Example 1:
Input:
ghosts = [[1, 0], [0, 3]]
target = [0, 1]
Output: true
Explanation:
You can directly reach the destination (0, 1) at time 1, while the ghosts
located at (1, 0) or (0, 3) have no way to catch up with you. Example 2: Input:
ghosts = [[1, 0]]
target = [2, 0]
Output: false
Explanation:
You need to reach the destination (2, 0), but the ghost at (1, 0) lies between
you and the destination. Example 3: Input: ghosts = [[2, 0]] target = [1, 0]
Output: false
Explanation:
The ghost can reach the target at the same time as you.
Note:

All points have coordinates with absolute value <= 10000.
The number of ghosts will not exceed 100.
/*
    Submission Date: 2018-07-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  if the manhattan distance (abs horizontal + abs vertical) of the target
  from the origin is less than or equal to the manhattan distance of the
  target with the ghost, then return false as the ghost can get there
  faster and just wait indefinitely.

  why ghost intercept is not good?
  if a ghost can intercept you, it means they can reach the target faster than
  you. the shortest path between two points is straight line so if ghost can
  take detour and intercept then it means if they just went straight, they
  would be there before you.
            if ghost gets here before you, they would already be at target
            x
  you --------------- target
            |         |
            |         |
  ghost--------------
  */
  bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
    int mine = abs(target[0]) + abs(target[1]);
    for (const auto& e : ghosts) {
      int dist = abs(e[0] - target[0]) + abs(e[1] - target[1]);
      if (dist <= mine) return false;
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
791. Custom Sort String
S and T are strings composed of lowercase letters. In S, no letter occurs more
than once.

S was sorted in some custom order previously. We want to permute the characters
of T so that they match the order that S was sorted. More specifically, if x
occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example :
Input:
S = "cba"
T = "abcd"
Output: "cbad"
Explanation:
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and
"a". Since "d" does not appear in S, it can be at any position in T. "dcba",
"cdba", "cbda" are also valid outputs.
 

Note:

S has length at most 26, and no character is repeated in S.
T has length at most 200.
S and T consist of lowercase letters only.
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string customSortString(string S, string T) {
    int N = S.size();

    vector<int> letter_to_ind(26, N);
    for (int i = 0; i < N; i++) letter_to_ind[S[i] - 'a'] = i;

    sort(T.begin(), T.end(),
         [&letter_to_ind](const char& lhs, const char& rhs) {
           return letter_to_ind[lhs - 'a'] < letter_to_ind[rhs - 'a'];
         });

    return T;
  }
};

int main() { return 0; }