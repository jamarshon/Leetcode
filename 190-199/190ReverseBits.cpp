/*
190. Reverse Bits
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 
(represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i < 32; i++) {
            res |= n % 2;
            n /= 2;
            if(i != 31) res *= 2;
        }
        return res;
    }
};

int main() {
    return 0;
}