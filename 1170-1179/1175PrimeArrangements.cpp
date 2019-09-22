/*
1175. Prime Arrangements
Return the number of permutations of 1 to n so that prime numbers are at prime
indices (1-indexed.)

(Recall that an integer is prime if and only if it is greater than 1, and cannot
be written as a product of two positive integers both smaller than it.)

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is
not because the prime number 5 is at index 1.

Example 2:

Input: n = 100
Output: 682289015

Constraints:

  1 <= n <= 100
/*
  Submission Date: 2019-09-21
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int mod = 1e9 + 7;

  // get the number of primes from [2, n]
  int sieve(int n) {
    int cnt = 0;
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= sqrt(n); i++) {
      if (is_prime[i]) {
        cnt++;
        for (int j = i * i; j <= n; j += i) {
          is_prime[j] = false;
        }
      }
    }
    for (int i = sqrt(n) + 1; i <= n; i++) cnt += is_prime[i];
    return cnt;
  }

  long long factorial(int n) {
    long long res = 1;
    for (int i = 1; i <= n; i++) res = (res * i) % mod;
    return res;
  }

  int numPrimeArrangements(int n) {
    /*
    return num_primes! * (n - num_primes)!
    because there are num_primes! ways to organize the primes
    and (n - num_primes)! ways to organize the composites
    */
    int num_primes = sieve(n);
    int num_composites = n - sieve(n);
    return (factorial(num_primes) * factorial(num_composites)) % mod;
  }
};

int main() { return 0; }
