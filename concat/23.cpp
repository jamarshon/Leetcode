
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
486. Predict the Winner
Given an array of scores that are non-negative integers. Player 1 picks one of 
the numbers from either end of the array followed by the player 2 and then 
player 1 and so on. Each time a player picks a number, that number will not be 
available for the next player. This continues until all the scores have been 

Given an array of scores, predict whether player 1 is the winner. You can assume 

Example 1:
Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. If he chooses 2 (or 
1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then 
player 1 will be left with 1 (or 2). So, final score of player 1 is 1 + 2 = 3, 
and player 2 is 5. Hence, player 1 will never be the winner and you need to 



Example 2:
Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 
and 7. No matter which number player 2 choose, player 1 can choose 233.Finally, 
player 1 has more score (234) than player 2 (12), so you need to return True 



Note:

1 <= length of the array <= 20. 
Any scores in the given array are non-negative integers and will not exceed 
If the scores of both players are equal, then player 1 is still the winner.
/*
    Submission Date: 2018-07-10
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
public:
    /*
    dp[i][j] is the maximum value from [i, j]. 
    it is either take from the left :
        nums[i] + min <- because opponent wants to minimize your next score
            dp[i+2][j] // opponent chose nums[i+1] from dp[i+1][j]
            dp[i+1][j-1] // opponent chose nums[j-1] from dp[i+1][j]
    or take from the right
        nums[j] + min <- because opponent wants to minimize your next score
            dp[i][j-2] // opponent chose nums[j-1] from dp[i][j-1]
            dp[i+1][j-1] // opponent chose nums[i] from dp[i][j-1]
    
    return the best score you can get dp[0][N-1] and the best score the opponent can
    get which is just sum - your score
    */
    bool PredictTheWinner(vector<int>& nums) {
        typedef long long ll;
        int N = nums.size();
        if(N == 0) return false;
        if(N == 1) return true;
        
        vector<vector<ll>> dp(N, vector<ll>(N));
        for(int gap = 0; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                if(gap == 0) dp[i][j] = nums[i];
                else if(gap == 1) dp[i][j] = max(nums[i], nums[j]);
                else { // j - i = gap >= 2 
                    dp[i][j] = max(
                        nums[i] + min(dp[i+2][j], dp[i+1][j-1]),
                        nums[j] + min(dp[i][j-2], dp[i+1][j-1])
                    );
                }
            }
        }
        
        ll sum = 0;
        for(const auto& e: nums) sum += e;
        return dp[0][N-1] >= sum - dp[0][N-1]; 
    }
};

class Solution {
public:
    /*
    same as before except using a sum array cause if take left
    nums[i] then opponent will get the value dp[i+1][j] hence you get sum from [0,j] - opponent value
    and same if take right
    */
    typedef long long ll;
    
    // sum from [i, j]
    ll GetSum(const vector<ll>& sum, int i, int j) {
        return i == 0 ? sum[j] : sum[j] - sum[i-1];
    }
    
    bool PredictTheWinner(vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return false;
        if(N == 1) return true;
        
        vector<ll> sum(N); // sum[i] = sum from [0, i]
        sum[0] = nums[0];
        for(int i = 1; i < N; i++) sum[i] = sum[i-1] + nums[i];
        
        vector<vector<ll>> dp(N, vector<ll>(N));
        for(int gap = 0; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                if(gap == 0) dp[i][j] = nums[i];
                else {
                    dp[i][j] = max(
                        nums[i] + GetSum(sum, i+1, j) - dp[i+1][j],
                        nums[j] + GetSum(sum, i, j-1) - dp[i][j-1]
                    );
                }
            }
        }
        
        return dp[0][N-1] >= sum[N-1] - dp[0][N-1]; 
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
498. Diagonal Traverse
Given a matrix of M x N elements (M rows, N columns), return all elements of the 


Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation:




Note:

The total number of elements of the given matrix will not exceed 10,000.
/*
    Submission Date: 2018-07-09
    Runtime: 52 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    all numbers in a diagonal indices add up to the same number (e.g i + j == x)
    the max is N-1 + M-1 = N - M - 2
    so for x = [0, N - M - 2], start from the top row go down i = [0, N) and see if
    x - i produces a j that is within the bounds [0, M).
    0 <= x - i < M means 
    x - M < i && i <= x
    0 <= i && i < N
    
    i > max(-1, x - M)
    i < min(N, x + 1)
    
    This creates all the diagonals going down.
    reverse the even diagonals and return
    */
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int N = matrix.size();
        int M = matrix[0].size();
        
        vector<int> res;
        
        for(int x = 0; x < N + M - 1; x++) {
            int sz = res.size();
            for(int i = max(0, x - M + 1); i < min(N, x + 1); i++) {
                res.push_back(matrix[i][x-i]); 
            }
            if(x % 2 == 0) reverse(res.begin() + sz, res.end());
        }
        
        return res;
    }
};

class Solution2 {
    int d[2][2] = {{-1, 1}, {1,-1}};
    bool up = true;
public:
    /*
    toggle between going up and down when hit out of bounds
    to find the new coordinate
        if going up: 
            if hits the right boundary then can't keep going right so go down
            else keep going right
        if going down:
            if hits the bottom boundary then can't keep going down so go right
            else keep going down
    */
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int N = matrix.size();
        int M = matrix[0].size();
        
        vector<int> res;
        int x = 0, y = 0;
        for(int i = 0; i < N*M; i++) {
            res.push_back(matrix[y][x]);
            int new_x = x + d[up][0];
            int new_y = y + d[up][1];
            if(0 <= new_x && new_x < M && 0 <= new_y && new_y < N) {
                x = new_x;
                y = new_y;
            } else {
                if(up) {
                    if(new_x == M) y++;
                    else x++;
                } else {
                    if(new_y == N) x++;
                    else y++;
                }
                up ^= 1;
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