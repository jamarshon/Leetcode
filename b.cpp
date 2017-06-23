#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;


int main() {
    string a = "x.x.x";
    replace(a.begin(), a.end(), '.', '\0');
    cout << a << endl;
    return 0;
}