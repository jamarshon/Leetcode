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
#include <cassert>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

class Solution {
public:
    /* Nlogk using minheap */
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap heap;
        for(int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if(heap.size() > k) heap.pop();
        }

        return heap.top();
    }
};

class Solution2 {
public:
    /* O(k) using quickselect
        using two ends of the array, slowly move towards the middle as low++, high--
        when comparing to nums[0]
    */
    int findKthLargest( vector<int> nums, int k) {
      int low = 0;
      int high = nums.size() - 1;
      int partition = 0;
      while (low <= high) {
        if(nums[low] <= nums[partition]) {
          low++;
        } else if(nums[high] > nums[partition]) {
          high--;
        } else if (nums[partition] < nums[low]) {
          swap(nums[low], nums[high]);
          --high;
        } else if (nums[partition] >= nums[high]) {
          swap(nums[low], nums[high]);
          ++low;
        } else {
            assert(false);
        }
      }
      
      swap(nums[high], nums[partition]);
      
      if(high == nums.size() - k) {
        return nums[high];
      }
        
      if (high > nums.size() - k) {
        return findKthLargest(vector<int>(nums.begin(), nums.begin() + high), k-(nums.size()-high));
      } else {
        return findKthLargest(vector<int>(nums.begin() + high+1, nums.end()), k);
      }
    }
};


class Solution3 {
public:
    /*
    O(k) using low_partition to be the right boundary of low meaning the first number > nums[0]
    */
    int findKthLargest( vector<int> nums, int k) {
        int low_partition = 0;

        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] <= nums[0]) {
                swap(nums[i], nums[low_partition]);
                ++low_partition;
            }
        }
        
        const int pivot_ind = low_partition - 1;
        swap(nums[pivot_ind], nums[0]);
        
        if(pivot_ind == nums.size() - k) {
            return nums[pivot_ind];
        }

        if (pivot_ind > nums.size() - k) {
            return findKthLargest(vector<int>(
                nums.begin(), nums.begin() + pivot_ind), k-(nums.size() - pivot_ind));
        }
        else {
            return findKthLargest(vector<int>(nums.begin() + pivot_ind + 1, nums.end()), k);
        }
    }
};

int main() {
    return 0;
}