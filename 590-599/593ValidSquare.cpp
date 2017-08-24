/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the 
four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array 
with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four 
equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-08-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

class Solution {
public:
    int distSq(vector<int>& a, vector<int>& b) {
        return pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2);
    }
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<int> dist;
        vector<vector<int>> v{p1, p2, p3, p4};
        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 4; j++) {
                dist.push_back(distSq(v[i], v[j]));
            }
        }

        // given points a,b,c,d -> dist will contain ab ac ad bc bd cd
        // out of these 6 distances, there are 4 distances which are the side distances (s)
        // and 2 that are hypotenuse (h)
        // s^2 + s^2 = h^2

        assert(dist.size() == 6);
        map<int,int> freq;
        for(auto e: dist) freq[e]++;

        if(freq.size() != 2) return false;
        int s = freq.begin() -> first;
        int h = next(freq.begin(), 1) -> first;
        return 2*s == h;
    }
};

int main() {
    Solution s;
    return 0;
}