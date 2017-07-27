/*
215. Kth Largest Element in an Array
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, 
not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ? k ? array's length.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap heap;
        for(int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if(heap.size() > k) heap.pop();
        }

        return heap.top();
    }
};

int main() {
    return 0;
}