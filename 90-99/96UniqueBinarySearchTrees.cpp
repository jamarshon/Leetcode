/*
96. Unique Binary Search Trees
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-06-28
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        long long dp[n + 1];

        dp[0] = dp[1] = 1;

        for(long long i = 1; i < n; i++) {
            dp[(int)i + 1] = dp[i]*(2*i + 2)*(2*i + 1)/(i + 1)/(i + 2);
        }

        return dp[n];
    }
};

int main() {
    Solution s;
    return 0;
}