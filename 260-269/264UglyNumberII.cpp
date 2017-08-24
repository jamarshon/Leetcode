/*
264. Ugly Number II
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only 
include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 
is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n 
does not exceed 1690.
/*
    Submission Date: 2017-08-23
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        typedef long long ll;
        typedef pair<ll,ll> pll;

        // pair where first is value and second is the minimum permissable
        // index for arr

        // we keep track of the smallest value using min heap and
        // remove the value to add smallest*arr[i] for i from index to 3
        // the index keeps track of allowable factors as 2*2*3 and
        // 3*2*2 is the same so by only keeping factors in increasing
        // order we can avoid duplicates
        // when n - 1 elements are removed then the top of the min heap
        // is the answer
        auto cmp = [](const pll& lhs, const pll& rhs) {
            return lhs.first == rhs.first ? lhs.second > rhs.second : lhs.first > rhs.first;
        };

        priority_queue<pll, vector<pll>, decltype(cmp)> pq(cmp);
        pq.emplace(1,0);

        int removed = 0;
        ll arr[3] = {2, 3, 5};
        while(removed < n - 1) {
            pll top = pq.top();
            pq.pop();

            for(int i = top.second; i < 3; i++) {
                pq.emplace(top.first*arr[i], i);
            }
            removed++;
        }

        return pq.top().first;
    }
};

int main() {
    Solution s;
    return 0;
}