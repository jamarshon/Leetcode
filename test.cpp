using namespace std;
#include <iostream>
#include <algorithm>

int main() {
	function<void()> a = [](){ cout << "hello world"<< endl; };
	a();
	return 0;
}