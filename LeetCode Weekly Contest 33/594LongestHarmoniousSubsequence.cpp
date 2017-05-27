/*
594. Longest Harmonious Subsequence
We define a harmonious array is an array where the difference between its maximum value and its minimum 
value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all 
its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.
/*
    Submission Date: 2017-05-27
    Runtime: 109 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        int max_len = 0;
        for(int d: nums) {
            int current = 0;
            if(freq.find(d) != freq.end()) {
                current += freq[d];
                freq[d] += 1;
            } else {
                freq[d] = 1;
            }

            int adj = 0;
            if(freq.find(d-1) != freq.end()) {
                adj = max(adj, freq[d-1]);
            }

            if(freq.find(d+1) != freq.end()) {
                adj = max(adj, freq[d+1]);
            }

            if(adj == 0) continue;
            current += adj + 1;
            max_len = max(current, max_len);
        }
        return max_len;
    }
};

int main() {
    vector<int> v{1,3,2,2,5,2,3,7};
    Solution s;
    cout << s.findLHS(v) << endl;
    return 0;
}