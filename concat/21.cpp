
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
461. Hamming Distance
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 2^31.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        while(x && y) {
            res += (x % 2) != (y % 2); // check if last bit are different
            x /= 2;
            y /= 2;
        }
        
        while(x) {
            x &= (x-1); // y is all zeros so just count number of ones in x
            res++;
        }
        
        while(y) {
            y &= (y-1); // x is all zeros so just count number of ones in y
            res++;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
463. Island Perimeter
You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. 
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and 
there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" (water inside that isn't 
connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height 
don't exceed 100. Determine the perimeter of the island.

Example:

[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

/*
    Submission Date: 2018-05-31
    Runtime: 245 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,-1,1};
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int res = 0;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == 0) continue;
                for(int k = 0; k < 4; k++) {
                    int new_x = dx[k] + j;
                    int new_y = dy[k] + i;
                    // if out of bounds or is a zero element, add one
                    if(new_x < 0 || new_x >= grid[0].size() || new_y < 0 || new_y >= grid.size() || 
                       grid[new_y][new_x] == 0) {
                        res++;
                    }
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
476. Number Complement
Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
Example 1:
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    // flip all bits then find the highest power of 2. Make that and all bits below it to 1 and AND it with the previous number.
    int findComplement(int num) {
        return ~num & ((1 << (int)log2(num) + 1) - 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
485. Max Consecutive Ones
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
/*
    Submission Date: 2018-06-03
    Runtime: 37 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int curr = 0;
        int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 1) {
                curr++;
                res = max(res, curr);
            } else {
                curr = 0;
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
491. Increasing Subsequences
Given an integer array, your task is to find all the different possible increasing 
subsequences of the given array, and the length of an increasing subsequence should be at least 2 .

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
Note:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered 
as a special case of increasing sequence.
/*
    Submission Date: 2017-03-11
    Runtime: 286 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> findSubsequences(const vector<int>& nums) {
        int N = nums.size();
        vector<vector<vector<int>>> dp(N);
        vector<vector<int>> res;
        set<vector<int>> used;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i] >= nums[j]) {
                    for(auto seq: dp[j]) {
                        seq.push_back(nums[i]);
                        dp[i].push_back(seq);
                    }
                }
            }
            dp[i].push_back({nums[i]});
        }
        
        for(auto vec: dp) {
            for(auto seq: vec) {
                if(seq.size() >= 2 && !used.count(seq)) {
                    res.push_back(seq);
                    used.insert(seq);
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
492. Construct the Rectangle
For a web developer, it is very important to know how to design a web page's size. So, given a specific rectangular web 
page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

1. The area of the rectangular web page you designed must equal to the given target area.

2. The width W should not be larger than the length L, which means L >= W.

3. The difference between length L and width W should be as small as possible.
You need to output the length L and the width W of the web page you designed in sequence.
Example:
Input: 4
Output: [2, 2]
Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the 
length L is 2, and the width W is 2.
Note:
The given area won't exceed 10,000,000 and is a positive integer
The web page's width and length you designed must be positive integers.
/*
    Submission Date: 2018-06-07
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        for(int i = sqrt(area); i >= 1; i--) {
            if(area % i == 0) return {area/i, i};
        }
        return {};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
496. Next Greater Element I
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for 
nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.
/*
    Submission Date: 2018-06-02
    Runtime: 11 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    /*
        For a stack of decreasing number, if there is a number x encountered.
        All the numbers in the stack that x is greater than will have their return value to be x
        and x is placed in the stack. This means there is no number in the stack that is less than x
        eg [1,3,4,2,3]
         []     1 => [1]
         [1]    3 => [3]    update greater(1) = 3
         [3]    4 => [4]    update greater(3) = 4
         [4]    2 => [4,2]
         [4,2]  3 => [4,3]  update greater(2) = 3
    */
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        if(nums.empty()) return {};
        
        int N = findNums.size();
        // decreasing numbers
        stack<int> stk;
        
        unordered_map<int,int> val_to_greater_val;
        for(const auto& x: nums) {
            while(!stk.empty() && stk.top() < x) {
                val_to_greater_val[stk.top()] = x;
                stk.pop();
            }
            
            stk.push(x);
        }
        
        vector<int> res;
        for(const auto& x: findNums) {
            res.push_back(val_to_greater_val.count(x) ? val_to_greater_val[x] : -1);
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
500. Keyboard Row
Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.


American keyboard


Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
Note:
You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // Have a map of character to row. Loop through each string and check if all the characters come from the same row.
    vector<string> findWords(vector<string>& words) {
        vector<string> v{"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        unordered_map<char, int> m;

        for(int i = 0; i < v.size(); i++) {
            for(const auto& c: v[i]) m[c] = i;
        }

        vector<string> res;
        for(const auto& s: words) {
            int ind = -1;
            bool can_add = true;
            for(const auto& c: s) {
                if(ind == -1) ind = m[tolower(c)];
                if(m[tolower(c)] != ind) {
                    can_add = false;
                    break;
                }
            }

            if(can_add) res.push_back(s);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
506. Relative Ranks
Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who 
will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal". 
For the left two athletes, you just need to output their relative ranks according to their scores.
Note:
N is a positive integer and won't exceed 10,000.
All the scores of athletes are guaranteed to be unique.
/*
    Submission Date: 2018-06-08
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        map<int,int, greater<int>> m;
        for(int i = 0; i < nums.size(); i++) m[nums[i]] = i;
        
        vector<string> rep{"Gold Medal", "Silver Medal", "Bronze Medal"};
        
        vector<string> res(nums.size());
        int ind = 0;
        for(const auto& kv: m) {
            res[kv.second] = ind < 3 ? rep[ind] : to_string(ind+1);
            ind++;
        }
        
        return res;
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
520. Detect Capital
Given a word, you need to judge whether the usage of capitals 
in it is right or not.

We define the usage of capitals in a word to be right when one 
of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than 
one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a 
right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase 
and lowercase latin letters.

/*
    Submission Date: 2017-07-30
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>

using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        int N = word.size();
        int capital_count = 0, lower_count = 0;
        for(auto c: word) {
            capital_count += isupper(c) != 0;
            lower_count += islower(c) != 0;
        }
        
        return capital_count == N || lower_count == N || 
            (capital_count == 1 && lower_count == N - 1 && isupper(word[0]));
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
521. Longest Uncommon Subsequence I
Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings. 
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence 
should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the 
order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be two strings, and the output needs to be the length of the longest uncommon subsequence. If the longest 
uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc"
Output: 3
Explanation: The longest uncommon subsequence is "aba" (or "cdc"), 
because "aba" is a subsequence of "aba", 
but not a subsequence of any other strings in the group of two strings. 
Note:

Both strings' lengths will not exceed 100.
Only letters from a ~ z will appear in input strings.
/*
    Submission Date: 2018-06-02
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
      question is asking if for all subsequences of A (ss_A) and all subsequences of B (ss_B)
      what is the longest ss_A that is not ss_B and vice versa

      if A == B, then no matter what subsequence of A is made, it can be made in B so return -1
      if len(A) > len(B) then removing letters from B will always be smaller than A so return A
      if len(A) < len(B) then removing letters from A will always be smaller than B  so return B
      if len(A) == len(B), since they are not the same if we arbitrarily choose A and start removing letters from B
      it will always be smaller than A, so return A. the samething can occur if choose B arbitrarily.
    */
    int findLUSlength(string a, string b) {
        if(a == b) return -1;
        return max(a.size(), b.size());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
525. Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

/*
    Submission Date: 2017-04-01
    Runtime: 162 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLen = 0;
        int currentSum = 0;
        
        // unordered_map has key to currentSum and value to earliest index seen with that 
        // currentSum. the idea is that if the cumulative sum is the same then the sum of 
        // elements between those two indices is zero meaning equal number of 0's and 1's
        // so finding the smallest index with the same currentSum results in the largest subarray
        unordered_map<int, int> m = {{0, -1}};
    
        for(int i = 0, len = nums.size(); i < len; i++) {
            if(nums[i] == 0) {
                currentSum--;
            } else {
                currentSum++;
            }
            
            if(m.find(currentSum) == m.end()) {
                m[currentSum] = i;
            } else {
                maxLen = max(maxLen, i - m[currentSum]);
            }
        }
        
        return maxLen;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
530. Minimum Absolute Difference in BST
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.
/*
    Submission Date: 2018-06-07
    Runtime: 19 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
public:
    /*
    help called on node returns the smallest and largest value with node as the root
    this means for a node, it is help(root->left)'s smallest value and help(root->right)'s largest value
    if they exist else it is just the node
    
    the minimum difference is this node minus largest value in the left subtree or smallest value in right subtree 
    minus this node
    */
    vector<int> help(TreeNode* root, int& res) {
        if(root == NULL) return {};
        vector<int> left = help(root->left, res);
        vector<int> right = help(root->right, res);
        
        int min_left = left.empty() ? root->val : left[0];
        int max_right = right.empty() ? root->val : right[1];
        
        if(!left.empty()) res = min(res, root->val - left[1]);
        if(!right.empty()) res = min(res, right[0] - root->val);
        
        return {min_left, max_right};
    }
    
    int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX;
        help(root, res);
        return res;
    }
};

class Solution {
public:
    /*
    inorder traversal keeping tracking of prev
    */
    void help(TreeNode* root, int& res, int& prev) {
        if(root == NULL) return;
        help(root->left, res, prev);
        if(prev != INT_MAX) {
            res = min(res, root->val - prev);
        }
        
        prev = root->val;
        help(root->right, res, prev);
    }
    
    int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX, prev = INT_MAX;
        help(root, res, prev);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
536. Construct Binary Tree from String
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, 
one or two pairs of parenthesis. The integer represents the root's value and a pair 
of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   

Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.

/*
    Submission Date: 2017-03-11
    Runtime: 42 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* str2tree(string s) {
        int len = s.size();
        if(len == 0) return NULL;

        int firstBracketIndex = s.find('(');
        if(firstBracketIndex == string::npos) return new TreeNode(stoi(s));

        TreeNode* node = new TreeNode(stoi(s.substr(0, firstBracketIndex)));
        int count = 1;
        int offset = firstBracketIndex + 1;
        int i = offset;

        while(count != 0) {
            if(s[i] == ')') count--;
            else if(s[i] == '(') count++;
            i++;
        }

        string leftExpression = s.substr(offset, i - 1 - offset);
        string rightExpression = (i == len) ? "" : s.substr(i + 1, len - i - 2);

        node -> left = str2tree(leftExpression);
        node -> right = str2tree(rightExpression);

        return node;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
538. Convert BST to Greater Tree
Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the 
original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
/*
    Submission Date: 2018-06-07
    Runtime:  ms
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
    /*
    reverse inorder traversal with curr storing the sum of all elements greater than current node
    */
    void help(TreeNode* node, int& curr) {
        if(node == NULL) return;
        help(node->right, curr);
        node->val += curr;
        curr = node->val;
        help(node->left, curr);
    }
    TreeNode* convertBST(TreeNode* root) {
        int curr = 0;
        help(root, curr);
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
539. Minimum Time Difference
Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum 
minutes difference between any two time points in the list.

Example 1:
Input: ["23:59","00:00"]
Output: 1

Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.

/*
    Submission Date: 2017-03-11
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

class Solution {
public:
    // Assume time b is larger than a
    int getDifference(string a, string b) {
        int hours = stoi(b.substr(0,2)) - stoi(a.substr(0,2));
        int minutes = stoi(b.substr(3,2)) - stoi(a.substr(3,2));
        return hours*60 + minutes;
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int minDiff = INT_MAX;
        int len = timePoints.size();

        for(int i = 1; i < len; i++) {
            int diff = getDifference(timePoints[i-1], timePoints[i]);
            if(diff < minDiff) minDiff = diff;
        }

        string firstTimePoint = timePoints.front();
        int wrappedHour = stoi(firstTimePoint.substr(0,2)) + 24;
        string wrap = to_string(wrappedHour) + firstTimePoint.substr(2);
        int wrapDiff = getDifference(timePoints.back(), wrap);

        if(wrapDiff < minDiff) minDiff = wrapDiff;
        return minDiff;
    }
};

int main() {
    return 0;
}
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
557. Reverse Words in a String III
Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.
/*
    Submission Date: 2018-05-31
    Runtime: 28 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    // from index 'start', find a space and reverse everything between start and space. change start to space + 1.
    string reverseWords(string s) {
        int start = 0;
        while(s.find(' ', start) != string::npos) {
            int space_ind = s.find(' ', start);
            reverse(s.begin() + start, s.begin() + space_ind);
            start = space_ind + 1;
        }
            
        reverse(s.begin() + start, s.end());
        return s;
    }
};

int main() {
    return 0;
}