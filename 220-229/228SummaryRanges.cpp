/*
228. Summary Ranges
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

/*
    Submission Date: 2017-08-06
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int N = nums.size();
        for(int i = 0; i < N;) {
            int start, prev;
            start = prev = nums[i++];
            while(i < N && nums[i] == prev + 1) {
                prev++;
                i++;
            }
            if(start == prev) {
                res.push_back(to_string(start));
            } else {
                res.push_back(to_string(start) + "->" + to_string(prev));
            }
        }
        return res;
    }
};

int main() {
    return 0;
}