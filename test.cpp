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

int main() {
    int N = 3;
    int M = 3;
    for(int x = 0; x < N + M - 1; x++) {
        for(int i = max(0, x - M + 1); i < min(N, x + 1); i++) {
            cout << i << ' ' << x - i << endl;
        }
        cout << endl;
        for(int i = 0; i < N; i++) {
            int j = x - i;
            if(0 <= j && j < M) cout << i << ' ' << j << endl;
        }
        cout << "end" << endl;
    }
    return 0;
}


