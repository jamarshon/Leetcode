/*
47. Permutations II
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void permuteUnique(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();
        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        for(int i = index; i < len; i++) {
            if(i != index && ((index == 0 && nums[i-1] == nums[i]) || nums[i] == nums[index])) continue;
            swap(nums[i], nums[index]);
            permuteUnique(nums, index + 1, res);
            swap(nums[i], nums[index]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        permuteUnique(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v;
    vector<vector<int>> t;

    v = {1,1,2};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 3

    v = {0,1,0,0,9};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 20

    v = {2,2,1,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 6


    v = {-1,2,0,-1,1,0,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 630
    return 0;
}