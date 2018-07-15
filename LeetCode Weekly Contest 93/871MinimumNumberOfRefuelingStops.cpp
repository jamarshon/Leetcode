/*
871. Minimum Number of Refueling Stops
A car travels from a starting position to a destination which is target miles 
east of the starting position. 

Along the way, there are gas stations.  Each station[i] represents a gas station 
that is station[i][0] miles east of the starting position, and has station[i][1] 
liters of gas. 

The car starts with an infinite tank of gas, which initially 
has startFuel liters of fuel in it.  It uses 1 liter of gas per 1 mile that it 
drives. 

When the car reaches a gas station, it may stop and refuel, transferring all the 
gas from the station into the car. 

What is the least number of refueling stops the car must make in order to reach 
its destination?  If it cannot reach the destination, return -1. 

Note that if the car reaches a gas station with 0 fuel left, the car can still 
refuel there.  If the car reaches the destination with 0 fuel left, it is still 
considered to have arrived. 

 


Example 1:

Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.



Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).



Example 3:

Input: target = 100, startFuel = 10, stations = 
[[10,60],[20,30],[30,30],[60,40]] 
Output: 2
Explanation: 
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters 
to 60 liters of gas. 
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the 
target. 
We made 2 refueling stops along the way, so we return 2.


 

Note:


    1 <= target, startFuel, stations[i][1] <= 10^9
    0 <= stations.length <= 500
    0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < 
target 
/*
    Submission Date: 2018-07-15
    Runtime: 44 ms
    Difficulty: HARD
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        typedef long long ll;
        int N = stations.size();
        
        // dp[t] is the furthest distance you can go with t number of refuels
        // so for a new stations[i] that is smaller distance than dp[t]
        // we can take a refuel (e.g update dp[t+1]) and have a new larger distance
        // by refueling at stations[i]
        vector<ll> dp(N + 1, 0);
        dp[0] = startFuel;
        for(int i = 0; i < N; i++) {
            for(int t = i; t >= 0; t--) {
                if(dp[t] >= stations[i][0]) {
                    dp[t+1] = max(dp[t+1], dp[t] + stations[i][1]);
                }
            }
        }
        
        for(int t = 0; t <= N; t++) if(dp[t] >= target) return t;
        return -1;
    }
};
        

class Solution3 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& s) {
        typedef long long ll;
        priority_queue<int> pq;
        // keep travelling until can't travel any more than use the largest fuel seen
        int res = 0;
        ll dist = startFuel;
        int ind = 0;
        while(true) {
            while(ind < s.size() && s[ind][0] <= dist) {
                pq.push(s[ind][1]);
                ind++;
            }
            
            if(dist >= target) return res;
            if(pq.empty()) return -1;
            // take largest refuel from pq
            dist += pq.top();
            pq.pop();
            res++;
        }
    }
};

class Solution2 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& s) {
        vector<vector<int>> stations;
        stations.push_back({0, 0});
        for(const auto& v: s) stations.push_back(v);
        stations.push_back({target, 0});
        
        int N = stations.size();
        // dp[i][j] = x where x is the minimum refuels to reach station i with j battery remaining
        vector<unordered_map<int,int>> dp(N);
        dp[0][startFuel] = 0; 
        
        int res = INT_MAX;
        
        for(int i = 0; i < N; i++) {
            for(auto battery_to_min: dp[i]) {
                int battery = battery_to_min.first;
                
                if(battery >= stations[N-1][0] - stations[i][0]) { // can reach target
                    res = min(res, battery_to_min.second);
                    continue;
                }
                
                // dont use station i
                for(int j = i + 1; j < N; j++) {
                    int rem = battery - (stations[j][0] - stations[i][0]);
                    if(rem < 0) break;
                    if(!dp[j].count(rem) || dp[j][rem] > battery_to_min.second)
                        dp[j][rem] = battery_to_min.second;
                }
                
                // use station i
                for(int j = i + 1; j < N; j++) {
                    int rem = battery - (stations[j][0] - stations[i][0]);
                    if(rem < 0) break;
                    rem += stations[j][1];
                    if(!dp[j].count(rem) || dp[j][rem] > battery_to_min.second + 1)
                        dp[j][rem] = battery_to_min.second + 1;
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};

int main() {
    return 0;
}
