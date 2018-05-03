
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
210. Course Schedule II
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a 
pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish 
all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, 
return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is 
[0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 
2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is
[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is 
represented.
You may assume that there are no duplicate edges in the input prerequisites.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

class Solution {
public:
    bool TopologicalSortUtil(const int vertex, const vector<vector<int>>& vertex_to_edges, unordered_set<int>& visited, 
        unordered_set<int>& expanding, stack<int>& st) {

        if(expanding.count(vertex)) {
            return true;
        }

        expanding.insert(vertex);
        
        for(auto neighbor: vertex_to_edges[vertex]) {
            if(visited.count(neighbor)) continue;
            bool has_cycle = TopologicalSortUtil(neighbor, vertex_to_edges, visited, expanding, st);
            if(has_cycle) return true;
        }

        visited.insert(vertex);
        expanding.erase(vertex);

        st.push(vertex);
        return false;
    }

    vector<int> TopologicalSort(const int numCourses, const vector<vector<int>>& vertex_to_edges) {
        unordered_set<int> visited;
        unordered_set<int> expanding;
        stack<int> st;

        bool has_cycle = false;
        for(int vertex = 0; vertex < numCourses; vertex++) {
            if(visited.count(vertex)) continue;
            has_cycle = TopologicalSortUtil(vertex, vertex_to_edges, visited, expanding, st);
            if(has_cycle) break;
        }

        vector<int> res;
        if(!has_cycle) {
            while(!st.empty()) {
                res.push_back(st.top());
                st.pop();
            }
        }

        return res;
    }
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> vertex_to_edges(numCourses, vector<int>{});

        for(auto prereq: prerequisites) {
            vertex_to_edges[prereq.second].push_back(prereq.first);
        }

        return TopologicalSort(numCourses, vertex_to_edges);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . 
means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.

/*
    Submission Date: 2017-08-03
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool is_word;
    TrieNode() {
        is_word = false;
        for(int i = 0; i < 26; i++) child[i] = NULL;
    }
};

class WordDictionary {
    TrieNode* root_;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root_ = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* curr = root_;
        for(int i = 0, N = word.size(); i < N; i++) {
            char c = word[i];
            if(curr -> child[c - 'a'] == NULL) curr -> child[c - 'a'] = new TrieNode();
            curr = curr -> child[c - 'a'];
        }
        curr -> is_word = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        queue<pair<TrieNode*, int>> q;
        q.emplace(root_, 0);

        TrieNode* curr;
        int index;
        while(!q.empty()) {
            tie(curr, index) = q.front();
            q.pop();

            if(index == word.size()) {
                if(curr -> is_word) return true;
                continue;
            }
            if(word[index] == '.') { // increase index and add all 26 child to the queue
                for(int i = 0; i < 26; i++) {
                    if(curr -> child[i] == NULL) continue;
                    q.emplace(curr -> child[i], index + 1);
                }
            } else {
                // check if current character is valid
                if(curr -> child[word[index] - 'a'] == NULL) continue; 
                q.emplace(curr -> child[word[index] - 'a'], index + 1);
            }
        }
        return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
212. Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those 
horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of 
data structure could answer such query efficiently?

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

struct TrieNode {
    bool is_leaf;
    TrieNode* children[26];
    TrieNode() {
        is_leaf = false;
        for(int i = 0; i < 26; i++) children[i] = NULL;
    }
};

class Trie {
    TrieNode* root_;
public:
    Trie() {
        root_ = new TrieNode();
    }

    TrieNode* insert(const vector<string>& words) {
        for(auto word: words) insert(word);
        return root_;
    }

    void insert(string word) {
        TrieNode* curr = root_;
        for(int i = 0; i < word.size(); i++) {
            int letter_index = word[i] - 'a';
            if(curr -> children[letter_index] == NULL) {
                curr -> children[letter_index] = new TrieNode();
            }
            curr = curr -> children[letter_index];
        }
        curr -> is_leaf = true;
    }
};

class Solution {
    vector<int> dx{-1,1,0,0};
    vector<int> dy{0,0,-1,1};
public:
    void check(const vector<vector<char>>& board, const TrieNode* node, string curr, int row, int col, int rows, int cols, 
        unordered_set<string>& res, set<pair<int,int>>& visited) {

        if(node -> is_leaf) res.insert(curr);

        visited.insert({row, col});

        for(int i = 0; i < 4; i++) {
            int new_row = row + dy[i];        
            int new_col = col + dx[i];
            if(0 <= new_row && new_row < rows && 0 <= new_col && new_col < cols) {
                if(visited.count({new_row, new_col})) continue; // visited already

                char board_char = board[new_row][new_col];
                if(node -> children[board_char - 'a'] == NULL) continue; // no words to match

                check(board, node -> children[board_char - 'a'], curr + string(1, board_char), new_row, new_col, rows, cols, res, visited);
            }      
        }

        visited.erase({row, col});
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.empty()) return {};

        Trie trie;
        TrieNode* root = trie.insert(words);
        int rows = board.size();
        int cols = board.front().size();

        unordered_set<string> res;
        set<pair<int,int>> visited;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                char board_char = board[i][j];
                if(root -> children[board_char - 'a'] != NULL) {
                    check(board, root -> children[board_char - 'a'], string(1, board_char), i, j, rows, cols, res, visited);
                }
            }
        }

        vector<string> ret(res.begin(), res.end());
        return ret;
    }
};
int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
213. House Robber II
After robbing those houses on that street, the thief has found himself a new place for his thievery 
so that he will not get too much attention. This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses 
remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();

        if(N == 0) return 0;
        if(N == 1) return nums.front();

        vector<int> dp(N);

        int res = 0;
        rob(nums, N, dp);
        res = max(res, dp[1]);
        rob(nums, N-1, dp);
        res = max(res, dp[0]);
        return res;
    }
    
    int rob(vector<int>& nums, int N, vector<int>& dp) {
        dp[N-1] = nums[N-1];

        for(int i = N - 2; i >= 0; i--) {
            dp[i] = max(dp[i + 1], nums[i] + (i + 2 < N ? dp[i+2] : 0));
        }

        return dp[0];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
214. Shortest Palindrome
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

/*
    Submission Date: 2017-07-23
    Runtime: 56 ms
    Difficulty: HARD
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    string Manacher(string s) {
        const char kNullChar = '\0';
        string str = string(1, kNullChar);

        for(auto c: s) str += string(1, c) + kNullChar;

        string max_str = "";
        int len = str.size();
        int right = 0;
        int center = 0;
        vector<int> dp(len, 0);
        
        int start_right = -1;
        for(int i = 1; i < len; i++) {
            int mirr = 2*center - i;

            // i is within right so can take the minimum of the mirror or distance from right
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            // keep expanding around i while it is the same and increment P[i]
            int left_index = i - (1 + dp[i]);
            int right_index = i + (1 + dp[i]);
            while(left_index != -1 && right_index != len && str[left_index] == str[right_index]) {
                left_index--;
                right_index++;
                dp[i]++;
            }
            
            if(left_index == -1) {
                string item = str.substr(left_index + 1, right_index - left_index - 2);           
                if(item.size() > max_str.size()) {
                    start_right = right_index;
                    max_str = item;
                }
            }

            // i goes beyond current right so it is the new center
            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }
        
        string suffix = "";
        max_str.erase(remove_if(max_str.begin(), max_str.end(), [&kNullChar](char c){ return c == kNullChar; }), max_str.end());
        for(int k = start_right; k < len; k++) {
            if(str[k] != kNullChar) {
                suffix += str[k];
            }
        }
        
        string reversed = suffix;
        reverse(reversed.begin(), reversed.end());
        return reversed + max_str + suffix;
    }

    string shortestPalindrome(string s) {
        return Manacher(s);
    }

    string shortestPalindrome2(string s) {
        int N = s.size();
        for(int i = N - 1; i >= 0; i--) {
            bool decision = true;
            for(int j = 0; j < (i + 1)/2; j++) {
                if(s[j] != s[i - j]) {
                    decision = false;
                    break;
                }
            }
            
            if(decision) {
                string suffix = "";
                for(int j = i + 1; j < N; j++) suffix += s[j];
                string reversed = suffix;
                reverse(reversed.begin(), reversed.end());
                return reversed + s.substr(0, i + 1) + suffix;
            }
        }
        return "";
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
215. Kth Largest Element in an Array
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, 
not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ? k ? array's length.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

class Solution {
public:
    /* Nlogk using minheap */
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap heap;
        for(int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if(heap.size() > k) heap.pop();
        }

        return heap.top();
    }
};

class Solution2 {
public:
    /* O(k) using quickselect
        using two ends of the array, slowly move towards the middle as low++, high--
        when comparing to nums[0]
    */
    int findKthLargest( vector<int> nums, int k) {
      int low = 0;
      int high = nums.size() - 1;
      int partition = 0;
      while (low <= high) {
        if(nums[low] <= nums[partition]) {
          low++;
        } else if(nums[high] > nums[partition]) {
          high--;
        } else if (nums[partition] < nums[low]) {
          swap(nums[low], nums[high]);
          --high;
        } else if (nums[partition] >= nums[high]) {
          swap(nums[low], nums[high]);
          ++low;
        } else {
            assert(false);
        }
      }
      
      swap(nums[high], nums[partition]);
      
      if(high == nums.size() - k) {
        return nums[high];
      }
        
      if (high > nums.size() - k) {
        return findKthLargest(vector<int>(nums.begin(), nums.begin() + high), k-(nums.size()-high));
      } else {
        return findKthLargest(vector<int>(nums.begin() + high+1, nums.end()), k);
      }
    }
};


class Solution3 {
public:
    /*
    O(k) using low_partition to be the right boundary of low meaning the first number > nums[0]
    */
    int findKthLargest( vector<int> nums, int k) {
        int low_partition = 0;

        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] <= nums[0]) {
                swap(nums[i], nums[low_partition]);
                ++low_partition;
            }
        }
        
        const int pivot_ind = low_partition - 1;
        swap(nums[pivot_ind], nums[0]);
        
        if(pivot_ind == nums.size() - k) {
            return nums[pivot_ind];
        }

        if (pivot_ind > nums.size() - k) {
            return findKthLargest(vector<int>(
                nums.begin(), nums.begin() + pivot_ind), k-(nums.size() - pivot_ind));
        }
        else {
            return findKthLargest(vector<int>(nums.begin() + pivot_ind + 1, nums.end()), k);
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
216. Combination Sum III
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 
1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]

/*
    Submission Date: 2017-08-03
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void recurse(int current, int sum, int K, int N, vector<int>& temp, vector<vector<int>>& res) {
        if(current > N) return;
        if(temp.size() == K) {
            if(sum == N) res.push_back(temp);
            return;
        }
        for(int i = current + 1; i < 10; i++) {
            temp.push_back(i);
            recurse(i, sum + i, K, N, temp, res);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int K, int N) {
        if(K == 0) return {};

        vector<vector<int>> res;
        vector<int> temp;
        recurse(0, 0, K, N, temp, res);
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> combinationSum3(int K, int N) {
        if(K == 0) return {};

        vector<vector<vector<vector<int>>>> dp(K + 1, vector<vector<vector<int>>>(N + 1));
        // dp[k][i] represents all the vectors that add up to i of length k that is in ascending order using numbers [1, 9]
        // dp[0][i] and dp[k][0] is empty
        // dp[1][i] is just [i]
        // dp[k + 1][i+j] = concat all elements of dp[k][i] with j 
        // for j < 10 && i = j <= N && j being the maximum of the element dp[k][i] 

        for(int k = 1; k < K; k++) {
            for(int i = 1; i < N; i++) {
                if(k == 1) dp[k][i] = {{i}};
                vector<vector<int>>& temp = dp[k][i];

                for(int l = 0; l < temp.size(); l++) {
                    vector<int>& temp_el = temp[l];
                    int largest = temp_el.empty() ? 0 : temp_el.back();

                    for(int j = largest + 1; j < 10 && i + j <= N; j++) {
                        temp_el.push_back(j);
                        dp[k+1][i+j].push_back(temp_el);
                        temp_el.pop_back();
                    }

                }
            }
        }

        return dp[K][N];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
217. Contains Duplicate
Given an array of integers, find if the array contains any duplicates. Your function should 
return true if any value appears at least twice in the array, and it should return false if 
every element is distinct.

/*
    Submission Date: 2017-08-03
    Runtime: 45 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for(auto num: nums) {
            if(seen.count(num)) return true;
            seen.insert(num);
        }
        return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
218. The Skyline Problem
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city 
when viewed from a distance. Now suppose you are given the locations and height of all the buildings 
as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings 
collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li 
and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its 
height. It is guaranteed that 0 ? Li, Ri ? INT_MAX, 0 < Hi ? INT_MAX, and Ri - Li > 0. You may assume all 
buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: 
[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of 
[ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of 
a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used 
to mark the termination of the skyline, and always has zero height. Also, the ground in between any two 
adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:
[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of 
height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

/*
    Submission Date: 2017-08-02
    Runtime: 29 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

using namespace std;

struct Item {
    int x, y;
    bool is_start;
};

struct SortCompare {
    bool operator()(const Item& lhs, const Item& rhs) {
        if(lhs.x != rhs.x) return lhs.x < rhs.x; // smaller x first
        // if an end and start are the same x, put the start building first
        if(lhs.is_start != rhs.is_start) return lhs.is_start; 
        // both are the same type
        if(lhs.is_start) {
            // both start put higher building first cause it overshadows the smaller ones
            return lhs.y > rhs.y;
        } else {
            // both end put smaller building first as we want to remove all the smaller ones first 
            return lhs.y < rhs.y;
        }
    }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> res;

        map<int, int> m;
        vector<Item> items;
        for(auto building: buildings) {
            items.push_back({building[0], building[2], true});
            items.push_back({building[1], building[2], false});
        }

        sort(items.begin(), items.end(), SortCompare());

        // for(auto item: items) cout << item.x << ' ' << item.y << ' ' << item.is_start << endl;
        for(auto item: items) {
            // we see if adding or removing an item changes the max
            if(item.is_start) {
                // adding this item increases the height so this item is part of output
                bool will_change_max = m.empty() || item.y > (m.rbegin() -> first);
                if(will_change_max) {
                    res.emplace_back(item.x, item.y);
                }
                m[item.y]++;
            } else {
                assert(!m.empty() && m.count(item.y) && m[item.y] > 0);
                if(m[item.y] == 1) {
                    // there is only one item of height item.y and it is the largest
                    // so removing it will change the height meaning the next largest
                    // height (0 if empty) and this current x will be part of output
                    bool will_change_max = item.y == m.rbegin() -> first;
                    m.erase(item.y);

                    if(will_change_max) {
                        pair<int, int> to_insert = {item.x, 0};
                        if(!m.empty()) to_insert.second = m.rbegin() -> first;
                        res.push_back(to_insert);
                    }
                } else {
                    m[item.y]--;
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
219. Contains Duplicate II
Given an array of integers and an integer k, find out whether there are two distinct indices 
i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j 
is at most k.

/*
    Submission Date: 2017-08-07
    Runtime: 39 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int N = nums.size();
        for(int i = 0; i < N; i++) {
            if(m.count(nums[i])) {
                if(i - m[nums[i]] <= k) return true;
            }
            m[nums[i]] = i;
        }
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}