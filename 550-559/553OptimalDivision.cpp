/*
553. Optimal Division
Given a list of positive integers, the adjacent integers will perform the float division. 
For example, [2,3,4] -> 2 / 3 / 4.

However, you can add any number of parenthesis at any position to change the priority of operations. 
You should find out how to add parenthesis to get the maximum result, and return the corresponding expression 
in string format. Your expression should NOT contain redundant parenthesis.

Example:
Input: [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant, 
since they don't influence the operation priority. So you should return "1000/(100/10/2)". 

Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2
Note:

The length of the input array is [1, 10].
Elements in the given array will be in range [2, 1000].
There is only one optimal division for each test case.
/*
    Submission Date: 2018-06-30
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    o(n) for a series of number dp_max[i] = nums[i]/dp_min[i+1]
    the minimum would be just divide all the numbers from [1,N)
    as they are all integers meaning its some number divide by all integers 
    in the denominator which would be the smallest. if nums[i] had
    decimals than the smallest would not be dividing all the numbers as it could
    be equivalent to putting a integer number in the numerator
    
    so return nums[0] / (nums[1]/nums[2]/ .... /nums[N-1])
    */
    string optimalDivision(vector<int>& nums) {
        int N = nums.size();
        string res = to_string(nums[0]);
        if(N == 1) return res;
        if(N == 2) return res + "/" + to_string(nums[1]);
        
        res += "/(";
        for(int i = 1; i < N; i++) {
            res += to_string(nums[i]) + (i == N-1 ? ")" : "/");
        }
        
        return res;
    }
    
    /*
    o(n^2) dp where dp_max[i] is the largest number created from [i, N) and dp_min[i] is the smallest
    then dp_max[i] is max(product of numbers between [i, j) /dp_min[j]) for j > i 
    and dp_min[i] is min(product of numbers between [i, j) /dp_max[j]) for j > i 
    
    strings in dp_max and dp_min are surrounded by parenthesis while product of numbers aren't
    
    return dp_max[0]
    */
    string optimalDivision2(vector<int>& nums) {
        int N = nums.size();
        vector<pair<string, double>> dp_max(N, {"", INT_MIN}), dp_min(N, {"", INT_MAX});
        dp_max[N-1] = {to_string(nums[N-1]), nums[N-1]};
        dp_min[N-1] = dp_max[N-1];
        
        if(N == 1) return dp_max[0].first;
        
        for(int i = N-2; i >= 0; i--) {
            string curr_s = to_string(nums[i]);
            double curr = nums[i];
            for(int j = i + 1; j < N; j++) {
                if(dp_max[i].second < curr/dp_min[j].second) {
                    dp_max[i] = {
                        "(" + curr_s + "/" + dp_min[j].first + ")",
                        curr/dp_min[j].second
                    };
                }
                
                if(dp_min[i].second > curr/dp_max[j].second) {
                    dp_min[i] = {
                        "(" + curr_s + "/" + dp_max[j].first + ")",
                        curr/dp_max[j].second
                    };
                }
                
                curr /= nums[j];
                curr_s += "/" + to_string(nums[j]);
            }
        }
        
        return dp_max[0].first.substr(1, dp_max[0].first.size() - 2);
    }
};

int main() {
    return 0;
}