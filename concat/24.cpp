
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
572. Subtree of Another Tree
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values 
with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The 
tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
/*
    Submission Date: 2018-06-09
    Runtime: 29 ms
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
    void serialize(TreeNode* node, string& res) {
        if(node == NULL) {
            res += "null,";
        } else {
            res += to_string(node->val) + ",";
            serialize(node->left, res);
            serialize(node->right, res);
        }
    }
    
    // check if s == t or s contains a subtree t
    bool isSubtree(TreeNode* s, TreeNode* t) {
        string s1 = "", s2 = "";
        serialize(s, s1);
        serialize(t, s2);
        return s1 == s2 || s1.find("," + s2) != string::npos;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
575. Distribute Candies
Given an integer array with even length, where different numbers in this array represent different kinds of candies. 
Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and 
sister. Return the maximum number of kinds of candies the sister could gain.
Example 1:
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 
Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1]. 
The sister has two different kinds of candies, the brother has only one kind of candies. 
Note:

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].
/*
    Submission Date: 2018-05-31
    Runtime: 247 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // Count the number of distinct candies. Return the min of this and the max size of the array which is candies.size()/2.
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> st(candies.begin(), candies.end());
        return min(candies.size()/2, st.size());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this 
subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array 
sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

/*
    Submission Date: 2017-05-13
    Runtime: 52 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
            int N = nums.size();
            vector<int> cpy(N);
            copy(nums.begin(), nums.end(), cpy.begin());
            sort(nums.begin(), nums.end());

            int i;
            for(i = 0; i < N; i++) {
                if(nums[i] != cpy[i]) break;
            }

            int j;
            for(j = N-1; j >= 0; j--) {
                if(nums[j] != cpy[j]) break;
            }

        return max(j - i + 1, 0);
    }
};

int main() {
    Solution s;
    vector<int> v{2, 6, 4, 8, 10, 9, 15};
    cout << s.findUnsortedSubarray(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
582. Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This 
is just like a tree structure. Only one process has PPID that is 0, which means this process 
has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains 
PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list 
of PIDs of processes that will be killed in the end. You should assume that when a process 
is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.
/*
    Submission Date: 2017-05-13
    Runtime: 166 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        int N = pid.size();
        for(int i = 0; i < N; i++) {
            int _ppid = ppid[i];
            int _pid = pid[i];

            if(m.find(_ppid) == m.end()) {
                m[_ppid] = {_pid};
            } else {
                m[_ppid].push_back(_pid);
            }
        }

        vector<int> result{kill};
        int i = 0;
        while(i < result.size()) {
            int current = result[i];
            if(m.find(current) != m.end()) { // non leaf
                vector<int> children = m[current];
                for(auto c: children) {
                    result.push_back(c);
                }
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution s;
    vector<int> pid{1, 3, 10, 5, 4, 1};
	vector<int> ppid{3, 0, 5, 3, 10, 5};
    int kill = 5;
    vector<int> t = s.killProcess(pid, ppid, kill);
	for(auto l: t) cout << l << " ";
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
583. Delete Operation for Two Strings
Given two words word1 and word2, find the minimum number of steps required to 
make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

/*
    Submission Date: 2017-05-13
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int row = word2.size() + 1;
        int col = word1.size() + 1;
        int dp[501][501];
        for(int i = 0; i < row; i++) dp[i][0] = i;
        for(int i = 0; i < col; i++) dp[0][i] = i;

        for(int i = 1; i < row; i++) {
            for(int j = 1; j < col; j++) {
                if(word2[i - 1] == word1[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + 1;
                }
            }
        }
        
        return dp[row - 1][col - 1];
    }
};

int main() {
	Solution s;
    cout << s.minDistance("sea", "eat");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
592. Fraction Addition and Subtraction
Given a string representing an expression of fraction addition 
and subtraction, you need to return the calculation result in string 
format. The final result should be irreducible fraction. If your final 
result is an integer, say 2, you need to change it to the format of 
fraction that has denominator 1. So in this case, 2 should be 
converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'. 
So does the output.
Each fraction (input and output) has format ±numerator/denominator. 
If the first input fraction or the output is positive, then '+' will 
be omitted.
The input only contains valid irreducible fractions, where the 
numerator and denominator of each fraction will always be in the 
range [1,10]. If the denominator is 1, it means this fraction is 
actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed 
to be valid and in the range of 32-bit int.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <cassert>

using namespace std;

typedef long long ll;
struct Fraction {
    ll num, den;
};

class Solution {
public:
    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    ll lcm(ll a, ll b) {
        return a*b/gcd(a,b);
    }

    // a/b + c/d = (a*lcm(b,d)/b + c*lcm(b,d)/d)/lcm(b,d)
    // 1/4 + 1/16 = (1*16/4 + 1*16/16)/16 = (4+1)/16
    // 1/3 + 2/4 = (1*12/3 + 2*12/4)/12 = (4+6)/12

    // (a*(b*d/gcd(b,d))/b + c*(b*d/gcd(b,d))/d)/(b*d/gcd(b,d))
    // (a*d/gcd(b,d) + c*b/gcd(b,d))/(b*d/gcd(b,d))
    // ((a*d + c*b)/gcd(b,d)*gcd(b,d))/(b*d)
    // (a*d + b*c)/(b*d)
    Fraction add(Fraction a, Fraction b) {
        return {a.num*b.den + a.den*b.num, a.den*b.den};
    }

    Fraction reduce(Fraction a) {
        int gcd_num_den = gcd(abs(a.num), a.den);
        return {a.num/gcd_num_den, a.den/gcd_num_den};
    }

    string fractionAddition(string s) {
        vector<Fraction> v;
        int N = s.size();
        bool is_negative = false;
        for(int i = 0; i < N;) {
            // s[i] is beginning of numerator which is either '-' (negative num), '+' (positive num) or
            // a number (positive num and is start of string)
            Fraction fr;
            is_negative = s[i] == '-';

            if(s[i] == '+' || is_negative) {
                i++;
            }

            ll curr = 0;
            while(isdigit(s[i])) {
                curr = curr*10 + (s[i] - '0');
                i++;
            }

            fr.num = is_negative ? -curr : curr;
            // s[i] is the '/' followed by a number so end i where the next operator starts
            assert(s[i++] == '/');

            curr = 0;
            while(isdigit(s[i]) && i < N) {
                curr = curr*10 + (s[i] - '0');
                i++;
            }

            fr.den = curr;
            v.push_back(fr);
        }

        Fraction res = v.front();
        res = reduce(res);
        for(int i = 1; i < v.size(); i++) {
            res = add(res, v[i]);
            res = reduce(res);
        }

        return to_string(res.num) + "/" + to_string(res.den);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the 
four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array 
with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four 
equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

class Solution {
public:
    int distSq(vector<int>& a, vector<int>& b) {
        return pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2);
    }
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<int> dist;
        vector<vector<int>> v{p1, p2, p3, p4};
        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 4; j++) {
                dist.push_back(distSq(v[i], v[j]));
            }
        }

        // given points a,b,c,d -> dist will contain ab ac ad bc bd cd
        // out of these 6 distances, there are 4 distances which are the side distances (s)
        // and 2 that are hypotenuse (h)
        // s^2 + s^2 = h^2

        assert(dist.size() == 6);
        map<int,int> freq;
        for(auto e: dist) freq[e]++;

        if(freq.size() != 2) return false;
        int s = freq.begin() -> first;
        int h = next(freq.begin(), 1) -> first;
        return 2*s == h;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-05-27
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    double eucl_sq(vector<int>& p1, vector<int>& p2) {
        return pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2);
    }

    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // distance squared
        vector<double> dist{eucl_sq(p1, p2), eucl_sq(p1, p3), eucl_sq(p1, p4), eucl_sq(p2, p3), eucl_sq(p2, p4), eucl_sq(p3, p4)};

        sort(dist.begin(), dist.end());

        // should result in 4 equal length sides and two longer sides that are the diagonals 
        bool equal_sides = dist[0] == dist[1] && dist[1] == dist[2] && dist[2] == dist[3];
        bool non_zero_sides = dist[0] > 0;

        // pythagoras: x^2 + x^2 = y^2 => 2x^2 = y^2
        bool correct_diagonals = dist[4] == dist[5] &&  2*dist[0] == dist[4];
        return equal_sides && non_zero_sides && correct_diagonals;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
594. Longest Harmonious Subsequence
We define a harmonious array is an array where the difference between its maximum value and its minimum 
value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all 
its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.
/*
    Submission Date: 2017-05-27
    Runtime: 109 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        int max_len = 0;
        for(int d: nums) {
            int current = 0;
            if(freq.find(d) != freq.end()) {
                current += freq[d];
                freq[d] += 1;
            } else {
                freq[d] = 1;
            }

            int adj = 0;
            if(freq.find(d-1) != freq.end()) {
                adj = max(adj, freq[d-1]);
            }

            if(freq.find(d+1) != freq.end()) {
                adj = max(adj, freq[d+1]);
            }

            if(adj == 0) continue;
            current += adj + 1;
            max_len = max(current, max_len);
        }
        return max_len;
    }
};

int main() {
    vector<int> v{1,3,2,2,5,2,3,7};
    Solution s;
    cout << s.findLHS(v) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
598. Range Addition II
Given an m * n matrix M initialized with all 0's and several update operations.

Operations are represented by a 2D array, and each operation is represented by an array with 
two positive integers a and b, which means M[i][j] should be added by one for all 0 <= i < a 
and 0 <= j < b.

You need to count and return the number of maximum integers in the matrix after performing 
all the operations.

Example 1:
Input: 
m = 3, n = 3
operations = [[2,2],[3,3]]
Output: 4
Explanation: 
Initially, M = 
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]

After performing [2,2], M = 
[[1, 1, 0],
 [1, 1, 0],
 [0, 0, 0]]

After performing [3,3], M = 
[[2, 2, 1],
 [2, 2, 1],
 [1, 1, 1]]

So the maximum integer in M is 2, and there are four of it in M. So return 4.
Note:
The range of m and n is [1,40000].
The range of a is [1,m], and the range of b is [1,n].
The range of operations size won't exceed 10,000.
/*
    Submission Date: 2017-05-29
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        for(vector<int> op: ops) {
            m = min(m, op[0]);
            n = min(n, op[1]);
        }
        return m*n;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
599. Minimum Index Sum of Two Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of 
favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there 
is a choice tie between answers, output all of them with no order requirement. You could assume 
there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with 
index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.
/*
    Submission Date: 2017-05-29
    Runtime: 103 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> m;
        for(int i = 0; i < list1.size(); i++) {
            m[list1[i]] = i;
        }
        
        vector<string> res;
        int min_index_sum = -1;
        for(int i = 0; i < list2.size(); i++) {
            string s2 = list2[i];
            if(m.count(s2)) {
                int new_sum = i + m[s2];
                if(min_index_sum == -1) {
                    min_index_sum = new_sum;
                    res.push_back(s2);
                    continue;
                }
                
                if(new_sum == min_index_sum) {
                    res.push_back(s2);
                } else if(new_sum < min_index_sum) {
                    min_index_sum = new_sum;
                    res.clear();
                    res.push_back(s2);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<string> v1{"Shogun","Tapioca Express","Burger King","KFC"};
    vector<string> v2{"Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"};
    vector<string> t = s.findRestaurant(v1, v2);
    cout << t.size() << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
604. Design Compressed String Iterator
Design and implement a data structure for a compressed string iterator. 
It should support the following operations: next and hasNext.

The given compressed string will be in the form of each letter followed 
by a positive integer representing the number of this letter existing in 
the original uncompressed string.

next() - if the original string still has uncompressed characters, return 
the next letter; Otherwise return a white space.
hasNext() - Judge whether there is any letter needs to be uncompressed.

Example:

StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");

iterator.next(); // return 'L'
iterator.next(); // return 'e'
iterator.next(); // return 'e'
iterator.next(); // return 't'
iterator.next(); // return 'C'
iterator.next(); // return 'o'
iterator.next(); // return 'd'
iterator.hasNext(); // return true
iterator.next(); // return 'e'
iterator.hasNext(); // return false
iterator.next(); // return ' '

/*
    Submission Date: 2017-06-11
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

class StringIterator {
vector<pair<char, long long>> v_;
int index_;
public:
    StringIterator(string compressedString) {
        index_ = 0;
        int len = compressedString.size();
        int i = 0;
        while(i < len) {
            char c = compressedString[i];
            i++;
            string rep = "";
            while(i < len && isdigit(compressedString[i])) {
                rep += compressedString[i];
                i++;
            }
            
            long long times = stoll(rep);
            // cout << c << ' ' << times << endl;
            v_.emplace_back(c, times);
        }
    }
    
    char next() {
        if(!hasNext()) return ' ';
        pair<char, long long>& p = v_[index_];
        p.second--;
        if(p.second == 0) index_++;
        return p.first;
    }
    
    bool hasNext() {
        return index_ < v_.size();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
605. Can Place Flowers
Suppose you have a long flowerbed in which some of the plots are planted 
and some are not. However, flowers cannot be planted in adjacent plots - 
they would compete for water and both would die.

Given a flowerbed (represented as an array containing 0 and 1, where 0 means 
empty and 1 means not empty), and a number n, return if n new flowers can be 
planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True
Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False
Note:
The input array won't violate no-adjacent-flowers rule.
The input array size is in the range of [1, 20000].
n is a non-negative integer which won't exceed the input array size.

/*
    Submission Date: 2017-06-11
    Runtime: 19 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        vector<int> v;

        // v.push_back(-1);
        for(int i = 0; i < len; i++) {
            if(flowerbed[i]) {
                v.push_back(i);
            }
        }
        // v.push_back(len);

        int v_len = v.size();
        for(int i = 1; i < v_len; i++) {
            int num_zeros = v[i] - v[i-1] - 1;
            // cout << v[i] << " " << v[i-1] << " " << num_zeros << " " << (num_zeros - 1)/2 << endl;
            if(num_zeros > 0) {
                int diff = (num_zeros - 1)/2;
                n -= diff;
            }
        }

        if(v_len) {
            n -= v[0]/2;
            // cout << n << endl;
            n -= (len - v[v_len - 1] - 1)/2;
            // cout << n << endl;
        } else {
            n -= (len+1)/2;
        }

        // cout << "n" << n << endl;
        return n <= 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
606. Construct String from Binary Tree
You need to construct a string consists of parenthesis and integers from a 
binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you 
need to omit all the empty parenthesis pairs that don't affect the one-to-one 
mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one 
mapping relationship between the input and the output.

/*
    Submission Date: 2017-06-11
    Runtime: 15 ms
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
    string tree2str(TreeNode* t) {
        if(t == NULL) return "";
        string root = to_string(t -> val);
        string left = tree2str(t -> left);
        string right = tree2str(t -> right);
        
        if(left.empty() && right.empty())
            return root;
        if(!left.empty() && right.empty())
            return root + "(" + left + ")";
        
        return root + "(" + left + ")" + "(" + right + ")";
    }
};

int main() {
    Solution s;
    return 0;
}