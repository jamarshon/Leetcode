/*
204. Count Primes
Count the number of prime numbers less than a non-negative number, n.

/*
    Submission Date: 2017-08-03
    Runtime: 43 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if(n <= 2) return 0;
        vector<bool> mask(n, true);
        
        mask[0] = mask[1] = false;
        
        int sqrt_n = sqrt(n);
        for(int i = 2; i <= sqrt_n; i++) {
            if(mask[i]) {
                int temp = i*i;
                while(temp < n) {
                    mask[temp] = false;
                    temp += i;
                }
            }
        }
        // for(auto e: mask) cout << e << ' '; cout << endl;
        return count(mask.begin(), mask.end(), true);
    }
};

int main() {
    return 0;
}