
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
233. Number of Digit One
Given an integer n, count the total number of digit 1 
appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 
1, 10, 11, 12, 13.

/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution2 {
public:
    // low is the form of 10^n where 10^n <= high < 10^(n+1) meaning low and high have same number of digits
    int countDigitOne(int low, int high) {
        while(low > high) low /= 10; // 100 and 002 we need to make them the same so 10 and 2

        if(low == 0) return 0;
        if(low == 1) return 1;

        int res = 0;
        int diff = min(high-low+1, low); // 461-100 -> 100 or 120-100 -> 20

        res += diff;

        int high_first_digit = high/low;
        
        // high_first_digit = 461/100 = 4 
        // we consider 0-99 100-199 200-299, 300-399, 400-461
        // there are high_first_digit - 1 full intervals countDigitOne(10, 99)
        // there is one incomplete interval countDigitOne(10,61)
        int full_interval = countDigitOne(low/10, low-1);
        for(int i = 0; i < high_first_digit; i++) { 
            res += full_interval;
        }

        res += countDigitOne(low/10, high % low);
        return res;
    }

    int countDigitOne(int x) {
        if(x < 0) return 0;

        int n = floor(log10(x));
        int low = round(pow(10, n));
        return countDigitOne(low, x);
    } 
};

class Solution {
public:
    int countDigitOne(int n) {
        typedef long long ll;
        ll res = 0;

        /*
            Given a number xxxxyzzz where indices are 76543210 and k=3 which is where y appears
            we want to count how many times y is one. 
            xxxx would be numbers 0000 to xxxx so they appear xxxx - 0000 + 1 times or (xxxx + 1)
            if y >= 2 then it means for the (xxxx+1) times, there is 10^k occurences that y is 1
                so it is just (xxxx+1)*10^k
            if y == 1 then for the (xxxx+1) times, there is (xxxx+1)-1 full intervals of 10^k that has 
                y equal to 1 and there is one partial interval for the numbers zzz which occur zzz - 000 + 1
                times or (zzz+1) so it is xxxx*10^k + zzz+1
            if y == 0 then the (xxxx+1) complete intervals do not include the last one as y is not greater than
                one so it is xxxx*10^k

            e.g (y >= 2) 4(3)zz there is x + 1 = 5 times x(1)zz can occur 0(1)zz, 1(1)zz, 2(1)zz, 3(1)zz, 4(1)zz
                y >= 2 meaning the last interval 4(1)zz is considered complete (4100 to 4199) is included by 4(3)zz
                so it is 5*10^2

                (y == 1) 4(1)zz the last interval 4(1)zz is not considered complete but for 0(1)zz, 1(1)zz, 2(1)zz, 
                3(1)zz there are 4*10^2 ones. The partial interval of 4(1)zz has zz + 1 number of ones as 4(1)00
                to 4(1)zz include zz + 1 elements for a total of 4*10^2 + (zz + 1)
                
                (y == 0) 4(0)zz the last interval 4(1)zz is not complete so there is 4*10^2 for 0(1)zz, 1(1)zz, 2(1)zz, 
                3(1)zz and the zz + 1 elements do not count towards the total as y is not one so just 4*10^2
        */
        for(ll i = 1; i <= n; i *= 10) { // i is 10^k
            // denote xxxxy as temp, xxxx as prefix, y as digit, and zz as suffix
            ll temp = n/i;
            ll prefix = temp / 10;
            ll digit = temp % 10;
            ll suffix = n % i;

            if(digit >= 2) {
                res += (prefix + 1)*i; // (xxxx+1)*10^k
            } else if(digit == 1) {
                res += (prefix)*i + (suffix + 1); // xxxx*10^k + zzz+1
            } else { // digit == 0
                res += (prefix)*i; // xxxx*10^k
            }
        }
        return res;
        
    }
};

int main() {
    Solution s;
    cout << s.countDigitOne(13) << endl; // 6
    cout << s.countDigitOne(100) << endl; // 21
    cout << s.countDigitOne(101) << endl; // 23
    cout << s.countDigitOne(102) << endl; // 24
    cout << s.countDigitOne(1410065408) << endl; // 1737167499
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
234. Palindrome Linked List
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

/*
    Submission Date: 2017-08-06
    Runtime: 28 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = curr -> next;

        while(curr) {
            curr -> next = prev;
            prev = curr;
            curr = next;
            if(next != NULL) next = curr -> next;
        }

        return prev;
    }

    bool isEqual(ListNode* a, ListNode* b) {
        while(a && b) {
            if(a -> val != b -> val) return false;
            a = a -> next;
            b = b -> next;
        }
        return a == NULL && b == NULL;
    }

    bool isPalindrome(ListNode* head) {
        ListNode* slow, *fast, *last_slow;
        last_slow = NULL;
        slow = fast = head;

        while(fast && fast -> next) {
            fast = fast -> next -> next;
            last_slow = slow;
            slow = slow -> next;
        }

        if(slow == head) return true;

        last_slow -> next = NULL;

        bool is_even_length = fast == NULL;
        // marker is where to start reversing if even and it's next is where to start reversing if odd
        // e.g marker is 1 in 0 -> 1 -> 2 -> 3 and marker is 2 in 0 -> 1 -> 2 -> 3 -> 4
        ListNode* marker = slow;

        ListNode* rev_head = is_even_length ? reverse(marker) : reverse(marker -> next); // reverse last half
        bool res = isEqual(head, rev_head); // check if first half and reversed second half is the same
        ListNode* rev_tail = reverse(rev_head); // undo the reverse
        if(is_even_length) {
            last_slow -> next = rev_tail;
        } else {
            last_slow -> next = marker; // place the marker back in between the first half and second half for odd length
            marker -> next = rev_tail;
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
235. Lowest Common Ancestor of a Binary Search Tree
Given a binary search tree (BST), find the lowest common ancestor 
(LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest 
common ancestor is defined between two nodes v and w as the 
lowest node in T that has both v and w as descendants (where 
we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. 
Another example is LCA of nodes 2 and 4 is 2, since a node can be a 
descendant of itself according to the LCA definition.

/*
    Submission Date: 2017-08-21
    Runtime: 29 ms
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL) return NULL;
        if(p == NULL || q == NULL) return p ? p : q;

        int p_val = p -> val, q_val = q -> val, root_val = root -> val;

        if(root_val > p_val && root_val > q_val) {
            return lowestCommonAncestor(root -> left, p, q);
        } else if(root_val < p_val && root_val < q_val) {
            return lowestCommonAncestor(root -> right, p, q);
        } else {
            return root;
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
236. Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in 
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is 
defined between two nodes v and w as the lowest node in T that has both v and w 
as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another 
example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of 
itself according to the LCA definition.

/*
    Submission Date: 2017-08-14
    Runtime: 16 ms
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
    int lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& res) {
        if(root == NULL) return 0;
        
        int count = 0;
        if(root == p) count++;
        if(root == q) count++;

        if(count == 2) { // root == p == q so root is lca
            res = root; 
            return 2; 
        }
        
        int left_count = lowestCommonAncestor(root -> left, p, q, res);
        if(left_count == 2) return 2; // found p and q in root -> left
        count += left_count;

        // root is either p or q and the other is in the left tree so root is lca
        if(count == 2) { 
            res = root;
            return 2;
        }
        
        int right_count = lowestCommonAncestor(root -> right, p, q, res);
        if(right_count == 2) return 2; // found p and q in root -> right
        count += right_count;

        // root and left_tree has either p or q and the other is in the right tree 
        // so root is lca
        if(count == 2) {
            res = root;
            return 2;
        }
        
        return count; 
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = NULL;
        lowestCommonAncestor(root, p, q, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
237. Delete Node in a Linked List
Write a function to delete a node (except the tail) in a singly linked list, given only access to 
that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list 
should become 1 -> 2 -> 4 after calling your function.

/*
    Submission Date: 2017-07-21
    Runtime: 16 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        node -> val = node -> next -> val;
        node -> next = node -> next -> next;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
238. Product of Array Except Self
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the 
product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

/*
    Submission Date: 2017-07-30
    Runtime: 68 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = nums.size();
        vector<int> dp(N);
        
        // forwards sweep
        int product = 1;
        for(int i = 0; i < N; i++) {
            dp[i] = product;
            product *= nums[i];
        }
        
        // backward sweep
        int back_product = 1;
        for(int i = N-1; i >= 0; i--) {
            dp[i] *= back_product;
            back_product *= nums[i];
        }
        
        return dp;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is 
moving from the very left of the array to the very right. You can 
only see the k numbers in the window. Each time the sliding window 
moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array's 
size for non-empty array.

Follow up:
Could you solve it in linear time?
/*
    Submission Date: 2017-08-21
    Runtime: 69 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        typedef pair<int,int> pii;
        list<pii> ls;

        int N = nums.size();
        vector<int> res;
        for(int i = 0; i < N; i++) {
            while(!ls.empty() && ls.front().second <= i - k) {
                ls.pop_front();
            }

            while(!ls.empty() && ls.back().first < nums[i]) {
                ls.pop_back();
            }

            ls.emplace_back(nums[i], i);
            if(i >= k - 1) res.push_back(ls.front().first);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix. 
This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
/*
    Submission Date: 2017-08-22
    Runtime: 79 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int M = matrix.size();
        int N = matrix.front().size();
        
        int i = 0;
        int j = N - 1;
        while(i < M && j >= 0) {
            if(matrix[i][j] == target) return true;
            if(matrix[i][j] > target) { // smaller than everything in this column 
                j--;
            } else if(matrix[i][j] < target) { // bigger than everything in this row
                i++;
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
257. Binary Tree Paths
Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
/*
    Submission Date: 2017-08-23
    Runtime: 79 ms
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
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == NULL) return {};
        
        string curr = to_string(root -> val);
        vector<string> res;
        
        vector<string> left = binaryTreePaths(root -> left);
        for(auto str: left) res.push_back(curr + "->" + str);
        
        vector<string> right = binaryTreePaths(root -> right);
        for(auto str: right) res.push_back(curr + "->" + str);
        
        if(left.empty() && right.empty()) res.push_back(curr);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
258. Add Digits
Given a non-negative integer num, repeatedly add all its 
digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. 
Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?
/*
    Submission Date: 2017-08-25
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

/*
    digital root problem (single digit) value obtained by an iterative 
    process of summing digits, on each iteration using the result from 
    the previous iteration to compute a digit sum

    cyclic around 9
    ...                 10                  20                  30
    0 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 
    ...             40                  50                  60
    5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 
    ...         70                  80                  90
    1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 
*/
class Solution {
public:
    int addDigits(int num) {
        return 1 + (num - 1) % 9;
    }
};

class Solution2 {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        int num_digits = floor(log10(num)) + 1;
        if(num_digits == 1) return num;
        
        int x = 0;
        while(num) {
            x += num % 10;
            num /= 10;
        }
        
        return addDigits(x);
    }
};

int main() {
    Solution s;
    for(int i = 0; i < 100; i++) {
        cout << i << ' ' << s.addDigits(i) << endl;
    }
    return 0;
}