/*
762. Prime Number of Set Bits in Binary Representation
Given two integers L and R, find the count of numbers in the range [L, R] (inclusive) having a prime number of set bits in 
their binary representation.

(Recall that the number of set bits an integer has is the number of 1s present when written in binary. For example, 21 written in binary is 
10101 which has 3 set bits. Also, 1 is not a prime.)

Example 1:

Input: L = 6, R = 10
Output: 4
Explanation:
6 -> 110 (2 set bits, 2 is prime)
7 -> 111 (3 set bits, 3 is prime)
9 -> 1001 (2 set bits , 2 is prime)
10->1010 (2 set bits , 2 is prime)
Example 2:

Input: L = 10, R = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
Note:

L, R will be integers L <= R in the range [1, 10^6].
R - L will be at most 10000.
/*
    Submission Date: 2018-06-02
    Runtime: 105 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
    int numbits(int x) {
        int res = 0;
        while(x) {
            x &= (x-1);
            res++;
        }
        return res;
    }
public:
    /*
        the number of bits for a number i = number of bits for i/2 + the last bit of i
        e.g 10101 = number of bits for 1010 + last bit which is 1
    */
    int countPrimeSetBits(int L, int R) {
        unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        unordered_map<int,int> n_to_bits;
        int res = 0;
        for(int i = L; i <= R; i++) {
            int bits;
            if(n_to_bits.count(i)) {
                bits = n_to_bits[i/2] + (i % 2);
            } else {
                bits = numbits(i);
            }
            n_to_bits[i] = bits;
            res += primes.count(bits);
        }
        return res;
    }
};

int main() {
    return 0;
}