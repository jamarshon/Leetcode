
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
665. Non-decreasing Array
Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].
/*
    Submission Date: 2018-06-09
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    for the first number where nums[i] < nums[i-1] where nums[i] = c
    a b c d
    
    then a <= b and c < b.
    the condition must hold c <= d as if c < d then it will be a a c (c-x) 
    or 10 10 7 6 where c has to be fixed and d as well
    
    if problem_ind == -1 means the array is already sorted in increasing order
    if it is 1 then just update nums[0] to equal nums[1]
    
    if a <= c then it is true as well as a <= b, a <= c and c <= d (from before)
    so a <= b <= c <= d
    
    if d does not exist or b <= d as a <= b and b <= d so replace c with any number 
    between [b,d] to get a b b d
    */
    bool checkPossibility(vector<int>& nums) {
        int problem_ind = -1;
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] < nums[i-1]) {
                if(problem_ind != -1) return false;
                problem_ind = i;
            }
        }
        
        return problem_ind < 2 || 
            nums[problem_ind-2] <= nums[problem_ind] || 
            (problem_ind + 1 == nums.size() || nums[problem_ind-1] <= nums[problem_ind+1]);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
667. Beautiful Arrangement II
Given two integers n and k, you need to construct a list which contains n 
different positive integers ranging from 1 to n and obeys the following 

Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - 



If there are multiple answers, print any of them.


Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 



Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 



Note:

The n and k are in the range 1 <= k < n <= 104.
/*
    Submission Date: 2018-07-02
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    place elements [1, n-k] in array then keep adding to the back numbers from
    [k, 1] alterating the sign (+, -) starting with +
    */
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        res.reserve(n);
        for(int i = 1; i + k <= n; i++) res.push_back(i);
        for(int i = 0; i < k; i++) {
            res.push_back(res.back() + (i % 2 == 0 ? 1 : -1)*(k - i));
        }
        
        return res;
    }
};

class Solution2 {
public:
    /*
    have two pointers i and j where i starts at 1 and j starts at n
    interweave i and j for the first k elements then just keep increasing i until reaches j
    e.g
    n = 5, k = 3
    
    weaves 3 2 1
    res    1 5 2 3 4 
    diff    4 3 1 1
    */
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        res.reserve(n);
        int j = n;
        for(int i = 1; i <= j;) {
            if(k > 1) {
                res.push_back(k-- % 2 ? i++ : j--);
            } else {
                res.push_back(i++);
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
677. Map Sum Pairs
Implement a MapSum class with insert, and sum methods.



For the method insert, you'll be given a pair of (string, integer). The string 
represents the key and the integer represents the value. If the key already 



For the method sum, you'll be given a string representing the prefix, and you 


Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
/*
    Submission Date: 2018-07-02
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

struct TrieNode {
    int sum;
    TrieNode* children[26];
    TrieNode() {
        sum = 0;
        for(int i = 0; i < 26; i++) children[i] = NULL;
    }
};

class MapSum {
    unordered_map<string, int> m;
    TrieNode* root;
public:
    /** Have a trie and unordered_map. the unordered_map keeps track of key and val
     the trie can find prefix easily. each node has sum which is the sum of all...l with each node visited getting the to_add
     added to their sum.
    */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        int to_add = m.count(key) ? val - m[key] : val;
        m[key] = val;
        TrieNode* curr = root;
        curr->sum += to_add;
        
        for(const auto& c: key) {
            if(curr->children[c - 'a'] == NULL) 
                curr->children[c - 'a'] = new TrieNode();
            curr = curr->children[c - 'a'];
            curr->sum += to_add;
        }
    }
    
    int sum(string prefix) {
        TrieNode* curr = root;
        for(const auto& c: prefix) {
            if(curr->children[c - 'a'] == NULL) return 0;
            curr = curr->children[c - 'a'];
        }
        
        return curr->sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
680. Valid Palindrome II
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
/*
    Submission Date: 2018-06-24
    Runtime: 129 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
public:
    /*
    dp[i][j] represents number of deletes to make a palindrome for string [i, j]
    */
    bool validPalindrome(string s) {
        int N = s.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        for(int gap = 1; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                dp[i][j] = s[i] == s[j] ? dp[i+1][j-1] : 1 + min(dp[i+1][j], dp[i][j-1]);
            }
        }
        
        return dp[0][N-1] <= 1;
    }
};

class Solution {
public:
    bool IsPalindrome(const string& s, int l, int r) {
        while(l < r) {
            if(s[l] == s[r]) {
                l++;
                r--;
            } else {
                return false;
            }
        }
        return true;
    }
    
    /*
    loop l and r until they do not match then check either if skipping l IsPalindrome(s, l+1, r)
    or skipping r IsPalindrome(s, l, r-1) will result in a palindrome
    */
    bool validPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;
        while(l < r) {
            if(s[l] == s[r]) {
                l++;
                r--;
            } else {
                return IsPalindrome(s, l+1, r) || IsPalindrome(s, l, r-1);
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
686. Repeated String Match
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.
/*
    Submission Date: 2018-06-24
    Runtime: 716 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
    if A is already in B, return 1
    else it is a suffix of A + A repeated n times + prefix of A
    so return n + 2
    for all suffix of A, check if it is a prefix of B. if it is then see how many times A repeats
    if it does repeat n times and the prefix of A is a suffix of B, then the answer is just n + 2.
    */
    int repeatedStringMatch(string A, string B) {
        if(A.find(B) != string::npos) return 1;
        for(int i = 0; i < A.size(); i++) {
            bool got_suffix = true;
            for(int j = 0; j < A.size() - i; j++) {
                if(B[j] != A[i+j]) {
                    got_suffix = false;
                    break;
                }
            }
            
            if(!got_suffix) continue;
            int res = 1;
            int A_ind = 0;
            for(int j = A.size() - i; j < B.size(); j++) {
                if(A_ind == 0) res++;
                
                if(B[j] != A[A_ind]) {
                    res = -1;
                    break;
                }
                
                A_ind = (A_ind + 1) % A.size();
            }
            
            if(res == -1) continue;
            return res;
        }
        
        return -1;
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