
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
123. Best Time to Buy and Sell Stock III
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you 
buy again).

/*
    Submission Date: 2017-08-03
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int K = 2;
        int N = prices.size();

        if(N <= 1) return 0;

        /**
            dp[k][i] represents maximum profit of at most k transactions until index i
            dp[k][0] = 0 as no points
            dp[0][i] = 0 as no transactions
            dp[k][i] = max(
                    dp[k][i-1], <- ignore element i 
                    price[i] + max{j = 0 to i}(-price[j] + dp[k-1][j]) <- take element i with element j
                                                                    and have k-1 transactions until index j 
                    )
        */
        vector<vector<int>> dp(K + 1, vector<int>(N, 0));
        for(int k = 1; k <= K; k++) {
            int tmp_max = dp[k-1][0] - prices[0];
            for(int i = 1; i < N; i++) {
                dp[k][i] = max(dp[k][i-1], prices[i] + tmp_max);
                tmp_max = max(tmp_max, dp[k-1][i] - prices[i]);
            }
        }

        return dp[K][N-1];
    }
    int maxProfit3(vector<int>& prices) {
        int lowest_price1 = INT_MAX,
            lowest_price2 = INT_MAX,
            max_profit1 = 0,
            max_profit2 = 0;

        // lowest_price2 = buy2 - max_profit_one_buy_one_sell (ie. sell1 - buy1)
        // max_profit2 = sell2 - (buy2 - max_profit_one_buy_one_sell)
        //             = profit2 + profit1
        for(auto price: prices) {
            lowest_price1 = min(lowest_price1, price);
            max_profit1 = max(max_profit1, price - lowest_price1);
            lowest_price2 = min(lowest_price2, price - max_profit1);
            max_profit2 = max(max_profit2, price - lowest_price2);
        }

        return max_profit2;
    }

    int maxProfit2(vector<int>& prices) {
        int N = prices.size();
        if(N == 0) return 0;

        // forward[i] is max profit from [0, i] and backward[i] is max profit from [i,N)
        vector<int> forward(N, 0), backward(N, 0);
        int min_price = prices[0]; 
        for(int i = 1; i < N; i++) {
            forward[i] = max(forward[i-1], prices[i] - min_price);
            if(prices[i] < min_price) min_price = prices[i];
        }

        int max_price = prices[N-1]; 
        for(int i = N - 2; i >= 0; i--) {
            backward[i] = max(backward[i+1], max_price - prices[i]);
            if(prices[i] > max_price) max_price = prices[i];
        }

        int res = 0;
        for(int i = 0; i < N; i++) {
            if(i + 1 < N) res = max(res, forward[i] + backward[i+1]);
            res = max(max(res, forward[i]), backward[i]);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
124. Binary Tree Maximum Path Sum
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any 
node in the tree along the parent-child connections. The path must contain at least one node and 
does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.

/*
    Submission Date: 2017-07-21
    Runtime: 19 ms
    Difficulty: HARD
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
    int maxPathSum(TreeNode* root) {
        if(root == NULL) return 0;
        int max_curr = root -> val;
        maxPathSum(root, max_curr);
        return max_curr;
    }
    int maxPathSum(TreeNode* root, int& max_curr) {
        if(root == NULL) return 0;

        int curr = root -> val;
        int left = maxPathSum(root -> left, max_curr);
        int right = maxPathSum(root -> right, max_curr);
        max_curr = max(max_curr, curr + left + right);
        curr = max(max(curr, curr + left), curr + right);
        max_curr = max(max_curr, curr);
        return curr;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int len = s.size();
        int i = 0;
        int j = len - 1;

        while(i < j) {
            while(!isalnum(s[i]) && i < j) i++;
            if(i >= j) return true;

            while(!isalnum(s[j]) && i < j) j--;
            if(i >= j) return true;

            if(tolower(s[i]) != tolower(s[j])) return false;
            i++;
            j--;
        }

        return true;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
126. Word Ladder II
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation 
sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please 
reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-21
    Runtime: 712 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

struct QueueItem {
    string vertex;
    vector<int> path;
    QueueItem(string _vertex, vector<int> _path=vector<int>{}): vertex(_vertex), path(_path) {}
};

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, vector<string>> vertex_to_edges;

        wordList.push_back(beginWord);

        int N = wordList.size();
        int word_len = beginWord.size();

        unordered_map<string, int> vertex_to_index;

        for(int i = 0; i < N; i++) {
            vertex_to_index[wordList[i]] = i;

            if(wordList[i] == beginWord && i != N - 1) continue;
            for(int j = i + 1; j < N; j++) {
                if(wordList[j] == beginWord && j != N - 1) continue;

                bool seen_different = false;
                bool can_add = true;
                for(int k = 0; k < word_len; k++) {
                    if(wordList[i][k] != wordList[j][k]) {
                        if(seen_different) {
                            can_add = false;
                            break;
                        }
                        seen_different = true;
                    }
                }

                if(can_add) {
                    vertex_to_edges[wordList[i]].push_back(wordList[j]);
                    vertex_to_edges[wordList[j]].push_back(wordList[i]);
                }
            }
        }

        queue<QueueItem> to_do;
        to_do.emplace(beginWord);

        unordered_set<string> visited;
        vector<vector<string>> res;

        vector<vector<int>> paths;
        int min_path = -1;

        while(!to_do.empty()) {
            QueueItem curr = to_do.front();
            to_do.pop();
            if(min_path != -1 && curr.path.size() > min_path) continue;

            if(curr.vertex == endWord) {
                if(min_path == -1) {
                    min_path = curr.path.size();
                }
                paths.push_back(curr.path);
                continue;
            }

            visited.insert(curr.vertex);

            curr.path.push_back(vertex_to_index[curr.vertex]);
            for(auto neighbor: vertex_to_edges[curr.vertex]) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr.path);
            }
        }

        for(auto path: paths) {
            vector<string> temp(path.size());
            transform(path.begin(), path.end(), temp.begin(), [wordList](const int index){
                return wordList[index];
            });

            temp.push_back(endWord);
            res.push_back(temp);
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
127. Word Ladder
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest 
transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-06-28
    Runtime: 1449 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
    bool differByOneLetter(string s1, string s2) {
        int len = s1.size();
        bool seen_different = false;
        for(int i = 0; i < len; i++) {
            if(s1[i] != s2[i]) {
                if(seen_different) return false;
                seen_different = true;
            }
        }
        return true;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, unordered_set<string>> adj;
        unordered_set<string> distinct(wordList.begin(), wordList.end());

        if(!distinct.count(endWord)) return 0;
        distinct.insert(beginWord);

        for(auto word_it = distinct.begin(); word_it != distinct.end(); word_it++) {
            for(auto match_word_it = next(word_it); match_word_it != distinct.end(); match_word_it++) {

                string word = *word_it;
                string match_word = *match_word_it;

                if(differByOneLetter(word, match_word)) {
                    adj[word].insert(match_word);
                    adj[match_word].insert(word);
                }
            }
        }

        queue<pair<string, int>> to_do({{beginWord, 1}});
        unordered_set<string> visited{{beginWord}};
        unordered_map<string, string> parent;

        string curr_word;
        int curr_dist;
        while(!to_do.empty()) {
            pair<string, int> curr = to_do.front();
            tie(curr_word, curr_dist) = curr;

            to_do.pop();
            if(curr_word == endWord) {
                string temp = endWord;
                // while(temp != beginWord) {
                //     cout << temp << endl;
                //     temp = parent[temp];
                // }
                return curr_dist;
            }

            unordered_set<string> neighbors = adj[curr_word];
            for(auto neighbor: neighbors) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr_dist + 1);
                parent[neighbor] = curr_word;
                visited.insert(neighbor);
            }
            
        }

        return 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
128. Longest Consecutive Sequence
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

/*
    Submission Date: 2017-06-29
    Runtime: 12 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int res = 0;
        for(auto item: s) {
            int range = 1;
            int temp = item - 1;
            while(s.count(temp)) {
                s.erase(temp);
                temp--;
                range++;
            }
            
            temp = item + 1;
            while(s.count(temp)) {
                s.erase(temp);
                temp++;
                range++;
            }

            res = max(res, range);
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
129. Sum Root to Leaf Numbers
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

/*
    Submission Date: 2017-07-14
    Runtime: 3 ms
    Difficulty: MEDIUM
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
    int sumNumbers(TreeNode* root, int current_path) {
        if(root == NULL) {
            return 0;
        } 

        int curr_sum = current_path*10 + root -> val;

        if(root -> left == NULL && root -> right == NULL) {
            return curr_sum;
        }

        int left = sumNumbers(root -> left, curr_sum);
        int right = sumNumbers(root -> right, curr_sum);
        return left + right;
    }

    int sumNumbers(TreeNode* root) {
        return sumNumbers(root, 0);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
130. Surrounded Regions
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    void bfs(vector<vector<char>>& board, int i, int j, int N, int M) {
        queue<pair<int, int>> q;
        q.emplace(i, j);

        int dk[4] = {0, -1, 1, 0};
        int dl[4] = {-1, 0, 0, 1};
        while(!q.empty()) {
            pair<int, int>& p = q.front();

            tie(i, j) = p;
            q.pop();

            if(board[i][j] != 'O') continue;
            board[i][j] = 'L';

            int new_i, new_j;
            for(int k = 0; k < 4; k++) {
                new_i = i + dk[k];
                new_j = j + dl[k];

                if(0 <= new_i && new_i < N && 0 <= new_j && new_j < M) {
                    if(board[new_i][new_j] != 'O') continue;
                    q.emplace(new_i, new_j);
                    // dfs(board, new_i, new_j, N, M);
                }
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int N = board.size();

        if(N == 0) return;

        int M = board.front().size();
        

        for(int i = 0; i < N; i++) {
            if(board[i][0] == 'O') bfs(board, i, 0, N, M);
            if(board[i][M-1] == 'O') bfs(board, i, M-1, N, M);
        }

        for(int i = 0; i < M; i++) {
            if(board[0][i] == 'O') bfs(board, 0, i, N, M);
            if(board[N-1][i] == 'O') bfs(board, N-1, i, N, M);
        }

        unordered_map<char, char> m{{'X', 'X'}, {'L', 'O'}, {'O', 'X'}};
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                board[i][j] = m[board[i][j]];
            }
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

/*
    Submission Date: 2017-07-24
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void generate(vector<int>& dp, string str, vector<string>& temp, int index, vector<vector<string>>& res) {
        if(index == str.size() - 1) {
            const char kNullChar = '\0';
            vector<string> temp_copy(temp.size());
            transform(temp.begin(), temp.end(), temp_copy.begin(), [&kNullChar](string s){
                s.erase(remove_if(s.begin(), s.end(), [&kNullChar](const char& c){ return c == kNullChar; }), s.end());
                return s;
            });
            res.push_back(temp_copy);
            return;
        }
        for(int i = index + 1; i < str.size(); i++) {
            if(dp[i] > 0) {
                if(i - dp[i] <= index) { // the palindrome extends to or past our current word so we can take a substring of it
                    int end = i - index;
                    string sub = str.substr(index, 2*end); // includes null at front but not back
                    temp.push_back(sub);
                    // index + sub.size() is the null behind sub
                    generate(dp, str, temp, index + sub.size(), res); 
                    temp.pop_back();
                }
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;

        const char kNullChar = '\0';

        string str = string(1, kNullChar);
        for(auto c: s) str += string(1,c) + kNullChar;

        int N = str.size();
        vector<int> dp(N, 0);
        int right = 0;
        int center = 0;

        for(int i = 1; i < N; i++) {
            int mirr = 2*center - i;
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            int left = i - (1 + dp[i]);
            int right = i + (1 + dp[i]);

            while(left >= 0 && right < N && str[left] == str[right]) {
                left--;
                right++;
                dp[i]++;
            }

            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }

        vector<string> temp;
        generate(dp, str, temp, 0, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
132. Palindrome Partitioning II
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        int len = s.size();
        int dp[len + 1];
        for(int i = 0; i <= len; i++) dp[i] = i-1;

        for(int i = 0; i < len; i++) {
            for(int j = 0; j < len; j++) {
                if(i + j > len || i - j < 0) break;
                if(s[i+j] != s[i-j]) break;
                dp[i + j + 1] = min(1 + dp[i-j], dp[i + j + 1]);
            }

            for(int j = 0; j < len; j++) {
                if(i + j + 1 > len || i - j < 0) break;
                if(s[i+j+1] != s[i-j]) break;
                if(i + j + 2 > len) break;
                dp[i + j + 2] = min(1 + dp[i-j], dp[i + j + 2]);
            }
        }

        return dp[len];
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
133. Clone Graph
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/

/*
    Submission Date: 2017-07-18
    Runtime: 33 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
    unordered_set<UndirectedGraphNode*> visited;
public:
    void cloneGraph(UndirectedGraphNode* head, UndirectedGraphNode *node) {
        visited.insert(node);
        for(auto neighbor: node -> neighbors) {
            if(!m.count(neighbor)) {
                m[neighbor] = new UndirectedGraphNode(neighbor -> label);
            }

            head -> neighbors.push_back(m[neighbor]);
            if(!visited.count(neighbor)) {
                cloneGraph(m[neighbor], neighbor);
            }
        }
    }

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;

        UndirectedGraphNode* head = new UndirectedGraphNode(node -> label);
        m[node] = head;
        cloneGraph(head, node);
        return head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
134. Gas Station
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next 
station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int N = gas.size();
        int start = 0;
        int curr_gas = 0;
        int need_to_overcome = 0;
        for(int i = 0; i < N; i++) {
            curr_gas += gas[i] - cost[i];
            if(curr_gas < 0) {
                need_to_overcome -= curr_gas;
                start = i + 1;
                curr_gas = 0;
            }
        }
        return (curr_gas >= need_to_overcome) ? start : -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
135. Candy
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int candy(const vector<int>& ratings) {
        int N = ratings.size();

        vector<int> forward(N, 1);
        vector<int> backward(N, 1);

        for(int i = 1; i < N; i++) {
            if(ratings[i] > ratings[i-1]) {
                forward[i] = forward[i-1] + 1;
            }
        }

        for(int i = N - 2; i >= 0; i--) {
            if(ratings[i] > ratings[i+1]) {
                backward[i] = backward[i+1] + 1;
            }
        }

        int count = 0;
        for(int i = 0; i < N; i++) {
            count += max(forward[i], backward[i]);
        }

        return count;
    }
};

int main() {
    Solution s;
    return 0;
}