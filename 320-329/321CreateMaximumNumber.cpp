/*
321. Create Maximum Number
Given two arrays of length m and n with digits 0-9 representing two numbers. 
Create the maximum number of length k <= m + n from digits of the two. The relative 
order of the digits from the same array must be preserved. Return an array of the k 
digits. You should try to optimize your time and space complexity.

Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]

Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]

Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
/*
    Submission Date: 2018-05-02
    Runtime: 72 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    /*
        Take i numbers from first array and k - i numbers from second array.
        Merge to find the largest possible string and store the largest for all i.
        O(k^3)
    */
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        string s1, s2;
        int m = nums1.size(), 
            n = nums2.size();
        
        s1.reserve(m);
        s2.reserve(n);
        
        for(auto e: nums1) s1.push_back(e + '0');
        for(auto e: nums2) s2.push_back(e + '0');
        
        string res = "";
        // need to maintain k-i >= 0, i <= m
        for (int i = 0; i <= min(m,k); i++) {
            if(k - i > n) continue; // s2 is too short to produce k-i elements needed
            string tmp = Merge(MaxArray(s1, i), MaxArray(s2, k - i), m, n);
            res = max(res, tmp);
        }
        
        vector<int> out(k);
        for(int i = 0; i < k; i++) out[i] = res[i] - '0';
        return out;
    }
    
    // O(m + n) merge of two substrings of size m and n by choosing letters to make the largest
    // possible.
    string Merge(const string& s1, const string& s2, int m, int n) {
        int i = 0,
            j = 0;
        string res;
        while(i < s1.size() || j < s2.size()) {
            if (s1.substr(min(i, m)) > s2.substr(min(j, n))) {
                res.push_back(s1[i++]);
            } else {
                res.push_back(s2[j++]);
            }
        }
        
        return res;
    }
    
    // maximum subsequence of s with size n, if s.size() <= n return s. O(n)
    string MaxArray(const string& s, int n) {
        string stk = "";
        for(int i = 0; i < s.size(); i++) {
            // if remaining elements and stack have more than enough elements
            // then keep removing from the stack while it is smaller than the current element
            while(s.size() - i + stk.size() > n && !stk.empty() && stk.back() < s[i]) stk.pop_back();
            // if the stk is already size n, no need to push
            if(stk.size() < n) stk.push_back(s[i]);
        }
        return stk;
    }
};

class Solution2 {
public:
    /*
        dp[i][j][k] represents the largest number created from nums1 from [0,i)
        and nums2 [0, j) of size k.

        dp[i][j][k] = max (
            dp[i-1][j][k-1] + nums1[i-1]    take a number from nums1
            dp[i-1][j][k]                   do not take a number 
            dp[i][j-1][k-1] + nums2[j-1]    take a number forom nums2
            dp[i][j-1][k]                   do not take a number
            )
    */
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int kk) {
        string s1, s2;
        for(auto e: nums1) s1.push_back(e + '0');
        for(auto e: nums2) s2.push_back(e + '0');
        vector<vector<vector<string>>> dp(
            s1.size() + 1, vector<vector<string>>(s2.size() + 1, vector<string>(kk + 1)));

        for(int k = 1; k <= kk; k++) {
            for(int i = 0; i <= s1.size(); i++) {
              for(int j = 0; j <= s2.size(); j++) {
                if(i > 0) {
                  dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + string(1, s1[i-1]));
                  dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
                }
                if(j > 0) {
                  dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k-1] + string(1, s2[j-1]));
                  dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k]);
                }
              }
            }
        }

        vector<int> res;
        for(const auto& e: dp[s1.size()][s2.size()][kk]) res.push_back(e - '0');
        return res;
    }
};

int main() {
    return 0;
}