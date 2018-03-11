
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
319. Bulb Switcher
There are n bulbs that are initially off. You first turn on all the bulbs. 
Then, you turn off every second bulb. On the third round, you toggle every 
third bulb (turning on if it's off or turning off if it's on). For the ith 
round, you toggle every i bulb. For the nth round, you only toggle the last 
bulb. Find how many bulbs are on after n rounds.

Example:

Given n = 3. 

At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off]. 

So you should return 1, because there is only one bulb is on.
/*
    Submission Date: 2017-09-10
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int bulbSwitch(int N) {
        return sqrt(N);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
322. Coin Change
You are given coins of different denominations and a total amount of money amount. Write a 
function to compute the fewest number of coins that you need to make up that amount. If that 
amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
/*
    Submission Date: 2017-03-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int N = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        
        dp[0] = 0;
        
        for(int i = 1; i <= N; i++) {
            for(int j = 0; j <= amount; j++) {
                if(j - coins[i-1] >= 0 && dp[j - coins[i-1]] != INT_MAX) { // we can take this coin
                    dp[j] = min(dp[j - coins[i-1]] + 1, dp[j]);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
331. Verify Preorder Serialization of a Binary Tree
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, 
we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", 
where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal 
serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' 
representing null pointer.

You may assume that the input format is always valid, for example it could never contain 
two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false
/*
    Submission Date: 2017-03-11
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
public:
    bool isValidSerialization(string preorder) {
        int count = 0;
        stringstream ss(preorder);
        string temp;
        while(getline(ss, temp, ',')) {
            if(count < 0) return false;
            if(temp == "#") {
                count--;
            } else {
                count++;
            }
        }
        
        return count == -1;
    }
};

int main() {
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
338. Counting Bits
Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num 
calculate the number of 1's in their binary representation and return them as an array.

Example:
For num = 5 you should return [0,1,1,2,1,2].

Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But 
can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like 
__builtin_popcount in c++ or in any other language.
/*
    Submission Date: 2017-03-11
    Runtime: 69 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1, 0);

        for(int i = 1; i <= num; i++) {
            res[i] = res[i/2] + (i % 2);
        }

        return res;
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