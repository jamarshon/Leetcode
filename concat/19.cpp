
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in 
both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your 
algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm 
is better?
What if elements of nums2 are stored on disk, and the memory is limited 
such that you cannot load all elements into the memory at once?
/*
    Submission Date: 2017-09-10
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int>* smaller = &nums1, *greater = &nums2;
        if(smaller -> size() > greater -> size()) swap(smaller, greater);
        
        unordered_map<int,int> smaller_freq;
        for(auto n: *smaller) smaller_freq[n]++;
        
        vector<int> res;
        for(auto n: *greater) {
            if(smaller_freq.count(n) && smaller_freq[n] > 0) {
                smaller_freq[n]--;
                res.push_back(n);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
354. Russian Doll Envelopes
You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can 
fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
/*
    Submission Date: 2018-05-24
    Runtime: 30 ms
    Difficulty: HARD
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    NlogN sort by width and break ties on height
    For all elements with the same width, apply the changes all at once
    Similar to LIS where dp[i] is the smallest element of sequence of length i
*/
class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());
        vector<int> heights;

        for(int i = 0; i < envelopes.size();) {
            int start = i;
            unordered_map<int, int> index_to_new_val;
            while(i < envelopes.size() && envelopes[i].first == envelopes[start].first) {
                auto it = lower_bound(heights.begin(), heights.end(), envelopes[i].second);
                int dist = it - heights.begin();
                if(!index_to_new_val.count(dist)) index_to_new_val[dist] = envelopes[i].second;
                i++;
            }

            for(const auto& kv: index_to_new_val) {
                if(kv.first < heights.size()) {
                    heights[kv.first] = kv.second;
                } else {
                    heights.push_back(kv.second);
                }
            }
        }
        return heights.size();
    }
};

/*
    N^2 similar to LIS where dp[i] means the longest sequence ending at element i
    Requires a sort first as all elements of smaller width should appear first.
*/
class Solution2 {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());
        vector<int> dp(envelopes.size(), 1);
        
        for(int i = 0; i < envelopes.size(); i++) {
            for(int j = 0; j < i; j++) {
                if(envelopes[i].first > envelopes[j].first && envelopes[i].second > envelopes[j].second) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        return dp.empty() ? 0 : *max_element(dp.begin(), dp.end());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False
/*
    Submission Date: 2018-05-02
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPerfectSquare(int num) {
      long long low = 1;
      long long high = num;
      while(low <= high) {
        long long mid = low + (high-low)/2;
        if(mid*mid == num) {
          return true;
        } else if(mid*mid < num) {
          low = mid + 1;
        } else {
          high = mid -1;
        }
      }
      return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
368. Largest Divisible Subset
Given a set of distinct positive integers, find the largest subset 
such that every pair (Si, Sj) of elements in this subset satisfies: 
Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)
Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]
/*
    Submission Date: 2017-08-21
    Runtime: 33 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        
        sort(nums.begin(), nums.end());
        int N = nums.size();
        
        vector<int> dp(N, 1), P(N,-1);
        int max_dp_ind = 0;
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i] % nums[j] == 0) {
                    if(dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        P[i] = j;
                    }
                }
            }
            
            if(dp[max_dp_ind] < dp[i]) max_dp_ind = i;
        }
        
        
        vector<int> res(dp[max_dp_ind]);
        int index = res.size();
        for(int i = max_dp_ind; i >= 0; i = P[i]) {
            res[--index] = nums[i];
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.
/*
    Submission Date: 2018-05-02
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <bitset>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
      // include the sign bit.
      bitset<32> res(0);
      bitset<32> aa(a);
      bitset<32> bb(b);

      int carry = 0;
      for(int i = 0; i < 32; i++) {
        int a_d = aa.test(i);
        int b_d = bb.test(i);

        res.set(i, a_d ^ b_d ^ carry);
        carry = (a_d && b_d) || (b_d && carry) || (a_d && carry);
      }

      return res.to_ullong();
    }
};

class Solution2 {
public:
    int getSum(int a, int b) {
        int res = 0;
        int carry = 0;
        
        for(int i = 0; i < 32; i++) {
            const int a_d = (1 << i) & a;
            const int b_d = (1 << i) & b;
            res |= a_d ^ b_d ^ carry;
            carry = ((a_d & b_d) | (b_d & carry) | (a_d & carry)) << 1;
        } 
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
373. Find K Pairs with Smallest Sums
You are given two integer arrays nums1 and nums2 sorted in ascending 
order and an integer k.

Define a pair (u,v) which consists of one element from the first 
array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

/*
    Submission Date: 2017-08-30
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        typedef pair<int,int> pii;
        
        if(nums1.empty() || nums2.empty()) return {};
        
        auto cmp = [&nums1, &nums2](const pii& lhs, const pii& rhs){
            int lhs_sum = nums1[lhs.first] + nums2[lhs.second];
            int rhs_sum = nums1[rhs.first] + nums2[rhs.second];
            return lhs_sum > rhs_sum;
        };
        
        int N1 = nums1.size(), N2 = nums2.size();

        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<pii> res;
        for(int i = 0; i < N1 && i < k; i++) pq.emplace(i, 0);

        while(res.size() < k && !pq.empty()) {
            pii top = pq.top();
            pq.pop();
            
            res.emplace_back(nums1[top.first], nums2[top.second]);

            if(top.second + 1 < N2) pq.emplace(top.first, top.second + 1);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
374. Guess Number Higher or Lower
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

-1 : My number is lower
 1 : My number is higher
 0 : Congrats! You got it!
Example:
n = 10, I pick 6.

Return 6.
/*
    Submission Date: 2018-05-02
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int low = 0;
        int high = n;
        while(low <= high) {
            int mid = low + (high-low)/2;
            int status = guess(mid);
            if(status == 0) {
                return mid;
            } else if(status == -1) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
383. Ransom Note
Given an arbitrary ransom note string and another string containing letters from all the magazines, 
write a function that will return true if the ransom note can be constructed from the magazines ; 
otherwise, it will return false.

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
        unordered_map<char,int> m;
        for(auto e: magazine) m[e]++;
        for(auto e: ransomNote) {
          if(m.count(e)) {
            if(m[e] == 0) return false;
            m[e]--;
          } else {
            return false;
          }
        }
        return true;
    }
};

int main() {
    return 0;
}
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
        if(curr > n) return;

        int limit = min(n + 1, curr == 1 ? 10: curr+10);
        for(int i = curr; i < limit; i++) {
            res.push_back(i);
            lexicalOrder(i*10, n, res);
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
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char,int> letter_to_first_ind;
        set<int> st;
        for(int i = 0; i < s.size(); i++) {
            if(letter_to_first_ind.count(s[i])) { 
                // we've seen this letter before so we remove it from the set
                if(st.count(letter_to_first_ind[s[i]])) {
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

String t is generated by random shuffling string s and then add one more letter at a random position.

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
        unordered_map<char,int> m;
        for(auto e: s) m[e]++;
        for(auto e: t) {
          if(m.count(e)) {
            if(m[e] == 0) return e;
            m[e]--;
          } else {
            return e;
          }
        }
        return '\0';
    }
};


int main() {
    return 0;
}
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
        
        while(s_index < s_len && t_index < t_len) {
            if(s[s_index] == t[t_index]) {
                s_index++;
            }
            t_index++;
        }
        
        return s_index == s_len;
    }

    bool isSubsequence2(string s, string t) {
        int N = s.size(), M = t.size();
        vector<vector<bool>> dp(N + 1, vector<bool>(M + 1, false));
        for(int i = 0; i <= M; i++) dp[0][i] = true;
    
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        return dp[N][M];
    }
};

int main() {
    return 0;
}
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

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

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
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 0;
        if(root -> left && root -> left -> left == NULL && root -> left -> right == NULL) {
            res += root -> left -> val;
        }
        
        return res + sumOfLeftLeaves(root -> left) + sumOfLeftLeaves(root -> right);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
405. Convert a Number to Hexadecimal
Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, 
the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.
Example 1:

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
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
        % 16 gets the last 4 bits. if it is negative then add 16 ie -1 -> 15.
        >> 4 shifts by 4 bits through sign extending so it is not equivalent to / 16
        since the last 4 bits are added first the string must be reversed.
        the last non zero character is the first character in the string so trim it.
    */
    char helper(int x){ if(x < 0) x += 16; return (x % 10) + (x < 10 ? '0' : 'a'); }
    string toHex(int num) {
        string res = "";
        int last_non_zero = 0;
        
        for(int i = 0; i < 8; i++) {
            res.push_back(helper(num % 16));
            num >>= 4;
            if(res.back() != '0') last_non_zero = i;
        }
        
        res = res.substr(0, last_non_zero + 1);
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
414. Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> distinct;
        int max_item = nums.front();
        for(auto num: nums) {
            max_item = max(max_item, num);
            if(distinct.count(num)) continue;
            min_heap.push(num);
            distinct.insert(num);
            if(min_heap.size() > 3) {
                int to_delete = min_heap.top();
                distinct.erase(to_delete);
                min_heap.pop();
            }
        }
        
        return min_heap.size() == 3 ? min_heap.top() : max_item;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
419. Battleships in a Board
Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. 
You may assume the following rules:
You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 
(N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
    N by checking if the element to the left and to the top of board[i][j] isn't a 'X'.
    If there is one then it means it is continuing a ship so it should not be counted.
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if(board.empty()) return 0;
        int res = 0;
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                if(board[i][j] == 'X' && (j == 0 || board[i][j-1] != 'X') && (i == 0 || board[i-1][j] != 'X')) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    return 0;
}