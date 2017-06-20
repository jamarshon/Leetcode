/*
46. Permutations
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void permuteHelper(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();

        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        for(int i = index; i < len; i++) {
            swap(nums[i], nums[index]);
            permuteHelper(nums, index + 1, res);
            swap(nums[i], nums[index]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        permuteHelper(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{1,2,3};
    vector<vector<int>> p = s.permute(v);
    for(auto v2: p) {
        for(auto e: v2) cout << e << ' ';
        cout << endl;
    }
    return 0;
}