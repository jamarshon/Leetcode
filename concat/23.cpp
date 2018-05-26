
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
836. Rectangle Overlap
A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the coordinates of its bottom-left corner, and (x2, y2) are 
the coordinates of its top-right corner.

Two rectangles overlap if the area of their intersection is positive.  To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two rectangles, return whether they overlap.

Example 1:

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
Example 2:

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
Notes:

Both rectangles rec1 and rec2 are lists of 4 integers.
All coordinates in rectangles will be between -10^9 and 10^9.
/*
    Submission Date: 2018-05-24
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool intersects(int a1, int a2, int b1, int b2) {
        return !(b1 >= a2 || a1 >= b2);
    }
    
    // Check if x intervals intersect and y intervals intersect
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return intersects(rec1[0], rec1[2], rec2[0], rec2[2]) && intersects(rec1[1], rec1[3], rec2[1], rec2[3]);
    }
};

int main() {
    return 0;
}