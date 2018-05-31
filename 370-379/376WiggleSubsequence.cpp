/*
376. Wiggle Subsequence
A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between 
positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than 
two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. 
In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive 
and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is 
obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Examples:
Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
Follow up:
Can you do it in O(n) time?
/*
    Submission Date: 2018-05-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        suppose the number we have is right after <, if we meet a smaller element then just add it to stack
        else if the element is larger than we pop back and add this larger element as it will give a wider
        range of numbers that can follow it
        the same logic applies to >, where if a smaller element is seen just pop back and add it to stack
    */
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> stk1{nums[0]}, stk2{nums[0]};
        for(int i = 1; i < nums.size(); i++) {
            if((stk1.size() % 2 == 0 && stk1.back() <= nums[i]) || 
               (stk1.size() % 2 == 1 && stk1.back() >= nums[i])) {
                stk1.pop_back();
            }
            
            if((stk2.size() % 2 == 1 && stk2.back() <= nums[i]) || 
               (stk2.size() % 2 == 0 && stk2.back() >= nums[i])) {
                stk2.pop_back();
            }
            
            stk1.push_back(nums[i]);
            stk2.push_back(nums[i]);
        }
        
        return max(stk1.size(), stk2.size());
    }
};

int main() {
    return 0;
}