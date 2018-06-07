/*
717. 1-bit and 2-bit Characters
We have two special characters. The first character can be represented by one bit 0. The second character can be represented by 
two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given 
string will always end with a zero.

Example 1:
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
Example 2:
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.
Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
/*
    Submission Date: 2018-06-07
    Runtime: 7 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int N = bits.size();
        vector<bool> dp(N, false);
        dp[N-1] = true;

        for(int i = N-2; i >= 0; i--) {
            if(bits[i] == 0) {
                dp[i] = dp[i+1];
            } else {
                if(i + 2 < N) dp[i] = dp[i+2];
            }
        }

        return dp[0];
    }
};


int main() {
    return 0;
}