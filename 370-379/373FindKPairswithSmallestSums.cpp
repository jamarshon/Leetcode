/*
373. Find K Pairs with Smallest Sums
You are given two integer arrays nums1 and nums2 sorted in ascending 
order and an integer k.

Define a pair (u,v) which consists of one element from the first 
array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]

/*
    Submission Date: 2017-08-30
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        typedef pair<int,int> pii;
        
        if(nums1.empty() || nums2.empty()) return {};
        
        auto cmp = [&nums1, &nums2](const pii& lhs, const pii& rhs){
            int lhs_sum = nums1[lhs.first] + nums2[lhs.second];
            int rhs_sum = nums1[rhs.first] + nums2[rhs.second];
            return lhs_sum > rhs_sum;
        };
        
        int N1 = nums1.size(), N2 = nums2.size();

        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<pii> res;
        for(int i = 0; i < N1 && i < k; i++) pq.emplace(i, 0);

        while(res.size() < k && !pq.empty()) {
            pii top = pq.top();
            pq.pop();
            
            res.emplace_back(nums1[top.first], nums2[top.second]);

            if(top.second + 1 < N2) pq.emplace(top.first, top.second + 1);
        }

        return res;
    }
};

int main() {
    return 0;
}