#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <bitset>

using namespace std;


int main() {

    for(int i = 0; i < 10; i++) {
        int n = i;
        int res = 1;
        while(n) {
            res *= n--;
        }

        cout << '{' << to_string(i) << ", " << res << "},"<< endl;
    }
    
    return 0;
}