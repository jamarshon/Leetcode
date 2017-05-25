/*
50. Pow(x, n)
Implement pow(x, n)

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
class Solution {
public:
    double myPow(double x, int n) {
        if(n == INT_MIN) {
            double res = myPow(x, -1*((n+1)/2 - 1));
            return 1/(res*res);
        }
        if(x == 1) return 1;
        if(n < 0) return 1/myPow(x, -n);
        if(n == 0) return 1;
        if(n == 1) return x;
        double res = myPow(x, n/2);
        res *= res;
        if(n % 2 == 0) {
            return res;
        } else {
            return x*res;
        }
    }
};

int main() {
    return 0;
}