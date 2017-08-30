#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        typedef pair<int,int> pii;
        auto cmp = [&nums1, &nums2](const pii& lhs, const pii& rhs){
            int lhs_sum = nums1[lhs.first] + nums2[lhs.second];
            int rhs_sum = nums1[rhs.first] + nums2[rhs.second];
            return lhs_sum > rhs_sum;
        };

        int N1 = nums1.size(), N2 = nums2.size();

        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<pair<int,int>> res;
        pq.emplace(0, 0);

        while(res.size() < k) {
            pii top = pq.top();
            pq.pop();
            res.emplace_back(nums1[top.first], nums2[top.second]);

            if(top.second + 1 < N2) pq.emplace(top.first, top.second + 1);
            if(top.first + 1 < N1) pq.emplace(top.first + 1, top.second);
        }

        return res;
    }
};

int main() {
    return 0;
}