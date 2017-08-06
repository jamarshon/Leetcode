/*
414. Third Maximum Number
Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> distinct;
        int max_item = nums.front();
        for(auto num: nums) {
            max_item = max(max_item, num);
            if(distinct.count(num)) continue;
            min_heap.push(num);
            distinct.insert(num);
            if(min_heap.size() > 3) {
                int to_delete = min_heap.top();
                distinct.erase(to_delete);
                min_heap.pop();
            }
        }
        
        return min_heap.size() == 3 ? min_heap.top() : max_item;
    }
};

int main() {
    return 0;
}