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

int main() {
    vector<int> v;
    sort(v.begin(), v.end(), Compare());
    priority_queue<int,vector<int>, greater<int>> pq;
    priority_queue<int,vector<int>, Compare> pq2;
    return 0;
}


