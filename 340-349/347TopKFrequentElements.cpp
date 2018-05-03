/*
347. Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
/*
    Submission Date: 2018-05-02
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> val_to_freq;
        map<int,vector<int>> freq_to_val;
        for(auto e: nums) val_to_freq[e]++;
        for(auto kv: val_to_freq) freq_to_val[kv.second].push_back(kv.first);
        vector<int> res;
        for(auto it = freq_to_val.rbegin(); it != freq_to_val.rend(); it++) {
            for(auto e: it->second) {
                res.push_back(e);
                if(res.size() == k) break;
            }
            if(res.size() == k) break;
        }
        return res;
    }
};

int main() {
    return 0;
}