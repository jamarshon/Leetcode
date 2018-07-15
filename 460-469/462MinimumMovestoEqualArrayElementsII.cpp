/*
462. Minimum Moves to Equal Array Elements II
Given a non-empty integer array, find the minimum number of moves required to 
make all array elements equal, where a move is incrementing a selected element 
by 1 or decrementing a selected element by 1. 

You may assume the array's length is at most 10,000.

Example:
Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one 
element): 

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]

/*
    Submission Date: 2018-07-01
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    O(nlogn) given that it is sorted compute the sum and say that is the lhs_cost
    rhs_cost = 0. as i decreases, there is a block of width i+1 and height diff
    that is removed from lhs_cost and a block of width N-i-1 and height diff that
    is added to the rhs_cost

    compute the lhs_cost, rhs_cost for all i and take the minimum.
    */
    typedef long long ll;
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        ll lhs_cost = 0;
        for(const auto& e: nums) lhs_cost += nums.back() - e;
        ll res = lhs_cost;
        
        ll rhs_cost = 0;
        int N = nums.size();
        for(int i = N-2; i >= 0; i--) {
            int diff = nums[i+1] - nums[i];
            lhs_cost -= diff*(i+1);
            rhs_cost += diff*(N-i-1);
            res = min(res, lhs_cost + rhs_cost);
        }
        return res;
    }
};

class Solution2 {
public:
    /*
    proof is suppose x is between two numbers (y, z where y <= z) 
    then u can say the sum of deviation is (x-y) + (z-x) = z - y. 
    so given an array of size n, u can just keep removing the min and max elements 
    which would be equivalent to finding the median as it is the x between all the pairs of y,z.
    (need y,z to be as far apart as possible in order to ensure x is between them)
    */
    int minMoves2_sort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        int N = nums.size();
        for(int i = 0; i < N/2; i++) {
            res += abs(nums[i] - nums[N-i-1]);
        }
        return res;
    }

    int minMoves2(vector<int>& nums) {
        int res = 0;
        int N = nums.size();
        nth_element(nums.begin(), nums.begin() + N/2, nums.end());
        
        int median = nums[N/2];
        
        for(const auto& e: nums) {
            res += abs(e - median);
        }
        return res;
    }
};

int main() {
    return 0;
}