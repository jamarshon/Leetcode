/*
292. Nim Game
You are playing the following Nim Game with your friend: There is a 
heap of stones on the table, each time one of you take turns to 
remove 1 to 3 stones. The one who removes the last stone will 
be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the 
game. Write a function to determine whether you can win the game 
given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will 
never win the game: no matter 1, 2, or 3 stones you remove, 
the last stone will always be removed by your friend.
/*
    Submission Date: 2017-08-26
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    /*
        if n <= 3, player wins as they just take it
        if n == 4, player loses as no matter what they take
        there will be some remaining for opponent

        if 4 < n <= 4 + 3, player can win as they can reduce 
        it to n == 4 by taking away [1,3] stones

        if n == 8, player loses as no matter what they take
        opponent can reduce it n == 4

        for the generalized case (n):
        if n % 4 == 0, player loses as whatever they take x = [1,3], 
        opponent takes 4 - x to get n % 4 == 0 again until n == 4
        which opponent wins
        so n % 4 != 0 where n % 4 == x where x = [1, 3] is when player 
        wins as player can reduce by x leading to n % 4 == 0 for the opponent
        causing the opponent to lose as seen above
    */
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};

int main() {
    Solution s;
    return 0;
}