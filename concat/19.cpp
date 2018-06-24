
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
341. Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers 
or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next 
should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by 
next should be: [1,4,6].
/*
    Submission Date: 2018-05-02
    Runtime: 19 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <stack>
#include <vector>
#include <tuple>

using namespace std;

class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
public:
    stack<pair<int, const vector<NestedInteger>*>> stk;
    vector<NestedInteger> cp;
    NestedIterator(vector<NestedInteger> &nestedList) {
        cp = nestedList;
        stk.emplace(0, &cp);
    }
    
    void traverse() {
        while(!stk.empty()) {
            int ind;
            const vector<NestedInteger>* v;
            tie(ind, v) = stk.top();
            stk.pop();
            if(ind < v->size()) {
                if(v->at(ind).isInteger()) {
                    stk.emplace(ind, v);
                    return;
                } else {
                    stk.emplace(ind + 1, v);
                    stk.emplace(0, &(v->at(ind).getList()));
                }
            }
        }    
    }
    
    int next() {
        traverse();
        
        int ind;
        const vector<NestedInteger>* v;
        tie(ind, v) = stk.top();
        stk.pop();
        stk.emplace(ind + 1, v);
        
        return v->at(ind).getInteger();
    }

    bool hasNext() {
        traverse();
        return !stk.empty();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
342. Power of Four
Given an integer (signed 32 bits), write a function to check 
whether it is a power of 4.

Example:
Given num = 16, return true. Given num = 5, return false.

Follow up: Could you solve it without loops/recursion?
/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfFour(int x) {
        // (x & (x-1)) == 0 checks for power of two as it would 
        // series of zeros with only one 1. so x-1 will AND with nothing
        // leaving zero
        // geometric series 1 + 4 + 16 + 64 + 256 -> a = 1, r = 4, n = 5
        // sum{i = 0 to n-1}(a*r^i = a*(1-r^n/(1-r)
        // so let x = sum{i = 0 to n-1}((1-4^n)/(1-4))
        // x = (4^n - 1)/3
        // 3*x = 4^n - 1 <- thus 4^n - 1 must be a multiple of 3
        return x > 0 && (x & (x-1)) == 0 && (x-1) % 3 == 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
343. Integer Break
Given a positive integer n, break it into the sum of at least two positive integers and 
maximize the product of those integers. Return the maximum product you can get.

For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).

Note: You may assume that n is not less than 2 and not larger than 58.
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<int, int> dp;
public:
    int integerBreak(int N) {
        return integerBreak(N,N);
    }
    
    int integerBreak(int n, int N) {
        if(dp.count(n)) return dp[n];
        
        int res = n == N ? 1 : n;
        for(int i = 1; i < n; i++) {
            res = max(res, i*integerBreak(n-i, N));
        }
        
        return dp[n] = res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
344. Reverse String
Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".
/*
    Submission Date: 2017-03-11
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string reverseString(string s) {
        int N = s.size();
        for(int i = 0; i < N/2; i++) {
            swap(s[i], s[N-i-1]);
        }
        return s;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
345. Reverse Vowels of a String
Write a function that takes a string as input and reverse only 
the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".

/*
    Submission Date: 2017-08-22
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cctype>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
        vector<int> indices;
        for(int i = 0; i < s.size(); i++) {
            if(vowels.count(tolower(s[i]))) {
                indices.push_back(i);
            }
        }
        
        int N = indices.size();
        for(int i = 0; i < N/2; i++) {
            char temp = s[indices[i]];
            s[indices[i]] = s[indices[N- i - 1]];
            s[indices[N - i - 1]] = temp;
        }
        
        return s;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
347. Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
/*
    Submission Date: 2018-05-02
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> val_to_freq;
        map<int,vector<int>> freq_to_val;
        for(auto e: nums) val_to_freq[e]++;
        for(auto kv: val_to_freq) freq_to_val[kv.second].push_back(kv.first);
        vector<int> res;
        for(auto it = freq_to_val.rbegin(); it != freq_to_val.rend(); it++) {
            for(auto e: it->second) {
                res.push_back(e);
                if(res.size() == k) break;
            }
            if(res.size() == k) break;
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
349. Intersection of Two Arrays
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.
/*
    Submission Date: 2018-05-02
    Runtime: 8 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_set<int> st(nums1.begin(), nums1.end());
        for(const auto& e: nums2) {
          if(st.count(e)) {
            res.push_back(e);
            st.erase(e);
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
350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in 
both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your 
algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm 
is better?
What if elements of nums2 are stored on disk, and the memory is limited 
such that you cannot load all elements into the memory at once?
/*
    Submission Date: 2017-09-10
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int>* smaller = &nums1, *greater = &nums2;
        if(smaller -> size() > greater -> size()) swap(smaller, greater);
        
        unordered_map<int,int> smaller_freq;
        for(auto n: *smaller) smaller_freq[n]++;
        
        vector<int> res;
        for(auto n: *greater) {
            if(smaller_freq.count(n) && smaller_freq[n] > 0) {
                smaller_freq[n]--;
                res.push_back(n);
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
354. Russian Doll Envelopes
You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can 
fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
/*
    Submission Date: 2018-05-24
    Runtime: 30 ms
    Difficulty: HARD
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    NlogN sort by width and break ties on height
    For all elements with the same width, apply the changes all at once
    Similar to LIS where dp[i] is the smallest element of sequence of length i
*/
class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());
        vector<int> heights;

        for(int i = 0; i < envelopes.size();) {
            int start = i;
            unordered_map<int, int> index_to_new_val;
            while(i < envelopes.size() && envelopes[i].first == envelopes[start].first) {
                auto it = lower_bound(heights.begin(), heights.end(), envelopes[i].second);
                int dist = it - heights.begin();
                if(!index_to_new_val.count(dist)) index_to_new_val[dist] = envelopes[i].second;
                i++;
            }

            for(const auto& kv: index_to_new_val) {
                if(kv.first < heights.size()) {
                    heights[kv.first] = kv.second;
                } else {
                    heights.push_back(kv.second);
                }
            }
        }
        return heights.size();
    }
};

/*
    N^2 similar to LIS where dp[i] means the longest sequence ending at element i
    Requires a sort first as all elements of smaller width should appear first.
*/
class Solution2 {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end());
        vector<int> dp(envelopes.size(), 1);
        
        for(int i = 0; i < envelopes.size(); i++) {
            for(int j = 0; j < i; j++) {
                if(envelopes[i].first > envelopes[j].first && envelopes[i].second > envelopes[j].second) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        return dp.empty() ? 0 : *max_element(dp.begin(), dp.end());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
357. Count Numbers with Unique Digits
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])
/*
    Submission Date: 2018-05-30
    Runtime: 2 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        let dp[n] denote a number with n digits (no leading zeros) that is completely unique
        dp[0] = 1           {0}
        dp[1] = 9           {1, 2, 3, 4, 5, 6, 8, 9}
        dp[2] = 9*dp[1]     for each number in dp[1], there are 9 numbers to choose from that are not in dp[1].
                            e.g. for dp[1] element 1, there is {10, 12, 13, 14, 15, 16, 17, 18, 19}
        dp[3] = 8*dp[2]     for each number in dp[2], there are 8 numbers to choose from that are not in dp[2]
                            e.g. for dp[2] element 12, there is {120, 123, 124, 125, 126, 127, 128, 129}
        ...
        dp[i] = min(9, 9 - i + 2)*dp[i-1]
        
        the result of length n is just the sum of dp[i] from [0, n]
    */
    int countNumbersWithUniqueDigits(int n) {
        int prev = 1;
        int res = 1;
        for(int i = 1; i <= min(10, n); i++) {
            prev *= min(9, 9 - i + 2);
            res += prev;
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False
/*
    Submission Date: 2018-05-02
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPerfectSquare(int num) {
      long long low = 1;
      long long high = num;
      while(low <= high) {
        long long mid = low + (high-low)/2;
        if(mid*mid == num) {
          return true;
        } else if(mid*mid < num) {
          low = mid + 1;
        } else {
          high = mid -1;
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
368. Largest Divisible Subset
Given a set of distinct positive integers, find the largest subset 
such that every pair (Si, Sj) of elements in this subset satisfies: 
Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)
Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]
/*
    Submission Date: 2017-08-21
    Runtime: 33 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        
        sort(nums.begin(), nums.end());
        int N = nums.size();
        
        vector<int> dp(N, 1), P(N,-1);
        int max_dp_ind = 0;
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i] % nums[j] == 0) {
                    if(dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        P[i] = j;
                    }
                }
            }
            
            if(dp[max_dp_ind] < dp[i]) max_dp_ind = i;
        }
        
        
        vector<int> res(dp[max_dp_ind]);
        int index = res.size();
        for(int i = max_dp_ind; i >= 0; i = P[i]) {
            res[--index] = nums[i];
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
371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.
/*
    Submission Date: 2018-05-02
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <bitset>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
      // include the sign bit.
      bitset<32> res(0);
      bitset<32> aa(a);
      bitset<32> bb(b);

      int carry = 0;
      for(int i = 0; i < 32; i++) {
        int a_d = aa.test(i);
        int b_d = bb.test(i);

        res.set(i, a_d ^ b_d ^ carry);
        carry = (a_d && b_d) || (b_d && carry) || (a_d && carry);
      }

      return res.to_ullong();
    }
};

class Solution2 {
public:
    int getSum(int a, int b) {
        int res = 0;
        int carry = 0;
        
        for(int i = 0; i < 32; i++) {
            const int a_d = (1 << i) & a;
            const int b_d = (1 << i) & b;
            res |= a_d ^ b_d ^ carry;
            carry = ((a_d & b_d) | (b_d & carry) | (a_d & carry)) << 1;
        } 
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
373. Find K Pairs with Smallest Sums
You are given two integer arrays nums1 and nums2 sorted in ascending 
order and an integer k.

Define a pair (u,v) which consists of one element from the first 
array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

/*
    Submission Date: 2017-08-30
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        typedef pair<int,int> pii;
        
        if(nums1.empty() || nums2.empty()) return {};
        
        auto cmp = [&nums1, &nums2](const pii& lhs, const pii& rhs){
            int lhs_sum = nums1[lhs.first] + nums2[lhs.second];
            int rhs_sum = nums1[rhs.first] + nums2[rhs.second];
            return lhs_sum > rhs_sum;
        };
        
        int N1 = nums1.size(), N2 = nums2.size();

        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<pii> res;
        for(int i = 0; i < N1 && i < k; i++) pq.emplace(i, 0);

        while(res.size() < k && !pq.empty()) {
            pii top = pq.top();
            pq.pop();
            
            res.emplace_back(nums1[top.first], nums2[top.second]);

            if(top.second + 1 < N2) pq.emplace(top.first, top.second + 1);
        }

        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
374. Guess Number Higher or Lower
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

-1 : My number is lower
 1 : My number is higher
 0 : Congrats! You got it!
Example:
n = 10, I pick 6.

Return 6.
/*
    Submission Date: 2018-05-02
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int low = 0;
        int high = n;
        while(low <= high) {
            int mid = low + (high-low)/2;
            int status = guess(mid);
            if(status == 0) {
                return mid;
            } else if(status == -1) {
                high = mid - 1;
            } else {
                low = mid + 1;
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
376. Wiggle Subsequence
A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between 
positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than 
two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. 
In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive 
and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is 
obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Examples:
Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
Follow up:
Can you do it in O(n) time?
/*
    Submission Date: 2018-05-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        suppose the number we have is right after <, if we meet a smaller element then just add it to stack
        else if the element is larger than we pop back and add this larger element as it will give a wider
        range of numbers that can follow it
        the same logic applies to >, where if a smaller element is seen just pop back and add it to stack
    */
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> stk1{nums[0]}, stk2{nums[0]};
        for(int i = 1; i < nums.size(); i++) {
            if((stk1.size() % 2 == 0 && stk1.back() <= nums[i]) || 
               (stk1.size() % 2 == 1 && stk1.back() >= nums[i])) {
                stk1.pop_back();
            }
            
            if((stk2.size() % 2 == 1 && stk2.back() <= nums[i]) || 
               (stk2.size() % 2 == 0 && stk2.back() >= nums[i])) {
                stk2.pop_back();
            }
            
            stk1.push_back(nums[i]);
            stk2.push_back(nums[i]);
        }
        
        return max(stk1.size(), stk2.size());
    }
};

int main() {
    return 0;
}