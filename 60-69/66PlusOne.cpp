/*
66. Plus One
Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <vector>

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;
        int currentSum;
        int carryIn = 1;
        
        while(carryIn > 0 && i >= 0) {
            currentSum = digits[i] + carryIn;
            digits[i] = currentSum % 10;
            carryIn = currentSum / 10;
            i--;
        } 
        
        if(carryIn > 0) digits.emplace(digits.begin(), carryIn);
        return digits;
    }
};

int main() {
	return 0;
}