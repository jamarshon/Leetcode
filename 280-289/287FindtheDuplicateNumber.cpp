/*
287. Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is 
between 1 and n (inclusive), prove that at least one duplicate number 
must exist. Assume that there is only one duplicate number, find the 
duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be 
repeated more than once.
/*
    Submission Date: 2017-08-30
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        Find beginning of cycle of linked list. nums[i] represents
        node i has a link to node nums[i]. since nums[i] is [1,n]
        it means it will always have a link to an element in the 
        array. there are n+1 numbers and they span from [1,n] so
        a duplicate must exist eg n = 2 -> 1,2,_ . 
        pigeonhole principle states that if n items are put into m 
        containers, with n > m, then at least one container must 
        contain more than one item. 
        a cycle will occur as two numbers point to the same index
        one number going into the cycle and the second completing
        the cycle e.g [1,3,4,2,2] ->
        indices 0 -> 1 -> 3 -> 2 -> 4 -> 2
        values  1 -> 3 -> 2 -> 4 -> 2 -> 4
        0 can't be the start of the cycle as there is no number
        going into the cycle (index 0) meaning this method won't work 
        (the guarantee of nums[i] between [1,n] must exist).
    */
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while(slow != fast);
        
        slow = 0;
        while(slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};

int main() {
    return 0;
}