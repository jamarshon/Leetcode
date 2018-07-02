/*
667. Beautiful Arrangement II
Given two integers n and k, you need to construct a list which contains n 
different positive integers ranging from 1 to n and obeys the following 

Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - 



If there are multiple answers, print any of them.


Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 



Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 



Note:

The n and k are in the range 1 <= k < n <= 104.
/*
    Submission Date: 2018-07-02
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    place elements [1, n-k] in array then keep adding to the back numbers from
    [k, 1] alterating the sign (+, -) starting with +
    */
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        res.reserve(n);
        for(int i = 1; i + k <= n; i++) res.push_back(i);
        for(int i = 0; i < k; i++) {
            res.push_back(res.back() + (i % 2 == 0 ? 1 : -1)*(k - i));
        }
        
        return res;
    }
};

class Solution2 {
public:
    /*
    have two pointers i and j where i starts at 1 and j starts at n
    interweave i and j for the first k elements then just keep increasing i until reaches j
    e.g
    n = 5, k = 3
    
    weaves 3 2 1
    res    1 5 2 3 4 
    diff    4 3 1 1
    */
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        res.reserve(n);
        int j = n;
        for(int i = 1; i <= j;) {
            if(k > 1) {
                res.push_back(k-- % 2 ? i++ : j--);
            } else {
                res.push_back(i++);
            }
        }
        return res;
    }
};

int main() {
    return 0;
}
