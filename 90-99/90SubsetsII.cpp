/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

/*
    Submission Date: 2017-06-25
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void print(vector<T> v) {
    for(auto e: v) cout << e << ' ';
    cout << endl;
}

template <typename T> 
void print2(vector<vector<T>> v) {
    for(auto v2: v) print(v2);
}

class Solution {
public:
    void subsetsWithDupHelper(vector<int>& nums, vector<int>& curr, int index, vector<vector<int>>& res) {
        res.push_back(curr);

        for(int i = index; i < nums.size(); i++) {
            if(i == index || nums[i] != nums[i-1]) {
                curr.push_back(nums[i]);
                subsetsWithDupHelper(nums, curr, i + 1, res);
                curr.pop_back();
            }
            
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> curr;
        sort(nums.begin(), nums.end());
        subsetsWithDupHelper(nums, curr, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v;
    v = {1,2,2};
    vector<vector<int>> v2 = s.subsetsWithDup(v);
    print2(v2);
    return 0;
}