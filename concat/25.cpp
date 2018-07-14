
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
547. Friend Circles
There are N students in a class. Some of them are friends, while some are not. 
Their friendship is transitive in nature. For example, if A is a direct friend 
of B, and B is a direct friend of C, then A is an indirect friend of C. And we 
defined a friend circle is a group of students who are direct or indirect 



Given a N*N matrix M representing the friend relationship between students in 
the class. If M[i][j] = 1, then the ith and jth students are direct friends with 
each other, otherwise not. And you have to output the total number of friend 


Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend 



Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd 
students are direct friends, so the 0th and 2nd students are indirect friends. 




Note:

N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.
/*
    Submission Date: 2018-07-05
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <cassert>

using namespace std;

template <typename T>
class UnionFind {
    // key is element, value is rank
    unordered_map<T, int> rank_;
    // key is element, value is parent
    unordered_map<T, T> parent_;
public:
    bool IsWithinSet(T e) {
        return parent_.count(e);
    }
 
    void CreateSet(T e) {
        assert(!IsWithinSet(e));
        parent_[e] = e;
        rank_[e] = 0;
    }
 
    // finds the root of e
    T Find(T e) {
        if(parent_[e] != e) {
            // this is not a root (root has parent to be equal itself)
            // so find root and apply path compression along path
            parent_[e] = Find(parent_[e]);
        }
        return parent_[e];
    }
 
    // unions the sets of e1 and e2 if necessary
    // return whether an union took place
    bool Union(T e1, T e2) {
        T e1_root = Find(e1);
        T e2_root = Find(e2);
 
        if(e1_root == e2_root) return false; // same root
 
        // Attach smaller rank tree under root of high rank tree
        // (Union by Rank)
        if(rank_[e1_root] < rank_[e2_root]) {
            parent_[e1_root] = e2_root;
        } else {
            parent_[e2_root] = e1_root;
            if(rank_[e1_root] == rank_[e2_root]) {
                rank_[e1_root]++;
            }
        }
 
        return true;
    }
};

class Solution {
public:
    /*
    basically find how many connected graphs there are
    so use union-find, for every edge from u to v, merge the sets u and v
    at the end find how many sets there are by finding the root of all
    the nodes and counting the distinct ones.
    
    O(N^2) as Union and Find are O(1)
    */
    int findCircleNum(vector<vector<int>>& M) {
        int N = M.size();
        UnionFind<int> uf;
        for(int i = 0; i < N; i++) uf.CreateSet(i);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(M[i][j] == 0) continue;
                uf.Union(i, j);
            }
        }
        
        unordered_set<int> roots;
        for(int i = 0; i < N; i++) roots.insert(uf.Find(i));
        return roots.size();
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
553. Optimal Division
Given a list of positive integers, the adjacent integers will perform the float division. 
For example, [2,3,4] -> 2 / 3 / 4.

However, you can add any number of parenthesis at any position to change the priority of operations. 
You should find out how to add parenthesis to get the maximum result, and return the corresponding expression 
in string format. Your expression should NOT contain redundant parenthesis.

Example:
Input: [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant, 
since they don't influence the operation priority. So you should return "1000/(100/10/2)". 

Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2
Note:

The length of the input array is [1, 10].
Elements in the given array will be in range [2, 1000].
There is only one optimal division for each test case.
/*
    Submission Date: 2018-06-30
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    o(n) for a series of number dp_max[i] = nums[i]/dp_min[i+1]
    the minimum would be just divide all the numbers from [1,N)
    as they are all integers meaning its some number divide by all integers 
    in the denominator which would be the smallest. if nums[i] had
    decimals than the smallest would not be dividing all the numbers as it could
    be equivalent to putting a integer number in the numerator
    
    so return nums[0] / (nums[1]/nums[2]/ .... /nums[N-1])
    */
    string optimalDivision(vector<int>& nums) {
        int N = nums.size();
        string res = to_string(nums[0]);
        if(N == 1) return res;
        if(N == 2) return res + "/" + to_string(nums[1]);
        
        res += "/(";
        for(int i = 1; i < N; i++) {
            res += to_string(nums[i]) + (i == N-1 ? ")" : "/");
        }
        
        return res;
    }
    
    /*
    o(n^2) dp where dp_max[i] is the largest number created from [i, N) and dp_min[i] is the smallest
    then dp_max[i] is max(product of numbers between [i, j) /dp_min[j]) for j > i 
    and dp_min[i] is min(product of numbers between [i, j) /dp_max[j]) for j > i 
    
    strings in dp_max and dp_min are surrounded by parenthesis while product of numbers aren't
    
    return dp_max[0]
    */
    string optimalDivision2(vector<int>& nums) {
        int N = nums.size();
        vector<pair<string, double>> dp_max(N, {"", INT_MIN}), dp_min(N, {"", INT_MAX});
        dp_max[N-1] = {to_string(nums[N-1]), nums[N-1]};
        dp_min[N-1] = dp_max[N-1];
        
        if(N == 1) return dp_max[0].first;
        
        for(int i = N-2; i >= 0; i--) {
            string curr_s = to_string(nums[i]);
            double curr = nums[i];
            for(int j = i + 1; j < N; j++) {
                if(dp_max[i].second < curr/dp_min[j].second) {
                    dp_max[i] = {
                        "(" + curr_s + "/" + dp_min[j].first + ")",
                        curr/dp_min[j].second
                    };
                }
                
                if(dp_min[i].second > curr/dp_max[j].second) {
                    dp_min[i] = {
                        "(" + curr_s + "/" + dp_max[j].first + ")",
                        curr/dp_max[j].second
                    };
                }
                
                curr /= nums[j];
                curr_s += "/" + to_string(nums[j]);
            }
        }
        
        return dp_max[0].first.substr(1, dp_max[0].first.size() - 2);
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