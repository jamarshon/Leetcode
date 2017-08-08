/*
220. Contains Duplicate III
iven an array of integers, find out whether there are two distinct indices 
i and j in the array such that the absolute difference between nums[i] and nums[j] 
is at most t and the absolute difference between i and j is at most k.

/*
    Submission Date: 2017-08-07
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution2 {
public:
    // O(nlogk) maintain window of k and do range search on it
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k < 0 || t < 0) return false;
        
        map<int, int> m;
        int N = nums.size();
        for(int i = 0; i < N; i++) {
            int above = (nums[i] > INT_MAX - t) ? INT_MAX : nums[i] + t;
            int below = (nums[i] < INT_MIN + t) ? INT_MIN : nums[i] - t;
            
            if(above < below) swap(above, below);
            
            auto below_it = m.lower_bound(below);
            auto above_it = m.upper_bound(above);
            
            while(below_it != above_it) {
                if(below_it -> second > 0) return true;
                below_it++;
            }
            
            m[nums[i]]++;
            if(i >= k) {
                m[nums[i-k]]--;
            }
        }
        return false;
    }
};

class Solution1 {
public:
    // nlogn + check if adjacent numbers are close enough in index
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k < 0 || t < 0) return false;
        
        int N = nums.size();
        vector<pair<int,int>> v;
        for(int i = 0; i < N; i++) {
            v.emplace_back(nums[i], i);
        }
        
        sort(v.begin(), v.end(), [](const pair<int,int>& lhs, const pair<int,int>& rhs){
            return lhs.first < rhs.first;
        });
        
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                if(v[i].first < 0 && v[j].first > INT_MAX + v[i].first) break;
                
                int diff = v[j].first - v[i].first;
                int idx_diff = abs(v[j].second - v[i].second);
                if(diff > t) break;
                if(idx_diff <= k) return true;
            }
        }
        return false;
    }
};

class Solution {
public:
    // numbers 0,1,2 and bucket of 3 they all get put into bucket[1]
    // since negative numbers are allowed we remap to nums[i] - INT_MIN as bucket 0 should include
    // INT_MIN, we check adjacent bucket to see if across bucket values work
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(k < 1 || t < 0) return false;

        unordered_map<long, long> m;
        int N = nums.size();
        for(int i = 0; i < N; i++) {
            long remapped_num = (long)nums[i] - INT_MIN;
            long bucket = remapped_num/((long)t + 1);

            bool another_el_same_bucket = m.count(bucket);
            bool bucket_below_close_enough = m.count(bucket-1) && remapped_num - m[bucket-1] <= t;
            bool bucket_above_close_enough = m.count(bucket+1) && m[bucket+1] - remapped_num<= t;
            if(another_el_same_bucket || bucket_below_close_enough || bucket_above_close_enough) {
                return true;
            }

            if(m.size() >= k) {
                long last_bucket = ((long)nums[i-k] - INT_MIN)/((long) t + 1);
                m.erase(last_bucket);
            }
            
            m[bucket] = remapped_num;
        }
        return false;
    }
};

int main() {
    return 0;
}