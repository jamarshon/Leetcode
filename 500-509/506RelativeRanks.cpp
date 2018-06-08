/*
506. Relative Ranks
Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who 
will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal". 
For the left two athletes, you just need to output their relative ranks according to their scores.
Note:
N is a positive integer and won't exceed 10,000.
All the scores of athletes are guaranteed to be unique.
/*
    Submission Date: 2018-06-08
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        map<int,int, greater<int>> m;
        for(int i = 0; i < nums.size(); i++) m[nums[i]] = i;
        
        vector<string> rep{"Gold Medal", "Silver Medal", "Bronze Medal"};
        
        vector<string> res(nums.size());
        int ind = 0;
        for(const auto& kv: m) {
            res[kv.second] = ind < 3 ? rep[ind] : to_string(ind+1);
            ind++;
        }
        
        return res;
    }
};


int main() {
    return 0;
}