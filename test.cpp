using namespace std;
#include <iostream>
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, 0, nums.size(), target);
    }
    int binarySearch(vector<int>& nums, int low, int high, int target) {
        cout << "here" << endl;
        if(low >= high) return -1;
        int midIndex = (low + high) >> 1,
            midValue = nums[midIndex];

        if(midValue == target) return midIndex;
        
        if(nums[low] < midValue) {
        		cout << midValue << endl;
            if(nums[low] < target && target < midValue) {
                return binarySearch(nums, low, midIndex, target);
            } else {
                return binarySearch(nums, midIndex, high, target);
            }
        } else {
            if(nums[low] < target || target < midValue) {
               return binarySearch(nums, low, midIndex, target);
            } else {
                return binarySearch(nums, midIndex, high, target);
            }
        }
    }
};
int main() {
	Solution s;
	vector<int> v = {1, 3};
	cout << s.search(v, 1) << endl;
	return 0;
}


