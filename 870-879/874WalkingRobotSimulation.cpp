/*
874. Walking Robot Simulation
A robot on an infinite grid starts at point (0, 0) and faces north.  The robot
can receive one of three possible types of commands:

  -2: turn left 90 degrees
  -1: turn right 90 degrees
  1 <= x <= 9: move forward x units

Some of the grid squares are obstacles. 

The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

If the robot would try to move onto them, the robot stays on the previous grid
square instead (but still continues following the rest of the route.)

Return the square of the maximum Euclidean distance that the robot will be from
the origin.

Example 1:

Input: commands = [4,-1,3], obstacles = []
Output: 25
Explanation: robot will go to (3, 4)

Example 2:

Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
Output: 65
Explanation: robot will be stuck at (1, 4) before turning left and going to (1,
8)

Note:

  0 <= commands.length <= 10000
  0 <= obstacles.length <= 10000
  -30000 <= obstacle[i][0] <= 30000
  -30000 <= obstacle[i][1] <= 30000
  The answer is guaranteed to be less than 2 ^ 31.
/*
  Submission Date: 2019-01-26
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int dx = 0;
  int dy = 1;

  /*
  0,1 => 1,0 => 0,-1 => -1,0
  */
  void rotateCW() {
    swap(dx, dy);
    dy = -dy;
  }

  /*
  0,1 => -1,0 => 0,-1 => 1,0
  */
  void rotateCCW() {
    swap(dx, dy);
    dx = -dx;
  }

  int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    int mx = 0;
    int my = 0;
    long long res = pow(mx, 2LL) + pow(my, 2LL);
    unordered_set<string> st;
    for (auto& p : obstacles) {
      st.insert(to_string(p[0]) + "," + to_string(p[1]));
    }

    for (auto& c : commands) {
      if (c == -2) {  // left
        rotateCCW();
      } else if (c == -1) {  // right
        rotateCW();
      } else {  // forward
        for (int i = 1; i <= c; i++) {
          string key = to_string(mx + dx) + "," + to_string(my + dy);
          if (st.count(key)) break;

          mx += dx;
          my += dy;

          long long pos = pow(mx, 2LL) + pow(my, 2LL);
          res = max(res, pos);
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
