
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
661. Image Smoother
Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to make the gray 
scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself. If a cell has 
less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
Note:
The value in the given matrix is in the range of [0, 255].
The length and width of the given matrix are in the range of [1, 150].
/*
    Submission Date: 2018-06-08
    Runtime: 178 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int help(const vector<vector<int>>& A, int i, int j, int N, int M) {
        int sum = 0;
        int points = 0;
        for(int k = -1; k <= 1; k++) {
            for(int l = -1; l <= 1; l++) {
                int new_i = i + k;
                int new_j = j + l;
                if(0 <= new_i && new_i < N && 0 <= new_j && new_j < M) {
                    points++;
                    sum += A[new_i][new_j];
                }
            }
        }
        
        return sum/points;
    }
    
    vector<vector<int>> imageSmoother(vector<vector<int>>& A) {
        if(A.empty()) return A;
        int N = A.size();
        int M = A[0].size();
        
        vector<vector<int>> res(N, vector<int>(M));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                res[i][j] = help(A, i, j, N, M);
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
662. Maximum Width of Binary Tree
Given a binary tree, write a function to get the maximum width of the 
given tree. The width of a tree is the maximum width among all levels. 
The binary tree has the same structure as a full binary tree, but some 
nodes are null.

The width of one level is defined as the length between the end-nodes 
(the leftmost and right most non-null nodes in the level, where the null 
nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the 
length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the 
length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the 
length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the 
length 8 (6,null,null,null,null,null,null,7).


Note: Answer will in the range of 32-bit signed integer.
/*
    Submission Date: 2017-08-21
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode*,int>> q;
        q.emplace(root, 0);
        
        int res = 0;
        
        TreeNode* front;
        int index;
        
        while(!q.empty()) {
            int q_size = q.size();
            int first_non_null = -1;
            for(int i = 0; i < q_size; i++) {
                tie(front, index) = q.front();
                q.pop();
                if(front) {
                    q.emplace(front -> left, index*2);
                    q.emplace(front -> right, index*2 + 1);
                    if(first_non_null == -1) first_non_null = index;
                    res = max(res, index - first_non_null + 1);
                }
            }
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
669. Trim a Binary Search Tree
Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in 
[L, R] (R >= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1
/*
    Submission Date: 2018-05-31
    Runtime: 18 ms
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
    if node val is within bounds, than return node with left and right subtrees trimmed
    if node val is > R that means all the element in the right subtree will also be bigger so return the trimmed left subtree
    if node val is < L that means all the element in the left subtree will also be smaller so return the trimmed right subtree
    */
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(root == NULL) return NULL;
        if(root->val > R) {
            return trimBST(root->left, L, R);
        } else if(root-> val < L) {
            return trimBST(root->right, L, R);
        } else {
            root->left = trimBST(root->left, L, R);
            root->right = trimBST(root->right, L, R);
            return root;
        }
    }
};
int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
671. Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in 
this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input: 
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input: 
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
/*
    Submission Date: 2018-06-08
    Runtime: 3 ms
    Difficulty: EASY
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
    /*
    bfs that once reaches a different node->val than root->val will stop putting that node's
    children. result is the minimum of all these first encountered different node-> val
    */
    int findSecondMinimumValue(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int res = INT_MAX;
        bool seen_others = false;
        
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if(node->val == root->val) {
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            } else {
                // found node that does not equal root->val, no need to go deeper as they will be >= node->val
                res = min(res, node->val);
                seen_others = true;
            }
        }
        
        return seen_others ? res : -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
674. Longest Continuous Increasing Subsequence
Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

Example 1:
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 
Example 2:
Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
Note: Length of the array will not exceed 10,000.
/*
    Submission Date: 2018-06-08
    Runtime: 14 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int res = 1;
        int pos_res = 1;
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] > nums[i-1]) {
                pos_res++;
            } else {
                pos_res = 1;
            }
            res = max(res, pos_res);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
676. Implement Magic Dictionary

Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify exactly one character into another 
character in this word, the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted 
across multiple test cases. Please see here for more details.
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class MagicDictionary {
public:
    /** Initialize your data structure here. */
    unordered_map<string, vector<pair<char, int>>> m_;
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        /*
            N words of size K O(Nk^2)
            hello -> [ello, [h, 0]], [hllo, [e, 1]], [helo, l, 2]], [helo, [l, 3]], [hell, [o, 4]]
        */
        m_.clear();
        for(const auto& s: dict) {
            for(int i = 0; i < s.size(); i++) {
                m_[s.substr(0, i) + s.substr(i+1)].emplace_back(s[i], i);
            }
        }
        
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string s) {
        // O(k^2*M) where M is size of vector for a key in m_
        for(int i = 0; i < s.size(); i++) {
            const auto& key = s.substr(0,i) + s.substr(i+1);
            if(!m_.count(key)) continue;
            for(const auto& p: m_[key]) {
                // looking for same index different letter
                if(p.second == i && p.first != s[i]) return true;
            }
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
682. Baseball Game
You're now a baseball game point recorder.

Given a list of strings, each string can be one of the 4 following types:

Integer (one round's score): Directly represents the number of points you get in this round.
"+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
"D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
"C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
Each round's operation is permanent and could have an impact on the round before and the round after.

You need to return the sum of the points you could get in all the rounds.

Example 1:
Input: ["5","2","C","D","+"]
Output: 30
Explanation: 
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get 2 points. The sum is: 7.
Operation 1: The round 2's data was invalid. The sum is: 5.  
Round 3: You could get 10 points (the round 2's data has been removed). The sum is: 15.
Round 4: You could get 5 + 10 = 15 points. The sum is: 30.
Example 2:
Input: ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation: 
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get -2 points. The sum is: 3.
Round 3: You could get 4 points. The sum is: 7.
Operation 1: The round 3's data is invalid. The sum is: 3.  
Round 4: You could get -4 points (the round 3's data has been removed). The sum is: -1.
Round 5: You could get 9 points. The sum is: 8.
Round 6: You could get -4 + 9 = 5 points. The sum is 13.
Round 7: You could get 9 + 5 = 14 points. The sum is 27.
Note:
The size of the input list will be between 1 and 1000.
Every integer represented in the list will be between -30000 and 30000.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    /*
    let stk be all the valid round points. if it is a number just add it as a round and increment res by the amount
    if it is a "+", take the last two rounds add add them up. put the sum as a round and increment res by the amount
    if it is a "D", take the last round, multiply it by two and add it as a around and increment res by the amount
    if it is a "C", take the last round and decrease res by the amount as well as pop that round off.
    */
    int calPoints(vector<string>& ops) {
        int res = 0; 
        vector<int> stk;
        for(const auto& s: ops) {
            int stk_size = stk.size();
            if(s == "+") {
                assert(stk_size >= 2);
                stk.push_back(stk[stk_size-1] + stk[stk_size-2]);
                res += stk.back();
            } else if(s == "D") {
                assert(stk_size >= 1);
                stk.push_back(stk[stk_size-1] * 2);
                res += stk.back();
            } else if(s == "C") {
                res -= stk.back();
                stk.pop_back();
            } else { // a number
                stk.push_back(stoi(s));
                res += stk.back();
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
687. Longest Univalue Path
Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
/*
    Submission Date: 2018-05-24
    Runtime: 112 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

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
        N by returning the longest path that starts from this node where a path is straight down where all
        the nodes have the same value. This is 1 + max(f(left), f(right)) if left and right have the same
        value as this node.
        Variable that is passed by reference is the result where it can be 1 + f(left) + f(right) if left
        and right have the same value as this node as it means there is a path for the left and a path for
        the right which creates a upside down v shape.
    */
    int solve(TreeNode* root, int& res) {
        if(!root) return 0;
        vector<int> longest_path_starting_at_child{solve(root->left, res), solve(root->right, res)};
        int pos_res = 1;
        int longest_path_starting_at_node = 0;
        
        if(root->left && root->left->val == root->val) {
            pos_res += longest_path_starting_at_child[0];
            longest_path_starting_at_node = longest_path_starting_at_child[0];
        }
        if(root->right && root->right->val == root->val) {
            pos_res += longest_path_starting_at_child[1];
            longest_path_starting_at_node = max(longest_path_starting_at_node, longest_path_starting_at_child[1]);
        }

        res = max(res, pos_res);
        return 1 + longest_path_starting_at_node;
    }

    int longestUnivaluePath(TreeNode* root) {
        int res = 1;
        solve(root, res);
        return res - 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
690. Employee Importance
You are given a data structure of employee information, which includes the employee's unique id, 
his importance value and his direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. They have 
importance value 15, 10 and 5, respectively. Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has 
[2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, you need to return the total importance value of this 
employee and all his subordinates.

Example 1:
Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee 2 and employee 3. They both have importance value 3. 
So the total importance value of employee 1 is 5 + 3 + 3 = 11.
Note:
One employee has at most one direct leader and may have several subordinates.
The maximum number of employees won't exceed 2000.
/*
    Submission Date: 2018-06-04
    Runtime: 135 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};

class Solution {
public:
    int dfs(int id, unordered_map<int, int> id_to_ind, const vector<Employee*>& employees) {
        int res = employees[id_to_ind[id]]->importance;
        for(const auto& e: employees[id_to_ind[id]]->subordinates) 
            res += dfs(e, id_to_ind, employees);
        return res;
    }

    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, int> id_to_ind;
        for(int i = 0; i < employees.size(); i++) id_to_ind[employees[i]->id] = i;
        
        return dfs(id, id_to_ind, employees);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
692. Top K Frequent Words
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word 
with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.
/*
    Submission Date: 2018-05-24
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string,int> freq_map;
        for(auto e: words) freq_map[e]++;
        
        map<int, vector<string>> grouped_map;
        for(auto kv: freq_map) grouped_map[kv.second].push_back(kv.first);
        
        vector<string> res;
        for(auto it = grouped_map.rbegin(); it != grouped_map.rend(); it++) {
            sort(it->second.begin(), it->second.end());
            for(auto e: it->second) {
                res.push_back(e);
                if(res.size() == k) break;
            }
            if(res.size() == k) break;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
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