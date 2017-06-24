#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <bitset>

using namespace std;


int main() {
    vector<int> v {0,1,3,2,6,7,5,4};
     for(auto i: v) cout << bitset<3>(i).to_string() << endl;
    return 0;
}