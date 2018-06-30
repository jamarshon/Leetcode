
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
415. Add Strings
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int carry = 0;
        int i = num1.size() - 1, 
            j = num2.size() - 1;
        
        while(i >= 0 || j >= 0) {
            int x = carry;
            if(i >= 0) x += (num1[i] - '0');
            if(j >= 0) x += (num2[j] -'0');
            
            carry = x / 10;
            res.push_back((x % 10) + '0');
            
            i--;
            j--;
        }
        
        if(carry > 0) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
419. Battleships in a Board
Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. 
You may assume the following rules:
You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 
(N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?
/*
    Submission Date: 2018-05-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
    N by checking if the element to the left and to the top of board[i][j] isn't a 'X'.
    If there is one then it means it is continuing a ship so it should not be counted.
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if(board.empty()) return 0;
        int res = 0;
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                if(board[i][j] == 'X' && (j == 0 || board[i][j-1] != 'X') && (i == 0 || board[i-1][j] != 'X')) {
                    res++;
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
433. Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices from 
"A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), 
where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. 
A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the 
minimum number of mutations needed to mutate from "start" to "end". If there is no 
such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    bool isConnect(string s1, string s2) {
        int diff_count = 0;
        for(int i = 0, len = s1.size(); i < len; i++) {
            diff_count += s1[i] != s2[i];
        }
        return diff_count == 1;
    }
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, vector<string>> graph;

        bank.push_back(start);
        int N = bank.size();
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                if(isConnect(bank[i], bank[j])) {
                    graph[bank[i]].push_back(bank[j]);
                    graph[bank[j]].push_back(bank[i]);
                }
            }
        }

        unordered_set<string> visited;
        queue<pair<string, int>> q;
        q.emplace(start, 0);
        visited.insert(start);

        string curr;
        int dist;
        while(!q.empty()) {
            tie(curr, dist) = q.front();
            // cout << curr << ' ' << dist << endl;
            q.pop();
            if(curr == end) return dist;
            for(auto neighbor: graph[curr]) {
                if(visited.count(neighbor)) continue;
                q.emplace(neighbor, dist + 1);
                visited.insert(neighbor);
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
434. Number of Segments in a String
Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5
/*
    Submission Date: 2018-06-09
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cctype>

using namespace std;

class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        for(int i = 0; i < s.size(); i++) {
            if(!isspace(s[i]) && (i == 0 || isspace(s[i-1]))) {
                res++;
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
437. Path Sum III
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
/*
    Submission Date: 2018-06-09
    Runtime: 28 ms
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
    /*
    returns path sums from this root down (not necessarily reach leaf)
    this is {root->val, 
            root->val + l for all l from f(root->left),
            root->val + r for all r from f(root->left),
            }
    first one meets terminate the path here, second one means this extends a left path
    and the last one extends a right path
    check if any of the new paths equal sum to increase res
    */
    vector<int> help(TreeNode* root, int sum, int& res) {
        if(root == NULL) return {};
        vector<int> left = help(root->left, sum, res);
        vector<int> right = help(root->right, sum, res);
        
        if(root->val == sum) res++;
        
        vector<int> paths;
        paths.reserve(1 + left.size() + right.size());
        paths.push_back(root->val);
        
        for(const auto& l: left) {
            paths.push_back(root->val + l);
            if(paths.back() == sum) res++;
        }
        
        for(const auto& r: right) {
            paths.push_back(root->val + r);
            if(paths.back() == sum) res++;
        }
        
        return paths;
    }
    
    int pathSum(TreeNode* root, int sum) {
        int res = 0;
        help(root, sum, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
438. Find All Anagrams in a String
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p 
will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

/*
    Submission Date: 2017-08-06
    Runtime: 106 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int M = s.size();
        int N = p.size();
        
        if(M < N) return res;
        unordered_map<char, int> freq, curr_freq;
        
        for(auto c: p) freq[c]++;
        
        for(int i = 0; i < N; i++) curr_freq[s[i]]++;
        
        int low = 0;
        int high = N;
        while(high <= M) {
            bool is_match = true;
            if(curr_freq.size() == freq.size()) {
                for(auto kv: freq) {
                    if(curr_freq.count(kv.first) && curr_freq[kv.first] == kv.second) continue;
                    is_match = false;
                    break;
                }
            } else {
                is_match = false;
            }
            
            if(is_match) res.push_back(low);
            if(high == M) break;
            char to_erase = s[low++];
            curr_freq[s[high++]]++;
            if(curr_freq[to_erase] == 1) curr_freq.erase(to_erase);
            else curr_freq[to_erase]--;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
441. Arranging Coins
You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed integer.

Example 1:

n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.
Example 2:

n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.
/*
    Submission Date: 2018-06-09
    Runtime: 33 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    /*
    sum of 0 to x = x(x+1)/2
    x(x+1)/2 = n
    x^2 + x - 2n = 0

    quadratic formula: x = (-1 + sqrt(8n + 1))/2
    */
    int arrangeCoins(int n) {
        return (-1 + sqrt(8LL*n + 1))/2;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
442. Find All Duplicates in an Array
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and 
others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

/*
    Submission Date: 2017-08-06
    Runtime: 176 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int N = nums.size();
        vector<int> res;
        for(int i = 0; i < N; i++) {
            while(nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
    
        for(int i = 0; i < N; i++) {
            if(nums[i] != i + 1) {
                res.push_back(nums[i]);
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
443. String Compression
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
Note:
All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    since length of 1 are not included the compressed string will always be less than
    the full string e.g a12 is smaller than aaa...
    hence it is safe to just overwrite existing string
    */
    int compress(vector<char>& s) {
        int write = 0;
        int N = s.size();
        for(int i = 0; i < N;) {
            int start = i;
            while(i < N && s[start] == s[i]) i++;
            string freq = to_string(i - start);
            s[write++] = s[start];
            if(i - start > 1) for(const auto& d: freq) s[write++] = d;
        }
        return write;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
447. Number of Boomerangs
Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) 
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
/*
    Submission Date: 2018-06-08
    Runtime: 284 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;
        int N = points.size();
        
        for(int i = 0; i < N; i++) {
            /*
            From this point find the distance of all points from this point.
            if there are m points that are at the same distance from this point,
            if m is less than 2 then it can't be used else it is permutation without
            repetition which is n!/(n-r)! = m!/(m-2)! = m*(m-1)
            */
            unordered_map<int, int> dist_sq_m;
            for(int j = 0; j < N; j++) {
                if(j == i) continue;
                int dist_sq = pow(points[i].first - points[j].first, 2) + 
                    pow(points[i].second - points[j].second, 2);
                dist_sq_m[dist_sq]++;
            }
            
            for(const auto& kv: dist_sq_m) {
                if(kv.second < 2) continue;
                res += kv.second*(kv.second - 1);
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