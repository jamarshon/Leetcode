
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
650. 2 Keys Keyboard
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad 
for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps 
permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
Note:
The n will be in the range [1, 1000].

/*
    Submission Date: 2017-07-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = dp[1] = 0;

        for(int i = 1; i <= n; i++) {
            int cost = dp[i] + 1;
            int temp = i*2;
            if(temp > n) break; 
            while(temp <= n) {
                dp[temp] = min(dp[temp], ++cost);
                temp += i;
            }
        }

        return dp[n];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
652. Find Duplicate Subtrees
Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to 
return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1: 
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.

/*
    Submission Date: 2017-07-30
    Runtime: 45 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
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
    string preorder(TreeNode* root, unordered_map<string, int>& freq, vector<TreeNode*>& res) {
        if(root != NULL) {
            string left = preorder(root -> left, freq, res);
            string right = preorder(root -> right, freq, res);
            
            string str = to_string(root -> val) + " " + left + right;
            
            if(freq[str] == 1) res.push_back(root);
            freq[str]++;
            return str;
        } else {
            return "null ";
        }
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> freq;
        vector<TreeNode*> res;
        preorder(root, freq, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
653. Two Sum IV - Input is a BST
Given a Binary Search Tree and a target number, return true if there exist two 
elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

/*
    Submission Date: 2017-08-06
    Runtime: 45 ms
    Difficulty: EASY
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

class Solution2 {
    unordered_map<int, vector<TreeNode*>> visited;
public:
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL) return false;
        int target = k - (root -> val);
        
        if(visited.count(target)) {
            for(auto l: visited[target]) {
                if(l != root) return true;
            }
        }
        
        TreeNode* curr = root;
        while(curr) {
            if(curr != root && curr -> val == target) return true;
            visited[curr -> val].push_back(curr);
            if(curr -> val > target) {
                curr = curr -> right;
            } else {
                curr = curr -> left;
            }
        }
        
        return findTarget(root -> left, k) || findTarget(root -> right, k);
    }
};

class Solution {
public:
    void inorder(TreeNode* curr, vector<int>& res) {
        if(curr == NULL) return;
        inorder(curr -> left, res);
        res.push_back(curr -> val);
        inorder(curr -> right, res);
    }
    bool findTarget(TreeNode* root, int k) {
        vector<int> sorted_arr;
        inorder(root, sorted_arr);
        int low = 0;
        int high = sorted_arr.size() - 1;
        
        while(low < high) {
            int sum = sorted_arr[low] + sorted_arr[high];
            if(sum == k) return true;
            if(sum < k) low++;
            else high--;
        }
        return false;
    }
};

int main() {
    return 0;
}
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