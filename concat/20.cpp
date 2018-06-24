
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
378. Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

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
#include <vector>
#include <queue>

using namespace std;

class Solution2 {
public:
    bool Get(const vector<vector<int>>& matrix, int num, int N, int M, int k) {
        int i = 0;
        int j = M-1;
        int curr = 0;
        
        int occurences = 0;
        
        while(i < N && j >= 0) {
            if(matrix[i][j] > num) {
                j--;
            } else {
                int temp = j;
                while(temp >= 0 && matrix[i][temp] == num) temp--;
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
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(Get(matrix, matrix[i][j], N, M, k)) {
                    return matrix[i][j];
                }
            }
        }
        
        return -1;
    }
};

struct Item {
    int i, j, val;
    Item(const int& _i, const int& _j, const int& _val): i(_i), j(_j), val(_val) {}
    bool operator>(const Item& rhs) const {
        return val > rhs.val;
    }
};

class Solution3 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int N = matrix.size();
        int M = matrix[0].size();
        
        priority_queue<Item, vector<Item>, greater<Item>> min_heap;
        for(int j = 0; j < M; j++) {
            min_heap.emplace(0, j, matrix[0][j]);
        }
        
        for(int i = 0; i < k - 1; i++) { // remove k- 1 elements to get the kth element
            Item smallest = min_heap.top();
            min_heap.pop();
            if(smallest.i + 1 < N) {
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
        int high = matrix[M-1][M-1];
        
        while(low <= high) {
            int mid = low + (high-low)/2;
            int num_smaller_than_mid = 0;
            // get the number of elements that are <= mid.
            // suppose the two elements in the array are 10 x 1, 10 x 2 and 10 x 3
            // if k == 15, mid = 2 and num_smaller_than_mid are 10, 20, 30 return low
            // gets the number larger than k
            for(int j = M-1, i = 0; i < N; i++) {
                while(j >= 0 && matrix[i][j] > mid) j--;
                num_smaller_than_mid += j + 1;
            }
            
            if(num_smaller_than_mid >= k) high = mid - 1; // too many elements
            else low = mid + 1; // too little elements
        }
        
        return low;
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
394. Decode String
Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
For example, there won't be input like 3a or 2[4].

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
        find a '[', use count to determine the matching ']'. recursively determine the string in between.
        find the number beside '[' and repeat the string in between that many times. look for '[' and repeat
        until there is no more '[', then just add the suffix.
    */
    string decodeString(string s) {
        int start = 0;
        
        string res = "";
        while(s.find('[', start) != string::npos) {
            int bracket_index = s.find('[', start);
        
            int num_index = bracket_index - 1;
            while(num_index >= 0 && isdigit(s[num_index])) {
                num_index--;
            }

            res += s.substr(start, num_index + 1 - start);
            
            int num = stoi(s.substr(num_index + 1, bracket_index - num_index - 1));
            int cnt = 0;
            for(int i = bracket_index; i < s.size(); i++) {
                cnt += s[i] == '[';            
                cnt -= s[i] == ']';
                if(cnt == 0) {
                    string to_repeat = decodeString(s.substr(bracket_index + 1, i - bracket_index - 1));
                    for(int j = 0; j < num; j++) {
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

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
400. Nth Digit
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

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
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

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
        while(i < 10) {
            if(sum + 9*pow(10, i-1)*i >= n) {
                int allowed = (n - (sum+1))/i;
                int num = pow(10, i-1) + allowed;
                string num_s = to_string(num);
                return num_s[(n - (sum+1)) % i] - '0';
            }
            sum += 9*pow(10, i-1)*i;
            i++;
        }
        
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
401. Binary Watch
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
/*
    Submission Date: 2018-06-08
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    int NumBits(int x) {
        int res = 0;
        while(x) {
            x &= (x-1);
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
        for(int i = 0; i < 60; i++) 
            m[NumBits(i)].push_back((i < 10 ? ":0" : ":") + to_string(i));
        
        vector<string> res;
        for(int i = 0; i < 12; i++) {
            int target = num - NumBits(i);
            if(!m.count(target)) continue;
            for(const auto& e: m[target])
                res.push_back(to_string(i) + e);
        }
        return res;
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
406. Queue Reconstruction by Height
Suppose you have a random list of people standing in a queue. Each person is described by a pair 
of integers (h, k), where h is the height of the person and k is the number of people in front of this 
person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.


Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
/*
    Submission Date: 2018-06-24
    Runtime: 42 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    sort by height (h) and break tie on number greater than or equal to before (called k)

    start from the lowest and for each of the same height, find the kth not used spot and 
    place the pair there. keep track of the number of same height elements already placed.
    */
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        vector<pair<int,int>> res(people.size(), {-1, -1});
        sort(people.begin(), people.end());
        
        int N = people.size();
        for(int i = 0; i < N;) {
            int start = i;
            while(people[i].first == people[start].first) {
                auto p = people[i];
                int to_go = p.second - (i - start);
                for(int j = 0; j < N; j++) {
                    if(res[j].second != -1) continue;
                    if(to_go == 0) {
                        res[j] = p;
                        break;
                    }
                    to_go--;
                }
                i++;
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
409. Longest Palindrome
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
/*
    Submission Date: 2018-05-30
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // return all the frequencies floored to nearest multiple of 2 and add one for if any of the frequency is odd
    int longestPalindrome(string s) {
        unordered_map<char, int> letter_to_freq;
        for(const auto& c: s) letter_to_freq[c]++;
        int res = 0;
        bool has_odd = false;
        
        for(const auto& kv: letter_to_freq) {
            res += (kv.second / 2)*2;
            has_odd |= kv.second % 2;
        }
        
        return res + has_odd;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. 
For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
/*
    Submission Date: 2018-05-31
    Runtime: 5 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res;
        for(int i = 1; i <= n; i++) {
            string s = "";
            if(i % 3 == 0) s += "Fizz";
            if(i % 5 == 0) s += "Buzz";
            if(s.empty()) s = to_string(i);
            res.push_back(s);
        }
        
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
415. Add Strings
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int carry = 0;
        int i = num1.size() - 1, 
            j = num2.size() - 1;
        
        while(i >= 0 || j >= 0) {
            int x = carry;
            if(i >= 0) x += (num1[i] - '0');
            if(j >= 0) x += (num2[j] -'0');
            
            carry = x / 10;
            res.push_back((x % 10) + '0');
            
            i--;
            j--;
        }
        
        if(carry > 0) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    return 0;
}