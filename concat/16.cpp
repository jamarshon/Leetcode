
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given 
prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] 
is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of 
size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution2 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        set<int> res{1};
        vector<int> last_prime(K, 1);

        while(res.size() < n) {
            int min_j = 0;
            for(int j = 1; j < K; j++) {
                if(last_prime[j] * primes[j] < last_prime[min_j] * primes[min_j]) {
                    min_j = j;
                }
            }

            res.insert(last_prime[min_j] * primes[min_j]);
            last_prime[min_j] = *res.upper_bound(last_prime[min_j]);
        }

        return *res.rbegin();
    }
};

class Solution3 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        // idx[j] corresponds to the first element in dp which 
        // primes[j]*dp[idx[j]] >= dp[i]
        vector<int> dp(n), idx(K, 0);
        dp[0] = 1;

        for(int i = 1; i < n; i++) {
            int best_j = 0;
            for(int j = 0; j < K; j++) {
                // avoid duplicates e.g 4*3 and 6*2
                if(dp[idx[j]] * primes[j] == dp[i-1]) idx[j]++; 
                if(dp[idx[j]] * primes[j] < dp[idx[best_j]] * primes[best_j]) {
                    best_j = j;
                }
            }
            dp[i] = dp[idx[best_j]] * primes[best_j];
            idx[best_j]++;
        }

        return dp[n-1];
    }
};

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size();
        if(n <= 0 || K <= 0) return 0;

        vector<int> dp(n);
        dp[0] = 1;
        // pair<prime, index in dp>
        auto func =[&dp](const pair<int,int> lhs, const pair<int,int> rhs){ 
            return lhs.first*dp[lhs.second] > rhs.first*dp[rhs.second];
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(func)> pq(func);

        for(int i = 0; i < K; i++) pq.push({primes[i], 0});

        for(int i = 1; i < n; i++) {
            pair<int,int> p;
            do {
                p = pq.top();
                pq.pop();
                dp[i] = p.first*dp[p.second];
                pq.emplace(p.first, p.second + 1);
            } while(p.first * dp[p.second] == dp[i-1]);
            
        }

        return dp[n-1];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
315. Count of Smaller Numbers After Self
You are given an integer array nums and you have to return a 
new counts array. The counts array has the property where 
counts[i] is the number of smaller elements to the right of 
nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
/*
    Submission Date: 2017-08-26
    Runtime: 36 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
public:
    /*
        nlogn using tree
        given arr A, traverse A from N-1 to 0 inserting value into tree
        tree is bst (right greater than root, left smaller than root) but it has properties
        of number of left children and number of duplicates
        this tree represents everything to the right of the current element
        when inserting, every right turn indicates that the current element is greater than
        this node so the number of elements this element is greater than is
        number of duplicates from this node and numbers of left children of this node as 
        left tree <= node < current element

        e.g. [3, 2, 2, 6, 1]
            1(0, 1)
             \
             6(3, 1)
             /
           2(0, 2)
               \
                3(0, 1)
        adding 5 would put it to the right of 3 so 1(0,1), 2(0,2) and 3(0,1) are where it turned right
        (0 + 1) (0 + 2) + (0 + 1) = 4
    */
    struct Node {
        Node* left, *right;
        int num_left, num_dup;
        int val;
        Node(int _val): val(_val), num_left(0), num_dup(1), left(NULL), right(NULL) {}
    };

    Node* insert(Node* root, int val, int& sum) {
        if(root == NULL) {
            return new Node(val);
        } else if(root -> val == val) {
            // duplicate increases and sum increases by number of left children
            root -> num_dup += 1;
            sum += root -> num_left;
        } else if(root -> val > val) {
            // go left so number of left children increases
            root -> num_left += 1;
            root -> left = insert(root -> left, val, sum);
        } else {
            // go right so sum increases by number of duplicates and number of left children
            sum += (root -> num_dup) + (root -> num_left);
            root -> right = insert(root -> right, val, sum);
        }

        return root;
    }

    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();
        vector<int> res(N);
        Node* root = NULL;
        for(int i = N-1; i >= 0; i--) {
            int sum = 0;
            root = insert(root, nums[i], sum); 
            res[i] = sum;
        }
        return res;
    }
};

class Solution {
    typedef pair<int,int> pii;
public:
    void mergeSort(vector<pii>& v, vector<pii>& sp, vector<int>& res,
            int start, int end) {
        /* for a subarray of v for indices [start, end], there
        is a left subarray [start, mid] and a right subarray
        [mid + 1, end]. If an item in the left subarray (left[i])
        is less than an item in the right subarray (right[j]), 
        then left[i] is the next element in the sorted sequence and
        there are j elements that are smaller than left[i] that is
        to the right of left[i] so res[indexof(left[i])] += j

        use <= because [0,j) should not include numbers that equal
        to left[i]
        */
        if(start >= end) return;
        int mid = start + (end - start)/2;
        mergeSort(v, sp, res, start, mid);
        mergeSort(v, sp, res, mid + 1, end);

        int idx = 0;
        int s1 = start, s2 = mid + 1;
        int e1 = mid + 1, e2 = end + 1;
        while(s1 < e1 || s2 < e2) {
            // left goes before right as right is empty (s2 >= e2)
            // or start of left is less than or equal to start of right
            if(s2 >= e2 || (s1 < e1 && v[s1].first <= v[s2].first)) {
                sp[idx++] = v[s1];
                res[v[s1].second] += s2 - mid - 1;
                s1++;
            } else {
                sp[idx++] = v[s2];
                s2++;
            }
        }
        
        for(int i = 0; i < idx; i++) v[i + start] = sp[i];
    }

    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();

        vector<pii> v, sp(N);

        for(int i = 0; i < N; i++) {
            v.emplace_back(nums[i], i);
        }

        vector<int> res(N, 0);
        
        mergeSort(v, sp, res, 0, N - 1);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{5,2,6,1};
    v = s.countSmaller(v);
    for(auto e: v) cout << e << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
318. Maximum Product of Word Lengths
Given a string array words, find the maximum value of 
length(word[i]) * length(word[j]) where the two words do not 
share common letters. You may assume that each word will contain 
only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
/*
    Submission Date: 2017-08-26
    Runtime: 42 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int res = 0;
        int N = words.size();
        
        // dp[i] is the bit representation of words[i] where bit at index i corresponds
        // with the ith letter of [a,b,c,...] that is in words[i]
        // e.g abcf would 0...100111
        
        vector<int> dp(N, 0);
        for(int i = 0; i < N; i++) {
            for(int j = 0, word_len = words[i].size(); j < word_len; j++) {
                dp[i] |= 1 << (words[i][j] - 'a');
            }
        }
        
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                if((dp[i] & dp[j]) == 0) { // no intersection
                    res = max(res, int(words[i].size() * words[j].size()));
                }
            }
        }
        
        return res;
    }
};
    
class Solution2 {
public:
    int maxProduct(vector<string>& words) {
        int res = 0;
        int N = words.size();
        for(int i = 0; i < N; i++) {
            unordered_set<char> word_i(words[i].begin(), words[i].end());
            for(int j = i + 1; j < N; j++) {
                bool intersect = false;
                for(int k = 0; k < words[j].size(); k++) {
                    if(word_i.count(words[j][k])) {
                        intersect = true;
                        break;
                    }
                }
                
                if(intersect) continue;
                int pos_res = words[i].size()*words[j].size();
                res = max(res, pos_res);
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
334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of 
length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else 
return false.
Your algorithm should run in O(n) time complexity and O(1) space 
complexity.

Examples:
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
/*
    Submission Date: 2017-08-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        we have a vector of size 3 where smallest[i] indicates
        the smallest last element of a sequence of size i

        similar to LIS

        for example if smallest is {1, _, _} and a 2 is found
        it becomes {1, 2, _} but if a 0 is found it becomes
        {0, 2, _}. Notice how it stops replacing as soon as finds
        a smallest[i] <= num. this is to prevent replacing multiple
        values.
    */
    bool increasingTriplet(vector<int>& nums) {
        vector<int> smallest(3, 0);        
        int size = 0;
        
        for(auto num: nums) {
            bool found_replace = false;
            for(int i = 0; i < size; i++) {
                if(num <= smallest[i]) {
                    smallest[i] = num;
                    found_replace = true;
                    break;
                }
            }
            
            if(found_replace) continue;
            
            if(size == 0 || smallest[size - 1] < num) {
                smallest[size++] = num;
            }
            
            if(size == 3) return true;
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
386. Lexicographical Numbers
Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size 
may be as large as 5,000,000.

/*
    Submission Date: 2017-08-21
    Runtime: 239 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void lexicalOrder(int curr, int n, vector<int>& res) {
        if(curr > n) return;

        int limit = min(n + 1, curr == 1 ? 10: curr+10);
        for(int i = curr; i < limit; i++) {
            res.push_back(i);
            lexicalOrder(i*10, n, res);
        }
    }
    
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        lexicalOrder(1, n, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return 
it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

/*
    Submission Date: 2017-08-21
    Runtime: 93 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char,int> letter_to_first_ind;
        set<int> st;
        for(int i = 0; i < s.size(); i++) {
            if(letter_to_first_ind.count(s[i])) { 
                // we've seen this letter before so we remove it from the set
                if(st.count(letter_to_first_ind[s[i]])) {
                    st.erase(letter_to_first_ind[s[i]]);
                }
            } else {
                letter_to_first_ind[s[i]] = i;
                st.insert(i);
            }
        }

        return st.empty() ? -1 : *st.begin();
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
392. Is Subsequence
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in 
both s and t. t is potentially a very long (length ~= 500,000) string, 
and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the 
original string by deleting some (can be none) of the characters 
without disturbing the relative positions of the remaining characters. 
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, 
and you want to check one by one to see if T has its subsequence. 
In this scenario, how would you change your code?

/*
    Submission Date: 2017-08-30
    Runtime: 69 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_index = 0, t_index = 0;
        int s_len = s.size(), t_len = t.size();
        
        while(s_index < s_len && t_index < t_len) {
            if(s[s_index] == t[t_index]) {
                s_index++;
            }
            t_index++;
        }
        
        return s_index == s_len;
    }

    bool isSubsequence2(string s, string t) {
        int N = s.size(), M = t.size();
        vector<vector<bool>> dp(N + 1, vector<bool>(M + 1, false));
        for(int i = 0; i <= M; i++) dp[0][i] = true;
    
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        return dp[N][M];
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