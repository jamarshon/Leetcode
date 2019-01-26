
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
733. Flood Fill
An image is represented by a 2-D array of integers, each integer representing
the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of
the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels
connected 4-directionally to the starting pixel of the same color as the
starting pixel, plus any pixels connected 4-directionally to those pixels (also
with the same color as the starting pixel), and so on. Replace the color of all
of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels
connected by a path of the same color as the starting pixel are colored with the
new color. Note the bottom corner is not colored 2, because it is not
4-directionally connected to the starting pixel. Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc <
image[0].length. The value of each color in image[i][j] and newColor will be an
integer in [0, 65535].
/*
    Submission Date: 2018-06-08
    Runtime: 57 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

 public:
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int newColor) {
    if (image.empty()) return {};
    queue<pair<int, int>> q;
    unordered_set<string> visited;

    int N = image.size();
    int M = image[0].size();
    int original_color = image[sr][sc];

    q.emplace(sr, sc);
    visited.insert(to_string(sr) + "," + to_string(sc));
    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();
      image[p.first][p.second] = newColor;

      for (int k = 0; k < 4; k++) {
        int new_row = p.first + dy[k];
        int new_col = p.second + dx[k];
        if (0 <= new_row && new_row < N && 0 <= new_col && new_col < M &&
            image[new_row][new_col] == original_color) {
          string key = to_string(new_row) + "," + to_string(new_col);
          if (!visited.count(key)) {
            q.emplace(new_row, new_col);
            visited.insert(key);
          }
        }
      }
    }

    return image;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
739. Daily Temperatures
Given a list of daily temperatures, produce a list that, for each day in the
input, tells you how many days you would have to wait until a warmer
temperature.  If there is no future day for which this is possible, put 0
instead.

For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73],
your output should be [1, 1, 4, 2, 1, 1, 0, 0].


Note:
The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].

/*
    Submission Date: 2018-06-30
    Runtime: 250 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  stk keeps an increasing temperatures to the right (represented as indices)
  while stk isn't emtpy and the current element is greater than the smallest
  element (ie stk top) pop the stk, basically it means this element replaces all
  the smaller elements as it will be closer to the next element while still
  being greater
  */
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> stk;
    int N = temperatures.size();
    vector<int> res(N, 0);
    for (int i = N - 1; i >= 0; i--) {
      while (!stk.empty() && temperatures[stk.top()] <= temperatures[i])
        stk.pop();
      res[i] = stk.empty() ? 0 : stk.top() - i;
      stk.push(i);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
743. Network Delay Time
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w),
where u is the source node, v is the target node, and w is the time it takes for
a signal to travel from source to target.

Now, we send a signal from a certain node K.  How long will it take for all
nodes to receive the signal?  If it is impossible, return -1.

Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
 public:
  typedef pair<int, int> pii;
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    vector<vector<pii>> edges(N);
    K--;
    for (auto& v : times) {
      edges[v[0] - 1].emplace_back(v[2], v[1] - 1);
    }

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, K);
    vector<int> dist(N, INT_MAX);
    dist[K] = 0;
    int cnt = 0;
    while (cnt < N && !q.empty()) {
      int weight, node;

      tie(weight, node) = q.top();
      q.pop();

      if (dist[node] == INT_MAX) break;
      if (dist[node] < weight) continue;
      cnt++;

      for (pii& n : edges[node]) {
        if (dist[n.second] == INT_MAX ||
            dist[node] + n.first < dist[n.second]) {
          dist[n.second] = dist[node] + n.first;
          q.emplace(dist[n.second], n.second);
        }
      }
    }
    int res = *max_element(dist.begin(), dist.end());
    return res == INT_MAX ? -1 : res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
744. Find Smallest Letter Greater Than Target
Given a list of sorted characters letters containing only lowercase letters, and
given a target letter target, find the smallest element in the list that is
larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters
= ['a', 'b'], the answer is 'a'.

Examples:
Input:
letters = ["c", "f", "j"]
target = "a"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "c"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "d"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "g"
Output: "j"

Input:
letters = ["c", "f", "j"]
target = "j"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "k"
Output: "c"
Note:
letters has a length in range [2, 10000].
letters consists of lowercase letters, and contains at least 2 unique letters.
target is a lowercase letter.
/*
    Submission Date: 2018-06-08
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  char nextGreatestLetter(vector<char>& letters, char target) {
    int low = 0;
    int high = letters.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (letters[mid] > target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    if (low == letters.size()) return letters[0];
    return letters[low];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
746. Min Cost Climbing Stairs
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0
indexed).

Once you pay the cost, you can either climb one or two steps. You need to find
minimum cost to reach the top of the floor, and you can either start from the
step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping
cost[3]. Note: cost will have a length in the range [2, 1000]. Every cost[i]
will be an integer in the range [0, 999].
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    if (cost.empty()) return 0;
    int N = cost.size();

    vector<int> dp(N + 2, 0);
    for (int i = N - 1; i >= 0; i--) {
      dp[i] = cost[i] + min(dp[i + 1], dp[i + 2]);
    }

    return N == 1 ? dp[0] : min(dp[0], dp[1]);
  }
};

int main() { return 0; }
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
letters from the string licensePlate.  Such a word is said to complete the given
string licensePlate

Here, for letters we ignore case.  For example, "P" on the licensePlate still
matches "p" on the word.

It is guaranteed an answer exists.  If there are multiple answers, return the
one that occurs first in the array.

The license plate might have the same letter occurring multiple times.  For
example, given a licensePlate of "PP", the word "pair" does not complete the
licensePlate, but the word "supper" does.


Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S",
and "T".
Note that the answer is not "step", because the letter "s" must occur in the
word twice.
Also note that we ignored case for the purposes of comparing whether a letter
exists in the word.



Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.



Note:

licensePlate will be a string with length in range [1, 7].
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
letter string, like `'Z'`.

For every block of color `C` we place not in the bottom row, we are placing it
on top of a left block of color `A` and right block of color `B`.  We are
allowed to place the block there only if `(A, B, C)` is an allowed triple.

We start with a bottom row of bottom, represented as a single string.  We also
start with a list of allowed triples allowed.  Each allowed triple is
represented as a string of length 3.

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
allowed triples.



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
'F', 'G'}.

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
each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2],
which isn't sorted.


Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks
possible.


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
are placed in an array.

Return the minimum number of rabbits that could be in the forest.

Examples:
Input: answers = [1, 1, 2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit than answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into
the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that
answered plus 2 that didn't.

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
