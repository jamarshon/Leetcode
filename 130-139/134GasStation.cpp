/*
134. Gas Station
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next 
station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int N = gas.size();
        int start = 0;
        int curr_gas = 0;
        int need_to_overcome = 0;
        for(int i = 0; i < N; i++) {
            curr_gas += gas[i] - cost[i];
            if(curr_gas < 0) {
                need_to_overcome -= curr_gas;
                start = i + 1;
                curr_gas = 0;
            }
        }
        return (curr_gas >= need_to_overcome) ? start : -1;
    }
};

int main() {
    Solution s;
    return 0;
}