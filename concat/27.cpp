
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
656. Coin Path
Given an array A (index starts at 1) consisting of N integers: A1, A2, ..., AN 
and an integer B. The integer B denotes that from any place (suppose the index is i) 
in the array A, you can jump to any one of the place in the array A indexed i+1, i+2, …, 
i+B if this place can be jumped to. Also, if you step on the index i, you have to pay Ai 
coins. If Ai is -1, it means you can’t jump to the place indexed i in the array.

Now, you start from the place indexed 1 in the array A, and your aim is to reach the place 
indexed N using the minimum coins. You need to return the path of indexes (starting from 1 to N) 
in the array you should take to get to the place indexed N using minimum coins.

If there are multiple paths with the same cost, return the lexicographically smallest such path.

If it's not possible to reach the place indexed N then you need to return an empty array.

Example 1:
Input: [1,2,4,-1,2], 2
Output: [1,3,5]
Example 2:
Input: [1,2,4,-1,2], 1
Output: []
Note:
Path Pa1, Pa2, ..., Pan is lexicographically smaller than Pb1, Pb2, ..., Pbm, if and only if at 
the first i where Pai and Pbi differ, Pai < Pbi; when no such i exists, then n < m.
A1 >= 0. A2, ..., AN (if exist) will in the range of [-1, 100].
Length of A is in the range of [1, 1000].
B is in the range of [1, 100].

/*
    Submission Date: 2017-08-06
    Runtime: 12 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

struct Compare {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const {
        return (lhs.first == rhs.first) ? (lhs.second < rhs.second) : (lhs.first < rhs.first);
    }
};

class Solution2 {
public:
    vector<vector<int>> createPath(int curr, unordered_map<int, vector<int>>& parent) {
        if(curr == 0) return {{}};

        vector<vector<int>> res;
        for(auto prev: parent[curr]) {
            vector<vector<int>> path = createPath(prev, parent);
            for(auto p: path) {
                p.push_back(curr);
                res.push_back(p);
            }
        }

        return res;
    }
    vector<int> cheapestJump(vector<int>& A, int B) {
        int N = A.size();
        
        // id is index, pair weight, to
        vector<vector<pair<int, int>>> graph(N + 1);
        
        graph[0] = {{A[0], 1}};
        for(int i = 0; i < N; i++) {
            if(A[i] == -1) continue;
            for(int j = 1; j <= B; j++) {
                if(i + j >= N) break;
                if(A[i + j] == -1) continue;
                // connect vertex i with vertex i + j by weight A[i + j]
                graph[i + 1].emplace_back(A[i + j], i + 1 + j);
            }
        }
        
        unordered_map<int, vector<int>> parent;
        set<pair<int, int>, Compare> edges_to_process;
        unordered_map<int, int> min_distance;
        
        for(int i = 1; i <= N; i++) {
            edges_to_process.emplace(INT_MAX, i);
            min_distance[i] = INT_MAX;
        }
        
        edges_to_process.emplace(0, 0);
        min_distance[0] = 0;
        parent[0] = {0};

        while(!edges_to_process.empty()) {
            // Minimum weight edge
            pair<int,int> min_edge = *edges_to_process.begin();
            edges_to_process.erase(edges_to_process.begin());

            int current_vertex = min_edge.second;
            int current_weight = min_edge.first;

            if(current_weight == INT_MAX) break;

            vector<pair<int,int>> neighbors = graph[current_vertex];
            for(pair<int,int> neighbor: neighbors) {
                auto edge_set_it = edges_to_process.find({min_distance[neighbor.second], neighbor.second});
                // done processing already
                if(edge_set_it == edges_to_process.end()) continue;

                // found a smaller distance
                if(current_weight + neighbor.first <= min_distance[neighbor.second]) {
                    if(current_weight + neighbor.first == min_distance[neighbor.second]) {
                        parent[neighbor.second].push_back(current_vertex);
                    } else {
                        min_distance[neighbor.second] = current_weight + neighbor.first;
                        parent[neighbor.second].push_back(current_vertex);
                        edges_to_process.erase(edge_set_it);
                        edges_to_process.emplace(min_distance[neighbor.second], neighbor.second);
                    }
                }
            }
        }
            
        if(min_distance[N] == INT_MAX) return {};

        vector<vector<int>> v = createPath(N, parent);
        return *min_element(v.begin(), v.end(), [](const vector<int>& lhs, const vector<int>& rhs){
            int M = lhs.size();
            int N = rhs.size();
            for(int i = 0; i < min(M,N); i++) {
                if(lhs[i] != rhs[i]) return lhs[i] < rhs[i];
            }
            return M < N;
        });
    }
};

class Solution {
public:
    vector<int> cheapestJump(vector<int>& A, int B) {
        int N = A.size();
        if(N == 0 || A[N-1] == -1) return {};
        // dp[i] represents cost of i to N-1
        vector<int> dp(N, INT_MAX), to(N, -1);
        
        dp[N-1] = A[N-1];
        for(int i = N-2; i >= 0; i--) {
            if(A[i] == -1) continue;
            // if we try smaller jumps first, don't need to worry about lexicographical order
            // [P0, P1, P2, ... i+j] choosing smallest j minimizes i + j
            // Clearly, when k = n-1, it is true because there is only 1 possible path, which is [n]. 
            // When k = i and i < n-1, we search for an index j, which has smallest cost or 
            // smallest j if the same cost. If there are >= 2 paths having the same minimum cost, 
            // for example,
            // P = [k+1, j+1, ..., n]
            // Q = [k+1, m+1, ..., n] (m > j)
            // The path P with smaller index j is always the lexicographically smaller path.
            // So the argument is true by induction.
            for(int j = 1; j <= B && i + j < N; j++) { 
                if(dp[i + j] == INT_MAX) continue;
                // cost of taking this jump is smaller
                if(A[i] + dp[i + j] < dp[i]) {
                    dp[i] = A[i] + dp[i + j];
                    to[i] = i + j;
                }
            }
        }
        
        vector<int> res;
        if(dp[0] == INT_MAX) return res; // no path to the end

        for(int i = 0; i >= 0; i = to[i])
            res.push_back(i + 1);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{1,2,4,-1,2};
    s.cheapestJump(v, 2);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
657. Judge Route Circle
Initially, there is a Robot at position (0, 0). Given a sequence of its moves, judge if this robot makes 
a circle, which means it moves back to the original place.

The move sequence is represented by a string. And each move is represent by a character. The valid robot moves are 
R (Right), L (Left), U (Up) and D (down). The output should be true or false representing whether the robot makes a circle.

Example 1:
Input: "UD"
Output: true
Example 2:
Input: "LL"
Output: false
/*
    Submission Date: 2018-05-31
    Runtime: 43 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    unordered_map<char, vector<int>> m_{
        {'U', {0,1}},
        {'D', {0,-1}},
        {'L', {-1,0}},
        {'R', {1,0}},
    };
public:
    bool judgeCircle(string moves) {
        int x = 0;
        int y = 0;
        for(const auto& c: moves) {
            x += m_[c][0];
            y += m_[c][1];
        }
        return x == 0 && y == 0;
    }
};

int main() {
    return 0;
}
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