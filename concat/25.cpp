
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
609. Find Duplicate File in System
Given a list of directory info including directory path, and all the files 
with contents in this directory, you need to find out all the groups of 
duplicate files in the file system in terms of their paths.

A group of duplicate files consists of at least two files that have exactly 
the same content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, 
f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. Note 
that n >= 1 and m >= 0. If m = 0, it means the directory is just the root 
directory.

The output is a list of group of duplicate file paths. For each group, it 
contains all the file paths of the files that have the same content. A 
file path is a string that has the following format:

"directory_path/file_name.txt"

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", 
"root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]

Note:
No order is required for the final output.

You may assume the directory name, file name and file content only has letters 
and digits, and the length of file content is in the range of [1,50].

The number of files given is in the range of [1,20000].

You may assume no files or directories share the same name in the same directory.

You may assume each given directory info represents a unique directory. Directory 
path and file info are separated by a single blank space.

Follow-up beyond contest:
Imagine you are given a real file system, how will you search files? DFS or BFS?

If the file content is very large (GB level), how will you modify your solution?

If you can only read the file by 1kb each time, how will you modify your solution?

What is the time complexity of your modified solution? 

What is the most time-consuming part and memory consuming part of it? 

How to optimize?

How to make sure the duplicated files you find are not false positive?

/*
    Submission Date: 2017-06-11
    Runtime: 19 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
    pair<string, string> getContent(string& s) {
        int bracket_ind = s.rfind("(") + 1;
        string content = s.substr(bracket_ind, s.size() - bracket_ind - 1);
        string filename = s.substr(0, bracket_ind - 1);
        return make_pair(filename, content);
    }
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        // key content, value file
        unordered_map<string, vector<string>> m;
        for(string path: paths) {
            stringstream ss(path);
            string token;
            string dir = "";
            while(getline(ss, token, ' ')) {
                if(dir.empty()) {
                    dir = token;
                } else {
                    string file = token;
                    pair<string, string> p = getContent(file);
                    if(m.count(p.second)) {
                        m[p.second].push_back(dir + "/" + p.first);
                    } else {
                        m[p.second] = {dir + "/" + p.first};
                    }
                }
            }
        }
        
        vector<vector<string>> res;
        for(pair<string, vector<string>> p: m) {
            if(p.second.size() > 1) res.push_back(p.second);
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
611. Valid Triangle Number
Given an array consists of non-negative integers, your task is to count 
the number of triplets chosen from the array that can make triangles if we 
take them as side lengths of a triangle.

Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

/*
    Submission Date: 2017-06-11
    Runtime: 442 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int count = 0;
        int len = nums.size();
        for(int i = 0; i < len; i++) {
            if(nums[i] == 0) continue;
            for(int j = i + 1; j < len; j++) {
                int sum = nums[i] + nums[j];
                vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), sum);
                
                int index = it - nums.begin() - 1;
                count += max(index - j, 0);
                // cout << index << ' '  << j << ' ' <<count<< endl;
            }
        }
        return count;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
617. Merge Two Binary Trees
Given two binary trees and imagine that when you put one of them to cover the 
other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two 
nodes overlap, then sum node values up as the new value of the merged node. 
Otherwise, the NOT null node will be used as the node of new tree.

Example 1:
Input: 
    Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
         3
        / \
       4   5
      / \   \ 
     5   4   7
Note: The merging process must start from the root nodes of both trees.

/*
    Submission Date: 2017-06-11
    Runtime: 45 ms
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
    TreeNode* mergeTreesHelper(TreeNode* t1, TreeNode* t2) {
        if(t1 == NULL && t2 == NULL) return NULL;
        
        TreeNode* curr = new TreeNode(-1);
        int new_val = -1;
        if(t1 != NULL && t2 != NULL) {
            new_val = t1 -> val + t2 -> val;
        } else if(t1 != NULL) {
            new_val = t1 -> val;
        } else {
            new_val = t2 -> val;
        }
        
        curr -> val = new_val;
        
        TreeNode* left = mergeTreesHelper(t1 ? t1 -> left : NULL, t2 ? t2 -> left : NULL);
        TreeNode* right = mergeTreesHelper(t1 ? t1 -> right : NULL, t2 ? t2 -> right : NULL);
        curr -> left = left;
        curr -> right = right;
        return curr;
    }
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        return mergeTreesHelper(t1, t2);
    }
};

int main() {
    Solution s;
    return 0;
}