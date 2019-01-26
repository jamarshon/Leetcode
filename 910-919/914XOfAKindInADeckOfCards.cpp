/*
914. X of a Kind in a Deck of Cards
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to
split the entire deck into 1 or more groups of cards, where:

  Each group has exactly X cards.
  All the cards in each group have the same integer.

Example 1:

Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

Example 2:

Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Example 3:

Input: [1]
Output: false
Explanation: No possible partition.

Example 4:

Input: [1,1]
Output: true
Explanation: Possible partition [1,1]

Example 5:

Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:

  1 <= deck.length <= 10000
  0 <= deck[i] < 10000
/*
  Submission Date: 2019-01-26
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }
  /*
  gcd(a,b,c) = gcd(gcd(a,b), c)
  hence, if the gcd(freq[0], ... freq[n-1]) is the
  largest number which divides into all of them which
  is X (just check X >= 2)
  */
  bool hasGroupsSizeX(vector<int>& deck) {
    unordered_map<int, int> freq;
    for (auto& e : deck) {
      freq[e]++;
    }

    int res = 0;
    for (auto& kv : freq) res = gcd(res, kv.second);
    return res > 1;
  }
};

int main() { return 0; }
