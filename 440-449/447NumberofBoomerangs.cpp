/*
447. Number of Boomerangs
Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) 
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
/*
    Submission Date: 2018-06-08
    Runtime: 284 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;
        int N = points.size();
        
        for(int i = 0; i < N; i++) {
            /*
            From this point find the distance of all points from this point.
            if there are m points that are at the same distance from this point,
            if m is less than 2 then it can't be used else it is permutation without
            repetition which is n!/(n-r)! = m!/(m-2)! = m*(m-1)
            */
            unordered_map<int, int> dist_sq_m;
            for(int j = 0; j < N; j++) {
                if(j == i) continue;
                int dist_sq = pow(points[i].first - points[j].first, 2) + 
                    pow(points[i].second - points[j].second, 2);
                dist_sq_m[dist_sq]++;
            }
            
            for(const auto& kv: dist_sq_m) {
                if(kv.second < 2) continue;
                res += kv.second*(kv.second - 1);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}