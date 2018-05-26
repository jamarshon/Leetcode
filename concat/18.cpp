
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
326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?
/*
    Submission Date: 2018-05-02
    Runtime: 80 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfThree(int n) {
        // 1162261467 largest power of 3 that can be represented by int and all it's factors are powers of 3.
        // a = nq + r where n < r means a % n = r
        // 3^19 % y => 3^19 = n*y + r
        // if y == 3^x, then this only true if r == 0 and n == 3^(19-x)
        return n > 0 && 1162261467 % n == 0;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
328. Odd Even Linked List
Given a singly linked list, group all odd nodes together followed by the even nodes. 
Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity 
and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was in the input. 
The first node is considered odd, the second node even and so on ...
/*
    Submission Date: 2018-05-02
    Runtime: 16 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode *first_odd, *first_even;
        first_odd = first_even = NULL;
        vector<ListNode*> arr{NULL, NULL};
        
        int index = 0;
        while(head) {
            ListNode* temp = head;
            head = head->next;
            temp->next = NULL;
            
            if(index == 0 && first_odd == NULL) {
                first_odd = temp;
            } else if(index == 1 && first_even == NULL) {
                first_even = temp;
            }
            
            if(arr[index] == NULL) arr[index] = temp;
            else{ arr[index]-> next = temp; arr[index] = temp; }
            
            index ^= 1;
        }
        
        if(arr[0]) {
            arr[0]->next = first_even;
        }
        return first_odd;
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
332. Reconstruct Itinerary
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], 
reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, 
the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that has the smallest 
lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller 
lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical 
order.
/*
    Submission Date: 2018-05-02
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:    
    // m is unordered key of 'from' with value of ordered key of 'to' with value frequency
    void recurse(unordered_map<string, map<string,int>>& m, string from, 
                 const int& tickets_to_use, vector<string>& curr, vector<string>& res) {
        if(tickets_to_use == 0) {
            assert(res.empty());
            res = curr;
        } else {
            if (!m.count(from)) return;
        
            for(auto& kv : m[from]) {
                if(kv.second > 0) {
                    // there is a to for from so try to use it
                    kv.second--;
                    curr.push_back(kv.first);
                    recurse(m, kv.first, tickets_to_use - 1, curr, res);
                    // if res isn't empty, then a path was found and return it
                    curr.pop_back();
                    if(!res.empty()) return;
                    kv.second++;
                    
                }
            }
        }
    }
    
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, map<string, int>> m;
        for(auto p: tickets) m[p.first][p.second]++;
        vector<string> res, curr;
        curr.push_back("JFK");
        recurse(m, curr.front(), tickets.size(), curr, res);
        return res;
    }
};


class Solution2 {
public:
    /*
    Eulerian path using Hierholzer's algorithm
    Starting from a vertex, do a dfs. put the vertex in the stack and then loop back outward.
    */
    void recurse(unordered_map<string, multiset<string>>& m, string from, vector<string>& stk) {
        while(!m[from].empty()) {
            const string& to = *(m[from].begin()); 
            m[from].erase(m[from].begin());
            recurse(m, to, stk);
        }

        stk.push_back(from);
    }
    
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, multiset<string>> m;
        for(auto p: tickets) m[p.first].insert(p.second);
        vector<string> stk;
        recurse(m, "JFK", stk);
        reverse(stk.begin(), stk.end());
        return stk;
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