
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
459. Repeated Substring Pattern
Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies 
of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
/*
    Submission Date: 2018-06-09
    Runtime: 53 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int N = s.size();
            
        for(int i = 1; i <= N/2; i++) {
            if(N % i == 0) {
                // N can be split into parts containing i elements
                string pos = "";
                string part = s.substr(0, i);
                for(int j = 0; j < N/i; j++) {
                    pos += part;
                }
                
                if(s == pos) return true;
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
461. Hamming Distance
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 2^31.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        while(x && y) {
            res += (x % 2) != (y % 2); // check if last bit are different
            x /= 2;
            y /= 2;
        }
        
        while(x) {
            x &= (x-1); // y is all zeros so just count number of ones in x
            res++;
        }
        
        while(y) {
            y &= (y-1); // x is all zeros so just count number of ones in y
            res++;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
462. Minimum Moves to Equal Array Elements II
Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, 
where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:

Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
/*
    Submission Date: 2018-07-01
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    O(nlogn) given that it is sorted compute the sum and say that is the lhs_cost
    rhs_cost = 0. as i decreases, there is a block of width i+1 and height diff
    that is removed from lhs_cost and a block of width N-i-1 and height diff that
    is added to the rhs_cost

    compute the lhs_cost, rhs_cost for all i and take the minimum.
    */
    typedef long long ll;
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        ll lhs_cost = 0;
        for(const auto& e: nums) lhs_cost += nums.back() - e;
        ll res = lhs_cost;
        
        ll rhs_cost = 0;
        int N = nums.size();
        for(int i = N-2; i >= 0; i--) {
            int diff = nums[i+1] - nums[i];
            lhs_cost -= diff*(i+1);
            rhs_cost += diff*(N-i-1);
            res = min(res, lhs_cost + rhs_cost);
        }
        return res;
    }
};

class Solution2 {
public:
    /*
    proof is suppose x is between two numbers (y, z where y <= z) 
    then u can say the sum of deviation is (x-y) + (z-x) = z - y. 
    so given an array of size n, u can just keep removing the min and max elements 
    which would be equivalent to finding the median as it is the x between all the pairs of y,z.
    (need y,z to be as far apart as possible in order to ensure x is between them)
    */
    int minMoves2_sort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        int N = nums.size();
        for(int i = 0; i < N/2; i++) {
            res += abs(nums[i] - nums[N-i-1]);
        }
        return res;
    }

    int minMoves2(vector<int>& nums) {
        int res = 0;
        int N = nums.size();
        nth_element(nums.begin(), nums.begin() + N/2, nums.end());
        
        int median = nums[N/2];
        
        for(const auto& e: nums) {
            res += abs(e - median);
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
463. Island Perimeter
You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. 
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and 
there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" (water inside that isn't 
connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height 
don't exceed 100. Determine the perimeter of the island.

Example:

[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

/*
    Submission Date: 2018-05-31
    Runtime: 245 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,-1,1};
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int res = 0;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == 0) continue;
                for(int k = 0; k < 4; k++) {
                    int new_x = dx[k] + j;
                    int new_y = dy[k] + i;
                    // if out of bounds or is a zero element, add one
                    if(new_x < 0 || new_x >= grid[0].size() || new_y < 0 || new_y >= grid.size() || 
                       grid[new_y][new_x] == 0) {
                        res++;
                    }
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
475. Heaters
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be wa
/*
    Submission Date: 2018-06-24
    Runtime: 73 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution2 {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(houses.empty()) return 0;
        
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int N = houses.size();
        int M = heaters.size();
        vector<int> dp(N, INT_MAX);
        // heaters[j] is the smallest heater greater than houses[i]
        for(int i = 0, j = 0; i < N && j < M;) {
            if(heaters[j] >= houses[i]) {
                dp[i] = heaters[j] - houses[i];
                i++;
            } else {
                j++;
            }
        }
        
        // heaters[j] is the largest element smaller than houses[i]
        for(int i = N-1, j = M-1; i >= 0 && j >= 0;) {
            if(heaters[j] <= houses[i]) {
                dp[i] = min(dp[i], houses[i] - heaters[j]);
                i--;
            } else {
                j--;
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(houses.empty()) return 0;
        
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int i = 0;
        int N = heaters.size();
        
        int res = -1;
        for(const auto& house: houses) {
            while(i + 1 < N && abs(heaters[i+1] - house) <= abs(heaters[i] - house)) i++;
            res = max(res, abs(heaters[i] - house));
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
476. Number Complement
Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
Example 1:
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    // flip all bits then find the highest power of 2. Make that and all bits below it to 1 and AND it with the previous number.
    int findComplement(int num) {
        return ~num & ((1 << (int)log2(num) + 1) - 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
479. Largest Palindrome Product
Find the largest palindrome made from the product of two n-digit numbers.

Since the result could be very large, you should return the largest palindrome mod 1337.

Example:

Input: 2

Output: 987

Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

Note:

The range of n is [1,8].
/*
    Submission Date: 2018-06-24
    Runtime: 713 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    typedef long long ll;
    int largestPalindrome(int n) {
        if(n == 1) return 9;
        
        ll x = pow(10, n) - 1LL; // 99
        ll max_x = x*x;
        
        ll lower = pow(10, n-1); // 10
        ll upper = x; // 99
        while(x) {
            // take a string of n digits and reverse + concat to get string of 2n digits
            string s = to_string(x);
            string rev = s;
            reverse(rev.begin(), rev.end());
            ll num = stoll(s + rev);
            if(num > max_x) { x--; continue; }
            
            // use upper instead of sqrt(num) as upper is larger
            for(ll fact = upper; fact > lower; fact--) {
                /* fact*fact >= num ensures that fact is greater than the second factor and
                    we do not redo calculation on the lower factors e.g num = 20 fact = 5
                    5*5 >= 20 (takes in 5 and 4)
                    fact = 4
                    4*4 < 20 (does not reconsider lower factors as they have already been checked)
                    
                    fact*fact >= num
                    fact >= num/fact (upper > num/fact)
                */
                if(num/fact < lower || fact*fact < num) break;
                
                if(num % fact == 0) {
                    return num % 1337;
                }
            }
            x--;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
482. License Key Formatting
You are given a license key represented as a string S which consists only alphanumeric character and dashes. 
The string is separated into N+1 groups by N dashes.

Given a number K, we would want to reformat the strings such that each group contains exactly K characters, 
except for the first group which could be shorter than K, but still must contain at least one character. 
Furthermore, there must be a dash inserted between two groups and all lowercase letters should be converted to uppercase.

Given a non-empty string S and a number K, format the string according to the rules described above.

Example 1:
Input: S = "5F3Z-2e-9-w", K = 4

Output: "5F3Z-2E9W"

Explanation: The string S has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.
Example 2:
Input: S = "2-5g-3-J", K = 2

Output: "2-5G-3J"

Explanation: The string S has been split into three parts, each part has 2 characters except the first part as 
it could be shorter as mentioned above.
Note:
The length of string S will not exceed 12,000, and K is a positive integer.
String S consists only of alphanumerical characters (a-z and/or A-Z and/or 0-9) and dashes(-).
String S is non-empty.
/*
    Submission Date: 2018-06-09
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cctype>

using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string s = "";
        // remove dashes and lower case letter
        for(const auto& c: S) {
            if(c == '-') continue;
            s.push_back(toupper(c));
        }
        
        int N = s.size();
        int first_size = N % K;
        
        string res = "";
        res.reserve(N + (N - 1)/2);
        for(int i = 0; i < N; i++) {
            if(i > 0 && (i - first_size) % K == 0) res.push_back('-');
            res.push_back(s[i]);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
485. Max Consecutive Ones
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
/*
    Submission Date: 2018-06-03
    Runtime: 37 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int curr = 0;
        int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 1) {
                curr++;
                res = max(res, curr);
            } else {
                curr = 0;
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
491. Increasing Subsequences
Given an integer array, your task is to find all the different possible increasing 
subsequences of the given array, and the length of an increasing subsequence should be at least 2 .

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
Note:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered 
as a special case of increasing sequence.
/*
    Submission Date: 2017-03-11
    Runtime: 286 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> findSubsequences(const vector<int>& nums) {
        int N = nums.size();
        vector<vector<vector<int>>> dp(N);
        vector<vector<int>> res;
        set<vector<int>> used;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i] >= nums[j]) {
                    for(auto seq: dp[j]) {
                        seq.push_back(nums[i]);
                        dp[i].push_back(seq);
                    }
                }
            }
            dp[i].push_back({nums[i]});
        }
        
        for(auto vec: dp) {
            for(auto seq: vec) {
                if(seq.size() >= 2 && !used.count(seq)) {
                    res.push_back(seq);
                    used.insert(seq);
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
492. Construct the Rectangle
For a web developer, it is very important to know how to design a web page's size. So, given a specific rectangular web 
page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

1. The area of the rectangular web page you designed must equal to the given target area.

2. The width W should not be larger than the length L, which means L >= W.

3. The difference between length L and width W should be as small as possible.
You need to output the length L and the width W of the web page you designed in sequence.
Example:
Input: 4
Output: [2, 2]
Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the 
length L is 2, and the width W is 2.
Note:
The given area won't exceed 10,000,000 and is a positive integer
The web page's width and length you designed must be positive integers.
/*
    Submission Date: 2018-06-07
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        for(int i = sqrt(area); i >= 1; i--) {
            if(area % i == 0) return {area/i, i};
        }
        return {};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
495. Teemo Attacking
In LOL world, there is a hero called Teemo and his attacking can make his enemy Ashe be in 
poisoned condition. Now, given the Teemo's attacking ascending time series towards Ashe and 
the poisoning time duration per Teemo's attacking, you need to output the total time that Ashe is in poisoned condition.

You may assume that Teemo attacks at the very beginning of a specific time point, and makes 
Ashe be in poisoned condition immediately.

Example 1:
Input: [1,4], 2
Output: 4
Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be poisoned immediately. 
This poisoned status will last 2 seconds until the end of time point 2. 
And at time point 4, Teemo attacks Ashe again, and causes Ashe to be in poisoned status for another 2 seconds. 
So you finally need to output 4.
Example 2:
Input: [1,2], 2
Output: 3
Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be poisoned. 
This poisoned status will last 2 seconds until the end of time point 2. 
However, at the beginning of time point 2, Teemo attacks Ashe again who is already in 
poisoned status. 
Since the poisoned status won't add up together, though the second poisoning attack will 
still work at time point 2, it will stop at the end of time point 3. 
So you finally need to output 3.
Note:
You may assume the length of given time series array won't exceed 10000.
You may assume the numbers in the Teemo's attacking time series and his poisoning time duration 
per attacking are non-negative integers, which won't exceed 10,000,000.
/*
    Submission Date: 2018-07-01
    Runtime: 103 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if(timeSeries.empty()) return 0;
        
        int N = timeSeries.size();
        
        int res = duration;
        for(int i = 1; i < N; i++) {
            res += min(duration, timeSeries[i] - timeSeries[i-1]);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
496. Next Greater Element I
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for 
nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.
/*
    Submission Date: 2018-06-02
    Runtime: 11 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    /*
        For a stack of decreasing number, if there is a number x encountered.
        All the numbers in the stack that x is greater than will have their return value to be x
        and x is placed in the stack. This means there is no number in the stack that is less than x
        eg [1,3,4,2,3]
         []     1 => [1]
         [1]    3 => [3]    update greater(1) = 3
         [3]    4 => [4]    update greater(3) = 4
         [4]    2 => [4,2]
         [4,2]  3 => [4,3]  update greater(2) = 3
    */
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        if(nums.empty()) return {};
        
        int N = findNums.size();
        // decreasing numbers
        stack<int> stk;
        
        unordered_map<int,int> val_to_greater_val;
        for(const auto& x: nums) {
            while(!stk.empty() && stk.top() < x) {
                val_to_greater_val[stk.top()] = x;
                stk.pop();
            }
            
            stk.push(x);
        }
        
        vector<int> res;
        for(const auto& x: findNums) {
            res.push_back(val_to_greater_val.count(x) ? val_to_greater_val[x] : -1);
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
500. Keyboard Row
Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.


American keyboard


Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
Note:
You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // Have a map of character to row. Loop through each string and check if all the characters come from the same row.
    vector<string> findWords(vector<string>& words) {
        vector<string> v{"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        unordered_map<char, int> m;

        for(int i = 0; i < v.size(); i++) {
            for(const auto& c: v[i]) m[c] = i;
        }

        vector<string> res;
        for(const auto& s: words) {
            int ind = -1;
            bool can_add = true;
            for(const auto& c: s) {
                if(ind == -1) ind = m[tolower(c)];
                if(m[tolower(c)] != ind) {
                    can_add = false;
                    break;
                }
            }

            if(can_add) res.push_back(s);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
501. Find Mode in Binary Search Tree
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
/*
    Submission Date: 2018-06-09
    Runtime: 15 ms
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
    typedef pair<int,int> pii;
    
    /*
    inorder traversal where if the current element is the same as the last then
    increase the frequency else reset it. if the frequency is greater than res
    frequency, then change res else if the frequency is the same than push back
    to res
    */
    void help(TreeNode* node, pii& curr, vector<pii>& res) {
        if(node == NULL) return;
        help(node->left, curr, res);
        
        if(curr.first == -1 || curr.second != node->val) {
            curr = {1, node->val};
        } else {
            curr.first++;
        }
        
        if(curr.first > res[0].first) {
            res = {curr};
        } else if(curr.first == res[0].first) {
            res.push_back(curr);
        }
        
        help(node->right, curr, res);
    }
    
    vector<int> findMode(TreeNode* root) {
        if(root == NULL) return {};
        
        vector<pii> res = {{0, INT_MIN}};
        pii curr = {-1, INT_MIN};
        help(root, curr, res);
    
        vector<int> v_i;
        v_i.reserve(res.size());
        for(const auto& p: res) v_i.push_back(p.second);
        return v_i;
    }
};
int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
504. Base 7
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].
/*
    Submission Date: 2018-06-08
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";
        
        string sgn = num < 0 ? "-" : "";
        num = abs(num);
        
        string res = "";
        while(num) {
            res.push_back((num % 7) + '0');
            num /= 7;
        }
        
        reverse(res.begin(), res.end());
        return sgn + res;
    }
};

int main() {
    return 0;
}