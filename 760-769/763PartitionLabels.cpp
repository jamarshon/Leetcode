/*
763. Partition Labels
A string S of lowercase letters is given. We want to partition this string into as many parts 
as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    everytime a letter is visited, update right to be max right and
    the index of the furthest right of this character
    if i == right it means all the caharacters between i and the previous pushed
    number contains letters that do not appear in any other part of the string.
    */
    vector<int> partitionLabels(string S) {
        unordered_map<char, int> last_seen;
        int N = S.size();
        for(int i = 0; i < N; i++) last_seen[S[i]] = i;
        int right = 0;
        
        vector<int> res;
        for(int i = 0; i < N; i++) {
            right = max(right, last_seen[S[i]]);
            if(i == right) res.push_back(i+1);
        }
        
        for(int i = res.size()-1; i >= 1; i--) res[i] -= res[i-1];
        return res;
    }
};

int main() {
    return 0;
}