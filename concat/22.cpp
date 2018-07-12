
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
448. Find All Numbers Disappeared in an Array
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
/*
    Submission Date: 2018-06-04
    Runtime: 155 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for(int i = 0; i < nums.size(); i++) {
            while(nums[nums[i]-1] != nums[i]) swap(nums[nums[i]-1], nums[i]);
        }
        
        vector<int> res;
        for(int i = 0; i < nums.size(); i++) {
            if(i + 1 != nums[i]) res.push_back(i+1);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
451. Sort Characters By Frequency
Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
/*
    Submission Date: 2018-06-30
    Runtime: 201 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> letter_to_freq;
        for(const auto& c: s) letter_to_freq[c]++;
        sort(s.begin(), s.end(), [&letter_to_freq](const char& lhs, const char& rhs) {
            return letter_to_freq[lhs] == letter_to_freq[rhs] ? lhs > rhs : letter_to_freq[lhs] > letter_to_freq[rhs];
        });
        return s;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
453. Minimum Moves to Equal Array Elements
Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, 
where a move is incrementing n - 1 elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
/*
    Submission Date: 2018-06-07
    Runtime: 51 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    increasing everything besides a number is equivalent to decreasing the number by 1
    so if all the numbers have to be decreased to equal the same
    value, then they should all be decreased until it reaches the smallest element in 
    the array
    
    e.g 1 4 7
    the 4 needs to be decreased 3 times and the 7 decreased 6 times to get 
    (4-1) + (7-1) = 9
    
    or
    
    let an array be A = {A[0], A[1], A[2], ... A[N]} and Z = {Z[0], Z[1], Z[2], Z[N]}
    where Z[i] means the number of rows where the element at i is zero then if x is
    the final value which all the elements equal to then
    
    A[0] + Z[1] + Z[2] + ... + Z[N] = x
    Z[0] + A[1] + Z[2] + ... + Z[N] = x
    Z[0] + Z[1] + A[2] + ... + Z[N] = x
    ...
    
    subtracting one row from another gets
    Z[0] - Z[1] + A[1] - A[0] = 0
    Z[1] - Z[0] = A[1] - A[0]
    
    let Z[0] = 0, 
    Z[i] = A[i] - A[i-1] + Z[i-1]
        = A[i] - A[i-1] + (A[i-1] - A[i-2] + Z[i-2])
        = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + Z[i-3]))
        = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + .... -A[1] + (A[1] - A[0] + Z[0])))
        ...
        = A[i] + (A[i-1] - A[i-1]) + (A[i-2] - A[i-2]) + .... (A[1] - A[1]) - A[0]
        = A[i] - A[0]
    
    The result is number of rows or sum Z[i] from i = [0, N]
    Z[i] must be >= 0 as number of rows can't be negative. to minimize then
    A[i] - A[0] should have A[0] as large as possible with having A[i] become < 0
    so A[0] should be the smallest in the array as A[min_ind] - A[min_ind] >= 0
    */
    int minMoves(vector<int>& nums) {
        if(nums.empty()) return 0;
        int min_el = *min_element(nums.begin(), nums.end());
        int res = 0;
        for(int i = 0; i < nums.size(); i++) {
            res += nums[i] - min_el;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
454. 4Sum II
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, 

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 
500. All integers are in the range of -228 to 228 - 1 and the result is 

Example:
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
/*
    Submission Date: 2018-07-08
    Runtime: 104 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /*
    O(n^2) generate all n^2 sums of A and B and put in hashmap of sum to frequency
    generate all n^2 sums of C and D and see if the sum exists in hashmap, if it does
    then res increases by the frequency as the frequency represents how many ways to 
    get that sum
    */
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> sum_A_B;
        for(const auto& a: A) {
            for(const auto& b: B) {
                sum_A_B[a + b]++;
            }
        }
        
        int res = 0;
        for(const auto& c: C) {
            for(const auto& d: D) {
                if(sum_A_B.count(-c-d)) {
                    res += sum_A_B[-c-d];
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
455. Assign Cookies
Assume you are an awesome parent and want to give your children some cookies. But, you should give 
each child at most one cookie. Each child i has a greed factor gi, which is the minimum size of a cookie that 
the child will be content with; and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to the 
child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Note:
You may assume the greed factor is always positive. 
You cannot assign more than one cookie to one child.

Example 1:
Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:
Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.
/*
    Submission Date: 2018-06-08
    Runtime: 42 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int res = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int j = 0;
        for(int i = 0; i < g.size(); i++) {
            while(j < s.size() && g[i] > s[j]) j++;
            if(j >= s.size()) break;
            j++;
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
477. Total Hamming Distance
The Hamming distance between two integers is the number of positions at which 

Now your job is to find the total Hamming distance between all pairs of the 


Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 



Note:

Elements of the given array are in the range of 0  to 10^9
Length of the array will not exceed 10^4.
/*
    Submission Date: 2018-07-08
    Runtime: 40 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    o(n) for the ith bit count how many 0 and how many 1 there are
    suppose there are x 0's and y 1's, then there are total x*y pairs
    because for every value in x, it can pair y values in y.
    */
    int totalHammingDistance(vector<int>& nums) {
        int N = nums.size();
        int res = 0;
        for(int i = 0; i < 31; i++) {
            int one_cnt = 0;
            for(const auto& n: nums) {
                bool one = n & (1 << i);
                one_cnt += one;
            }
            
            res += one_cnt*(N - one_cnt);
        }
        return res;
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
481. Magical String
A magical string S consists of only '1' and '2' and obeys the following rules:


The string S is magical because concatenating the number of contiguous 



The first few elements of string S is the following:
S = "1221121221221121122……"



If we group the consecutive '1's and '2's in S, it will be:


1   22  11  2  1  22  1  22  11  2  11  22 ......


and the occurrences of '1's or '2's in each group are:


1   2      2    1   1    2     1    2     2    1    2    2 ......



You can see that the occurrence sequence above is the S itself. 



Given an integer N as input, return the number of '1's in the first N number in 


Note:
N will not exceed 100,000.



Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains 
/*
    Submission Date: 2018-07-10
    Runtime: 8 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<char, char> t{{'1', '2'}, {'2', '1'}};
public:
    /*
    if(s[i] == '1') the last character should only occur once so push the opposite
    else the last character should occur twice so push the same then the opposite
    
    keep track of s.size() as well as the one_cnt
    */
    int magicalString(int n) {
        if(n == 0) return 0;
        int one_cnt = 1;
        string s = "1";
        int i = 0;
        while(s.size() < n) {
            if(s[i] == '1') {
                s.push_back(t[s.back()]);
                if(s.back() == '1') one_cnt++;
            } else { // s[i] == '2'
                s.push_back(s.back());
                if(s.back() == '1') one_cnt++;
                if(s.size() < n) { 
                    s.push_back(t[s.back()]);
                    if(s.back() == '1') one_cnt++;
                }
            }
            i++;
        }
        
        return one_cnt;
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