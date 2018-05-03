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