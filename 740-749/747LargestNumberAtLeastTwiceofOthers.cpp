/*
747. Largest Number At Least Twice of Others
In a given integer array nums, there is always exactly one largest element.

Find whether the largest element in the array is at least twice as much as every other number in the array.

If it is, return the index of the largest element, otherwise return -1.

Example 1:

Input: nums = [3, 6, 1, 0]
Output: 1
Explanation: 6 is the largest integer, and for every other number in the array x,
6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
 

Example 2:

Input: nums = [1, 2, 3, 4]
Output: -1
Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.
 

Note:

nums will have a length in the range [1, 50].
Every nums[i] will be an integer in the range [0, 99].
/*
    Submission Date: 2018-06-08
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    priority queue minheap to get the 2 largest element along with their index
    compare if the largest element is > second largest element * 2 then return index of largest element
    else -1
    */
    typedef pair<int,int> pii;
    int dominantIndex(vector<int>& nums) {
        if(nums.empty()) return -1;
        
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        for(int i = 0; i < nums.size(); i++) {
            pq.emplace(nums[i], i);
            if(pq.size() > 2) pq.pop();
        }
        
        int top_ind = pq.top().second;
        pq.pop();
        
        if(pq.empty()) return top_ind;
        
        return nums[top_ind] > nums[pq.top().second]/2 ? -1 : pq.top().second;
    }
};

int main() {
    return 0;
}