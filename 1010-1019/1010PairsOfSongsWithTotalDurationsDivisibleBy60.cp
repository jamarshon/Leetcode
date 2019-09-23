/*
1010. Pairs of Songs With Total Durations Divisible by 60
In a list of songs, the i-th song has a duration of time[i] seconds. 

Return the number of pairs of songs for which their total duration in seconds is
divisible by 60.  Formally, we want the number of indices i < j with (time[i] +
time[j]) % 60 == 0.

Example 1:

Input: [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60

Example 2:

Input: [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by
60.

Note:

  1 <= time.length <= 60000
  1 <= time[i] <= 500
/*
  Submission Date: 2019-09-23
  Runtime: 48 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int numPairsDivisibleBy60(vector<int>& time) {
    /*
    similar to two sum using a hashmap except
    we are looking for the modulo of the complement
    */
    unordered_map<int, int> seen;
    int res = 0;
    for (const auto& e : time) {
      int ee = e % 60;
      int complement = (60 - ee) % 60;
      if (seen.count(complement)) {
        res += seen[complement];
      }
      seen[ee]++;
    }
    return res;
  }
};

int main() { return 0; }
