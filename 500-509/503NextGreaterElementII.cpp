/*
503. Next Greater Element II
Given a circular array (the next element of the last element is the first 
element of the array), print the Next Greater Number for every element. The Next 
Greater Number of a number x is the first greater number to its traversing-order 
next in the array, which means you could search circularly to find its next 
greater number. If it doesn't exist, output -1 for this number. 


Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; The number 2 can't find 
next greater number; The second 1's next greater number needs to search 
circularly, which is also 2. 



Note:
The length of given array won't exceed 10000.

/*
    Submission Date: 2018-07-08
    Runtime: 68 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class Solution {
public:
    /*
     stack is in decreasing order, it represents an index which has
     not met an element greater than it. for all the elements that
     are smaller than the current element, make res[element] = current element
     then put current element in the stack
     
     if we ensure that the stack only has elements from 0 < N and traverse
     the array twice then after the first traversal, there will be a stack
     of elements that have nothing greater than it from [i, N) and in the 
     second traversal it will try to find [0, i)
    */
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();
        vector<int> res(N, -1);
        stack<int> stk;
        for(int i = 0; i < 2 * N; i++) {
            while(!stk.empty() && nums[stk.top()] < nums[i % N]) {
                res[stk.top()] = nums[i % N];
                stk.pop();
            }
            
            if(i < N) stk.push(i);
        }
        
        return res;
    }
};

class Solution2 {
public:
    /*
    maintian a stack of increasing numbers similar to before but
    first prepopulate the stack by running through the array once
    then run through the array again, and if the back element in the 
    stack is equal to the current element then remove it from the stk
    to preserve wraparound that does not exceed index i
    */
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();
        list<int> stk;
        for(int i = N-1; i >= 0; i--) {
            while(!stk.empty() && stk.front() <= nums[i]) {
                stk.pop_front();
            }
            stk.push_front(nums[i]);
        }
        
        vector<int> res(N, -1);
        for(int i = N-1; i >= 0; i--) {
            if(!stk.empty() && stk.back() == nums[i]) {
                stk.pop_back();
            }
            
            while(!stk.empty() && stk.front() <= nums[i]) {
                stk.pop_front();
            }
            
            if(!stk.empty()) {
                res[i] = stk.front();
            }
            stk.push_front(nums[i]);
        }
        return res;
    }
};

int main() {
    return 0;
}
