
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
654. Maximum Binary Tree
Given an integer array with no duplicates. A maximum tree building on this array is defined as 
follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum 
number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum 
number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].

/*
    Submission Date: 2017-08-06
    Runtime: 66 ms
    Difficulty: MEDIUM
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

class Solution2 {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int N = nums.size();
        
        int top = -1;
        vector<int> st(N, 0);
        vector<int> T(N, 0);
        for(int i = 0; i < N; i++) {
            int temp_top = top;
            while(temp_top >= 0 && nums[st[temp_top]] < nums[i]) {
                temp_top--;
            }
            
            if(temp_top != -1) T[i] = st[temp_top];
            
            if(temp_top < top) {
                T[st[temp_top + 1]] = i;
            }
            st[++temp_top] = i;
            top = temp_top;
        }
        
        T[st[0]] = -1;
        
        TreeNode* nodes[N];
        for(int i = 0; i < N; i++) nodes[i] = new TreeNode(nums[i]);
        
        TreeNode* root;
        for(int i = 0; i < N; i++) {
            int parent_ind = T[i];
            if(parent_ind == -1) root = nodes[i];
            else if(i < parent_ind) nodes[parent_ind] -> left = nodes[i];
            else nodes[parent_ind] -> right = nodes[i];
        }
        
        return root;
    }
};

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for(auto num: nums) {
            TreeNode* curr = new TreeNode(num);
            TreeNode* left = NULL;
            while(!stk.empty() && stk.back() -> val < num) {
                left = stk.back();
                stk.pop_back();
            }

            curr -> left = left;
            if(!stk.empty()) {
                stk.back() -> right = curr;
            }
            stk.push_back(curr);
        }
        return stk.front();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
655. Print Binary Tree
Print a binary tree in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary tree.
The column number n should always be an odd number.
The root node's value (in string format) should be put in the exactly middle of the 
first row it can be put. The column and the row where the root node belongs will separate 
the rest space into two parts (left-bottom part and right-bottom part). You should print the 
left subtree in the left-bottom part and print the right subtree in the right-bottom part. The 
left-bottom part and the right-bottom part should have the same size. Even if one subtree is 
none while the other is not, you don't need to print anything for the none subtree but still 
need to leave the space as large as that for the other subtree. However, if two subtrees are 
none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
Note: The height of binary tree is in the range of [1, 10].

/*
    Submission Date: 2017-08-06
    Runtime: 66 ms
    Difficulty: MEDIUM
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
    int depth(TreeNode* root) {
        if(root == NULL) return -1;
        return 1 + max(depth(root -> left), depth(root -> right));
    }
    
    void populate(TreeNode* root, vector<vector<string>>& res, int row, int start, int end) {
        if(root == NULL) return;
        if(start >= end) return;
        if(row >= res.size()) return;
        
        string val = to_string(root -> val);
        int mid = start + (end - start)/2;
        res[row][mid] = val;
        
        populate(root -> left, res, row + 1, start, mid);
        populate(root -> right, res, row + 1, mid + 1, end);
    }
    vector<vector<string>> printTree(TreeNode* root) {
        // get the maximum depth of the tree
        int rd = depth(root);
        int col = (1 << (rd + 1)) - 1; 
        // the matrix has depth rows and 2^(depth + 1) - 1 columns
        vector<vector<string>> res(rd + 1, vector<string>(col, "")); 
        populate(root, res, 0, 0, col);
        return res;
    }
};

int main() {
    return 0;
}
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