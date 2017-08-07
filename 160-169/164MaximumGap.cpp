/*
164. Maximum Gap
Given an unsorted array, find the maximum difference between the successive elements in its 
sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit 
signed integer range.

/*
    Submission Date: 2017-08-06
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
    vector<int> freq_, temp_space_;
public:
    // time complexity is O(d*(n + k)) where k is the radix or base (k=10)
    // d is the number of counting sort calls (max number of digits)
    void radix_sort(vector<int>& nums) {
        int N = nums.size();
        freq_.assign(10, 0);
        temp_space_.assign(N, 0);

        int divide = 1;
        while(count_sort(nums, divide, N)){
            divide *= 10;
        }
    }

    // returns true if it moves anything
    bool count_sort(vector<int>& nums, int divide, int N) {
        fill(freq_.begin(), freq_.end(), 0);
        function<int(int)> get_digit = [&divide](int num){ return num/divide % 10; };

        // get the frequency of each number
        int less_than_divide_count = 0;
        for(auto num: nums) {
            less_than_divide_count += num < divide;
            freq_[get_digit(num)]++;
        }

        if(less_than_divide_count == N) return false;

        // convert number to indices
        for(int i = 1; i < 10; i++) {
            freq_[i] += freq_[i - 1];
        }

        // write to temp_space_ starting from the back to keep stable
        for(int i = N-1; i >= 0; i--) {
            int& idx = freq_[get_digit(nums[i])];
            temp_space_[idx - 1] = nums[i]; 
            idx--;
        }

        for(int i = 0; i < N; i++) {
            nums[i] = temp_space_[i];
        }

        return true;
    }

    int maximumGap(vector<int>& nums) {
        int N = nums.size();
        if(N < 2) return 0;

        radix_sort(nums);

        int max_gap = 0;
        for(int i = 1; i < N; i++) 
            max_gap = max(max_gap, nums[i] - nums[i-1]);
        return max_gap;
    }
};

int main() {
    Solution s;
    vector<int> v{10,4,2,23,30,1};
    // vector<int> v{5,4,2,6,9,1};
    int r = s.maximumGap(v);
    cout << "r=" << r << endl;
    return 0;
}