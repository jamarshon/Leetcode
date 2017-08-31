#include <iostream>

using namespace std;

class A {
public:
    A(int b){ 
        cout << b << endl;
    }
};

int main() {
    A* a;
    a = new A(1);
    return 0;
}