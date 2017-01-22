using namespace std;
#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0, j = 1, len = nums.size();
        if(len == 0) return 0;
        
        while(true) {
            while(j < len && nums[i] == nums[j]) j++;
            if(j == len - 1) return i + 1;
            swap(nums[++i], nums[j++]);
        }
    }
};

int main() {
   Solution s;
   vector<int> v = {1,1,1,2,2,3};
   s.removeDuplicates(v);
   for(int i: v) cout << i << endl;
    return 0;
}