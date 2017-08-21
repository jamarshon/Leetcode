/*
386. Lexicographical Numbers
Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size 
may be as large as 5,000,000.

/*
    Submission Date: 2017-08-21
    Runtime: 239 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void lexicalOrder(int curr, int n, vector<int>& res) {
        if(curr > n) return;

        int limit = min(n + 1, curr == 1 ? 10: curr+10);
        for(int i = curr; i < limit; i++) {
            res.push_back(i);
            lexicalOrder(i*10, n, res);
        }
    }
    
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        lexicalOrder(1, n, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}