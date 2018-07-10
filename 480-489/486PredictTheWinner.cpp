/*
486. Predict the Winner
Given an array of scores that are non-negative integers. Player 1 picks one of 
the numbers from either end of the array followed by the player 2 and then 
player 1 and so on. Each time a player picks a number, that number will not be 
available for the next player. This continues until all the scores have been 

Given an array of scores, predict whether player 1 is the winner. You can assume 

Example 1:
Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. If he chooses 2 (or 
1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then 
player 1 will be left with 1 (or 2). So, final score of player 1 is 1 + 2 = 3, 
and player 2 is 5. Hence, player 1 will never be the winner and you need to 



Example 2:
Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 
and 7. No matter which number player 2 choose, player 1 can choose 233.Finally, 
player 1 has more score (234) than player 2 (12), so you need to return True 



Note:

1 <= length of the array <= 20. 
Any scores in the given array are non-negative integers and will not exceed 
If the scores of both players are equal, then player 1 is still the winner.
/*
    Submission Date: 2018-07-10
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
public:
    /*
    dp[i][j] is the maximum value from [i, j]. 
    it is either take from the left :
        nums[i] + min <- because opponent wants to minimize your next score
            dp[i+2][j] // opponent chose nums[i+1] from dp[i+1][j]
            dp[i+1][j-1] // opponent chose nums[j-1] from dp[i+1][j]
    or take from the right
        nums[j] + min <- because opponent wants to minimize your next score
            dp[i][j-2] // opponent chose nums[j-1] from dp[i][j-1]
            dp[i+1][j-1] // opponent chose nums[i] from dp[i][j-1]
    
    return the best score you can get dp[0][N-1] and the best score the opponent can
    get which is just sum - your score
    */
    bool PredictTheWinner(vector<int>& nums) {
        typedef long long ll;
        int N = nums.size();
        if(N == 0) return false;
        if(N == 1) return true;
        
        vector<vector<ll>> dp(N, vector<ll>(N));
        for(int gap = 0; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                if(gap == 0) dp[i][j] = nums[i];
                else if(gap == 1) dp[i][j] = max(nums[i], nums[j]);
                else { // j - i = gap >= 2 
                    dp[i][j] = max(
                        nums[i] + min(dp[i+2][j], dp[i+1][j-1]),
                        nums[j] + min(dp[i][j-2], dp[i+1][j-1])
                    );
                }
            }
        }
        
        ll sum = 0;
        for(const auto& e: nums) sum += e;
        return dp[0][N-1] >= sum - dp[0][N-1]; 
    }
};

class Solution {
public:
    /*
    same as before except using a sum array cause if take left
    nums[i] then opponent will get the value dp[i+1][j] hence you get sum from [0,j] - opponent value
    and same if take right
    */
    typedef long long ll;
    
    // sum from [i, j]
    ll GetSum(const vector<ll>& sum, int i, int j) {
        return i == 0 ? sum[j] : sum[j] - sum[i-1];
    }
    
    bool PredictTheWinner(vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return false;
        if(N == 1) return true;
        
        vector<ll> sum(N); // sum[i] = sum from [0, i]
        sum[0] = nums[0];
        for(int i = 1; i < N; i++) sum[i] = sum[i-1] + nums[i];
        
        vector<vector<ll>> dp(N, vector<ll>(N));
        for(int gap = 0; gap < N; gap++) {
            for(int i = 0; i + gap < N; i++) {
                int j = i + gap;
                if(gap == 0) dp[i][j] = nums[i];
                else {
                    dp[i][j] = max(
                        nums[i] + GetSum(sum, i+1, j) - dp[i+1][j],
                        nums[j] + GetSum(sum, i, j-1) - dp[i][j-1]
                    );
                }
            }
        }
        
        return dp[0][N-1] >= sum[N-1] - dp[0][N-1]; 
    }
};

int main() {
    return 0;
}
