
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
151. Reverse Words in a String
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.

Clarification:
What constitutes a word?
A sequence of non-space characters constitutes a word.
Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing spaces.
How about multiple spaces between two words?
Reduce them to a single space in the reversed string.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        int write_idx = 0;
        int N = s.size();

        for(int i = 0; i < N;) {
            // finding first non space char
            while(i < N && isspace(s[i])) {
                i++;
            }

            if(i < N) {
                // add space if needed between words
                if(write_idx != 0) {
                    s[write_idx++] = ' ';
                }

                // write all non space char to write_idx 
                while(i < N && !isspace(s[i])) {
                    s[write_idx++] = s[i++];
                }

            }
        }

        s.resize(write_idx);
        N = s.size();

        reverse(s.begin(), s.end());
        for(int i = 0; i < N; i++) {
            int start = i;
            while(i < N && !isspace(s[i])) {
                i++;
            }
            reverse(s.begin() + start, s.begin() + i);
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
152. Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has 
the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int N = nums.size();
        
        if(N == 0) return 0;
        
        int min_dp[N];
        int max_dp[N];
        
        min_dp[0] = max_dp[0] = nums.front();
        
        int res = max_dp[0];
        
        for(int i = 1; i < N; i++) {
            min_dp[i] = min(min(min_dp[i-1]*nums[i], max_dp[i-1]*nums[i]), nums[i]);
            max_dp[i] = max(max(min_dp[i-1]*nums[i], max_dp[i-1]*nums[i]), nums[i]);
            res = max(res, max_dp[i]);
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
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        int min_item = INT_MAX;
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(nums[low] <= nums[mid]) { // this region is sorted
                min_item = min(min_item, nums[low]);
                low = mid + 1;
            } else {
                min_item = min(min_item, nums[mid]);
                high = mid - 1;
            }
        }

        return min_item;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
154. Find Minimum in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int low = 0;
        int high = nums.size() - 1;
        
        int min_item = nums[low];
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(nums[low] < nums[mid]) { // first half is sorted
                min_item = min(min_item, nums[low]);
                low = mid + 1;
            } else if(nums[low] > nums[mid]) { // second half is sorted
                min_item = min(min_item, nums[mid]);
                high = mid - 1;
            } else {
                min_item = min(min_item, nums[low]);
                low++;
            }
        }
        return min_item;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: EASY
*/

#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

struct MinStackNode {
  int val;
  MinStackNode* next; 
  int min_so_far;
};

class MinStack {
  MinStackNode * top_node;
  
public:
    MinStack() {
      top_node = NULL;      
    }
    
    void push(int x) {
        MinStackNode* new_top = new MinStackNode();
        new_top -> val = x;
        new_top -> next = top_node; 
            
        if (top_node == NULL ) {
            new_top -> min_so_far = x;
        } else if(top_node -> min_so_far <= x){
            new_top -> min_so_far = top_node -> min_so_far;
        } else{
            new_top -> min_so_far = x;
        } 
        
        top_node = new_top;
    }
    
    void pop() {
        assert(top_node != NULL);
        MinStackNode* temp =  top_node;
        top_node = top_node -> next;
        delete temp;
    }
    
    int top() {
        assert(top_node != NULL);
        return top_node -> val;
    }
    
    int getMin() {
        return top_node -> min_so_far;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
160. Intersection of Two Linked Lists
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

/*
    Submission Date: 2017-07-26
    Runtime: 39 ms
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
    int length(ListNode* head) {
        int count = 0;
        while(head) {
            head = head -> next;
            count++;
        }

        return count;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int length_A = length(headA);
        int length_B = length(headB);

        if(length_A > length_B) swap(headA, headB);

        int diff = abs(length_B - length_A);
        for(int i = 0; i < diff; i++) {
            headB = headB -> next;
        }

        while(headA && headB) {
            if(headA == headB) return headA;
            headA = headA -> next;
            headB = headB -> next;
        }

        return NULL;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
162. Find Peak Element
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int N = nums.size();
        int low = 0;
        int high = N-1;

        while(low <= high) {
            int mid = (low + high) >> 1;

            bool left_is_smaller = mid == 0 || nums[mid-1] < nums[mid];
            bool right_is_smaller = mid == N - 1 || nums[mid] > nums[mid+1];

            if(left_is_smaller && right_is_smaller) { // peak
                return mid;
            } else if(left_is_smaller && !right_is_smaller) { // peak on right
                low = mid + 1;
            } else if(!left_is_smaller && right_is_smaller) { // peak on left
                high = mid - 1;
            } else { // both sides have peak
                low = mid + 1;
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
165. Compare Version Numbers
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level 
revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        if(version1 == version2) return 0;

        stringstream stream_version1(version1);
        stringstream stream_version2(version2);

        vector<int> token_version1, token_version2;
        string temp;
        while(getline(stream_version1, temp, '.')) token_version1.push_back(stoi(temp));
        while(getline(stream_version2, temp, '.')) token_version2.push_back(stoi(temp));

        int token1_size = token_version1.size();
        int token2_size = token_version2.size();

        int N = max(token1_size, token2_size);
        for(int i = 0; i < N; i++) {
            int token1 = i < token1_size ? token_version1[i] : 0;
            int token2 = i < token2_size ? token_version2[i] : 0;
            if(token1 > token2) {
                return 1;
            } else if(token1 < token2) {
                return -1;
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
166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction, 
return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

/*
    Submission Date: 2017-06-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string fractionToDecimal(long long numerator, long long denominator) {
        if(numerator == 0) return "0";
        
        unordered_map<int, int> m;
        string sign = ((numerator < 0) ^ (denominator < 0)) ? "-" : "";
        
        string res = "";
        
        numerator = abs(numerator);
        denominator = abs(denominator);
        int num_of_digits = numerator < denominator ? 1: floor(log10(numerator/denominator)) + 1;
        
        while(numerator) {
            if(m.count(numerator)) {
                res = res.substr(0, m[numerator]) + "(" + res.substr(m[numerator]) + ")";
                break;
            }
            m[numerator] = res.size();
            res += to_string(numerator/denominator);
            numerator %= denominator;
            numerator *= 10;
        }
        
        string rem = res.substr(num_of_digits);
        res = sign + res.substr(0, num_of_digits) + (rem.size() ? "." : "") + rem;
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
167. Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order, find two numbers such that they 
add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where 
index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not 
zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int N = numbers.size();
        int low = 0;
        int high = N-1;
        while(low < high) {
            int curr_sum = numbers[low] + numbers[high];
            if(curr_sum == target) {
                return {low + 1, high + 1};
            } else if(curr_sum < target) {
                low++;
            } else {
                high--;
            }
        }   
        return {};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
168. Excel Sheet Column Title
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB 

/*
    Submission Date: 2017-07-26
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        return n == 0 ? "" : convertToTitle((n-1)/26) + string(1, ((n-1) % 26) + 'A');
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
169. Majority Element
Given an array of size n, find the majority element. The majority element is the element that appears more 
than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> value_to_freq;
        int max_freq_value = nums.front();
        for(auto num: nums) {
            value_to_freq[num]++;
            if(value_to_freq[num] > value_to_freq[max_freq_value])
                max_freq_value = num;
        }
        return max_freq_value;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
171. Excel Sheet Column Number
Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
        return s == "" ? 0 : titleToNumber(s.substr(0, s.size() - 1))*26 + (s[s.size()-1] - 'A' + 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
172. Factorial Trailing Zeroes
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        return n == 0 ? 0 : n/5 + trailingZeroes(n/5);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
173. Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

/*
    Submission Date: 2017-07-26
    Runtime: 22 ms
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

class BSTIterator {
    vector<TreeNode*> path_;
public:
    BSTIterator(TreeNode *root) {
        TreeNode* curr = root;
        while(curr) {
            path_.push_back(curr);
            curr = curr -> left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !path_.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* curr = path_.back();
        path_.pop_back();

        int ret_val = curr -> val;

        curr = curr -> right;
        while(curr) {
            path_.push_back(curr);
            curr = curr -> left;
        }

        return ret_val;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
174. Dungeon Game
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. 
The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned 
in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point 
drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these 
rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health 
(positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or 
downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows 
the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)  -3  3
-5  -10 1
10  30  -5 (P)

Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room 
where the princess is imprisoned.

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int rows = dungeon.size();
        if(rows == 0) return 0;

        int cols = dungeon.front().size();
        vector<vector<int>> hp(rows + 1, vector<int>(cols + 1, INT_MAX));
        hp[rows][cols - 1] = 1;
        hp[rows - 1][cols] = 1;
        
        for(int i = rows-1; i >= 0; i--) {
            for(int j = cols-1; j >= 0; j--) {
                hp[i][j] = max(1, min(hp[i+1][j], hp[i][j+1]) - dungeon[i][j]);
            }
        }
        
        return hp[0][0];
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    string concat(const vector<string>& nums_str) {
        return accumulate(nums_str.begin(), nums_str.end(), string(), [](const string& memo, const string& el){ return memo + el; });
    }

    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "0";
        int N = nums.size();
        vector<string> nums_str(N);
        transform(nums.begin(), nums.end(), nums_str.begin(), [](const int& num){ return to_string(num); });
        sort(nums_str.begin(), nums_str.end(), [](const string& lhs, const string& rhs){
            return lhs + rhs > rhs + lhs;        
        });

        if(nums_str.front()[0] == '0') return "0";
        return concat(nums_str);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". 
When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> freq;
        for(int i = 0; i <= (int)s.size() - 10; i++) {
            string seq = s.substr(i, 10);
            freq[seq]++;
        }

        vector<string> res;
        for(auto kv: freq) {
            if(kv.second > 1) {
                res.push_back(kv.first);
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    return 0;
}