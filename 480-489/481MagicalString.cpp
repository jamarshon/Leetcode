/*
481. Magical String
A magical string S consists of only '1' and '2' and obeys the following rules:


The string S is magical because concatenating the number of contiguous 
occurrences of characters '1' and '2' generates the string S itself. 



The first few elements of string S is the following:
S = "1221121221221121122……"



If we group the consecutive '1's and '2's in S, it will be:


1   22  11  2  1  22  1  22  11  2  11  22 ......


and the occurrences of '1's or '2's in each group are:


1   2      2    1   1    2     1    2     2    1    2    2 ......



You can see that the occurrence sequence above is the S itself. 



Given an integer N as input, return the number of '1's in the first N number in 
the magical string S. 


Note:
N will not exceed 100,000.



Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains 
three 1's, so return 3. 

/*
    Submission Date: 2018-07-10
    Runtime: 8 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<char, char> t{{'1', '2'}, {'2', '1'}};
public:
    /*
    if(s[i] == '1') the last character should only occur once so push the opposite
    else the last character should occur twice so push the same then the opposite
    
    keep track of s.size() as well as the one_cnt
    */
    int magicalString(int n) {
        if(n == 0) return 0;
        int one_cnt = 1;
        string s = "1";
        int i = 0;
        while(s.size() < n) {
            if(s[i] == '1') {
                s.push_back(t[s.back()]);
                if(s.back() == '1') one_cnt++;
            } else { // s[i] == '2'
                s.push_back(s.back());
                if(s.back() == '1') one_cnt++;
                if(s.size() < n) { 
                    s.push_back(t[s.back()]);
                    if(s.back() == '1') one_cnt++;
                }
            }
            i++;
        }
        
        return one_cnt;
    }
};

int main() {
    return 0;
}
