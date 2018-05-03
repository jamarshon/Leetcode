/*
371. Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.
/*
    Submission Date: 2018-05-02
    Runtime: 2 ms
    Difficulty: EASY
*/
#include <iostream>
#include <bitset>

using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
      // include the sign bit.
      bitset<32> res(0);
      bitset<32> aa(a);
      bitset<32> bb(b);

      int carry = 0;
      for(int i = 0; i < 32; i++) {
        int a_d = aa.test(i);
        int b_d = bb.test(i);

        res.set(i, a_d ^ b_d ^ carry);
        carry = (a_d && b_d) || (b_d && carry) || (a_d && carry);
      }

      return res.to_ullong();
    }
};

class Solution2 {
public:
    int getSum(int a, int b) {
        int res = 0;
        int carry = 0;
        
        for(int i = 0; i < 32; i++) {
            const int a_d = (1 << i) & a;
            const int b_d = (1 << i) & b;
            res |= a_d ^ b_d ^ carry;
            carry = ((a_d & b_d) | (b_d & carry) | (a_d & carry)) << 1;
        } 
        
        return res;
    }
};

int main() {
    return 0;
}