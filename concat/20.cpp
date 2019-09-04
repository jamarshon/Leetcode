
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
378. Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending
order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth
distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.
/*
    Submission Date: 2018-05-30
    Runtime: 38 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution2 {
 public:
  bool Get(const vector<vector<int>>& matrix, int num, int N, int M, int k) {
    int i = 0;
    int j = M - 1;
    int curr = 0;

    int occurences = 0;

    while (i < N && j >= 0) {
      if (matrix[i][j] > num) {
        j--;
      } else {
        int temp = j;
        while (temp >= 0 && matrix[i][temp] == num) temp--;
        i++;
        curr += temp + 1;
        occurences += j - temp;
      }
    }

    return curr < k && k <= curr + occurences;
  }

  // for each element in the array, count the number of elements smaller than it
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (Get(matrix, matrix[i][j], N, M, k)) {
          return matrix[i][j];
        }
      }
    }

    return -1;
  }
};

struct Item {
  int i, j, val;
  Item(const int& _i, const int& _j, const int& _val)
      : i(_i), j(_j), val(_val) {}
  bool operator>(const Item& rhs) const { return val > rhs.val; }
};

class Solution3 {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    priority_queue<Item, vector<Item>, greater<Item>> min_heap;
    for (int j = 0; j < M; j++) {
      min_heap.emplace(0, j, matrix[0][j]);
    }

    for (int i = 0; i < k - 1;
         i++) {  // remove k- 1 elements to get the kth element
      Item smallest = min_heap.top();
      min_heap.pop();
      if (smallest.i + 1 < N) {
        smallest.i++;
        smallest.val = matrix[smallest.i][smallest.j];
        min_heap.push(smallest);
      }
    }

    return min_heap.top().val;
  }
};

class Solution {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    // matrix[i][j] >= matrix[k][l] for all k > i && l > j
    int low = matrix[0][0];
    int high = matrix[M - 1][M - 1];

    while (low <= high) {
      int mid = low + (high - low) / 2;
      int num_smaller_than_mid = 0;
      // get the number of elements that are <= mid.
      // suppose the two elements in the array are 10 x 1, 10 x 2 and 10 x 3
      // if k == 15, mid = 2 and num_smaller_than_mid are 10, 20, 30 return low
      // gets the number larger than k
      for (int j = M - 1, i = 0; i < N; i++) {
        while (j >= 0 && matrix[i][j] > mid) j--;
        num_smaller_than_mid += j + 1;
      }

      if (num_smaller_than_mid >= k)
        high = mid - 1;  // too many elements
      else
        low = mid + 1;  // too little elements
    }

    return low;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
380. Insert Delete GetRandom O(1)
Design a data structure that supports all following operations in average O(1)
time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element
must have the same probability of being returned.

Example:
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();
/*
  Submission Date: 2019-02-10
  Runtime: 64 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
  /*
  need a vector the random function
  m_ key is the element and the value is its index in v_
  when we remove a kv from m_ in order to keep the rest of the
  values in m_ to point to the right place we have to ensure
  that none of them moves so we swap the last one with the
  one we're removing and then removing the last one.
  this means none of the indicies change besides the last one.
  */
  unordered_map<int, int> m_;
  vector<int> v_;

 public:
  /** Initialize your data structure here. */
  RandomizedSet() {}

  /** Inserts a value to the set. Returns true if the set did not already
   * contain the specified element. */
  bool insert(int val) {
    if (m_.count(val)) return false;
    m_[val] = v_.size();
    v_.push_back(val);
    return true;
  }

  /** Removes a value from the set. Returns true if the set contained the
   * specified element. */
  bool remove(int val) {
    if (!m_.count(val)) return false;
    int ind = m_[val];

    // fix map. erase after in case val is the last element
    m_[v_.back()] = ind;
    m_.erase(val);

    // fix vector
    swap(v_.back(), v_[ind]);
    v_.pop_back();
    return true;
  }

  /** Get a random element from the set. */
  int getRandom() { return v_[rand() % v_.size()]; }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
382. Linked List Random Node
Given a singly linked list, return a random node's value from the linked list.
Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you?
Could you solve this efficiently without using extra space?


Example:
// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should
have equal probability of returning.
solution.getRandom();

/*
    Submission Date: 2018-07-10
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  ListNode* head_;
  default_random_engine gen;
  uniform_int_distribution<int> uniform_dist;

 public:
  /** @param head The linked list's head.
      Note that the head is guaranteed to be not null, so it contains at least
     one node. */
  Solution(ListNode* head) { head_ = head; }

  /*
  resevoir sampling for ensuring each element has an equal probability of being
  chosen k/n where n is the number of nodes which is unknown and k is the size
  of the output (k randomly chosen nodes). n is not known in advanced and if a
  node is added the probabilities should update according
  
  fill buffer with the first k element
  for k + 1 to n, give the node a k/i probability of chosen to replace an
  element in the buffer
  
  proof that this is k/n. the probability the node is chosen is k/i and the
  probability it is not replaced by any of the further nodes is (1 - 1/i+1)(1 -
  1/i+2) ... (1 - 1/n) as at the time j, the node has a k/j chance of replacing
  any of the spots but a 1/j chance of replacing that exact cell. so not
  replaced is 1 - 1/j and this is done for ever time j > i
  
  (k/i)(1 - 1/i+1)(1 - 1/i+2) ... (1 - 1/n)
  (k/i)(i / i+1)(i+1 / i+2) ... (n-1 / n)
  k/n
  
  now the case is k=1
  */
  int getRandom() {
    vector<ListNode*> buffer = {head_};

    int i = 1;
    ListNode* curr = head_->next;
    while (curr) {
      i++;

      // create a number x between [0, i) and if 0 <= x < k then replace
      // buffer[x] with element for a k/i chance
      uniform_int_distribution<int>::param_type new_range(0, i - 1);
      uniform_dist.param(new_range);

      int x = uniform_dist(gen);
      if (x < buffer.size()) {  // x == 0
        buffer[x] = curr;
      }
      curr = curr->next;
    }

    return buffer[0]->val;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
383. Ransom Note
Given an arbitrary ransom note string and another string containing letters from
all the magazines, write a function that will return true if the ransom note can
be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
/*
    Submission Date: 2018-05-02
    Runtime: 34 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> m;
    for (auto e : magazine) m[e]++;
    for (auto e : ransomNote) {
      if (m.count(e)) {
        if (m[e] == 0) return false;
        m[e]--;
      } else {
        return false;
      }
    }
    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
384. Shuffle an Array
Shuffle a set of numbers without duplicates.


Example:
// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3]
must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();

/*
    Submission Date: 2018-07-13
    Runtime: 148 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<int> original;
  vector<int> curr;

 public:
  Solution(vector<int> nums) { original = curr = nums; }

  /** Resets the array to its original configuration and return it. */
  vector<int> reset() { return curr = original; }

  /** Returns a random shuffling of the array. */
  /*
  
  swap(curr[i], curr[0, i])
  
  let j = [0, i]
  (1) If i == j, nums[i] does not need to change its position, which has
  probability 1/(1+i). (2) if i !=j, nums[i] needs to be swapped with nums[j].
      The probability of any number x in the range [0,i-1] to be at position j =
          nums[i] changes its position * x is at position i
          = (1-1/(1+i))*(1/i) = 1/(1+i)
  */
  vector<int> shuffle() {
    for (int i = 1; i < curr.size(); i++) {
      swap(curr[i], curr[rand() % (i + 1)]);
    }
    return curr;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
386. Lexicographical Numbers
Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size
may be as large as 5,000,000.

/*
    Submission Date: 2017-08-21
    Runtime: 239 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void lexicalOrder(int curr, int n, vector<int>& res) {
    if (curr > n) return;

    int limit = min(n + 1, curr == 1 ? 10 : curr + 10);
    for (int i = curr; i < limit; i++) {
      res.push_back(i);
      lexicalOrder(i * 10, n, res);
    }
  }

  vector<int> lexicalOrder(int n) {
    vector<int> res;
    lexicalOrder(1, n, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return
it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

/*
    Submission Date: 2017-08-21
    Runtime: 93 ms
    Difficulty: EASY
*/
#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  int firstUniqChar(string s) {
    unordered_map<char, int> letter_to_first_ind;
    set<int> st;
    for (int i = 0; i < s.size(); i++) {
      if (letter_to_first_ind.count(s[i])) {
        // we've seen this letter before so we remove it from the set
        if (st.count(letter_to_first_ind[s[i]])) {
          st.erase(letter_to_first_ind[s[i]]);
        }
      } else {
        letter_to_first_ind[s[i]] = i;
        st.insert(i);
      }
    }

    return st.empty() ? -1 : *st.begin();
  }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
389. Find the Difference
Given two strings s and t which consist of only lowercase letters.

String t is generated by random shuffling string s and then add one more letter
at a random position.

Find the letter that was added in t.

Example:

Input:
s = "abcd"
t = "abcde"

Output:
e

Explanation:
'e' is the letter that was added.
/*
    Submission Date: 2018-05-02
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  char findTheDifference(string s, string t) {
    unordered_map<char, int> m;
    for (auto e : s) m[e]++;
    for (auto e : t) {
      if (m.count(e)) {
        if (m[e] == 0) return e;
        m[e]--;
      } else {
        return e;
      }
    }
    return '\0';
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
392. Is Subsequence
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in
both s and t. t is potentially a very long (length ~= 500,000) string,
and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the
original string by deleting some (can be none) of the characters
without disturbing the relative positions of the remaining characters.
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B,
and you want to check one by one to see if T has its subsequence.
In this scenario, how would you change your code?

/*
    Submission Date: 2017-08-30
    Runtime: 69 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int s_index = 0, t_index = 0;
    int s_len = s.size(), t_len = t.size();

    while (s_index < s_len && t_index < t_len) {
      if (s[s_index] == t[t_index]) {
        s_index++;
      }
      t_index++;
    }

    return s_index == s_len;
  }

  bool isSubsequence2(string s, string t) {
    int N = s.size(), M = t.size();
    vector<vector<bool>> dp(N + 1, vector<bool>(M + 1, false));
    for (int i = 0; i <= M; i++) dp[0][i] = true;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        if (s[i - 1] == t[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = dp[i][j - 1];
        }
      }
    }
    return dp[N][M];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
394. Decode String
Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; No extra white spaces,
square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits
and that digits are only for those repeat numbers, k. For example, there won't
be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
/*
    Submission Date: 2018-05-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
      find a '[', use count to determine the matching ']'. recursively determine
     the string in between. find the number beside '[' and repeat the string in
     between that many times. look for '[' and repeat until there is no more
     '[', then just add the suffix.
  */
  string decodeString(string s) {
    int start = 0;

    string res = "";
    while (s.find('[', start) != string::npos) {
      int bracket_index = s.find('[', start);

      int num_index = bracket_index - 1;
      while (num_index >= 0 && isdigit(s[num_index])) {
        num_index--;
      }

      res += s.substr(start, num_index + 1 - start);

      int num = stoi(s.substr(num_index + 1, bracket_index - num_index - 1));
      int cnt = 0;
      for (int i = bracket_index; i < s.size(); i++) {
        cnt += s[i] == '[';
        cnt -= s[i] == ']';
        if (cnt == 0) {
          string to_repeat =
              decodeString(s.substr(bracket_index + 1, i - bracket_index - 1));
          for (int j = 0; j < num; j++) {
            res += to_repeat;
          }
          start = i + 1;
          break;
        }
      }
    }

    return res + s.substr(start);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
400. Nth Digit
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9,
10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n <
231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0,
which is part of the number 10.
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
  /*
  1-9, 10-99, 100-999
  have digits i=1,2,3 respectively
  so find the smallest i which does not exceed n
  
  so 10^(i-1) + allowed is the number
  allowed is (n - (sum of previous numbers with less than i digits))/i
  
  once the number is found, find the character by seeing the remainder
  */
  int findNthDigit(int n) {
    int sum = 0;
    int i = 1;
    while (i < 10) {
      if (sum + 9 * pow(10, i - 1) * i >= n) {
        int allowed = (n - (sum + 1)) / i;
        int num = pow(10, i - 1) + allowed;
        string num_s = to_string(num);
        return num_s[(n - (sum + 1)) % i] - '0';
      }
      sum += 9 * pow(10, i - 1) * i;
      i++;
    }

    return -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
401. Binary Watch
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6
LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are
currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16",
"0:32"] Note: The order of output does not matter. The hour must not contain a
leading zero, for example "01:00" is not valid, it should be "1:00". The minute
must be consist of two digits and may contain a leading zero, for example "10:2"
is not valid, it should be "10:02".
/*
    Submission Date: 2018-06-08
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  int NumBits(int x) {
    int res = 0;
    while (x) {
      x &= (x - 1);
      res++;
    }

    return res;
  }

 public:
  /*
  map with key being number of bits and value being the number
  for each hour, get the number of bits and then lookup the remaining
  number of bits needed
  */
  vector<string> readBinaryWatch(int num) {
    unordered_map<int, vector<string>> m;
    for (int i = 0; i < 60; i++)
      m[NumBits(i)].push_back((i < 10 ? ":0" : ":") + to_string(i));

    vector<string> res;
    for (int i = 0; i < 12; i++) {
      int target = num - NumBits(i);
      if (!m.count(target)) continue;
      for (const auto& e : m[target]) res.push_back(to_string(i) + e);
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
404. Sum of Left Leaves
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively.
Return 24.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int sumOfLeftLeaves(TreeNode *root) {
    if (root == NULL) return 0;
    int res = 0;
    if (root->left && root->left->left == NULL && root->left->right == NULL) {
      res += root->left->val;
    }

    return res + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
405. Convert a Number to Hexadecimal
Given an integer, write an algorithm to convert it to hexadecimal. For negative
integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero,
it is represented by a single zero character '0'; otherwise, the first character
in the hexadecimal string will not be the zero character. The given number is
guaranteed to fit within the range of a 32-bit signed integer. You must not use
any method provided by the library which converts/formats the number to hex
directly. Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"
/*
    Submission Date: 2018-05-26
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
      % 16 gets the last 4 bits. if it is negative then add 16 ie -1 -> 15.
      >> 4 shifts by 4 bits through sign extending so it is not equivalent to /
     16 since the last 4 bits are added first the string must be reversed. the
     last non zero character is the first character in the string so trim it.
  */
  char helper(int x) {
    if (x < 0) x += 16;
    return (x % 10) + (x < 10 ? '0' : 'a');
  }
  string toHex(int num) {
    string res = "";
    int last_non_zero = 0;

    for (int i = 0; i < 8; i++) {
      res.push_back(helper(num % 16));
      num >>= 4;
      if (res.back() != '0') last_non_zero = i;
    }

    res = res.substr(0, last_non_zero + 1);
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }