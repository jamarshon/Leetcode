
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
292. Nim Game
You are playing the following Nim Game with your friend: There is a 
heap of stones on the table, each time one of you take turns to 
remove 1 to 3 stones. The one who removes the last stone will 
be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the 
game. Write a function to determine whether you can win the game 
given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will 
never win the game: no matter 1, 2, or 3 stones you remove, 
the last stone will always be removed by your friend.
/*
    Submission Date: 2017-08-26
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        if n <= 3, player wins as they just take it
        if n == 4, player loses as no matter what they take
        there will be some remaining for opponent

        if 4 < n <= 4 + 3, player can win as they can reduce 
        it to n == 4 by taking away [1,3] stones

        if n == 8, player loses as no matter what they take
        opponent can reduce it n == 4

        for the generalized case (n):
        if n % 4 == 0, player loses as whatever they take x = [1,3], 
        opponent takes 4 - x to get n % 4 == 0 again until n == 4
        which opponent wins
        so n % 4 != 0 where n % 4 == x where x = [1, 3] is when player 
        wins as player can reduce by x leading to n % 4 == 0 for the opponent
        causing the opponent to lose as seen above
    */
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
295. Find Median from Data Stream
Median is the middle value in an ordered integer list. If the size of 
the list is even, there is no middle value. So the median is the mean 
of the two middle value.

Examples: 
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the 
data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2
/*
    Submission Date: 2017-09-10
    Runtime: 172 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class MedianFinder {
    typedef priority_queue<int, vector<int>, less<int>> MaxHeap;
    typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

    MaxHeap max_heap_;
    MinHeap min_heap_;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(max_heap_.empty()) {
            max_heap_.push(num);
        } else {
            if(num > max_heap_.top()) {
                min_heap_.push(num);
            } else {
                max_heap_.push(num);
            }

            // Maintain abs(max_heap_.size() - min_heap_.size()) <= 1
            if(max_heap_.size() > min_heap_.size() + 1) { // max_heap_ too large
                min_heap_.push(max_heap_.top());
                max_heap_.pop();
            } else if(min_heap_.size() > max_heap_.size() + 1) { // min_heap_ too large
                max_heap_.push(min_heap_.top());
                min_heap_.pop();
            }
        }
    }
    
    double findMedian() {
        /*
        Three cases: since abs(max_heap_.size() - min_heap_.size()) <= 1
        denote x as min(max_heap_.size() - min_heap_.size())
        1) size x and x means even elements so it just the average of max of first heap and min of second heap
        2) size x + 1 and x means odd elements so the max of the first heap is the median element
        3) size x and x + 1 means odd elements so the min of the second heap is the median element
        */
        if(max_heap_.size() == min_heap_.size()) {
            return (double)(max_heap_.top() + min_heap_.top())/2.0;
        } else if(max_heap_.size() > min_heap_.size()) {
            return max_heap_.top();
        } else {
            return min_heap_.top();
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into 
a sequence of bits so that it can be stored in a file or memory buffer, or 
transmitted across a network connection link to be reconstructed later in 
the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is 
no restriction on how your serialization/deserialization algorithm should 
work. You just need to ensure that a binary tree can be serialized to a 
string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a 
binary tree. You do not necessarily need to follow this format, so please 
be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. 
Your serialize and deserialize algorithms should be stateless.
/*
    Submission Date: 2017-09-10
    Runtime: 46 ms
    Difficulty: HARD
*/
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) {
            return "#,";
        } else {
            string curr = to_string(root -> val) + ",";
            string left = serialize(root -> left);
            string right = serialize(root -> right);
            return curr + left + right;
        }
    }
    
    TreeNode* deserializeHelper(const string& data, int& index) {
        size_t comma_ind = data.find(",", index);
        assert(comma_ind != string::npos);
        
        string curr = data.substr(index, comma_ind - index);
        index = comma_ind + 1;
        
        if(curr == "#") return NULL;
        
        TreeNode* root = new TreeNode(stoi(curr));
        root -> left = deserializeHelper(data, index);
        root -> right = deserializeHelper(data, index);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        return deserializeHelper(data, index);
    }
};

class Codec2 {
public:

    // Encodes a tree to a single string.
    string structure(TreeNode* root) {
        if(root == NULL) return "0";
        return "1" + structure(root -> left) + structure(root -> right);
    }
    
    string values(TreeNode* root) {
        if(root == NULL) return "";
        string curr = to_string(root -> val) + ",";
        string left = values(root -> left);
        string right = values(root -> right);
        return curr + left + right;
        
    }
    string serialize(TreeNode* root) {
        string st = structure(root);
        string val = values(root);
        return st + "," + val;
    }
    
    TreeNode* deserializeHelper(const string& st, stringstream& ss, int& index) {
        if(st[index] == '0') return NULL;
        string temp;
        getline(ss, temp, ',');
        assert(!temp.empty());
        
        TreeNode* curr = new TreeNode(stoi(temp));
        index++;
        curr -> left = deserializeHelper(st, ss, index);
        index++;
        curr -> right = deserializeHelper(st, ss, index);
        
        return curr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        
        size_t comma_ind = data.find(",");
        string st = data.substr(0, comma_ind);
        string val = data.substr(comma_ind + 1);
        stringstream ss(val);
        return deserializeHelper(st, ss, index);
    }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
299. Bulls and Cows
You are playing the following Bulls and Cows game with your friend: 
You write down a number and ask your friend to guess what the number is. 
Each time your friend makes a guess, you provide a hint that indicates how 
many digits in said guess match your secret number exactly in both digit 
and position (called "bulls") and how many digits match the secret number 
but locate in the wrong position (called "cows"). Your friend will use 
successive guesses and hints to eventually derive the secret number.

For example:

Secret number:  "1807"
Friend's guess: "7810"
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)
Write a function to return a hint according to the secret number and 
friend's guess, use A to indicate the bulls and B to indicate the cows. 
In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain 
duplicate digits, for example:

Secret number:  "1123"
Friend's guess: "0111"
In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is 
a cow, and your function should return "1A1B".
You may assume that the secret number and your friend's guess only contain 
digits, and their lengths are always equal.
/*
    Submission Date: 2017-09-10
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        int secret_freq[10] = {0};
        int guess_freq[10] = {0};
        
        int N = secret.size();
        int bulls = 0;
        for(int i = 0; i < N; i++) {
            if(secret[i] == guess[i]) {
                bulls++;
            } else {
                secret_freq[secret[i] - '0']++;
                guess_freq[guess[i] - '0']++;
            }
        }
        
        int cows = 0;
        for(int i = 0; i < 10; i++) {
            cows += min(secret_freq[i], guess_freq[i]);
        }
        
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
300. Longest Increasing Subsequence
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there 
may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?
/*
    Submission Date: 2017-03-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int N = nums.size(), dp_len = 0;
        vector<int> dp(N, -1), P(N, -1);
        
        for(int i = 0; i < N; i++) {
            auto it = lower_bound(dp.begin(), dp.begin() + dp_len, nums[i], [&nums](const int& dp_el, const int& val){
                return nums[dp_el] < val;
            });
            
            int it_ind = it - dp.begin();
            dp[it_ind] = i;
            
            if(it_ind > 0) P[i] = dp[it_ind - 1];
            if(it_ind == dp_len) dp_len++;
        }
        
        vector<int> lis_seq(dp_len);
        int index = lis_seq.size();
        for(int i = dp[dp_len - 1]; i >= 0; i = P[i])
            lis_seq[--index] = nums[i];
        
        return dp_len;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
303. Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
/*
    Submission Date: 2017-03-11
    Runtime: 162 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
    vector<int> dp_;
public:
    NumArray(vector<int> nums) {
        if(nums.empty()) return;
        
        int N = nums.size();
        dp_.resize(N);
        
        dp_[0] = nums[0];
        for(int i = 1; i < N; i++) {
            dp_[i] = dp_[i-1] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        return dp_[j] - (i - 1 >= 0 ? dp_[i-1] : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
304. Range Sum Query 2D - Immutable
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper 
left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = 
(4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
    int rows_, cols_;
    vector<vector<int>> dp_;
public:
    NumMatrix(vector<vector<int>> matrix) {
        rows_ = matrix.size();
        cols_ = matrix.empty() ? 0 : matrix[0].size();
        
        dp_.assign(rows_, vector<int>(cols_));
        for(int i = 0; i < rows_; i++) {
            for(int j = 0; j < cols_; j++) {
                dp_[i][j] = matrix[i][j];
                if(i > 0) dp_[i][j] += dp_[i-1][j]; 
                if(i > 0 && j > 0) dp_[i][j] -= dp_[i-1][j-1]; 
                if(j > 0) dp_[i][j] += dp_[i][j-1]; 
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = dp_[row2][col2];
        if(row1 > 0) res -= dp_[row1-1][col2];
        if(col1 > 0) res -= dp_[row2][col1-1];
        if(row1 > 0 && col1 > 0) res += dp_[row1-1][col1-1];
        return res;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
306. Additive Number
Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. 
Except for the first two numbers, each subsequent number in the 
sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an 
additive sequence: 1, 1, 2, 3, 5, 8.

1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
"199100199" is also an additive number, the additive sequence is: 
1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199
Note: Numbers in the additive sequence cannot have leading zeros, 
so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9', write a function 
to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?
/*
    Submission Date: 2017-08-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int N = num.size();
        
        long long o1 = 0;
        long long o2 = 0;
        
        // given a string, we extract o1 and o2 from it leaving (o3)xxxx and calling the recursive function
        for(int i = 0; i < N; i++) {
            o1 = o1*10 + (num[i] - '0');
            o2 = 0;
            for(int j = i + 1; j < N; j++) {
                o2 = o2*10 + (num[j] - '0');
                if(isAdditiveNumber(num.substr(j + 1), o2, o1 + o2)) {
                    return true;
                }
                if(o2 == 0) break; // o2 begins with 0
            }
            
            if(o1 == 0) break; // o1 begins with 0
        }
        
        return false;
    }
    
    // num should be (o3)xxxx if it is o3 then return true
    // else if it is (o3)xxxx then call the function on xxxx looking for o2 + o3 at the front and o3 becomes o2
    // f(num, o2, o3) -> f(num.substr(i), o3, o2 + o3) where i the first index of x
    bool isAdditiveNumber(string num, long long o2, long long o3) {
        int N = num.size();
        if(N == 0) return false;
        if(num.front() == '0') return N == 1 && o3 == 0; // o3 begins with zero
        
        long long curr = 0;
        for(int i = 0; i < N; i++) {
            curr = curr*10 + (num[i] - '0');
            if(curr > o3) return false;
            if(curr == o3) {
                return i == N-1 || isAdditiveNumber(num.substr(i + 1), o3, o2 + o3);
            }
        }
        
        return false;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
307. Range Sum Query - Mutable
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
/*
    Submission Date: 2017-03-11
    Runtime: 83 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
    vector<int> tree;
    int N;
    
    int lsb(int x){ return x & ~(x-1); }
    
    // [1,i]
    int query(int i) {
        int sum = 0;
        while(i != 0) {
            sum += tree[i];
            i -= lsb(i);
        }
        return sum;
    }
public:
    NumArray(vector<int> nums) {
        N = nums.size();
        tree.resize(N+1);
        
        tree[0] = 0;
        for(int i = 1; i <= N; i++) tree[i] = nums[i-1];
        
        for(int i = 1; i <= N; i++) {
            int parent = i + lsb(i);
            if(parent <= N) tree[parent] += tree[i];
        }
    }
    
    void update(int i, int val) {
        int delta = val - sumRange(i,i);
        i++;
        while(i <= N) {
            tree[i] += delta;
            i += lsb(i);
        }
    }
    
    int sumRange(int i, int j) {
        return query(j+1) - query(i);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
309. Best Time to Buy and Sell Stock with Cooldown
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before 
you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        if(N < 2) return 0;
        
        vector<int> dp(N);
        dp[N-1] = 0;
        dp[N-2] = max(0, prices[N-1] - prices[N-2]);
        
        int max_sold = max(prices[N-1], prices[N-2]);
        for(int i = N-3; i >= 0; i--) {
            // buy now prices[i] and sell on day j then get dp[j+2]
            // -prices[i] + prices[j] + dp[j+2];
            dp[i] = max(dp[i+1], -prices[i] + max_sold); 
            max_sold = max(max_sold, prices[i] + dp[i+2]);
        }
        
        return dp[0];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
310. Minimum Height Trees
For a undirected graph with tree characteristics, we can choose any 
node as the root. The result graph is then a rooted tree. Among all 
possible rooted trees, those with minimum height are called minimum 
height trees (MHTs). Given such a graph, write a function to find all 
the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will 
be given the number n and a list of undirected edges (each edge is a 
pair of labels).

You can assume that no duplicate edges will appear in edges. Since 
all edges are undirected, [0, 1] is the same as [1, 0] and thus 
will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

Note:

(1) According to the definition of tree on Wikipedia: “a tree is 
an undirected graph in which any two vertices are connected by 
exactly one path. In other words, any connected graph without 
simple cycles is a tree.”

(2) The height of a rooted tree is the number of edges on the 
longest downward path between the root and a leaf.
/*
    Submission Date: 2017-08-21
    Runtime: 76 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if(n == 1) return {0}; // one node so the root of mht is itself
        
        vector<unordered_set<int>> graph(n);
        for(auto p: edges) {
            graph[p.first].insert(p.second);
            graph[p.second].insert(p.first);
        }
        
        vector<int> leaves;
        for(int i = 0; i < n; i++) {
            // this node is connected to only one other node (parent) so it is a leaf
            if(graph[i].size() == 1) {
                leaves.push_back(i);
            }
        }
        
        // reverse BFS the idea is to select nodes that are only connected to one other node
        // these nodes are leafs and are removed. Update the new leafs by keeping track of the
        // number of children of each node. If it goes to 1, it means it is only connected to its
        // parent and is now a leaf
        // when there are only 2 or less leafs then it means these are the roots
        
        while(n > 2) { // tree has more than 2 nodes
            n -= leaves.size(); // remove the leafs
            
            vector<int> new_leaves;
            for(auto leaf: leaves) {
                int parent = *graph[leaf].begin();
                graph[parent].erase(leaf); // from the parent remove the leaf
                if(graph[parent].size() == 1) { // if the parent has no children, it is now a new leaf
                    new_leaves.push_back(parent);
                }
            }
            leaves = new_leaves;
        }
        
        return leaves;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given 
prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] 
is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of 
size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution2 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        set<int> res{1};
        vector<int> last_prime(K, 1);

        while(res.size() < n) {
            int min_j = 0;
            for(int j = 1; j < K; j++) {
                if(last_prime[j] * primes[j] < last_prime[min_j] * primes[min_j]) {
                    min_j = j;
                }
            }

            res.insert(last_prime[min_j] * primes[min_j]);
            last_prime[min_j] = *res.upper_bound(last_prime[min_j]);
        }

        return *res.rbegin();
    }
};

class Solution3 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        // idx[j] corresponds to the first element in dp which 
        // primes[j]*dp[idx[j]] >= dp[i]
        vector<int> dp(n), idx(K, 0);
        dp[0] = 1;

        for(int i = 1; i < n; i++) {
            int best_j = 0;
            for(int j = 0; j < K; j++) {
                // avoid duplicates e.g 4*3 and 6*2
                if(dp[idx[j]] * primes[j] == dp[i-1]) idx[j]++; 
                if(dp[idx[j]] * primes[j] < dp[idx[best_j]] * primes[best_j]) {
                    best_j = j;
                }
            }
            dp[i] = dp[idx[best_j]] * primes[best_j];
            idx[best_j]++;
        }

        return dp[n-1];
    }
};

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        vector<int> dp(n);
        dp[0] = 1;
        // pair<prime, index in dp>
        auto func =[&dp](const pair<int,int> lhs, const pair<int,int> rhs){ 
            return lhs.first*dp[lhs.second] > rhs.first*dp[rhs.second];
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(func)> pq(func);

        for(int i = 0; i < K; i++) pq.push({primes[i], 0});

        for(int i = 1; i < n; i++) {
            pair<int,int> p;
            do {
                p = pq.top();
                pq.pop();
                dp[i] = p.first*dp[p.second];
                pq.emplace(p.first, p.second + 1);
            } while(p.first * dp[p.second] == dp[i-1]);
            
        }

        return dp[n-1];
    }
};

int main() {
    return 0;
}