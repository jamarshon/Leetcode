/*
682. Baseball Game
You're now a baseball game point recorder.

Given a list of strings, each string can be one of the 4 following types:

Integer (one round's score): Directly represents the number of points you get in this round.
"+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
"D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
"C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
Each round's operation is permanent and could have an impact on the round before and the round after.

You need to return the sum of the points you could get in all the rounds.

Example 1:
Input: ["5","2","C","D","+"]
Output: 30
Explanation: 
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get 2 points. The sum is: 7.
Operation 1: The round 2's data was invalid. The sum is: 5.  
Round 3: You could get 10 points (the round 2's data has been removed). The sum is: 15.
Round 4: You could get 5 + 10 = 15 points. The sum is: 30.
Example 2:
Input: ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation: 
Round 1: You could get 5 points. The sum is: 5.
Round 2: You could get -2 points. The sum is: 3.
Round 3: You could get 4 points. The sum is: 7.
Operation 1: The round 3's data is invalid. The sum is: 3.  
Round 4: You could get -4 points (the round 3's data has been removed). The sum is: -1.
Round 5: You could get 9 points. The sum is: 8.
Round 6: You could get -4 + 9 = 5 points. The sum is 13.
Round 7: You could get 9 + 5 = 14 points. The sum is 27.
Note:
The size of the input list will be between 1 and 1000.
Every integer represented in the list will be between -30000 and 30000.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    /*
    let stk be all the valid round points. if it is a number just add it as a round and increment res by the amount
    if it is a "+", take the last two rounds add add them up. put the sum as a round and increment res by the amount
    if it is a "D", take the last round, multiply it by two and add it as a around and increment res by the amount
    if it is a "C", take the last round and decrease res by the amount as well as pop that round off.
    */
    int calPoints(vector<string>& ops) {
        int res = 0; 
        vector<int> stk;
        for(const auto& s: ops) {
            int stk_size = stk.size();
            if(s == "+") {
                assert(stk_size >= 2);
                stk.push_back(stk[stk_size-1] + stk[stk_size-2]);
                res += stk.back();
            } else if(s == "D") {
                assert(stk_size >= 1);
                stk.push_back(stk[stk_size-1] * 2);
                res += stk.back();
            } else if(s == "C") {
                res -= stk.back();
                stk.pop_back();
            } else { // a number
                stk.push_back(stoi(s));
                res += stk.back();
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}