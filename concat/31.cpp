
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
693. Binary Number with Alternating Bits
Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
/*
    Submission Date: 2018-06-02
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution2 {
public:
    // 0x5555555555555555 checks if any of the even bits are set as 5 is 0101
    bool IsPowerOfFour(long long x) {
        return (x & ~(x-1)) == x && (x & 0x5555555555555555);
    }
    
    // 0xaaaaaaaaaaaaaaaa checks if any of the odd bits are set as a is 1010
    bool IsPowerOfFourTimesTwo(long long x) {
        return (x & ~(x-1)) == x && (x & 0xaaaaaaaaaaaaaaaa);
    }
    /*
        sum of geometric series is (1-r^n)/(1-r) so sum 2^(2i) and sum 2^(2i+1) becomes
        sum(2^(2i)) = sum(4^i) = (1-4^n)/(1-4) = (4^n-1)/3
        sum(2^(2i+1)) = 2*sum(4^i) = 2*(1-4^n)/(1-4) = (2*4^n-2)/3
        so check if the number x = (4^n-1)/3 or x = (2*4^n-2)/3 works
    */
    bool hasAlternatingBits(long long n) {
        return IsPowerOfFour(3*n+1) || IsPowerOfFourTimesTwo(n*3+2);
    }
};

class Solution {
public:
    /*
        shift number by two bits and xor it with itself. only the leading one should remeain
        first operation gives one if x[i] != x[i+2] so if they are all zero it means x[0] = x[2] = x[4] = ... x[2*n]
        and x[1] = x[3] = x[5] = ... x[2*n+1]

        x[0] and x[1] can give 4 combinations 00, 01, 10, 11 so checking that there is just a leading one ensures
        there is only one 1 and one 0 that propogate correctly to the rest of the numbers.
    */
    bool hasAlternatingBits(int n) {
        int x = ((n >> 2) ^ n);
        return (x & ~(x-1)) == x;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
695. Max Area of Island
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) 
connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.
/*
    Submission Date: 2018-06-03
    Runtime: 32 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,-1,1};
public:
    int dfs(vector<vector<int>>& grid, int i, int j, int N, int M) {
        grid[i][j] = 0;
        
        int res = 1;
        for(int k = 0; k < 4; k++) {
            int new_x = j + dx[k];
            int new_y = i + dy[k];
            if((0 <= new_x && new_x < M) && (0 <= new_y && new_y < N) && grid[new_y][new_x] == 1) {
                res += dfs(grid, new_y, new_x, N, M);
            }
        }
        return res;
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int N = grid.size();
        int M = grid[0].size();
        int res = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(grid[i][j] == 1) {
                    res = max(res, dfs(grid, i, j, N, M));
                }
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
696. Count Binary Substrings
Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, 
and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.
/*
    Submission Date: 2018-05-24
    Runtime: 45 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        suppose there is prev_cnt which is the number of repeated characters before index i that is
        different than s[i].
        Find how many s[i] repeats e.g. if it repeats from [i,j)
        The number of times s[i] repeats (j-i) and the number of times previous character repeated (prev_cnt)
        and the minimum between these two is the number of times that the substrings can have the same
        number of characters from both characters.
        e.g
        3 4
        000 1111
        min(3,4) = 3
        000 111, 00 11, 0 1
    */
    int countBinarySubstrings(string s) {
        int res = 0;
        int N = s.size();
        int prev_cnt = 0;
        for(int i = 0; i < N;) {
            int start = i;
            while(i < N && s[i] == s[start]) i++;
            res += min(prev_cnt, i - start);
            prev_cnt = i - start;
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
697. Degree of an Array
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
/*
    Submission Date: 2018-05-24
    Runtime: 59 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
public:
    /*
        Find the maximum frequency, loop through and if the number occurs as many times as max frequency
        then store the first seen and last seen index.
        Loop through the first seen and last seen indicies to find the shortest one.
    */
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int,int> val_to_freq;
        int max_freq = 0;
        for(const auto& n: nums) {
            val_to_freq[n]++;
            max_freq = max(max_freq, val_to_freq[n]);
        }
        
        unordered_map<int, pair<int, int>> val_to_seen_boundaries;
        for(int i = 0; i < nums.size(); i++) {
            if(val_to_freq[nums[i]] != max_freq) continue;
            if(!val_to_seen_boundaries.count(nums[i])) val_to_seen_boundaries[nums[i]] = {i, i};
            val_to_seen_boundaries[nums[i]].second = i;
        }
        
        int res = INT_MAX;
        for(const auto& kv: val_to_seen_boundaries) res = min(res, kv.second.second - kv.second.first);
        return res + 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
709. To Lower Case
Implement function ToLowerCase() that has a string parameter str, and returns 
/*
    Submission Date: 2018-07-12
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string toLowerCase(string str) {
        for(auto& c: str) c = tolower(c);
        return str;
    }
};

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
712. Minimum ASCII Delete Sum for Two Strings
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
Note:

0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].
/*
    Submission Date: 2018-07-01
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
    dp[i][j] is minimum cost for s1[0, i) s2[0, j)
    dp[0][0] = 0
    dp[0][j] = s2[j-1] + dp[i][j-1] // sum of ascii of s2[0, j)
    dp[i][0] = s1[i-1] + dp[i-1][j] // sum of ascii of s1[0, i)
    
    if s1[i-1] == s2[j-1] 
        dp[i][j] = dp[i-1][j-1] // this character does not to be deleted so
                                // it is just excluding the two end characters
    else
        dp[i][j] = min(
            s1[i-1] + dp[i-1][j], // the cost of the end character of s1 + cost of not using that character
            s2[j-1] + dp[i][j-1] // cost of the end character of s2 + cost of not using that character
        )
    */
    int minimumDeleteSum(string s1, string s2) {
        int N = s1.size(), M = s2.size();
        int dp[N+1][M+1];
        for(int i = 0; i <= N; i++) {
            for(int j = 0; j <= M; j++) {
                if(i == 0 && j == 0) {
                    dp[i][j] = 0;
                } else if(i == 0) {
                    dp[i][j] = s2[j-1] + dp[i][j-1];
                } else if(j == 0) {
                    dp[i][j] = s1[i-1] + dp[i-1][j];
                } else if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(s1[i-1] + dp[i-1][j], s2[j-1] + dp[i][j-1]);
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
717. 1-bit and 2-bit Characters
We have two special characters. The first character can be represented by one bit 0. The second character can be represented by 
two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given 
string will always end with a zero.

Example 1:
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
Example 2:
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.
Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
/*
    Submission Date: 2018-06-07
    Runtime: 7 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int N = bits.size();
        vector<bool> dp(N, false);
        dp[N-1] = true;

        for(int i = N-2; i >= 0; i--) {
            if(bits[i] == 0) {
                dp[i] = dp[i+1];
            } else {
                if(i + 2 < N) dp[i] = dp[i+2];
            }
        }

        return dp[0];
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
720. Longest Word in Dictionary
Given a list of strings words representing an English Dictionary, find the longest word in words that can be 
built one character at a time by other words in words. If there is more than one possible answer, return the longest word with 
the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input: 
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation: 
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input: 
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: 
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].
/*
    Submission Date: 2018-05-24
    Runtime: 56 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    bool is_word;
    TrieNode* child[26];
    TrieNode() {
        is_word = false;
        for(int i = 0; i < 26; i++) child[i] = NULL;
    }
};

class Trie {
public:
    TrieNode* root_;
    
    /** Initialize your data structure here. */
    Trie() {
        root_ = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* curr = root_;
        for(auto c: word) {
            if(curr -> child[c - 'a'] == NULL) curr -> child[c - 'a'] = new TrieNode();
            curr = curr -> child[c - 'a'];
        }
        curr -> is_word = true;
    }
};

class Solution {
public:
    string dfs(TrieNode* node, string letter) {
        if(node == NULL || !node->is_word) return "";
        string max_child = "";
        for(int i = 0; i < 26; i++) {
            string child = dfs(node -> child[i], string(1, 'a' + i));
            if(child.size() > max_child.size()) {
                max_child = child;
            }
        }
        
        return letter + max_child;
    }
    string longestWord(vector<string>& words) {
        Trie trie;
        for(const auto& s: words) trie.insert(s);
        trie.root_ -> is_word = true;
        return dfs(trie.root_, "");
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
724. Find Pivot Index
Given an array of integers nums, write a method that returns the "pivot" index of this array.

We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.

If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.

Example 1:
Input: 
nums = [1, 7, 3, 6, 5, 6]
Output: 3
Explanation: 
The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the sum of numbers to the right of index 3.
Also, 3 is the first index where this occurs.
Example 2:
Input: 
nums = [1, 2, 3]
Output: -1
Explanation: 
There is no index that satisfies the conditions in the problem statement.
Note:

The length of nums will be in the range [0, 10000].
Each element nums[i] will be an integer in the range [-1000, 1000].
/*
    Submission Date: 2018-06-09
    Runtime: 45 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    make right = sum of all array then at each index i decrease nums[i]
    have left = 0 and increase it by nums[i] to compare if
    the left sum == right sum
    */
    int pivotIndex(vector<int>& nums) {
        int right = 0;
        for(const auto& e: nums) right += e;
        
        int left = 0;
        for(int i = 0; i < nums.size(); i++) {
            right -= nums[i];
            if(left == right) return i;
            left += nums[i];
        }
        
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
728. Self Dividing Numbers
A self-dividing number is a number that is divisible by every digit it contains.

For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.

Also, a self-dividing number is not allowed to contain the digit zero.

Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.

Example 1:
Input: 
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
Note:

The boundaries of each input argument are 1 <= left <= right <= 10000.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> res;
        
        for(int i = left; i <= right; i++) {
            int x = i;
            bool can_use = true;
            while(x) {
                if(x % 10 == 0 || i % (x % 10) != 0) {
                    can_use = false;
                    break;
                }
                x /= 10;
            }
            
            if(can_use) res.push_back(i);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
733. Flood Fill
An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, 
"flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color 
as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), 
and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input: 
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: 
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected 
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
/*
    Submission Date: 2018-06-08
    Runtime: 57 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image.empty()) return {};
        queue<pair<int,int>> q;
        unordered_set<string> visited;
        
        int N = image.size();
        int M = image[0].size();
        int original_color = image[sr][sc];
        
        q.emplace(sr, sc);
        visited.insert(to_string(sr) + "," + to_string(sc));
        while(!q.empty()) {
            pair<int,int> p = q.front();
            q.pop();
            image[p.first][p.second] = newColor;
            
            for(int k = 0; k < 4; k++) {
                int new_row = p.first + dy[k];
                int new_col = p.second + dx[k];
                if(0 <= new_row && new_row < N && 0 <= new_col && new_col < M && image[new_row][new_col] == original_color) {
                    string key = to_string(new_row) + "," + to_string(new_col);
                    if(!visited.count(key)) {
                        q.emplace(new_row, new_col);
                        visited.insert(key);
                    }
                }
            }
        }
        
        return image;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
739. Daily Temperatures
Given a list of daily temperatures, produce a list that, for each day in the input, 
tells you how many days you would have to wait until a warmer temperature. If there is no future day for which 
this is possible, put 0 instead.

For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
/*
    Submission Date: 2018-06-30
    Runtime: 250 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    /*
    stk keeps an increasing temperatures to the right (represented as indices)
    while stk isn't emtpy and the current element is greater than the smallest element 
    (ie stk top) pop the stk, basically it means this element replaces all the smaller elements
    as it will be closer to the next element while still being greater
    */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        int N = temperatures.size();
        vector<int> res(N, 0);
        for(int i = N-1; i >= 0; i--) {
            while(!stk.empty() && temperatures[stk.top()] <= temperatures[i]) stk.pop();
            res[i] = stk.empty() ? 0 : stk.top() - i;
            stk.push(i);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
744. Find Smallest Letter Greater Than Target
Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the 
smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

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
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(letters[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        if(low == letters.size()) return letters[0];
        return letters[low];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
746. Min Cost Climbing Stairs
On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to 
reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].
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
        if(cost.empty()) return 0;
        int N = cost.size();
        
        vector<int> dp(N + 2, 0);
        for(int i = N-1; i >= 0; i--) {
            dp[i] = cost[i] + min(dp[i+1], dp[i+2]);
        }
        
        return N == 1 ? dp[0] : min(dp[0], dp[1]);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
747. Largest Number At Least Twice of Others
In a given integer array nums, there is always exactly one largest element.

Find whether the largest element in the array is at least twice as much as every other number in the array.

If it is, return the index of the largest element, otherwise return -1.

Example 1:

Input: nums = [3, 6, 1, 0]
Output: 1
Explanation: 6 is the largest integer, and for every other number in the array x,
6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
 

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
    compare if the largest element is > second largest element * 2 then return index of largest element
    else -1
    */
    typedef pair<int,int> pii;
    int dominantIndex(vector<int>& nums) {
        if(nums.empty()) return -1;
        
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        for(int i = 0; i < nums.size(); i++) {
            pq.emplace(nums[i], i);
            if(pq.size() > 2) pq.pop();
        }
        
        int top_ind = pq.top().second;
        pq.pop();
        
        if(pq.empty()) return top_ind;
        
        return nums[top_ind] > nums[pq.top().second]/2 ? -1 : pq.top().second;
    }
};

int main() {
    return 0;
}