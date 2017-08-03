/*
119. Pascal's Triangle II
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

/*
    Submission Date: 2017-08-02
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1);

        res[0] = 1;
        long long prev = 1;
        for(int i = 1; i < res.size(); i++) {
            res[i] = prev*(rowIndex-i+1)/i;
            prev = res[i];
        }

        return res;
    }
};

int main() {
    return 0;
}