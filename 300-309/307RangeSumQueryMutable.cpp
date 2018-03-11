/*
307. Range Sum Query - Mutable
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
/*
    Submission Date: 2017-03-11
    Runtime: 83 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
    vector<int> tree;
    int N;
    
    int lsb(int x){ return x & ~(x-1); }
    
    // [1,i]
    int query(int i) {
        int sum = 0;
        while(i != 0) {
            sum += tree[i];
            i -= lsb(i);
        }
        return sum;
    }
public:
    NumArray(vector<int> nums) {
        N = nums.size();
        tree.resize(N+1);
        
        tree[0] = 0;
        for(int i = 1; i <= N; i++) tree[i] = nums[i-1];
        
        for(int i = 1; i <= N; i++) {
            int parent = i + lsb(i);
            if(parent <= N) tree[parent] += tree[i];
        }
    }
    
    void update(int i, int val) {
        int delta = val - sumRange(i,i);
        i++;
        while(i <= N) {
            tree[i] += delta;
            i += lsb(i);
        }
    }
    
    int sumRange(int i, int j) {
        return query(j+1) - query(i);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main() {
    return 0;
}