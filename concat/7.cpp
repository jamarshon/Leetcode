
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
106. Construct Binary Tree from Inorder and Postorder Traversal
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-24
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inorder_val_to_ind;

        int N = postorder.size();

        for(int i = 0; i < N; i++) {
            inorder_val_to_ind[inorder[i]] = i;
        }
        return buildTree(inorder, postorder, inorder_val_to_ind, 0, N, 0, N);
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, 
        unordered_map<int, int>& inorder_val_to_ind, 
        int in_start, int in_end, int post_start, int post_end) {

        assert(in_end >= in_start && post_end >= post_start);
        assert(in_end - in_start == post_end - post_start);

        if(in_end == in_start) return NULL;

        int root_val = postorder[post_end - 1];
        int left_size = inorder_val_to_ind[root_val] - in_start;
        int right_size = in_end - inorder_val_to_ind[root_val] - 1;

        TreeNode* root = new TreeNode(root_val);
        root -> left = buildTree(inorder, postorder, inorder_val_to_ind, 
            in_start, inorder_val_to_ind[root_val], post_start, post_start + left_size);
        root -> right = buildTree(inorder, postorder, inorder_val_to_ind, 
            inorder_val_to_ind[root_val] + 1, in_end, post_start + left_size, post_end - 1);
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
107. Binary Tree Level Order Traversal II
Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]

/*
    Submission Date: 2017-07-20
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <deque>
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q{{root}};
        deque<vector<int>> dq;
        
        while(!q.empty()) {
            int q_size = q.size();
            vector<int> temp;
            for(int i = 0; i < q_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    q.push(curr -> left);
                    q.push(curr -> right);
                    temp.push_back(curr -> val);
                }
                q.pop();
            }
            if(!temp.empty()) dq.push_front(temp);
        }

        vector<vector<int>> res(dq.begin(), dq.end());
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
108. Convert Sorted Array to Binary Search Tree
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

/*
    Submission Date: 2017-07-18
    Runtime: 12 ms
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
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        if(start > end) return NULL;
        int mid = start + (end - start + 1)/2;

        TreeNode* root = new TreeNode(nums[mid]);
        root -> left = sortedArrayToBST(nums, start, mid - 1);
        root -> right = sortedArrayToBST(nums, mid + 1, end);
        return root;
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
109. Convert Sorted List to Binary Search Tree
Given a singly linked list where elements are sorted in ascending order, 
convert it to a height balanced BST.

/*
    Submission Date: 2017-06-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode* convertToBST(ListNode* list_node, int n) {
        if(n <= 0) return NULL;
        int mid = n/2;
        ListNode* temp = list_node;
        for(int i = 0; i < mid; i++) {
            temp = temp -> next;
        }
        TreeNode* new_val = new TreeNode(temp -> val);
        TreeNode* right_child = convertToBST(temp -> next, n - mid - 1);
        TreeNode* left_child = convertToBST(list_node, mid);
        new_val -> left = left_child;
        new_val -> right = right_child;
        return new_val;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        ListNode* temp = head;
        int n = 0;
        while(temp) {
            n++;
            temp = temp -> next;
        }
        return convertToBST(head, n);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which 
the depth of the two subtrees of every node never differ by more than 1.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
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
    int computeHeight(TreeNode* root) {
        if(root == NULL) return -1;

        int left_height = computeHeight(root -> left);
        if(left_height == INT_MIN) return INT_MIN;
        int right_height = computeHeight(root -> right);
        if(right_height == INT_MIN) return INT_MIN;

        if(abs(left_height - right_height) > 1) return INT_MIN;
        return max(left_height, right_height) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return computeHeight(root) != INT_MIN;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path 
from the root node down to the nearest leaf node.

/*
    Submission Date: 2017-07-16
    Runtime: 9 ms
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
    int minDepth(TreeNode* root) {
        if(root == NULL) return 0;
        if(root -> left == NULL && root -> right == NULL) {
            return 1;
        }

        // either one child or two child meaning res will be updated at least once
        int res = INT_MAX;
        if(root -> left) {
            res = min(res, minDepth(root -> left));
        }

        if(root -> right) {
            res = min(res, minDepth(root -> right));
        }

        return res + 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
112. Path Sum
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up 
all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
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
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;

        int curr = root -> val;
        if(curr == sum && root -> left == NULL && root -> right == NULL) return true;

        return hasPathSum(root -> left, sum - curr) || hasPathSum(root -> right, sum - curr);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
113. Path Sum II
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]

/*
    Submission Date: 2017-07-24
    Runtime: 9 ms
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
    void pathSum(TreeNode* root, int curr_sum, int sum, vector<int>& curr, vector<vector<int>>& res) {
        if(root == NULL) return;

        curr.push_back(root -> val);
        curr_sum += root -> val;

        if(root -> left == NULL && root -> right == NULL) {
            if(curr_sum == sum) {
                res.push_back(curr);
            }
        } else {
            pathSum(root -> left, curr_sum, sum, curr, res);
            pathSum(root -> right, curr_sum, sum, curr, res);
        }

        curr.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> curr;
        pathSum(root, 0, sum, curr, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
114. Flatten Binary Tree to Linked List
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a 
pre-order traversal.

/*
    Submission Date: 2017-07-04
    Runtime: 6 ms
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
    void flatten(TreeNode* root) {
        if(root == NULL) return;
        if(root -> left == NULL && root -> right == NULL) return;
        flatten(root -> left);
        flatten(root -> right);
        if(root -> left) {
            TreeNode* right = root -> right;
            root -> right = root -> left;
            TreeNode* temp = root -> right;
            while(temp -> right) {
                temp = temp -> right;
            }
            temp -> right = right;
            root -> left = NULL;
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
115. Distinct Subsequences
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some 
(can be none) of the characters without disturbing the relative positions of the remaining characters. 
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.

/*
    Submission Date: 2017-08-02
    Runtime: 28 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int M = t.size();
        int N = s.size();

        // row is template and column is pattern
        vector<vector<int>> dp(M + 1, vector<int>(N + 1, 0));

        // if template is empty then there is one way to make pattern into it
        // if pattern is empty, there is no way to make it match template so 0
        fill(dp[0].begin(), dp[0].begin() + N + 1, 1);

        for(int i = 1; i <= M; i++) {
            for(int j = 1; j <= N; j++) {
                // if they are same character it means it is the number of ways
                // using this common character so dp[i-1][j-1] and number of ways
                // not using this character dp[i][j-1]
                // e.g. t = rab and s = rabb it is number of sequences of ra and rab ("b" of pattern used)
                // plus rab and rab ("b" of pattern not used)
                if(t[i-1] == s[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }

        return dp[M][N];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
116. Populating Next Right Pointers in Each Node
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }
Populate each next pointer to point to its next right node. If there is no next right node, the 
next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every 
parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

/*
    Submission Date: 2017-07-18
    Runtime: 22 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode* curr = root;
        TreeLinkNode* next_level_start = NULL;
        while(curr) {
            next_level_start = curr -> left;

            while(curr) {
                if(curr->left) {
                    curr -> left -> next = curr -> right;
                }
                if(curr -> right) {
                    if(curr -> next) {
                        curr -> right -> next = curr -> next -> left;
                    } else {
                        curr -> right -> next = NULL;
                    }
                }
                curr = curr -> next;
            }

            curr = next_level_start;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
117. Populating Next Right Pointers in Each Node II
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL

/*
    Submission Date: 2017-08-02
    Runtime: 26 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode* next_level_head, *next_level_curr;
        TreeLinkNode* curr = root;
        while(curr) {
            next_level_head = next_level_curr = NULL;
            while(curr) {
                if(curr -> left) {
                    if(next_level_head == NULL) next_level_head = curr -> left;
                    if(next_level_curr == NULL) {
                        next_level_curr = curr -> left;
                    } else {
                        next_level_curr -> next = curr -> left;
                        next_level_curr = next_level_curr -> next;
                    }
                }

                if(curr -> right) {
                    if(next_level_head == NULL) next_level_head = curr -> right;
                    if(next_level_curr == NULL) {
                        next_level_curr = curr -> right;
                    } else {
                        next_level_curr -> next = curr -> right;
                        next_level_curr = next_level_curr -> next;
                    }
                }

                curr = curr -> next;
            }
            
            curr = next_level_head;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
118. Pascal's Triangle
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows, vector<int>{});

        for(int i = 0; i < numRows; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0 || j == i) res[i].push_back(1);
                else res[i].push_back(res[i-1][j-1] + res[i-1][j]);
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
119. Pascal's Triangle II
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

/*
    Submission Date: 2017-08-02
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);

        res[0] = 1;
        long long prev = 1;
        for(int i = 1; i < res.size(); i++) {
            res[i] = prev*(rowIndex-i+1)/i;
            prev = res[i];
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
120. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to 
adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total 
number of rows in the triangle.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int M = triangle.size();
        for(int i = 0; i < M; i++) {
            int N = triangle[i].size();
            for(int j = 0; j < N; j++) {
                if(i == 0 && j == 0) continue;
                if(j == 0) 
                    triangle[i][j] += triangle[i-1][j];
                else if(j == N - 1)
                    triangle[i][j] += triangle[i-1][j-1];
                else
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
            }
        }

        int res = INT_MAX;
        for(auto e: triangle.back()) res = min(res, e);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the 
stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;

        int smallest, profit;
        smallest = prices.front();
        profit = 0;

        for(int i = 0; i < prices.size(); i++) {
            smallest = min(prices[i], smallest);
            profit = max(profit, prices[i] - smallest);
        }
        return profit;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
122. Best Time to Buy and Sell Stock II
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple 
transactions at the same time (ie, you must sell the stock before you buy again).

/*
    Submission Date: 2017-08-02
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        int res = 0;
        // "a <= b <= c <= d"
        // the profit is "d - a = (b - a) + (c - b) + (d - c)" 
        // "a <= b >= b' <= c <= d"
        // the profit is "(b - a) + (d - b')"
        for(int i = 0; i < N - 1 ; i++) res += max(prices[i+1] - prices[i], 0);
        return res;
    }
};

int main() {
    return 0;
}