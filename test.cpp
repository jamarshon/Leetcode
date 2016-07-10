using namespace std;
#include <unordered_map>
#include <iostream>
#include <vector>
int main() {
	int arr[] = {1,2,3};
	vector<int> a;
	a(begin(arr), end(arr));
	cout << a.size();
	return 0;
}