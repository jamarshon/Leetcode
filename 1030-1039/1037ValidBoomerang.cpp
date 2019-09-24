/*
1037. Valid Boomerang
A boomerang is a set of 3 points that are all distinct and not in a straight
line.

Given a list of three points in the plane, return whether these points are a
boomerang.

Example 1:

Input: [[1,1],[2,3],[3,2]]
Output: true

Example 2:

Input: [[1,1],[2,2],[3,3]]
Output: false

Note:

  points.length == 3
  points[i].length == 2
  0 <= points[i][j] <= 100
/*
  Submission Date: 2019-09-23
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isBoomerang(vector<vector<int>>& points) {
    /*
    check if the slope of points[0] points[1] and points[0] points[2]
    are the same

    (points[1][1] - points[0][1])/(points[1][0] - points[0][0])
    != (points[2][1] - points[0][1])/(points[2][0] - points[0][0])
    */
    return (points[1][1] - points[0][1]) * (points[2][0] - points[0][0]) !=
           (points[2][1] - points[0][1]) * (points[1][0] - points[0][0]);
  }
};

class Solution2 {
 public:
  bool isBoomerang(vector<vector<int>>& points) {
    /*
    calculate y=mx+b from points[0] and points[1]
    then check if plugging in points[2] returns the same
    y
    */
    if (points[0] == points[1] || points[0] == points[2] ||
        points[1] == points[2])
      return false;
    int dx = points[1][0] - points[0][0];
    int dy = points[1][1] - points[0][1];
    if (dx == 0) return points[2][0] != points[1][0];
    float m = float(dy) / dx;
    float b = points[0][1] - m * points[0][0];
    return m * points[2][0] + b != points[2][1];
  }
};

int main() { return 0; }
