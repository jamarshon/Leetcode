/*
475. Heaters
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be wa
/*
    Submission Date: 2018-06-24
    Runtime: 73 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution2 {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(houses.empty()) return 0;
        
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int N = houses.size();
        int M = heaters.size();
        vector<int> dp(N, INT_MAX);
        // heaters[j] is the smallest heater greater than houses[i]
        for(int i = 0, j = 0; i < N && j < M;) {
            if(heaters[j] >= houses[i]) {
                dp[i] = heaters[j] - houses[i];
                i++;
            } else {
                j++;
            }
        }
        
        // heaters[j] is the largest element smaller than houses[i]
        for(int i = N-1, j = M-1; i >= 0 && j >= 0;) {
            if(heaters[j] <= houses[i]) {
                dp[i] = min(dp[i], houses[i] - heaters[j]);
                i--;
            } else {
                j--;
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(houses.empty()) return 0;
        
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int i = 0;
        int N = heaters.size();
        
        int res = -1;
        for(const auto& house: houses) {
            while(i + 1 < N && abs(heaters[i+1] - house) <= abs(heaters[i] - house)) i++;
            res = max(res, abs(heaters[i] - house));
        }
        return res;
    }
};

int main() {
    return 0;
}