
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
543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary 
tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
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
    returns the height of a node so height(root) = 1 + max(height(left), height(right))
    res can be updated to 2 + height(left) + height(right) as the longest path in the left
    and right go through this node.
    */
    int help(TreeNode* root, int& res) {
        if(root == NULL) return -1;
        int left = help(root->left, res);
        int right = help(root->right, res);
        res = max(res, 2 + left + right);
        return 1 + max(left, right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        help(root, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
551. Student Attendance Record I
You are given a string representing an attendance record for a student. The record only contains the following three characters:
'A' : Absent.
'L' : Late.
'P' : Present.
A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False
/*
    Submission Date: 2018-06-08
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool checkRecord(string s) {
        int l_streak = 0;
        bool seen_absent = false;
        for(const auto& c: s) {
            if(c == 'L') {
                if(l_streak == 2) return false;
                l_streak++;
            } else {
                if(c == 'A') {
                    if(seen_absent) return false;
                    seen_absent = true;
                } // c == 'P'
                
                l_streak = 0;
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
561. Array Partition I
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) 
which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
/*
    Submission Date: 2018-05-31
    Runtime: 85 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     for a pair ai and bi where bi is not used, it means bi should be the smallest element > ai
     in order to maximize the rest of the result
    */
    int arrayPairSum(vector<int>& nums) {
        int res = 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i+= 2) res += nums[i];
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
563. Binary Tree Tilt
Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and 
the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
/*
    Submission Date: 2018-06-08
    Runtime: 16 ms
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
    returns the sum of subtree with node as root
    */
    int help(TreeNode* node, int& res) {
        if(node == NULL) return 0;
        int left = help(node->left, res);
        int right = help(node->right, res);
        res += abs(left - right);
        return node->val + left + right;
    }
    
    int findTilt(TreeNode* root) {
        int res = 0;
        help(root, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
565. Array Nesting
A zero-indexed array A consisting of N different integers is given. The array contains 
all integers in the range [0, N - 1].

Sets S[K] for 0 <= K < N are defined as follows:

S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.

Sets S[K] are finite for each K and should NOT contain duplicates.

Write a function that given an array A consisting of N integers, return the size of 
the largest set S[K] for this array.

Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
Note:
N is an integer within the range [1, 20,000].
The elements of A are all distinct.
Each element of array A is an integer within the range [0, N-1].
/*
    Submission Date: 2017-05-29
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int N = nums.size();
        vector<bool> mask(N, true);
        int max_set = 0;
        for(int i = 0; i < N; i++) {
            if(mask[i]) { // hasn't been processed
                int current = i;
                int current_set = 0;
                while(true) {
                    if(current >= N || !mask[current]) break;
                    mask[current] = false;
                    current = nums[current];
                    current_set++;
                }
                max_set = max(current_set, max_set);
            }
        }
        return max_set;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
566. Reshape the Matrix
In MATLAB, there is a very useful function called 'reshape', which can reshape a matrix into a new one with different size but keep its original data.

You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of 
the wanted reshaped matrix, respectively.

The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

Example 1:
Input: 
nums = 
[[1,2],
 [3,4]]
r = 1, c = 4
Output: 
[[1,2,3,4]]
Explanation:
The row-traversing of nums is [1,2,3,4]. The new reshaped matrix is a 1 * 4 matrix, fill it row by row by using the previous list.
Example 2:
Input: 
nums = 
[[1,2],
 [3,4]]
r = 2, c = 4
Output: 
[[1,2],
 [3,4]]
Explanation:
There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix. So output the original matrix.
Note:
The height and width of the given matrix is in range [1, 100].
The given r and c are all positive.
/*
    Submission Date: 2018-05-31
    Runtime: 39 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if(nums.empty()) return {};
        int N = nums.size();
        int M = nums[0].size();
        
        // cannot gain or lose elements
        if(N*M != r*c) return nums;
        
        vector<vector<int>> res(r, vector<int>(c));
        int x = 0;
        int y = 0;
        
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                res[i][j] = nums[y][x];
                x++;
                if(x == M) {
                    x = 0;
                    y++;
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
567. Permutation in String
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, 
one of the first string's permutations is the substring of the second string.
Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
/*
    Submission Date: 2018-06-02
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    /*
    frequency map of s1 with variable to_use as global to check if everything equals 0
    use sliding window where everything in a window is a valid character and does not 
    exceed the frequency map limit for certain character
    for a new character, if it exceeds the limit or its not a valid character than keep
    moving front (restoring freq map). if it is not a valid character, the map will be
    restored and to_do = original
    Check if character is valid, if it is use it else move front so that it is not
    included
    */
    bool checkInclusion(string s1, string s2) {
        vector<int> freq(26 , 0);
        unordered_set<char> letters(s1.begin(), s1.end());
        for(const auto& c: s1) freq[c - 'a']++;
        
        int front = 0;
        int back = 0;
        
        int N = s2.size();
        int to_use = s1.size();
        
        while(back < N) {
            if(to_use == 0) return true;
            // slide the front until the letter is removed
            int back_val = s2[back] - 'a';
            while(front < back && freq[back_val] == 0) {
                freq[s2[front] - 'a']++;
                front++;
                to_use++;
            }
            
            /* if the back letter is in s1, decrease the frequency and to_use
                else it means front == back as freq[s2[back]] == 0 so increase front 
                to not include this letter
            */
            if(letters.count(s2[back])) {
                freq[back_val]--;
                to_use--;
            } else {
                front++;
            }
            
            back++;
        }
        
        return to_use == 0;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
575. Distribute Candies
Given an integer array with even length, where different numbers in this array represent different kinds of candies. 
Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and 
sister. Return the maximum number of kinds of candies the sister could gain.
Example 1:
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 
Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1]. 
The sister has two different kinds of candies, the brother has only one kind of candies. 
Note:

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].
/*
    Submission Date: 2018-05-31
    Runtime: 247 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // Count the number of distinct candies. Return the min of this and the max size of the array which is candies.size()/2.
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> st(candies.begin(), candies.end());
        return min(candies.size()/2, st.size());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this 
subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array 
sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

/*
    Submission Date: 2017-05-13
    Runtime: 52 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
            int N = nums.size();
            vector<int> cpy(N);
            copy(nums.begin(), nums.end(), cpy.begin());
            sort(nums.begin(), nums.end());

            int i;
            for(i = 0; i < N; i++) {
                if(nums[i] != cpy[i]) break;
            }

            int j;
            for(j = N-1; j >= 0; j--) {
                if(nums[j] != cpy[j]) break;
            }

        return max(j - i + 1, 0);
    }
};

int main() {
    Solution s;
    vector<int> v{2, 6, 4, 8, 10, 9, 15};
    cout << s.findUnsortedSubarray(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
582. Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This 
is just like a tree structure. Only one process has PPID that is 0, which means this process 
has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains 
PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list 
of PIDs of processes that will be killed in the end. You should assume that when a process 
is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.
/*
    Submission Date: 2017-05-13
    Runtime: 166 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        int N = pid.size();
        for(int i = 0; i < N; i++) {
            int _ppid = ppid[i];
            int _pid = pid[i];

            if(m.find(_ppid) == m.end()) {
                m[_ppid] = {_pid};
            } else {
                m[_ppid].push_back(_pid);
            }
        }

        vector<int> result{kill};
        int i = 0;
        while(i < result.size()) {
            int current = result[i];
            if(m.find(current) != m.end()) { // non leaf
                vector<int> children = m[current];
                for(auto c: children) {
                    result.push_back(c);
                }
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution s;
    vector<int> pid{1, 3, 10, 5, 4, 1};
	vector<int> ppid{3, 0, 5, 3, 10, 5};
    int kill = 5;
    vector<int> t = s.killProcess(pid, ppid, kill);
	for(auto l: t) cout << l << " ";
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
583. Delete Operation for Two Strings
Given two words word1 and word2, find the minimum number of steps required to 
make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

/*
    Submission Date: 2017-05-13
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int row = word2.size() + 1;
        int col = word1.size() + 1;
        int dp[501][501];
        for(int i = 0; i < row; i++) dp[i][0] = i;
        for(int i = 0; i < col; i++) dp[0][i] = i;

        for(int i = 1; i < row; i++) {
            for(int j = 1; j < col; j++) {
                if(word2[i - 1] == word1[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + 1;
                }
            }
        }
        
        return dp[row - 1][col - 1];
    }
};

int main() {
	Solution s;
    cout << s.minDistance("sea", "eat");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
592. Fraction Addition and Subtraction
Given a string representing an expression of fraction addition 
and subtraction, you need to return the calculation result in string 
format. The final result should be irreducible fraction. If your final 
result is an integer, say 2, you need to change it to the format of 
fraction that has denominator 1. So in this case, 2 should be 
converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'. 
So does the output.
Each fraction (input and output) has format ±numerator/denominator. 
If the first input fraction or the output is positive, then '+' will 
be omitted.
The input only contains valid irreducible fractions, where the 
numerator and denominator of each fraction will always be in the 
range [1,10]. If the denominator is 1, it means this fraction is 
actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed 
to be valid and in the range of 32-bit int.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <cassert>

using namespace std;

typedef long long ll;
struct Fraction {
    ll num, den;
};

class Solution {
public:
    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    ll lcm(ll a, ll b) {
        return a*b/gcd(a,b);
    }

    // a/b + c/d = (a*lcm(b,d)/b + c*lcm(b,d)/d)/lcm(b,d)
    // 1/4 + 1/16 = (1*16/4 + 1*16/16)/16 = (4+1)/16
    // 1/3 + 2/4 = (1*12/3 + 2*12/4)/12 = (4+6)/12

    // (a*(b*d/gcd(b,d))/b + c*(b*d/gcd(b,d))/d)/(b*d/gcd(b,d))
    // (a*d/gcd(b,d) + c*b/gcd(b,d))/(b*d/gcd(b,d))
    // ((a*d + c*b)/gcd(b,d)*gcd(b,d))/(b*d)
    // (a*d + b*c)/(b*d)
    Fraction add(Fraction a, Fraction b) {
        return {a.num*b.den + a.den*b.num, a.den*b.den};
    }

    Fraction reduce(Fraction a) {
        int gcd_num_den = gcd(abs(a.num), a.den);
        return {a.num/gcd_num_den, a.den/gcd_num_den};
    }

    string fractionAddition(string s) {
        vector<Fraction> v;
        int N = s.size();
        bool is_negative = false;
        for(int i = 0; i < N;) {
            // s[i] is beginning of numerator which is either '-' (negative num), '+' (positive num) or
            // a number (positive num and is start of string)
            Fraction fr;
            is_negative = s[i] == '-';

            if(s[i] == '+' || is_negative) {
                i++;
            }

            ll curr = 0;
            while(isdigit(s[i])) {
                curr = curr*10 + (s[i] - '0');
                i++;
            }

            fr.num = is_negative ? -curr : curr;
            // s[i] is the '/' followed by a number so end i where the next operator starts
            assert(s[i++] == '/');

            curr = 0;
            while(isdigit(s[i]) && i < N) {
                curr = curr*10 + (s[i] - '0');
                i++;
            }

            fr.den = curr;
            v.push_back(fr);
        }

        Fraction res = v.front();
        res = reduce(res);
        for(int i = 1; i < v.size(); i++) {
            res = add(res, v[i]);
            res = reduce(res);
        }

        return to_string(res.num) + "/" + to_string(res.den);
    }
};

int main() {
    Solution s;
    return 0;
}