/*
135. Candy
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following
requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int candy(const vector<int>& ratings) {
    int N = ratings.size();

    vector<int> forward(N, 1);
    vector<int> backward(N, 1);

    for (int i = 1; i < N; i++) {
      if (ratings[i] > ratings[i - 1]) {
        forward[i] = forward[i - 1] + 1;
      }
    }

    for (int i = N - 2; i >= 0; i--) {
      if (ratings[i] > ratings[i + 1]) {
        backward[i] = backward[i + 1] + 1;
      }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
      count += max(forward[i], backward[i]);
    }

    return count;
  }
};

int main() {
  Solution s;
  return 0;
}