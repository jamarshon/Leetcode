/*
846. Hand of Straights
Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, 

Return true if and only if she can.

 




Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].

Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.

 

Note:


    1 <= hand.length <= 10000
    0 <= hand[i] <= 10^9
    1 <= W <= hand.length
/*
    Submission Date: 2018-07-11
    Runtime: 44 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    /*
    create a frequency map. have a sorted queue of ends and loop through freq map
    if the ends isn't empty (meaning it is a part of some interval) and previous value in freq map 
    doesn't equal current value - 1, it means a jump occured without interval ending so return false
    
    if the frequency is less than the number of intervals (ends.size()), return false as more of 
    this number is needed
    
    if the frequency is greater than the number of intervals, then add this number + W - 1 as
    the end interval and do this freq - number of intervals times.
    
    remove all the ends that equal the current value
    
    finally return if ends is empty meaning all the intervals have been completed.
    */
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int,int> freq;
        for(const auto& h: hand) freq[h]++;
        queue<int> ends;
        
        pair<int,int> prev = {-1, -1};
        for(const auto& kv: freq) {
            if(prev.first != -1 && kv.first != prev.first + 1 && !ends.empty()) return false;
            prev = kv;
            int diff = kv.second - ends.size();
            if(diff < 0) return false; // too many numbers needed
            if(diff > 0) {
                // new ends
                for(int i = 0; i < diff; i++)
                    ends.push(kv.first + W - 1);
            }
            
            while(!ends.empty() && kv.first == ends.front()) ends.pop();
        }
        
        return ends.empty();
    }
};

int main() {
    return 0;
}
