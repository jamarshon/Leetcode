/*
789. Escape The Ghosts
You are playing a simplified Pacman game. You start at the point (0, 0), and your 
destination is (target[0], target[1]). There are several ghosts on the map, the i-th ghost 
starts at (ghosts[i][0], ghosts[i][1]).

Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal directions: 
north, east, west, or south, going from the previous point to a new point 1 unit of distance away.

You escape if and only if you can reach the target before any ghost reaches you (for any given 
moves the ghosts may take.)  If you reach any square (including the target) at the same time as 
a ghost, it doesn't count as an escape.

Return True if and only if it is possible to escape.

Example 1:
Input: 
ghosts = [[1, 0], [0, 3]]
target = [0, 1]
Output: true
Explanation: 
You can directly reach the destination (0, 1) at time 1, while the ghosts located at (1, 0) or 
(0, 3) have no way to catch up with you.
Example 2:
Input: 
ghosts = [[1, 0]]
target = [2, 0]
Output: false
Explanation: 
You need to reach the destination (2, 0), but the ghost at (1, 0) lies between you and the destination.
Example 3:
Input: 
ghosts = [[2, 0]]
target = [1, 0]
Output: false
Explanation: 
The ghost can reach the target at the same time as you.
Note:

All points have coordinates with absolute value <= 10000.
The number of ghosts will not exceed 100.
/*
    Submission Date: 2018-07-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    if the manhattan distance (abs horizontal + abs vertical) of the target
    from the origin is less than or equal to the manhattan distance of the 
    target with the ghost, then return false as the ghost can get there
    faster and just wait indefinitely.

    why ghost intercept is not good?
    if a ghost can intercept you, it means they can reach the target faster than
    you. the shortest path between two points is straight line so if ghost can
    take detour and intercept then it means if they just went straight, they
    would be there before you.
              if ghost gets here before you, they would already be at target
              x   
    you --------------- target
              |         |
              |         |
    ghost--------------
    */
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int mine = abs(target[0]) + abs(target[1]);
        for(const auto& e: ghosts) {
            int dist = abs(e[0]-target[0]) + abs(e[1]-target[1]);
            if(dist <= mine) return false;
        }
        return true;
    }
};

int main() {
    return 0;
}