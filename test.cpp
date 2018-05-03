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

int main() {
    int n = 129140163;
    const double& eps = numeric_limits<double>::epsilon();
    const double& frac = log(n)/log(3);
    const double& mod_one = fmod(frac, 1.0);
    printf("%.18f\n", mod_one);
    printf("%.18f\n", frac);
    // double a = log(n)/log(3);
    // double ep = numeric_limits<double>::epsilon();
    // printf("%.18f\n", round(a));
    // printf("%.18f\n",  abs(a-round(a)));
    // printf("%.18f\n",  ep);
    // printf("%.18f\n",  16*ep);
    // printf("%.18f\n",   numeric_limits<float>::epsilon());
    // for(int i = 0; i < 100; i++) {
        // if(abs(a-round(a)) <= i*ep) {
            // cout << i << endl;
            // break;
        // }
    // }

    return 0;
}