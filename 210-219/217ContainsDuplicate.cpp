/*
217. Contains Duplicate
Given an array of integers, find if the array contains any duplicates. Your function should 
return true if any value appears at least twice in the array, and it should return false if 
every element is distinct.

/*
    Submission Date: 2017-08-03
    Runtime: 45 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for(auto num: nums) {
            if(seen.count(num)) return true;
            seen.insert(num);
        }
        return false;
    }
};

int main() {
    return 0;
}