using namespace std;
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    // vector<vector<int>> threeSum(vector<int>& nums) {
    //     int len = nums.size();
    //     if(len < 3) return {{}};
        
    //     vector<vector<int>> result;
    //     sort(nums.begin(), nums.end());
    //     for(int b: nums) cout << b; cout << endl;
    //     for(int i = 1; i < len; i++) {
    //         int low = i + 1;
    //         int high = len - 1;
    //         int target = -1*nums[i];
    //         while(low < high) {
    //             if(nums[low] + nums[high] == target) {
    //                 result.push_back({target, nums[low], nums[high]});
    //                 low++;
    //                 high--;
                    
    //             } else if(nums[low] + nums[high] > target) {
    //                 high--;
    //             } else {
    //                 low++;
    //             }
    //         }
    //         break;
    //     }
        
    //     return result;
    // }
};
int main() {
    Solution s;
    // vector<int> v{-1,0,1,2,-1,-4};
    // vector<vector<int>> c = s.threeSum(v);
    // for(auto t: c){
    //   for(int e: t) cout << e; cout << endl;
    // }
    cout << INT_MAX;
    int *p = (int *)(1000);
    int a = 1000;
    int* c = new int(1000);
    cout << *c;
    return 0;
}