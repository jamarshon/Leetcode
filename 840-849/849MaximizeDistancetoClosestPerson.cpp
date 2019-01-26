/*
849. Maximize Distance to Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents
that the seat is empty.

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest
person to him is maximized.

Return that maximum distance to closest person.

Example 1:

Input: [1,0,0,0,1,0,1]
Output: 2
Explanation:
If Alex sits in the second open seat (seats[2]), then the closest person has
distance 2. If Alex sits in any other open seat, the closest person has
distance 1. Thus, the maximum distance to the closest person is 2. Example 2:

Input: [1,0,0,0]
Output: 3
Explanation:
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Note:

1 <= seats.length <= 20000
seats contains only 0s or 1s, at least one 0, and at least one 1.
/*
    Submission Date: 2018-06-24
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxDistToClosest(vector<int>& seats) {
    if (seats.empty()) return INT_MAX;

    int N = seats.size();
    // left[i] indicates the distance to the closest 1 to the left
    vector<int> left(N, INT_MAX);
    for (int i = 0; i < N; i++) {
      if (seats[i] == 1)
        left[i] = 0;
      else if (i > 0 && left[i - 1] < INT_MAX) {
        left[i] = left[i - 1] + 1;
      }
    }

    int right = INT_MAX;
    int res = INT_MIN;
    /*
    if there is at least one 1 and 0
    left[i] will be INT_MAX until the first 1 then some number after it
    
    hence if starting from the back, the number will not be INT_MAX so right
    will be correctly minimized.
    */
    for (int i = N - 1; i >= 0; i--) {
      if (seats[i] == 1)
        right = 0;
      else if (right < INT_MAX)
        right++;

      res = max(res, min(left[i], right));
    }

    return res;
  }
};

int main() { return 0; }