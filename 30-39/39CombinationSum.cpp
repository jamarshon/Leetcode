/*
39. Combination Sum
Given a set of candidate numbers (C) (without duplicates) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7, 
A solution set is: 
[
  [7],
  [2, 2, 3]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void combinationSum(vector<int>& candidates, int sum, vector<vector<int>>& res, vector<int>& curr, int index) {
        for(int i = index; i < candidates.size(); i++) {
            int c = candidates[i];
            if(c > sum) break;

            curr.push_back(c);
            if(c == sum) {
                res.push_back(curr);
                curr.pop_back();
                break;
            } else {
                combinationSum(candidates, sum - c, res, curr, i);
                curr.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> curr;
        combinationSum(candidates, target, res, curr, 0);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}