/*
384. Shuffle an Array
Shuffle a set of numbers without duplicates.


Example:
// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] 
must equally likely to be returned. 
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();

/*
    Submission Date: 2018-07-13
    Runtime: 148 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> original;
    vector<int> curr;
public:
    Solution(vector<int> nums) {
        original = curr = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return curr = original;
    }
    
    /** Returns a random shuffling of the array. */
    /*
    
    swap(curr[i], curr[0, i])
    
    let j = [0, i]
    (1) If i == j, nums[i] does not need to change its position, which has probability 1/(1+i).
    (2) if i !=j, nums[i] needs to be swapped with nums[j]. 
        The probability of any number x in the range [0,i-1] to be at position j = 
            nums[i] changes its position * x is at position i
            = (1-1/(1+i))*(1/i) = 1/(1+i)
    */
    vector<int> shuffle() {
        for(int i = 1; i < curr.size(); i++) {
            swap(curr[i], curr[rand() % (i+1)]);
        }
        return curr;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

int main() {
    return 0;
}
