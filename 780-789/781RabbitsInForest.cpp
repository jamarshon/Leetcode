/*
781. Rabbits in Forest
In a forest, each rabbit has some color. Some subset of rabbits (possibly all of
them) tell you how many other rabbits have the same color as them. Those answers
are placed in an array.

Return the minimum number of rabbits that could be in the forest.

Examples:
Input: answers = [1, 1, 2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit than answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into
the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that
answered plus 2 that didn't.

Input: answers = [10, 10, 10]
Output: 11

Input: answers = []
Output: 0


Note:


    answers will have length at most 1000.
    Each answers[i] will be an integer in the range [0, 999].

/*
    Submission Date: 2018-07-02
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  convert numbers to frequency.
  if x occurs y times it means each group of size x+1 in y could refer to the
  same rabbits so find how many x+1 groups are in y and multiply by x+1 to get
  the total number of rabbits e.g 1 1 1 1 1 1 1 x = 1 y = 7 groups of 2 (1 1) (1
  1) (1 1) (1) there are 4 groups of two and multiply this by 1+1 = 8 the groups
  are referring to only rabbits in their own group.
  */
  int numRabbits(vector<int>& answers) {
    unordered_map<int, int> freq;
    for (const auto& n : answers) freq[n]++;
    int res = 0;
    for (const auto& kv : freq) {
      res += ceil((float)kv.second / (kv.first + 1)) * (kv.first + 1);
    }
    return res;
  }
};

int main() { return 0; }
