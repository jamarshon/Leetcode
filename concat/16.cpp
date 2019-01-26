
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
282. Expression Add Operators
Given a string that contains only digits 0-9 and a target value, return all
possibilities to add binary operators (not unary) +, -, or * between the digits
so they evaluate to the target value.

Examples:
"123", 6 -> ["1+2+3", "1*2*3"]
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

/*
    Submission Date: 2017-08-12
    Runtime: 59 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void getOperators(string num, int index, int target, string curr, int val,
                    string curr_product, int product, vector<string>& res) {
    int N = num.size();
    if (index == N) {  // no more numbers to process
      if (curr.empty()) {
        // result just contains multiplication curr="" curr_product="ab*c*de" ->
        // "ab*c*de"
        if (product == target) res.push_back(curr_product);
      } else {
        // try add/subtract product to current and see if it reaches target
        // e.g curr = "ab*c*de + f - g*hi"
        // curr_product = "jk*lmn*qr" -> "ab*c*de + f - g*hi - jk*lmn*qr"
        // or "ab*c*de + f - g*hi + jk*lmn*qr". curr_product could just be one
        // number like "qrs"
        if (val - product == target) res.push_back(curr + "-" + curr_product);
        if (val + product == target) res.push_back(curr + "+" + curr_product);
      }
      return;
    }

    int sub_val = num[index] - '0';
    for (int i = index + 1; i <= N; i++) {
      string sub = num.substr(index, i - index);

      // either continue product
      if (!curr_product.empty()) {
        getOperators(num, i, target, curr, val, curr_product + "*" + sub,
                     product * sub_val, res);
      }

      // end product and add or subtract it
      if (!curr.empty()) {
        getOperators(num, i, target, curr + "-" + curr_product, val - product,
                     sub, sub_val, res);
      }

      string new_curr = curr.empty() ? curr_product : curr + "+" + curr_product;
      getOperators(num, i, target, new_curr, val + product, sub, sub_val, res);

      // cannot process multiple zeros e.g 000 + xyz, 0xy or 000*xy is not valid
      // must be single zeros and no leading zeros
      if (num[index] == '0') break;

      // check for overflow of sub_val
      int char_val = num[i] - '0';
      if (sub_val > (INT_MAX - char_val) / 10) break;

      sub_val = sub_val * 10 + char_val;
    }
  }

  vector<string> addOperators(string num, int target) {
    vector<string> res;
    getOperators(num, 0, target, "", 0, "", 0, res);
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
283. Move Zeroes
Given an array nums, write a function to move all 0's to the end
of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your
function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

/*
    Submission Date: 2017-08-30
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int N = nums.size();
    int read_idx = 0, write_idx = 0;
    while (read_idx < N) {
      if (nums[read_idx] != 0) {
        nums[write_idx] = nums[read_idx];
        write_idx++;
      }
      read_idx++;
    }

    while (write_idx < N) nums[write_idx++] = 0;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
284. Peeking Iterator
Given an Iterator class interface with methods: next() and hasNext(),
design and implement a PeekingIterator that support the peek()
operation -- it essentially peek() at the element that will be
returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the
beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling
next() after that still return 2.

You call next() the final time and it returns 3, the last element.
Calling hasNext() after that should return false.

Follow up: How would you extend your design to be generic and work
with all types, not just integer?
/*
    Submission Date: 2017-08-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
  struct Data;
  Data* data;

 public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);
  virtual ~Iterator();
  // Returns the next element in the iteration.
  int next();
  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

class PeekingIterator : public Iterator {
  Iterator* it_;

 public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
    it_ = new Iterator(nums);
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    assert(hasNext());
    Iterator* temp = new Iterator(*it_);
    int res = it_->next();
    delete it_;
    it_ = temp;
    return res;
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    assert(hasNext());
    return it_->next();
  }

  bool hasNext() const { return it_->hasNext(); }
};

class PeekingIterator2 : public Iterator {
  int prev_;
  bool remaining_;
  Iterator* it_;

 public:
  PeekingIterator2(const vector<int>& nums) : Iterator(nums) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
    it_ = new Iterator(nums);
    remaining_ = it_->hasNext();
    if (remaining_) {
      prev_ = it_->next();
    }
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() { return prev_; }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    int res = prev_;
    remaining_ = it_->hasNext();
    if (remaining_) prev_ = it_->next();
    return res;
  }

  bool hasNext() const { return remaining_; }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
287. Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is
between 1 and n (inclusive), prove that at least one duplicate number
must exist. Assume that there is only one duplicate number, find the
duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be
repeated more than once.
/*
    Submission Date: 2017-08-30
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      Find beginning of cycle of linked list. nums[i] represents
      node i has a link to node nums[i]. since nums[i] is [1,n]
      it means it will always have a link to an element in the
      array. there are n+1 numbers and they span from [1,n] so
      a duplicate must exist eg n = 2 -> 1,2,_ .
      pigeonhole principle states that if n items are put into m
      containers, with n > m, then at least one container must
      contain more than one item.
      a cycle will occur as two numbers point to the same index
      one number going into the cycle and the second completing
      the cycle e.g [1,3,4,2,2] ->
      indices 0 -> 1 -> 3 -> 2 -> 4 -> 2
      values  1 -> 3 -> 2 -> 4 -> 2 -> 4
      0 can't be the start of the cycle as there is no number
      going into the cycle (index 0) meaning this method won't work
      (the guarantee of nums[i] between [1,n] must exist).
  */
  int findDuplicate(vector<int>& nums) {
    int slow = 0;
    int fast = 0;

    do {
      slow = nums[slow];
      fast = nums[nums[fast]];
    } while (slow != fast);

    slow = 0;
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[fast];
    }

    return slow;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
289. Game of Life
According to the Wikipedia's article: "The Game of Life, also known
simply as Life, is a cellular automaton devised by the British
mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live
(1) or dead (0). Each cell interacts with its eight neighbors
(horizontal, vertical, diagonal) using the following four rules
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused
by under-population.
Any live cell with two or three live neighbors lives on to the next
generation.
Any live cell with more than three live neighbors dies, as if by
over-population..
Any dead cell with exactly three live neighbors becomes a live cell,
as if by reproduction.
Write a function to compute the next state (after one update) of the
board given its current state.

Follow up:
Could you solve it in-place? Remember that the board needs to be
updated at the same time: You cannot update some cells first and
then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In
principle, the board is infinite, which would cause problems
when the active area encroaches the border of the array. How
would you address these problems?
/*
    Submission Date: 2017-08-30
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  typedef pair<int, int> pii;

 public:
  int getAdajacent(const vector<vector<int>>& board, int row, int col, int M,
                   int N) {
    int res = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        int x = row + i;
        int y = col + j;
        if (0 <= x && x < M && 0 <= y && y < N) {
          res += board[x][y] & 1;
        }
      }
    }

    return res;
  }
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;

    vector<pii> make_live, make_dead;
    int M = board.size();
    int N = board[0].size();

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live = getAdajacent(board, i, j, M, N);
        if (board[i][j] == 0) {
          if (live == 3) make_live.emplace_back(i, j);
        } else {
          if (live < 2 || live > 3) make_dead.emplace_back(i, j);
        }
      }
    }

    for (auto p : make_dead) board[p.first][p.second] = 0;
    for (auto p : make_live) board[p.first][p.second] = 1;
  }

  void gameOfLife2(vector<vector<int>>& board) {
    if (board.empty()) return;

    int M = board.size();
    int N = board[0].size();

    /*
        O(1) space by storing whether to toggle for the next
        state in the second bit. 1x means needs to toggle whereas
        0x means doesn't need to toggle. Get state of z by (z & 1)
        and get whether to toggle by (z >> 1) so next state of
        z is just (z >> 1) ^ (z & 1)
    */
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int live = getAdajacent(board, i, j, M, N);
        if (board[i][j] == 0) {
          board[i][j] |= (live == 3) << 1;
        } else {
          board[i][j] |= (live < 2 || live > 3) << 1;
        }
      }
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        board[i][j] = (board[i][j] >> 1) ^ (board[i][j] & 1);
      }
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
290. Word Pattern
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a
letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains
lowercase letters separated by a single space.
/*
    Submission Date: 2017-09-10
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool wordPattern(string pattern, string str) {
    unordered_map<char, string> letter_to_word;
    unordered_map<string, char> word_to_letter;

    stringstream ss(str);
    string word;

    int i = 0, N = pattern.size();
    while (i < N) {
      ss >> word;
      if (word.empty()) return false;
      if (letter_to_word.count(pattern[i]) || word_to_letter.count(word)) {
        if (word_to_letter[word] != pattern[i] ||
            letter_to_word[pattern[i]] != word)
          return false;
      } else {
        letter_to_word[pattern[i]] = word;
        word_to_letter[word] = pattern[i];
      }
      i++;
    }

    bool rem = (bool)(ss >> word);
    return !rem;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
292. Nim Game
You are playing the following Nim Game with your friend: There is a
heap of stones on the table, each time one of you take turns to
remove 1 to 3 stones. The one who removes the last stone will
be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the
game. Write a function to determine whether you can win the game
given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will
never win the game: no matter 1, 2, or 3 stones you remove,
the last stone will always be removed by your friend.
/*
    Submission Date: 2017-08-26
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
      if n <= 3, player wins as they just take it
      if n == 4, player loses as no matter what they take
      there will be some remaining for opponent

      if 4 < n <= 4 + 3, player can win as they can reduce
      it to n == 4 by taking away [1,3] stones

      if n == 8, player loses as no matter what they take
      opponent can reduce it n == 4

      for the generalized case (n):
      if n % 4 == 0, player loses as whatever they take x = [1,3],
      opponent takes 4 - x to get n % 4 == 0 again until n == 4
      which opponent wins
      so n % 4 != 0 where n % 4 == x where x = [1, 3] is when player
      wins as player can reduce by x leading to n % 4 == 0 for the opponent
      causing the opponent to lose as seen above
  */
  bool canWinNim(int n) { return n % 4 != 0; }
};

int main() {
  Solution s;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
295. Find Median from Data Stream
Median is the middle value in an ordered integer list. If the size of
the list is even, there is no middle value. So the median is the mean
of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the
data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
/*
    Submission Date: 2017-09-10
    Runtime: 172 ms
    Difficulty: HARD
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
  typedef priority_queue<int, vector<int>, less<int>> MaxHeap;
  typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

  MaxHeap max_heap_;
  MinHeap min_heap_;

 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    if (max_heap_.empty()) {
      max_heap_.push(num);
    } else {
      if (num > max_heap_.top()) {
        min_heap_.push(num);
      } else {
        max_heap_.push(num);
      }

      // Maintain abs(max_heap_.size() - min_heap_.size()) <= 1
      if (max_heap_.size() > min_heap_.size() + 1) {  // max_heap_ too large
        min_heap_.push(max_heap_.top());
        max_heap_.pop();
      } else if (min_heap_.size() >
                 max_heap_.size() + 1) {  // min_heap_ too large
        max_heap_.push(min_heap_.top());
        min_heap_.pop();
      }
    }
  }

  double findMedian() {
    /*
    Three cases: since abs(max_heap_.size() - min_heap_.size()) <= 1
    denote x as min(max_heap_.size() - min_heap_.size())
    1) size x and x means even elements so it just the average of max of first
    heap and min of second heap 2) size x + 1 and x means odd elements so the
    max of the first heap is the median element 3) size x and x + 1 means odd
    elements so the min of the second heap is the median element
    */
    if (max_heap_.size() == min_heap_.size()) {
      return (double)(max_heap_.top() + min_heap_.top()) / 2.0;
    } else if (max_heap_.size() > min_heap_.size()) {
      return max_heap_.top();
    } else {
      return min_heap_.top();
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into
a sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in
the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is
no restriction on how your serialization/deserialization algorithm should
work. You just need to ensure that a binary tree can be serialized to a
string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a
binary tree. You do not necessarily need to follow this format, so please
be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states.
Your serialize and deserialize algorithms should be stateless.
/*
    Submission Date: 2017-09-10
    Runtime: 46 ms
    Difficulty: HARD
*/
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (root == NULL) {
      return "#,";
    } else {
      string curr = to_string(root->val) + ",";
      string left = serialize(root->left);
      string right = serialize(root->right);
      return curr + left + right;
    }
  }

  TreeNode* deserializeHelper(const string& data, int& index) {
    size_t comma_ind = data.find(",", index);
    assert(comma_ind != string::npos);

    string curr = data.substr(index, comma_ind - index);
    index = comma_ind + 1;

    if (curr == "#") return NULL;

    TreeNode* root = new TreeNode(stoi(curr));
    root->left = deserializeHelper(data, index);
    root->right = deserializeHelper(data, index);
    return root;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int index = 0;
    return deserializeHelper(data, index);
  }
};

class Codec2 {
 public:
  // Encodes a tree to a single string.
  string structure(TreeNode* root) {
    if (root == NULL) return "0";
    return "1" + structure(root->left) + structure(root->right);
  }

  string values(TreeNode* root) {
    if (root == NULL) return "";
    string curr = to_string(root->val) + ",";
    string left = values(root->left);
    string right = values(root->right);
    return curr + left + right;
  }
  string serialize(TreeNode* root) {
    string st = structure(root);
    string val = values(root);
    return st + "," + val;
  }

  TreeNode* deserializeHelper(const string& st, stringstream& ss, int& index) {
    if (st[index] == '0') return NULL;
    string temp;
    getline(ss, temp, ',');
    assert(!temp.empty());

    TreeNode* curr = new TreeNode(stoi(temp));
    index++;
    curr->left = deserializeHelper(st, ss, index);
    index++;
    curr->right = deserializeHelper(st, ss, index);

    return curr;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int index = 0;

    size_t comma_ind = data.find(",");
    string st = data.substr(0, comma_ind);
    string val = data.substr(comma_ind + 1);
    stringstream ss(val);
    return deserializeHelper(st, ss, index);
  }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
299. Bulls and Cows
You are playing the following Bulls and Cows game with your friend:
You write down a number and ask your friend to guess what the number is.
Each time your friend makes a guess, you provide a hint that indicates how
many digits in said guess match your secret number exactly in both digit
and position (called "bulls") and how many digits match the secret number
but locate in the wrong position (called "cows"). Your friend will use
successive guesses and hints to eventually derive the secret number.

For example:

Secret number:  "1807"
Friend's guess: "7810"
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)
Write a function to return a hint according to the secret number and
friend's guess, use A to indicate the bulls and B to indicate the cows.
In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain
duplicate digits, for example:

Secret number:  "1123"
Friend's guess: "0111"
In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is
a cow, and your function should return "1A1B".
You may assume that the secret number and your friend's guess only contain
digits, and their lengths are always equal.
/*
    Submission Date: 2017-09-10
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string getHint(string secret, string guess) {
    int secret_freq[10] = {0};
    int guess_freq[10] = {0};

    int N = secret.size();
    int bulls = 0;
    for (int i = 0; i < N; i++) {
      if (secret[i] == guess[i]) {
        bulls++;
      } else {
        secret_freq[secret[i] - '0']++;
        guess_freq[guess[i] - '0']++;
      }
    }

    int cows = 0;
    for (int i = 0; i < 10; i++) {
      cows += min(secret_freq[i], guess_freq[i]);
    }

    return to_string(bulls) + "A" + to_string(cows) + "B";
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
300. Longest Increasing Subsequence
Given an unsorted array of integers, find the length of longest increasing
subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4.
Note that there may be more than one LIS combination, it is only necessary for
you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?
/*
    Submission Date: 2017-03-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    if (nums.empty()) return 0;

    int N = nums.size(), dp_len = 0;
    vector<int> dp(N, -1), P(N, -1);

    for (int i = 0; i < N; i++) {
      auto it = lower_bound(dp.begin(), dp.begin() + dp_len, nums[i],
                            [&nums](const int& dp_el, const int& val) {
                              return nums[dp_el] < val;
                            });

      int it_ind = it - dp.begin();
      dp[it_ind] = i;

      if (it_ind > 0) P[i] = dp[it_ind - 1];
      if (it_ind == dp_len) dp_len++;
    }

    vector<int> lis_seq(dp_len);
    int index = lis_seq.size();
    for (int i = dp[dp_len - 1]; i >= 0; i = P[i]) lis_seq[--index] = nums[i];

    return dp_len;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
301. Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input
string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
/*
    Submission Date: 2018-05-26
    Runtime: 2 ms
    Difficulty: HARD
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      last_i means checking for negative (more ')' than '(') from string from
     [last_i, s.size()) last_j indicates the last removed ')'
      
      suppose the open < 0, that means ')' must be removed. If there are
     multiple ')' like ")))" then the first one should be removed. Loop from the
     last removed ')' ie. last_j to i and look for these ')' to remove.
      
      s from [0, last_i) is guaranteed to have a open of 0
      suppose s = "()())r)"
      ( ) ( ) ) r )
      0 1 2 3 4 5 6
      
      last_i = 0, last_j = 0 : open is -1 at 4
          remove ')' at 1 last_i = 4, last_j = 1
              ( ( ) ) r )
              0 1 2 3 4 5
              
              open is -1 at 5
                  remove ')' at 2 last_i = 5, last_j = 2
                      ( ( ) r )
                      0 1 2 3 4
                      
                      final res remove (1, 3)
                  remove ')' at 5 last_i = 5, last_j = 5
                      ( ( ) ) r
                      0 1 2 3 4
                      
                      final res remove (1, 6)
          remove ')' at 3 last_i = 4, last_j = 3
              ( ) ( ) r )
              0 1 2 3 4 5
              
              open is -1 at 5
                  remove ')' at 3 last_i = 5, last_j = 3
                      ( ) ( r )
                      0 1 2 3 4
                      
                      final res remove (3, 4)
                  remove ')' at 5 last_i = 5, last_j = 5
                      ( ) ( ) r
                      0 1 2 3 4
                      
                      final res move (3, 6)
      
      last_j keeps track of where we can take ')' from
      
      to consider the case where there is too many '(', just reverse the string
      and change all '(' to ')' and '(' to ')'

  */
  void solve(string s, const int& last_i, const int& last_j,
             vector<string>& res, const vector<char>& p) {
    int open = 0;
    for (int i = last_i; i < s.size(); i++) {
      open += s[i] == p[0];
      open -= s[i] == p[1];
      if (open >= 0) continue;
      for (int j = last_j; j <= i; j++) {
        if (s[j] == p[1] && (j == last_j || s[j - 1] != p[1])) {
          solve(s.substr(0, j) + s.substr(j + 1), i, j, res, p);
        }
      }
      return;
    }

    reverse(s.begin(), s.end());
    if (p[0] == '(') {
      solve(s, 0, 0, res, {')', '('});
    } else {
      res.push_back(s);
    }
  }

  vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    solve(s, 0, 0, res, {'(', ')'});
    return res;
  }
};

int main() { return 0; }