/*
788. Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  
Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 
6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation: 
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].
/*
    Submission Date: 2018-06-04
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /*
    dp[i] = -1 if i cannot be rotated else it equals the rotated number of i
    therefore dp[i] = dp[i/10] + rot[i % 10] as i/10 gets the rotated version i
    without the last number and rot[i % 10] gets the rotated version of the last number
    of i
    */
    int rotatedDigits(int N) {
        vector<int> dp(N + 1, -1);
        unordered_map<int,int> rot{{0, 0}, {1, 1}, {8, 8}, 
                                   {2, 5}, {5, 2}, {6, 9}, {9, 6}};
        int res = 0;
        for(int i = 1; i <= N; i++) {
            if(!rot.count(i % 10)) continue;
            if(i < 10) {
                dp[i] = rot[i];
                res += dp[i] != i;
            } else {
                if(dp[i/10] == -1) continue;
                dp[i] = dp[i/10] * 10 + rot[i % 10];
                res += dp[i] != i;
            }
        }
        return res;
    }
};

int main() {
    return 0;
}