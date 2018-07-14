#include <iostream>
#include <fstream>
#include <cmath>
 
using namespace std;

bool IsPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= n/i; i++) if(n % i == 0) return false;
    return true;
}

int main() {
    ofstream fout ("primes.out");
    for(int i = 0; i < 10; i++) if(IsPrime(i)) fout << i << endl;
    return 0;
}


