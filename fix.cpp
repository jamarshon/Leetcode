#include <iostream>
#include <algorithm>

using namespace std;

void fix(string arr) {
    replace(arr.begin(), arr.end(), '[', '{');
    replace(arr.begin(), arr.end(), ']', '}');
    cout << arr << endl;
}

template <typename T>
void print(vector<T> v) {
    for(auto e: v) cout << e << ' ';
    cout << endl;
}

template <typename T> 
void print2(vector<vector<T>> v) {
    for(auto v2: v) print(v2);
}

int main() {
    fix("[[-6,9],[1,6],[8,10],[-1,4],[-6,-2],[-9,8],[-5,3],[0,3]]");
    return 0;
}

