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
    fix("[[2], [1], [1,2,2], [2,2], [1,2], [] ]");
    return 0;
}

