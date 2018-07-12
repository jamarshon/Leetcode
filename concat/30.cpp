
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
684. Redundant Connection
In this problem, a tree is an undirected graph that is connected and has no 

The given input is a graph that started as a tree with N nodes (with distinct 
values 1, 2, ..., N), with one additional edge added.  The added edge has two 

The resulting graph is given as a 2D-array of edges.  Each element of edges is a 
pair [u, v] with u < v, that represents an undirected edge connecting nodes u 

Return an edge that can be removed so that the resulting graph is a tree of N 
nodes.  If there are multiple answers, return the answer that occurs last in the 
given 2D-array.  The answer edge [u, v] should be in the same format, with u < 
Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3


Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3


Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is 





Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly 
the graph is an undirected graph. For the directed graph follow up please see 
/*
    Submission Date: 2018-07-11
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <algorithm>

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
    union find
    for each node uv, find if u and v are seperate sets. if they are, union the
    sets else they are in the same set and already connected so return uv
    */
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFind<int> uf;
        for(const auto& uv: edges) {
            if(!uf.IsWithinSet(uv[0])) uf.CreateSet(uv[0]);
            if(!uf.IsWithinSet(uv[1])) uf.CreateSet(uv[1]);
            if(!uf.Union(uv[0], uv[1])) { // no union occured as same set already
                return uv;
            }
        }
        
        return {};
    }
};

class Solution2 {
    vector<int> path;
    int u = -1;
public:
    bool dfs(int from, unordered_map<int, vector<int>>& adj, unordered_set<int>& visited, int parent) {
        for(const auto& to: adj[from]) {
            if(to == parent) continue;
            if(visited.count(to)) {
                u = to;
                return true;
            }
            
            visited.insert(to);
            
            path.push_back(to);
            if(dfs(to, adj, visited, from)) { return true; }
            path.pop_back();
        }
        
        return false;
    }
    
    /*
    do dfs and keep track of path. for nodes that are not in cycle the popback will remove them
    the result is path is vector of nodes that go into a cycle and u marks where the cycle begins
    now traverse the cycle (ie path) and find the edge that has highest index
    */
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;
        
        unordered_map<int, unordered_map<int, int>> priority;
        int i = 0;
        for(const auto& uv: edges){
            adj[uv[1]].push_back(uv[0]);
            adj[uv[0]].push_back(uv[1]);
            priority[uv[0]][uv[1]] = i++;
        }
        
        unordered_set<int> visited;
        
        // no disjoint so can just start at one node and will traverse everything
        visited.insert(1);
        path.push_back(1);
        
        bool cycle = dfs(1, adj, visited, -1);
        assert(cycle);
        i = 0;
        while(path[i] != u) i++;
        
        int start = i;
        int pos_u = -1;
        int pos_v = -1;
        int N = path.size();
        for(int j = i; j < N; j++) cout << path[j] << ' '; cout << endl;
        for(; i < N; i++) {
            auto p = minmax(path[i], i + 1 < N ? path[i+1] : path[start]);
            if(pos_u == -1 || priority[p.first][p.second] > priority[pos_u][pos_v]) {
                pos_u = p.first;
                pos_v = p.second;
            }
        }
        
        return {pos_u, pos_v};
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
712. Minimum ASCII Delete Sum for Two Strings
Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
Note:

0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].
/*
    Submission Date: 2018-07-01
    Runtime: 15 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
    dp[i][j] is minimum cost for s1[0, i) s2[0, j)
    dp[0][0] = 0
    dp[0][j] = s2[j-1] + dp[i][j-1] // sum of ascii of s2[0, j)
    dp[i][0] = s1[i-1] + dp[i-1][j] // sum of ascii of s1[0, i)
    
    if s1[i-1] == s2[j-1] 
        dp[i][j] = dp[i-1][j-1] // this character does not to be deleted so
                                // it is just excluding the two end characters
    else
        dp[i][j] = min(
            s1[i-1] + dp[i-1][j], // the cost of the end character of s1 + cost of not using that character
            s2[j-1] + dp[i][j-1] // cost of the end character of s2 + cost of not using that character
        )
    */
    int minimumDeleteSum(string s1, string s2) {
        int N = s1.size(), M = s2.size();
        int dp[N+1][M+1];
        for(int i = 0; i <= N; i++) {
            for(int j = 0; j <= M; j++) {
                if(i == 0 && j == 0) {
                    dp[i][j] = 0;
                } else if(i == 0) {
                    dp[i][j] = s2[j-1] + dp[i][j-1];
                } else if(j == 0) {
                    dp[i][j] = s1[i-1] + dp[i-1][j];
                } else if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(s1[i-1] + dp[i-1][j], s2[j-1] + dp[i][j-1]);
                }
            }
        }
        
        return dp[N][M];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
717. 1-bit and 2-bit Characters
We have two special characters. The first character can be represented by one bit 0. The second character can be represented by 
two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given 
string will always end with a zero.

Example 1:
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
Example 2:
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.
Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
/*
    Submission Date: 2018-06-07
    Runtime: 7 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int N = bits.size();
        vector<bool> dp(N, false);
        dp[N-1] = true;

        for(int i = N-2; i >= 0; i--) {
            if(bits[i] == 0) {
                dp[i] = dp[i+1];
            } else {
                if(i + 2 < N) dp[i] = dp[i+2];
            }
        }

        return dp[0];
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