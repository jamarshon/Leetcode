
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
617. Merge Two Binary Trees
Given two binary trees and imagine that when you put one of them to cover the 
other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two 
nodes overlap, then sum node values up as the new value of the merged node. 
Otherwise, the NOT null node will be used as the node of new tree.

Example 1:
Input: 
    Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
         3
        / \
       4   5
      / \   \ 
     5   4   7
Note: The merging process must start from the root nodes of both trees.

/*
    Submission Date: 2017-06-11
    Runtime: 45 ms
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
    TreeNode* mergeTreesHelper(TreeNode* t1, TreeNode* t2) {
        if(t1 == NULL && t2 == NULL) return NULL;
        
        TreeNode* curr = new TreeNode(-1);
        int new_val = -1;
        if(t1 != NULL && t2 != NULL) {
            new_val = t1 -> val + t2 -> val;
        } else if(t1 != NULL) {
            new_val = t1 -> val;
        } else {
            new_val = t2 -> val;
        }
        
        curr -> val = new_val;
        
        TreeNode* left = mergeTreesHelper(t1 ? t1 -> left : NULL, t2 ? t2 -> left : NULL);
        TreeNode* right = mergeTreesHelper(t1 ? t1 -> right : NULL, t2 ? t2 -> right : NULL);
        curr -> left = left;
        curr -> right = right;
        return curr;
    }
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        return mergeTreesHelper(t1, t2);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
622. Design Circular Queue
Design your implementation of the circular queue. The circular queue is a linear
data structure in which the operations are performed based on FIFO (First In
First Out) principle and the last position is connected back to the first
position to make a circle. It is also called ‘Ring Buffer’.
One of the Benefits of the circular queue is that we can make use of the spaces
in front of the queue. In a normal queue, once the queue becomes full, we can
not insert the next element even if there is a space in front of the queue. But
using the circular queue, we can use the space to store new values.
Your implementation should support following operations:


    MyCircularQueue(k): Constructor, set the size of the queue to be k.
    Front: Get the front item from the queue. If the queue is empty, return -1.
    Rear: Get the last item from the queue. If the queue is empty, return -1.
    enQueue(value): Insert an element into the circular queue. Return true if
the operation is successful. deQueue(): Delete an element from the circular
queue. Return true if the operation is successful. isEmpty(): Checks whether the
circular queue is empty or not. isFull(): Checks whether the circular queue is
full or not.


Example:

MyCircularQueue circularQueue = new MycircularQueue(3); // set the size to be 3

circularQueue.enQueue(1);  // return true

circularQueue.enQueue(2);  // return true

circularQueue.enQueue(3);  // return true

circularQueue.enQueue(4);  // return false, the queue is full

circularQueue.Rear();  // return 3

circularQueue.isFull();  // return true

circularQueue.deQueue();  // return true

circularQueue.enQueue(4);  // return true

circularQueue.Rear();  // return 4
 
 

Note:


    All values will be in the range of [1, 1000].
    The number of operations will be in the range of [1, 1000].
    Please do not use the built-in Queue library.

/*
    Submission Date: 2018-07-12
    Runtime: 20 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class MyCircularQueue {
  vector<int> q_;
  int k_;
  int front_;
  int back_;
  int size_;

 public:
  /** Initialize your data structure here. Set the size of the queue to be k. */
  MyCircularQueue(int k) {
    q_.assign(k, 0);
    front_ = 0;
    back_ = -1;
    k_ = k;
    size_ = 0;
  }

  /** Insert an element into the circular queue. Return true if the operation is
   * successful. */
  bool enQueue(int value) {
    if (isFull()) return false;
    back_ = (back_ + 1) % k_;
    q_[back_] = value;
    size_++;
    return true;
  }

  /** Delete an element from the circular queue. Return true if the operation is
   * successful. */
  bool deQueue() {
    if (isEmpty()) return false;
    front_ = (front_ + 1) % k_;
    size_--;
    return true;
  }

  /** Get the front item from the queue. */
  int Front() {
    if (isEmpty()) return -1;
    return q_[front_];
  }

  /** Get the last item from the queue. */
  int Rear() {
    if (isEmpty()) return -1;
    return q_[back_];
  }

  /** Checks whether the circular queue is empty or not. */
  bool isEmpty() { return size_ == 0; }

  /** Checks whether the circular queue is full or not. */
  bool isFull() { return size_ == k_; }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
623. Add One Row to Tree
Given the root of a binary tree, then value v and depth d, you need to add a row of 
nodes with value v at the given depth d. The root node is at depth 1.

The adding rule is: given a positive integer depth d, for each NOT null tree nodes 
N in depth d-1, create two tree nodes with value v as N's left subtree root and right 
subtree root. And N's original left subtree should be the left subtree of the new left 
subtree root, its original right subtree should be the right subtree of the new right 
subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a 
tree node with value v as the new root of the whole original tree, and the original 
tree is the new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.

/*
    Submission Date: 2017-06-18
    Runtime: 19 ms
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
    void getRow(TreeNode* root, int d, vector<TreeNode*>& vec) {
        if(root == NULL) return;
        if(d == 0) {
            vec.push_back(root);
            return;
        }
        
        getRow(root -> left, d - 1, vec);
        getRow(root -> right, d - 1, vec);
    }
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        // get all nodes at depth d - 1
        vector<TreeNode*> vec;
        if(d == 1) {
            TreeNode* new_root = new TreeNode(v);
            new_root -> left = root;
            root = new_root;
        } else {
            getRow(root, d - 2, vec);
            for(auto t: vec) {
                TreeNode* left = t -> left;
                TreeNode* right = t -> right;
                t -> left = new TreeNode(v);
                t -> right = new TreeNode(v);
                t -> left -> left = left;
                t -> right -> right = right;
            }
        }
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
624. Maximum Distance in Arrays
Given m arrays, and each array is sorted in ascending order. Now you can pick up two 
integers from two different arrays (each array picks one) and calculate the distance. 
We define the distance between two integers a and b to be their absolute difference 
|a-b|. Your task is to find the maximum distance.

Example 1:
Input: 
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation: 
One way to reach the maximum distance 4 is to pick 1 in the first or third array 
and pick 5 in the second array.
Note:
Each given array will have at least 1 number. There will be at least two non-empty arrays.
The total number of the integers in all the m arrays will be in the range of [2, 10000].
The integers in the m arrays will be in the range of [-10000, 10000].

/*
    Submission Date: 2017-06-18
    Runtime: 32 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Start {
    int index;
    int first_value;
};

struct End {
    int index;
    int last_value;
};

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int N = arrays.size();
        vector<Start> v;
        vector<End> v2;
        for(int i = 0; i < N; i++) {
            Start e = {i, arrays[i][0]};
            End e2 = {i, arrays[i].back()};
            v.push_back(e);
            v2.push_back(e2);
        }

        sort(v.begin(), v.end(), [](Start e, Start b){ return e.first_value < b.first_value; });
        sort(v2.begin(), v2.end(), [](End e, End b){ return e.last_value > b.last_value; });

        int max_dist = -1;
        int max_search = N;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < max_search; j++) {
                if(v[i].index != v2[j].index) {
                    max_dist = max(abs(v2[j].last_value - v[i].first_value), max_dist);
                    max_search = j;
                    break;
                }
            }
        }
        return max_dist;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
628. Maximum Product of Three Numbers
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:
Input: [1,2,3]
Output: 6
Example 2:
Input: [1,2,3,4]
Output: 24
Note:
The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.

/*
    Submission Date: 2017-07-09
    Runtime: 79 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int N = nums.size();
        
        if(N < 3) return INT_MIN;
        
        sort(nums.begin(), nums.end());
        
        // three largest or 1 largest and 2 smallest
        return max(nums[N-1]*nums[N-2]*nums[N-3], nums[N-1]*nums[0]*nums[1]);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
633. Sum of Square Numbers
Given a non-negative integer c, your task is to decide whether there're two
integers a and b such that a2 + b2 = c.

Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False
/*
    Submission Date: 2018-05-30
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

/*
    use newton's method to find roots where xn_plus_1 = (xn + x/xn)/2
*/
class Solution2 {
  bool is_square(int x) {
    if (x < 0) return -1;
    int xn = 0;
    int xn_plus_1 = x;
    while (abs(xn - xn_plus_1) > 1) {
      xn = xn_plus_1;
      xn_plus_1 = (xn + x / xn) / 2;
    }

    return xn * xn == x || xn_plus_1 * xn_plus_1 == x;
  }

 public:
  bool judgeSquareSum(int c) {
    for (int i = 0; i <= sqrt(c); i++) {
      if (is_square(c - i * i)) return true;
    }
    return false;
  }
};

class Solution {
 public:
  /*
      two pointers. if a^2 + b^2 > c then increasing a will not help so decrease
     b if it is < c then decreasing b will not help so increase a
  */
  bool judgeSquareSum(int c) {
    int low = 0;
    int high = sqrt(c);
    while (low <= high) {
      int x = low * low + high * high;
      if (x == c) return true;
      if (x < c) {
        low++;
      } else {
        high--;
      }
    }
    return false;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
636. Exclusive Time of Functions
Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, 
find the exclusive time of these functions.

Each function has a unique id, start from 0 to n-1. A function may be called recursively or by 
another function.

A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" 
means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the 
very end of time 0.

Exclusive time of a function is defined as the time spent within this function, the time spent by 
calling other functions should not be considered as this function's exclusive time. You should 
return the exclusive time of each function sorted by their function id.

Example 1:
Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
Note:
Input logs will be sorted by timestamp, NOT log id.
Your output should be sorted by function id, which means the 0th element of your output corresponds 
to the exclusive time of function 0.
Two functions won't start or end at the same time.
Functions could be called recursively, and will always end.
1 <= n <= 100

/*
    Submission Date: 2017-07-15
    Runtime: 63 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <cassert>

using namespace std;

struct Log {
    int id;
    string status;
    int timestamp;
};

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> times(n, 0);
        stack<Log> st;
        for(string log: logs) {
            stringstream ss(log);
            string temp, temp2, temp3;
            getline(ss, temp, ':');
            getline(ss, temp2, ':');
            getline(ss, temp3, ':');

            Log item = {stoi(temp), temp2, stoi(temp3)};
            if(item.status == "start") {
                st.push(item);
            } else {
                assert(st.top().id == item.id);

                int time_added = item.timestamp - st.top().timestamp + 1;
                times[item.id] += item.timestamp - st.top().timestamp + 1;
                st.pop();

                if(!st.empty()) {
                    assert(st.top().status == "start");
                    times[st.top().id] -= time_added;
                }
            }
        }

        return times;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
637. Average of Levels in Binary Tree
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return 
[3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.

/*
    Submission Date: 2017-07-09
    Runtime: 22 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
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
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        vector<double> res;
        
        while(!q.empty()) {
            int size = q.size();
            int size1 = 0;
            double sum = 0;
            for(int i = 0; i < size; i++) {
                TreeNode* f = q.front();
                if(f) {
                    sum += f -> val;
                    size1++;
                    q.push(f -> left);
                    q.push(f -> right);
                }
                
                q.pop();
            }
            if(size1)
            res.push_back(sum/size1);
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
638. Shopping Offers
In LeetCode Store, there are some kinds of items to sell. Each item has a price.

However, there are some special offers, and a special offer consists of one or more different kinds of 
items with a sale price.

You are given the each item's price, a set of special offers, and the number we need to buy for each item. 
The job is to output the lowest price you have to pay for exactly certain items as given, where you could
 make optimal use of the special offers.

Each special offer is represented in the form of an array, the last number represents the price you need 
to pay for this special offer, other numbers represents how many specific items you could get if you buy 
this offer.

You could use any of special offers as many times as you want.

Example 1:
Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
Output: 14
Explanation: 
There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B. 
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
Example 2:
Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
Output: 11
Explanation: 
The price of A is $2, and $3 for B, $4 for C. 
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 
for 1C. 
You cannot add more items, though only $9 for 2A ,2B and 1C.
Note:
There are at most 6 kinds of items, 100 special offers.
For each item, you need to buy at most 6 of them.
You are not allowed to buy more items than you want, even if that would lower the overall price.

/*
    Submission Date: 2017-07-09
    Runtime: 26 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, int> m;
public:
    int shoppingOffersHelper(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        string key = "";
        
        int N = needs.size();
        
        int res = INT_MAX;
        
        int count = 0;
        int price_cost = 0;
        for(int i = 0; i < N; i++) {
            key += to_string(needs[i]);
            count += needs[i] == 0;
            price_cost += needs[i]*price[i];
        }
        
        if(m.count(key)) return m[key];
        
        if(count == N) return 0;
        
        res = min(res, price_cost);
        
        vector<vector<int>> restore;
        for(auto it = special.begin(); it != special.end();) {
            vector<int> sp = *it;
            
            bool should_erase = false;
            for(int i = 0; i < N; i++) {
                if(sp[i] > needs[i]) {
                    should_erase = true;
                    break;
                }
            }
            
            if(should_erase) {
                restore.push_back(sp);
                it = special.erase(it);
            } else {
                // everything in sp[i] <= needs[i] so we can take it
                for(int i = 0; i < N; i++) {
                    needs[i] -= sp[i];
                }
                
                res = min(sp[N] + shoppingOffersHelper(price, special, needs), res);
                for(int i = 0; i < N; i++) {
                    needs[i] += sp[i];
                }
                it++;
            }
        }
        
        for(auto e: restore) special.push_back(e);
        return m[key] = res;
    }
    
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {       
        return shoppingOffersHelper(price, special, needs);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
640. Solve the Equation
Solve a given equation and return the value of x in the form of string "x=#value". The equation contains 
only '+', '-' operation, the variable x and its coefficient.

If there is no solution for the equation, return "No solution".

If there are infinite solutions for the equation, return "Infinite solutions".

If there is exactly one solution for the equation, we ensure that the value of x is an integer.

Example 1:
Input: "x+5-3+x=6+x-2"
Output: "x=2"
Example 2:
Input: "x=x"
Output: "Infinite solutions"
Example 3:
Input: "2x=x"
Output: "x=0"
Example 4:
Input: "2x+3x-6x=x+2"
Output: "x=-1"
Example 5:
Input: "x=x+2"
Output: "No solution"

/*
    Submission Date: 2017-07-09
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
    pair<long long, long long> getCount(string s) {
        long long x_count = 0;
        long long c_count = 0;
        for(int i = 0; i < s.size();) {
            string prev = "";
            bool seen_number = false;
            bool end_x = false;
            while(i < s.size()) {
                if(isdigit(s[i])) {
                    prev += s[i];
                    seen_number = true;
                    i++;
                } else if(s[i] == '+' || s[i] == '-') {
                    if(!seen_number) {
                        prev += s[i];
                        i++;
                    } else {
                        break;
                    }
                } else if(s[i] == 'x') {
                    end_x = true;
                    i++;
                    break;
                }
            }

            if(end_x) {
                if(prev == "+") x_count++;
                else if(prev == "-") x_count--;
                else if(prev == "") x_count++;
                else x_count += stoll(prev);
            } else {
                if(prev == "+") c_count++;
                else if(prev == "-") c_count--;
                else if(prev == "") c_count++;
                else c_count += stoll(prev);
            }
        }

        return {x_count, c_count};
    }
    string solveEquation(string equation) {
        // put all the x on the left side and all the numbers on the right side
        string s = equation;
        string inf = "Infinite solutions";
        string none = "No solution";

        int eq_ind = s.find("=");
        if(eq_ind == string::npos) return none;

        string left = s.substr(0, eq_ind);
        string right = s.substr(eq_ind + 1);

        
        long long x_count1, c_count1;
        tie(x_count1, c_count1) = getCount(left);

        long long x_count2, c_count2;
        tie(x_count2, c_count2) = getCount(right);

        long long left_x_count = x_count1 - x_count2;
        long long right_c_count = c_count2 - c_count1;

        if(left_x_count == 0) return right_c_count == 0 ? inf : none;

        return "x=" + to_string(right_c_count/left_x_count);
    }
};

int main() {
    Solution s;
    return 0;
}