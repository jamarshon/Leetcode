/*
739. Daily Temperatures
Given a list of daily temperatures, produce a list that, for each day in the 
input, tells you how many days you would have to wait until a warmer 
temperature.  If there is no future day for which this is possible, put 0 
instead. 

For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], 
your output should be [1, 1, 4, 2, 1, 1, 0, 0]. 


Note:
The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].

/*
    Submission Date: 2018-06-30
    Runtime: 250 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    /*
    stk keeps an increasing temperatures to the right (represented as indices)
    while stk isn't emtpy and the current element is greater than the smallest element 
    (ie stk top) pop the stk, basically it means this element replaces all the smaller elements
    as it will be closer to the next element while still being greater
    */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        int N = temperatures.size();
        vector<int> res(N, 0);
        for(int i = N-1; i >= 0; i--) {
            while(!stk.empty() && temperatures[stk.top()] <= temperatures[i]) stk.pop();
            res[i] = stk.empty() ? 0 : stk.top() - i;
            stk.push(i);
        }
        
        return res;
    }
};

int main() {
    return 0;
}