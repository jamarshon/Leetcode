
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
796. Rotate String
We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to
the rightmost position. For example, if A = 'abcde', then it will be 'bcdea'
after one shift on A. Return True if and only if A can become B after some
number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
Note:

A and B will have length at most 100.
/*
    Submission Date: 2018-06-04
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool rotateString(string A, string B) {
    if (A.size() != B.size()) return false;
    string A2 = A + A;
    return A2.find(B) != string::npos;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
797. All Paths From Source to Target
Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0
to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.
graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []]
Output: [[0,1,3],[0,2,3]]
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of
nodes inside one path.
/*
    Submission Date: 2018-06-24
    Runtime: 103 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void dfs(int from, const vector<vector<int>>& graph, vector<int>& curr,
           vector<vector<int>>& res) {
    if (graph[from].empty()) {
      res.push_back(curr);
    } else {
      for (auto e : graph[from]) {
        curr.push_back(e);
        dfs(e, graph, curr, res);
        curr.pop_back();
      }
    }
  }

  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<int> curr{0};
    vector<vector<int>> res;
    dfs(0, graph, curr, res);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
804. Unique Morse Code Words
International Morse Code defines a standard encoding where each letter is mapped
to a series of dots and dashes, as follows: "a" maps to ".-", "b" maps to
"-...", "c" maps to "-.-.", and so on.

For convenience, the full table for the 26 letters of the English alphabet is
given below:

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
Now, given a list of words, each word can be written as a concatenation of the
Morse code of each letter. For example, "cab" can be written as "-.-.-....-",
(which is the concatenation "-.-." + "-..." + ".-"). We'll call such a
concatenation, the transformation of a word.

Return the number of different transformations among all words we have.

Example:
Input: words = ["gin", "zen", "gig", "msg"]
Output: 2
Explanation:
The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."

There are 2 different transformations, "--...-." and "--...--.".
 

Note:

The length of words will be at most 100.
Each words[i] will have length in range [1, 12].
words[i] will only consist of lowercase letters.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  vector<string> morse_{".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",
                        "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",
                        "---",  ".--.", "--.-", ".-.",  "...",  "-",    "..-",
                        "...-", ".--",  "-..-", "-.--", "--.."};

 public:
  int uniqueMorseRepresentations(vector<string>& words) {
    unordered_set<string> comb;
    for (const auto& s : words) {
      string curr = "";
      for (const auto& c : s) {
        curr += morse_[c - 'a'];
      }
      comb.insert(curr);
    }
    return comb.size();
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
806. Number of Lines To Write String
We are to write the letters of a given string S, from left to right into lines.
Each line has maximum width 100 units, and if writing a letter would cause the
width of the line to exceed 100 units, it is written on the next line. We are
given an array widths, an array where widths[0] is the width of 'a', widths[1]
is the width of 'b', ..., and widths[25] is the width of 'z'.

Now answer two questions: how many lines have at least one character from S, and
what is the width used by the last such line? Return your answer as an integer
list of length 2.

Example :
Input:
widths =
[10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "abcdefghijklmnopqrstuvwxyz"
Output: [3, 60]
Explanation:
All letters have the same length of 10. To write all 26 letters,
we need two full lines and one line with 60 units.
Example :
Input:
widths =
[4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "bbbcccdddaaa"
Output: [2, 4]
Explanation:
All letters except 'a' have the same length of 10, and
"bbbcccdddaa" will cover 9 * 10 + 2 * 4 = 98 units.
For the last 'a', it is written on the second line because
there is only 2 units left in the first line.
So the answer is 2 lines, plus 4 units in the second line.
 
Note:

The length of S will be in the range [1, 1000].
S will only contain lowercase letters.
widths is an array of length 26.
widths[i] will be in the range of [2, 10].
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> numberOfLines(vector<int>& widths, string S) {
    int current_len = 0;
    int num_lines = 0;
    for (const auto& c : S) {
      if (current_len + widths[c - 'a'] > 100) {
        num_lines++;
        current_len = 0;
      }
      current_len += widths[c - 'a'];
    }
    return {num_lines + 1, current_len};
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
807. Max Increase to Keep City Skyline
In a 2 dimensional array grid, each value grid[i][j] represents the height of a
building located there. We are allowed to increase the height of any number of
buildings, by any amount (the amounts can be different for different buildings).
Height 0 is considered to be a building as well.

At the end, the "skyline" when viewed from all four directions of the grid, i.e.
top, bottom, left, and right, must be the same as the skyline of the original
grid. A city's skyline is the outer contour of the rectangles formed by all the
buildings when viewed from a distance. See the following example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation:
The grid is:
[ [3, 0, 8, 4],
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

Notes:

1 < grid.length = grid[0].length <= 50.
All heights grid[i][j] are in the range [0, 100].
All buildings in grid[i][j] occupy the entire grid cell: that is, they are a 1 x
1 x grid[i][j] rectangular prism.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int N = grid.size();
    int M = grid[0].size();
    vector<int> max_col(M, 0), max_row(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        max_col[j] = max(max_col[j], grid[i][j]);
        max_row[i] = max(max_row[i], grid[i][j]);
      }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        res += min(max_col[j], max_row[i]) - grid[i][j];
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
811. Subdomain Visit Count
A website domain like "discuss.leetcode.com" consists of various subdomains. At
the top level, we have "com", at the next level, we have "leetcode.com", and at
the lowest level, "discuss.leetcode.com". When we visit a domain like
"discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and
"com" implicitly.

Now, call a "count-paired domain" to be a count (representing the number of
visits this domain received), followed by a space, followed by the address. An
example of a count-paired domain might be "9001 discuss.leetcode.com".

We are given a list cpdomains of count-paired domains. We would like a list of
count-paired domains, (in the same format as the input, and in any order), that
explicitly counts the number of visits to each subdomain.

Example 1:
Input:
["9001 discuss.leetcode.com"]
Output:
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation:
We only have one website domain: "discuss.leetcode.com". As discussed above, the
subdomain "leetcode.com" and "com" will also be visited. So they will all be
visited 9001 times.

Example 2:
Input:
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output:
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1
intel.mail.com","951 com"] Explanation: We will visit "google.mail.com" 900
times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times. For
the subdomains, we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1
= 951 times, and "org" 5 times.

Notes:

The length of cpdomains will not exceed 100.
The length of each domain name will not exceed 100.
Each address will have either 1 or 2 "." characters.
The input count in any count-paired domain will not exceed 10000.
The answer output can be returned in any order.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> subdomainVisits(vector<string>& cpdomains) {
    unordered_map<string, int> domain_to_count;
    for (const auto& s : cpdomains) {
      int num = 0;
      int i = 0;
      while (i < s.size()) {
        if (isdigit(s[i])) {
          num = num * 10 + (s[i] - '0');
        } else {
          break;
        }
        i++;
      }

      string domain = s.substr(i + 1);
      while (domain.find('.') != string::npos) {
        domain_to_count[domain] += num;
        domain = domain.substr(domain.find('.') + 1);
      }

      domain_to_count[domain] += num;
    }

    vector<string> res;
    for (const auto& kv : domain_to_count) {
      res.push_back(to_string(kv.second) + " " + kv.first);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
812. Largest Triangle Area
You have a list of points in the plane. Return the area of the largest triangle
that can be formed by any 3 of the points.

Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation:
The five points are show in the figure below. The red triangle is the largest.

Notes:

3 <= points.length <= 50.
No points will be duplicated.
 -50 <= points[i][j] <= 50.
Answers within 10^-6 of the true value will be accepted as correct.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  double largestTriangleArea(vector<vector<int>>& points) {
    int res = 0;
    int N = points.size();
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        for (int k = j + 1; k < N; k++) {
          /*
          given points (a,b), (c,d), (e,f)
          vector A = (c-a, d-b, 0) and B = (e-a, f-b, 0)
          cross product of A and B is
          ((d-b)*0 - (f-b)*0, -((c-a)*0 - (e-a)*0), (c-a)*(f-b) - (e-a)*(d-b))
          (0, 0, (c-a)*(f-b) - (e-a)*(d-b))
          magnitude of A cross B is area of parallelogram so divide by half
          */
          int c_minus_a = points[j][0] - points[i][0];
          int d_minus_b = points[j][1] - points[i][1];
          int e_minus_a = points[k][0] - points[i][0];
          int f_minus_b = points[k][1] - points[i][1];

          res = max(res, abs(c_minus_a * f_minus_b - e_minus_a * d_minus_b));
        }
      }
    }
    return res / 2.0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
814. Binary Tree Pruning
We are given the head node root of a binary tree, where additionally every
node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1
has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant
of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
 
Explanation:
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.


Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]



Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]



Note:

The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.
/*
    Submission Date: 2018-06-24
    Runtime: 4 ms
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
  bool HasOne(TreeNode* root) {
    if (root == NULL) return false;
    bool l = HasOne(root->left);
    bool r = HasOne(root->right);

    if (!l) {
      delete root->left;
      root->left = NULL;
    }
    if (!r) {
      delete root->right;
      root->right = NULL;
    }

    return root->val == 1 || l || r;
  }

  TreeNode* pruneTree(TreeNode* root) {
    if (!HasOne(root)) {
      delete root;
      return NULL;
    }
    return root;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
817. Linked List Components
We are given head, the head node of a linked list containing unique integer

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G, where two values are connected

Example 1:

Input:
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation:
0 and 1 are connected, so [0, 1] and [3] are the two connected components.


Example 2:

Input:
head: 0->1->2->3->4
G = [0, 3, 1, 4]
Output: 2
Explanation:
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two


Note:


    If N is the length of the linked list given by head, 1 <= N <= 10000.
    The value of each node in the linked list will be in the range [0, N - 1].
    1 <= G.length <= 10000.
    G is a subset of all values in the linked list.
/*
    Submission Date: 2018-07-02
    Runtime: 35 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  int numComponents(ListNode* head, vector<int>& G) {
    unordered_set<int> G_set(G.begin(), G.end());
    ListNode* curr = head;
    int res = 0;
    while (curr) {
      // looking for the start of a component
      while (curr && !G_set.count(curr->val)) {
        curr = curr->next;
      }

      if (curr) {
        res++;
        // looking for the end of a component
        while (curr && G_set.count(curr->val)) {
          curr = curr->next;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
819. Most Common Word
Given a paragraph and a list of banned words, return the most frequent word that
is not in the list of banned words. It is guaranteed there is at least one word
that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of
punctuation.  Words in the paragraph are not case sensitive. The answer is in
lowercase.

Example:
Input:
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
Output: "ball"
Explanation:
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent
non-banned word in the paragraph. Note that words in the paragraph are not case
sensitive, that punctuation is ignored (even if adjacent to words, such as
"ball,"), and that "hit" isn't the answer even though it occurs more because it
is banned.
 

Note:

1 <= paragraph.length <= 1000.
1 <= banned.length <= 100.
1 <= banned[i].length <= 10.
The answer is unique, and written in lowercase (even if its occurrences in
paragraph may have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
Different words in paragraph are always separated by a space.
There are no hyphens or hyphenated words.
Words only consist of letters, never apostrophes or other punctuation symbols.
/*
    Submission Date: 2018-06-04
    Runtime:  ms
    Difficulty:
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  string mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_set<string> banned_set(banned.begin(), banned.end());
    unordered_map<string, int> freq;

    stringstream ss(paragraph);
    string temp;

    string res = "";
    while (getline(ss, temp, ' ')) {
      for (int i = 0; i < temp.size(); i++) temp[i] = tolower(temp[i]);
      while (!temp.empty() && !isalpha(temp.back())) temp.pop_back();
      if (banned_set.count(temp)) continue;
      freq[temp]++;
      if (res.empty() || freq[res] < freq[temp]) res = temp;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
821. Shortest Distance to a Character
Given a string S and a character C, return an array of integers representing the
shortest distance from the character C in the string.

Example 1:

Input: S = "loveleetcode", C = 'e'
Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

Note:

S string length is in [1, 10000].
C is a single character, and guaranteed to be in string S.
All letters in S and C are lowercase.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  keep track of last seen C and use that as the distance
  then do it from the back and take the min of this value with the previous
  value
  */
  vector<int> shortestToChar(string S, char C) {
    int N = S.size();
    vector<int> res(N, INT_MAX);

    int last_C_forward = -1;
    int last_C_backward = -1;
    for (int i = 0; i < N; i++) {
      if (S[i] == C) last_C_forward = i;
      if (S[N - i - 1] == C) last_C_backward = N - i - 1;

      if (last_C_forward >= 0) {
        res[i] = min(res[i], i - last_C_forward);
      }

      if (last_C_backward >= 0) {
        res[N - i - 1] = min(res[N - i - 1], last_C_backward - (N - i - 1));
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
824. Goat Latin
A sentence S is given, composed of words separated by spaces. Each word consists
of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language
similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the
word. For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter
and append it to the end, then add "ma". For example, the word "goat" becomes
"oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence,
starting with 1. For example, the first word gets "a" added to the end, the
second word gets "aa" added to the end and so on. Return the final sentence
representing the conversion from S to Goat Latin.

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa
hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each
word. 1 <= S.length <= 150.
/*
    Submission Date: 2018-05-31
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

class Solution {
  unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

 public:
  string toGoatLatin(string S) {
    stringstream ss(S);
    string token;
    string res = "";
    int i = 1;
    while (getline(ss, token, ' ')) {
      if (!res.empty()) res += ' ';
      if (vowels.count(tolower(token[0]))) {
        res += token;
      } else {
        res += token.substr(1) + string(1, token[0]);
      }

      res += "ma" + string(i, 'a');
      i++;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
825. Friends Of Appropriate Ages
Some people will make friend requests. The list of their ages is given and
ages[i] is the age of the ith person.

Person A will NOT friend request person B (B != A) if any of the following
conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will
not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output:
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.
/*
    Submission Date: 2018-06-29
    Runtime: 39 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  1 <= ages[i] <= 120
  so have a[i] be the frequency of age i
  for an age i, there should be an age j <= i which can be friends with
  j > 0.5*i + 7     ie. j = 0.5*i + 8
  j must be !(j > 100 && i < 100) note this will never occur as j <= i
  
  so for every person of age i (a[i]) and every person of age j (a[j])
  there can be a[j] * a[i] friend requests made as for a person in j
  can make friend with every person in i (a[i] times) and there are a[j] of
  these people
  
  if j == i, then it is a[i] * (a[i] - 1) as every person in i
  can make friends with a[i] - 1 people as they cannot make friends with
  themself
  */
  int numFriendRequests(vector<int>& ages) {
    vector<int> a(121, 0);

    for (const auto& e : ages) a[e]++;

    int res = 0;
    for (int i = 1; i < 121; i++) {
      for (int j = 0.5 * i + 8; j <= i; j++) res += a[j] * (a[i] - (i == j));
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
830. Positions of Large Groups
In a string S of lowercase letters, these letters form consecutive groups of the
same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx",
"z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting
and ending positions of every large group.

The final answer should be in lexicographic order.

 

Example 1:

Input: "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the single large group with starting  3 and ending
positions 6. Example 2:

Input: "abc"
Output: []
Explanation: We have "a","b" and "c" but no large group.
Example 3:

Input: "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
 

Note:  1 <= S.length <= 1000
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
  vector<vector<int>> largeGroupPositions(string S) {
    vector<vector<int>> res;
    for (int i = 0; i < S.size();) {
      int j = i;
      while (j < S.size() && S[i] == S[j]) j++;
      if (j - i >= 3) {
        res.push_back({i, j - 1});
      }
      i = j;
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
832. Flipping an Image
Given a binary matrix A, we want to flip the image horizontally, then invert it,
and return the resulting image.

To flip an image horizontally means that each row of the image is reversed.  For
example, flipping [1, 1, 0] horizontally results in [0, 1, 1].

To invert an image means that each 0 is replaced by 1, and each 1 is replaced by
0. For example, inverting [0, 1, 1] results in [1, 0, 0].

Example 1:

Input: [[1,1,0],[1,0,1],[0,0,0]]
Output: [[1,0,0],[0,1,0],[1,1,1]]
Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
Example 2:

Input: [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Notes:

1 <= A.length = A[0].length <= 20
0 <= A[i][j] <= 1
/*
    Submission Date: 2018-05-31
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
    for (auto& row : A) {
      reverse(row.begin(), row.end());
      for (auto& el : row) el ^= 1;
    }

    return A;
  }
};

int main() { return 0; }