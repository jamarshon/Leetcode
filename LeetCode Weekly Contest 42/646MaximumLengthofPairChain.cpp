/*
646. Maximum Length of Pair Chain
You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be 
formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given 
pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
Note:
The number of given pairs will be in the range [1, 1000].

/*
    Submission Date: 2017-07-23
    Runtime: 82 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](vector<int> v1, vector<int> v2){
            return v1[1] < v2[1];
        });
        
        vector<vector<int>> res;
        
        for(auto p: pairs) {
            if(res.empty() || res.back()[1] < p[0]) {
                res.push_back(p);
            }
        }
        
        return res.size();
    }
};

int main() {
    return 0;
}