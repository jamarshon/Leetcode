
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
241. Different Ways to Add Parentheses
Given a string of numbers and operators, return all possible results from computing all the 
different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <functional>
#include <sstream>

using namespace std;

struct Element {
    bool is_operator;
    int value;
    Element(bool _is_operator, int _value): is_operator(_is_operator), value(_value) {}
};

struct ETreeNode {
    Element e;
    ETreeNode* left, *right;
    ETreeNode(Element _e): e(_e), left(NULL), right(NULL) {}
};

class SolutionTree {
public:
    ETreeNode* cloneWithOffset(ETreeNode* curr, int offset) {
        if(curr == NULL) return NULL;
        Element offset_e = curr -> e;
        offset_e.value += offset;

        ETreeNode* new_curr = new ETreeNode(offset_e);
        new_curr -> left = cloneWithOffset(curr -> left, offset);
        new_curr -> right = cloneWithOffset(curr -> right, offset);
        return new_curr;
    }

    void destroyTree(ETreeNode* root) {
        if(root == NULL) return;
        destroyTree(root -> left);
        destroyTree(root -> right);
        delete root;
    }

    vector<ETreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        vector<vector<ETreeNode*>> dp(n + 1);
        dp[0] = {NULL};

        for(int len = 1; len <= n; len++) {
            for(int j = 0; j < len; j++) {
                vector<ETreeNode*> left_trees = dp[j],
                                right_trees = dp[len - j - 1];
                for(auto left_tree: left_trees) {
                    for(auto right_tree: right_trees) {
                        ETreeNode* curr = new ETreeNode(Element{true, j});
                        curr -> left = cloneWithOffset(left_tree, 0);
                        curr -> right = cloneWithOffset(right_tree, j+1);
                        dp[len].push_back(curr);
                    }
                }
                
            }
        }

        for(int i = 0; i < n; i++) {
            for(auto tree: dp[i]) destroyTree(tree);
        }
        return dp[n];
    }

    void inorderPlaceValuesAndOperators(ETreeNode* root, vector<Element>& numbers, vector<Element> operators, int& i, int& j){
        if(root == NULL) return;
        inorderPlaceValuesAndOperators(root -> left, numbers, operators, i, j);
        root -> e = operators[i++];
        if(root -> left == NULL) {
            root -> left = new ETreeNode(numbers[j++]);
        }

        if(root -> right) {
            inorderPlaceValuesAndOperators(root -> right, numbers, operators, i, j);
        } else {
            root -> right = new ETreeNode(numbers[j++]);
        }
    }

    int evaluateTree(ETreeNode* root) {
        assert(root != NULL); // should never happen as the numbers are the leafs
        if(root -> e.is_operator) {
            if(root -> e.value == '*') {
                return evaluateTree(root -> left) * evaluateTree(root -> right);
            } else if(root -> e.value == '+') {
                return evaluateTree(root -> left) + evaluateTree(root -> right);
            } else if(root -> e.value == '-'){
                return evaluateTree(root -> left) - evaluateTree(root -> right);
            } else {
                assert(false);
                return -1;
            }
        } else {
            return root -> e.value;
        }
    }

    void preorder(ETreeNode* curr) {
        if(curr == NULL) {
            cout << "NULL ";
        } else {
            if(curr -> e.is_operator) cout << char(curr -> e.value) << ' ';
            else cout << (curr -> e.value) << ' ';
            preorder(curr -> left);
            preorder(curr -> right);
        }
    }

    vector<int> diffWaysToCompute(string input) {
        int start = 0;
        int end = 0;
        int N = input.size();

        vector<Element> operators;
        vector<Element> numbers;
        while(end < N) {
            if(input[end] == '*' || input[end] == '-' || input[end] == '+') {
                string s = input.substr(start, end - start);
                if(!s.empty()) {
                    numbers.emplace_back(false, stoi(s));
                }
                operators.emplace_back(true, input[end]);
                start = end + 1;
            }
            end++;
        }

        string s = input.substr(start, end - start);
        if(!s.empty()) {
            numbers.emplace_back(false, stoi(s));
        }

        vector<ETreeNode*> uniqueTrees = generateTrees(operators.size());
        vector<int> res;
        int i,j;
        for(auto tree: uniqueTrees) {
            i = j = 0;
            inorderPlaceValuesAndOperators(tree, numbers, operators, i, j);
            res.push_back(evaluateTree(tree));
        }
        return res;
    }
};


class SolutionDP {
    unordered_map<char, function<int(int,int)>> ops_m {
        {'*', [](const int& a, const int& b){ return a*b; }},
        {'+', [](const int& a, const int& b){ return a+b; }},
        {'-', [](const int& a, const int& b){ return a-b; }},
    };
public: 
    vector<int> diffWaysToCompute(string input) {
        vector<int> nums; // nums will be size N and ops should be size N - 1 but extra added just for convenience
        vector<char> ops;

        int num;
        char op;
        stringstream ss(input + "+");

        while(ss >> num && ss >> op) {
            nums.push_back(num);
            ops.push_back(op);
        }

        int N = nums.size();
        if(N == 1) return nums;

        /**
            dp[i][j] is a vector of all possible values from operations from index i to j inclusive where indexes
            correspond with integers from the nums array
            e.g. "2*3-4*5" -> nums = [2,3,4,5] and ops = ['*', '-', '*'] dp[2][3] = {20} as 4*5 or ops[2](dp[2][2], dp[3][3])

            dp[i][i] would just be {nums[i]}
            dp[i][j] would be {op[k](dp[i][k], dp[k+1][j]), ... for all k from [i, j)}
            final result is just indexes 0 to N-1 or dp[0][N-1]
        */
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N));

        for(int i = N-1; i >= 0; i--) {
            for(int j = i; j < N; j++) {
                if(i == j) {
                    dp[i][j] = {nums[i]};
                } else {
                    for(int k = i; k < j; k++) {
                        vector<int>& left = dp[i][k];
                        vector<int>& right = dp[k+1][j];
                        function<int(int,int)> op = ops_m[ops[k]];
                        for(auto left_el: left) {
                            for(auto right_el: right) {
                                dp[i][j].push_back(op(left_el, right_el));
                            }
                        }
                    }
                }
            }
        }
        return dp[0][N-1];
    }
};

class Solution {
    unordered_map<string, vector<int>> dp;
    unordered_map<char, function<int(int,int)>> ops_m {
        {'*', [](const int& a, const int& b){ return a*b; }},
        {'+', [](const int& a, const int& b){ return a+b; }},
        {'-', [](const int& a, const int& b){ return a-b; }},
    };
public:
    vector<int> diffWaysToCompute(string input) {
        if(dp.count(input)) return dp[input];
        int N = input.size();
        vector<int> res;
        for(int i = 0; i < N; i++) {
            if(!isdigit(input[i])) {
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i + 1));
                function<int(int, int)> op = ops_m[input[i]];
                for(auto left_el: left) {
                    for(auto right_el: right) {
                        res.push_back(op(left_el, right_el));
                    }
                }
            }
        }
        
        if(res.empty()) res.push_back(stoi(input)); // no operations left
        return dp[input] = res;
    }
};

int main() {
    Solution s;
    vector<int> v = s.diffWaysToCompute("2*3-4*5");
    for(auto e: v) cout << e << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
242. Valid Anagram
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

/*
    Submission Date: 2017-08-06
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        
        unordered_map<char, int> s_freq, t_freq;
        for(int i = 0, len = s.size(); i < len; i++) {
            s_freq[s[i]]++;
            t_freq[t[i]]++;
        }
        
        if(s_freq.size() != t_freq.size()) return false;
        for(auto kv: s_freq) {
            if(t_freq.count(kv.first) && t_freq[kv.first] == kv.second) continue;
            return false;
        }
        return true;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
263. Ugly Number
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isUgly2(int num) {
        if(num <= 0) return false;
        if(num == 1) return true;

        if(num % 2 == 0) return isUgly(num / 2);
        if(num % 3 == 0) return isUgly(num / 3);
        if(num % 5 == 0) return isUgly(num / 5);
        
        return false;
    }

    bool isUgly(int num) {
        if(num <= 0) return false;

        int primes[3] = {2,3,5};
        for(int i = 0; i < 3; i++) {
            while(num % primes[i] == 0) {
                num /= primes[i];
            }
        }

        return num == 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
404. Sum of Left Leaves
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
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
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 0;
        if(root -> left && root -> left -> left == NULL && root -> left -> right == NULL) {
            res += root -> left -> val;
        }
        
        return res + sumOfLeftLeaves(root -> left) + sumOfLeftLeaves(root -> right);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
414. Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> distinct;
        int max_item = nums.front();
        for(auto num: nums) {
            max_item = max(max_item, num);
            if(distinct.count(num)) continue;
            min_heap.push(num);
            distinct.insert(num);
            if(min_heap.size() > 3) {
                int to_delete = min_heap.top();
                distinct.erase(to_delete);
                min_heap.pop();
            }
        }
        
        return min_heap.size() == 3 ? min_heap.top() : max_item;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
433. Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices from 
"A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), 
where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. 
A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the 
minimum number of mutations needed to mutate from "start" to "end". If there is no 
such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    bool isConnect(string s1, string s2) {
        int diff_count = 0;
        for(int i = 0, len = s1.size(); i < len; i++) {
            diff_count += s1[i] != s2[i];
        }
        return diff_count == 1;
    }
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, vector<string>> graph;

        bank.push_back(start);
        int N = bank.size();
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                if(isConnect(bank[i], bank[j])) {
                    graph[bank[i]].push_back(bank[j]);
                    graph[bank[j]].push_back(bank[i]);
                }
            }
        }

        unordered_set<string> visited;
        queue<pair<string, int>> q;
        q.emplace(start, 0);
        visited.insert(start);

        string curr;
        int dist;
        while(!q.empty()) {
            tie(curr, dist) = q.front();
            // cout << curr << ' ' << dist << endl;
            q.pop();
            if(curr == end) return dist;
            for(auto neighbor: graph[curr]) {
                if(visited.count(neighbor)) continue;
                q.emplace(neighbor, dist + 1);
                visited.insert(neighbor);
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p 
will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

/*
    Submission Date: 2017-08-06
    Runtime: 106 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int M = s.size();
        int N = p.size();
        
        if(M < N) return res;
        unordered_map<char, int> freq, curr_freq;
        
        for(auto c: p) freq[c]++;
        
        for(int i = 0; i < N; i++) curr_freq[s[i]]++;
        
        int low = 0;
        int high = N;
        while(high <= M) {
            bool is_match = true;
            if(curr_freq.size() == freq.size()) {
                for(auto kv: freq) {
                    if(curr_freq.count(kv.first) && curr_freq[kv.first] == kv.second) continue;
                    is_match = false;
                    break;
                }
            } else {
                is_match = false;
            }
            
            if(is_match) res.push_back(low);
            if(high == M) break;
            char to_erase = s[low++];
            curr_freq[s[high++]]++;
            if(curr_freq[to_erase] == 1) curr_freq.erase(to_erase);
            else curr_freq[to_erase]--;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
442. Find All Duplicates in an Array
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and 
others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

/*
    Submission Date: 2017-08-06
    Runtime: 176 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int N = nums.size();
        vector<int> res;
        for(int i = 0; i < N; i++) {
            while(nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
    
        for(int i = 0; i < N; i++) {
            if(nums[i] != i + 1) {
                res.push_back(nums[i]);
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
525. Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

/*
    Submission Date: 2017-04-01
    Runtime: 162 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLen = 0;
        int currentSum = 0;
        
        // unordered_map has key to currentSum and value to earliest index seen with that 
        // currentSum. the idea is that if the cumulative sum is the same then the sum of 
        // elements between those two indices is zero meaning equal number of 0's and 1's
        // so finding the smallest index with the same currentSum results in the largest subarray
        unordered_map<int, int> m = {{0, -1}};
    
        for(int i = 0, len = nums.size(); i < len; i++) {
            if(nums[i] == 0) {
                currentSum--;
            } else {
                currentSum++;
            }
            
            if(m.find(currentSum) == m.end()) {
                m[currentSum] = i;
            } else {
                maxLen = max(maxLen, i - m[currentSum]);
            }
        }
        
        return maxLen;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
536. Construct Binary Tree from String
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, 
one or two pairs of parenthesis. The integer represents the root's value and a pair 
of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   

Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.

/*
    Submission Date: 2017-03-11
    Runtime: 42 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* str2tree(string s) {
        int len = s.size();
        if(len == 0) return NULL;

        int firstBracketIndex = s.find('(');
        if(firstBracketIndex == string::npos) return new TreeNode(stoi(s));

        TreeNode* node = new TreeNode(stoi(s.substr(0, firstBracketIndex)));
        int count = 1;
        int offset = firstBracketIndex + 1;
        int i = offset;

        while(count != 0) {
            if(s[i] == ')') count--;
            else if(s[i] == '(') count++;
            i++;
        }

        string leftExpression = s.substr(offset, i - 1 - offset);
        string rightExpression = (i == len) ? "" : s.substr(i + 1, len - i - 2);

        node -> left = str2tree(leftExpression);
        node -> right = str2tree(rightExpression);

        return node;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
539. Minimum Time Difference
Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum 
minutes difference between any two time points in the list.

Example 1:
Input: ["23:59","00:00"]
Output: 1

Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.

/*
    Submission Date: 2017-03-11
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

class Solution {
public:
    // Assume time b is larger than a
    int getDifference(string a, string b) {
        int hours = stoi(b.substr(0,2)) - stoi(a.substr(0,2));
        int minutes = stoi(b.substr(3,2)) - stoi(a.substr(3,2));
        return hours*60 + minutes;
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int minDiff = INT_MAX;
        int len = timePoints.size();

        for(int i = 1; i < len; i++) {
            int diff = getDifference(timePoints[i-1], timePoints[i]);
            if(diff < minDiff) minDiff = diff;
        }

        string firstTimePoint = timePoints.front();
        int wrappedHour = stoi(firstTimePoint.substr(0,2)) + 24;
        string wrap = to_string(wrappedHour) + firstTimePoint.substr(2);
        int wrapDiff = getDifference(timePoints.back(), wrap);

        if(wrapDiff < minDiff) minDiff = wrapDiff;
        return minDiff;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
541. Reverse String II
Given a string and an integer k, you need to reverse the first k characters for every 2k 
characters counting from the start of the string. If there are less than k characters left, 
reverse all of them. If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>

class Solution {
public:
    string reverseStr(string s, int k) {
        string finalStr = "";
        bool reverse = true;
        int i = 0, len = s.size();
        while(i < len) {
            string currentStr = string(1, s[i++]);
            while(i%k != 0 && i < len) {
                currentStr = reverse ? s[i] + currentStr : currentStr + s[i];
                i++;
            }
            finalStr += currentStr;
            reverse ^= true;
        }
        
        return finalStr;
    }
};

int main() {
    return 0;
}