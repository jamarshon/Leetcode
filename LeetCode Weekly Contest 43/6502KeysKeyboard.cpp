/*
650. 2 Keys Keyboard
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad 
for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps 
permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
Note:
The n will be in the range [1, 1000].

/*
    Submission Date: 2017-07-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = dp[1] = 0;

        for(int i = 1; i <= n; i++) {
            int cost = dp[i] + 1;
            int temp = i*2;
            if(temp > n) break; 
            while(temp <= n) {
                dp[temp] = min(dp[temp], ++cost);
                temp += i;
            }
        }

        return dp[n];
    }
};

int main() {
    return 0;
}