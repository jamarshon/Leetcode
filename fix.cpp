#include <iostream>
#include <algorithm>

using namespace std;

void fix(string arr) {
    replace(arr.begin(), arr.end(), '[', '{');
    replace(arr.begin(), arr.end(), ']', '}');
    cout << arr << endl;
}

int main() {
    fix("[[7],[9],[6]]");
}