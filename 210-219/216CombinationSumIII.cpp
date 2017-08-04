/*
216. Combination Sum III
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 
1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]

/*
    Submission Date: 2017-08-03
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void recurse(int current, int sum, int K, int N, vector<int>& temp, vector<vector<int>>& res) {
        if(current > N) return;
        if(temp.size() == K) {
            if(sum == N) res.push_back(temp);
            return;
        }
        for(int i = current + 1; i < 10; i++) {
            temp.push_back(i);
            recurse(i, sum + i, K, N, temp, res);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int K, int N) {
        if(K == 0) return {};

        vector<vector<int>> res;
        vector<int> temp;
        recurse(0, 0, K, N, temp, res);
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> combinationSum3(int K, int N) {
        if(K == 0) return {};

        vector<vector<vector<vector<int>>>> dp(K + 1, vector<vector<vector<int>>>(N + 1));
        // dp[k][i] represents all the vectors that add up to i of length k that is in ascending order using numbers [1, 9]
        // dp[0][i] and dp[k][0] is empty
        // dp[1][i] is just [i]
        // dp[k + 1][i+j] = concat all elements of dp[k][i] with j 
        // for j < 10 && i = j <= N && j being the maximum of the element dp[k][i] 

        for(int k = 1; k < K; k++) {
            for(int i = 1; i < N; i++) {
                if(k == 1) dp[k][i] = {{i}};
                vector<vector<int>>& temp = dp[k][i];

                for(int l = 0; l < temp.size(); l++) {
                    vector<int>& temp_el = temp[l];
                    int largest = temp_el.empty() ? 0 : temp_el.back();

                    for(int j = largest + 1; j < 10 && i + j <= N; j++) {
                        temp_el.push_back(j);
                        dp[k+1][i+j].push_back(temp_el);
                        temp_el.pop_back();
                    }

                }
            }
        }

        return dp[K][N];
    }
};

int main() {
    return 0;
}