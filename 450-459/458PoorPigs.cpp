/*
458. Poor Pigs
There are 1000 buckets, one and only one of them contains poison, the rest are 
filled with water. They all look the same. If a pig drinks that poison it will 
die within 15 minutes. What is the minimum amount of pigs you need to figure out 

Answer this question, and write an algorithm for the follow-up general case.

Follow-up: 

If there are n buckets and a pig drinking poison will die within m minutes, how 
many pigs (x) you need to figure out the "poison" bucket within p minutes? There 
/*
    Submission Date: 2018-07-13
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    /*
    there are minutesToTest/minutesToDie opportunities e.g 60/15=4
    to try. create minutesToTest/minutesToDie + 1 values in a dimension,
    create as many pigs as dimensions who takes one entry along a certain dimension
    every minutesToDie. the +1 means when minutesToTest is over, then the last entry has to 
    be the one.
    
    e.g suppose 2 dimensions (pigs) with 5 values in a dimension, one pig can take 
    every potion in a row every minutesToDie and another pig can take 
    every potion in a col every minutesToDie. thus, they can find 
    the poison for 5^2. if there was 3 pigs, then 5^3 and so on.
    
    entries = minutesToTest/minutesToDie + 1
    entries^pigs > buckets
    log(buckets)/log(entries) > buckets
    */
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int entries = minutesToTest/minutesToDie + 1;
        return ceil(log(buckets)/log(entries));
    }
};

int main() {
    return 0;
}
