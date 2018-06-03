#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

struct Compare {
    bool operator()(const int& left, const int& right) const { return left < right; }
};


double my_root(int x, double epsilon=1e-9) {
    if(x < 0) return -1;
    double xn = 0;
    double xn_plus_1 = x;
    while(abs(xn - xn_plus_1) >= epsilon) {
        xn = xn_plus_1;
        xn_plus_1 = (xn + x/xn)/2.0;
    } 

    return xn_plus_1;
}

void isqrt(int x){
    int xn = 0;
    int xn_plus_1 = x;
    while(abs(xn - xn_plus_1) > 1) {
        xn = xn_plus_1;
        xn_plus_1 = (xn + x/xn)/2;
    } 

}

bool isprime(int x) {
    if(x < 2) return false;
    for(int i = 2; i <= sqrt(x); i++) {
        if(x % i == 0) return false;
    }
    return true;
}

class Solution {
    int numbits(int x) {
        int res = 0;
        while(x) {
            x &= (x-1);
            res++;
        }
        return res;
    }

    int hibit(unsigned int n) {
        n |= (n >>  1);
        n |= (n >>  2);
        n |= (n >>  4);
        n |= (n >>  8);
        n |= (n >> 16);
        return n - (n >> 1);
    }
public:
    int countPrimeSetBits(int L, int R) {
        unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        unordered_map<int, int> n_to_bits;
        int res = 0;
        for(int i = L; i <= R; i++) {
            int bits;
            if(n_to_bits.count(i/2)) {
                if( n_to_bits[i/2] + 1 != numbits(i)) {
                    cout << i << ' ' << (bitset<32>(i).to_string()) << ' ' << n_to_bits[i/2] << ' ' << numbits(i) << endl;
                }
            }
            if(false && n_to_bits.count(i/2)) {
                bits = n_to_bits[i/2] + 1;
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
    Solution s;
    s.countPrimeSetBits(66, 137);
    return 0;
}



