/*
1025. Divisor Game
Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number N on the chalkboard.  On each player's turn, that
player makes a move consisting of:

  Choosing any x with 0 < x < N and N % x == 0.
  Replacing the number N on the chalkboard with N - x.

Also, if a player cannot make a move, they lose the game.

Return True if and only if Alice wins the game, assuming both players play
optimally.

Example 1:

Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:

Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

Note:

  1 <= N <= 1000
/*
  Submission Date: 2019-09-07
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool divisorGame(int N) {
    // suppose N is odd, then it cannot be divided by 2
    // or any multiples of 2. the divisor is odd meaning
    // N - divisor would be odd - odd = even. hence, if
    // N is odd, then the current user will have to make
    // it even for the next user.
    //
    // if N is even, the current user can force the
    // opponent to get an odd number by subtracting one.
    //
    // even => odd
    // odd => even
    //
    // base case odd 1 is a lost
    // at even 2, it is a win as even (2) => odd (1)
    // at odd 3, it is a lost as odd (3) => even (2) => odd (1)
    // at even 4, it is a win as even (4) => odd (3) => even (2) => odd (1)
    // thus, we can win only if N is even by forcing
    // the oponent to get odd numbers until they reach 1
    return N % 2 == 0;
  }
};

int main() { return 0; }
