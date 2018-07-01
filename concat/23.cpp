
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
507. Perfect Number
We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.
Example:
Input: 28
Output: True
Explanation: 28 = 1 + 2 + 4 + 7 + 14
Note: The input number n will not exceed 100,000,000. (1e8)
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
    bool checkPerfectNumber(int num) {
        if(num < 2) return false;
        int res = 1;
        for(int i = 2; i <= sqrt(num); i++) {
            if(num % i == 0) {
                res += i;
                res += num/i;
            }
        }
        
        return res == num;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
508. Most Frequent Subtree Sum
Given the root of a tree, you are asked to find the most frequent subtree sum. The 
subtree sum of a node is defined as the sum of all the node values formed by the subtree 
rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, 
return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
/*
    Submission Date: 2018-06-30
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int f(TreeNode* node, unordered_map<int,int>& sum_to_freq, int& max_freq) {
        if(node == NULL) return 0;
        
        int sum = node->val + f(node->left, sum_to_freq, max_freq) + f(node->right, sum_to_freq, max_freq);
        sum_to_freq[sum]++;
        max_freq = max(max_freq, sum_to_freq[sum]);
        return sum;
    }
    
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int,int> sum_to_freq;
        int max_freq = 0;
        f(root, sum_to_freq, max_freq);
        vector<int> res;
        for(const auto& kv: sum_to_freq) 
            if(kv.second == max_freq) res.push_back(kv.first);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
513. Find Bottom Left Tree Value
Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2: 
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.
/*
    Submission Date: 2018-06-24
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        
        TreeNode* res =  NULL;
        while(!q.empty()) {
            res = q.front();
            
            int level = q.size();
            for(int i = 0; i < level; i++) {
                TreeNode* node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        
        return res->val;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]

/*
    Submission Date: 2018-06-29
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if(root == NULL) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()) {
            int n = q.size();
            int max_level = q.front()->val;
            for(int i = 0; i < n; i++) {
                TreeNode* curr = q.front();
                q.pop();
                max_level = max(max_level, curr->val);
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            res.push_back(max_level);
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
532. K-diff Pairs in an Array
Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. 
Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.

Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Note:
The pairs (i, j) and (j, i) count as the same pair.
The length of the array won't exceed 10,000.
All the integers in the given input belong to the range: [-1e7, 1e7].
/*
    Submission Date: 2018-06-24
    Runtime: 43 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(k < 0) return 0;
        int res = 0;
        unordered_set<int> st;
        unordered_set<int> counted;
        for(const auto& e: nums) {
            if(st.count(e)) { counted.insert(e); continue; }
            res += st.count(e + k);
            res += st.count(e - k);
            st.insert(e);
        }
        
        return k == 0 ? counted.size() : res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
535. Encode and Decode TinyURL
TinyURL is a URL shortening service where you enter a URL such as 
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how 
your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to 
a tiny URL and the tiny URL can be decoded to the original URL.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
A vector and return the encoded as an index to retrieve the original string
The encode called upon the same string should not return the same encoded string
as it would have collision problems so usually a randomizer and a storage of encoded
to original is needed.
*/
class Solution {
public:
    vector<string> m;
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        m.push_back(longUrl);
        return to_string(m.size());
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return m[stoi(shortUrl)-1];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

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
537. Complex Number Multiplication
Given two strings representing two complex numbers.

You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of 
[-100, 100]. And the output should be also in this form.
/*
    Submission Date: 2018-06-24
    Runtime: 4 ms
    Difficulty: MEDIUM 
*/
#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
    pair<int,int> Extract(string S) {
        int plus_S_ind = S.find("+");
        string a = S.substr(0, plus_S_ind);
        string b = S.substr(plus_S_ind + 1, S.size() - (plus_S_ind + 1) - 1);
        return {stoi(a), stoi(b)};
    }
    string complexNumberMultiply(string S1, string S2) {
        int a, b, c, d;
        tie(a,b) = Extract(S1);
        tie(c,d) = Extract(S2);
        
        int real = a*c - b*d;
        int imag = b*c + d*a;
        
        string res = to_string(real) + "+" + to_string(imag) + "i";
        return res;
        
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
540. Single Element in a Sorted Array
Given a sorted array consisting of only integers where every element appears twice 
except for one element which appears once. Find this single element that appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if((mid % 2 == 0 && nums[mid] == nums[mid+1]) || 
               (mid % 2 == 1 && nums[mid] == nums[mid-1])
              ) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return nums[low];
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