using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
	// constructors used in the same order as described above:
  	vector<int> first{1,4,3};                         
  	vector<int> second (4,100);                       // four ints with value 100
  	vector<int> third (first.begin() + 1,first.end());  // iterating through second
  	third.reserve(5);
  	vector<int> fourth (third);                       // a copy of third
  	for (auto elem: third) {
  		cout << elem << endl;
  	}
  	cout << third.size();
	/*int lookup[2][3];
	int rows = sizeof lookup / sizeof lookup[0],
		cols = sizeof lookup[0] / sizeof (int);
	
	generate_n(lookup[0], 3, UniqueNumber); // fill the first row with 1 2 3
	fill_n(lookup[1], 2, 100); // fill the first two elements of the second row with 100
	int copy [2][3];
	fill_n(*copy, sizeof lookup / sizeof(int), 100); // default value of the matrix with 100
	memcpy(copy[1], lookup, sizeof(int) * 3); // fill the second row with the first row of lookup
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			cout << copy[i][j] << " ";
		}
		cout << endl;
	}
	bool c = "ab" < "b";
	string d = "abc";
	string e = d.substr(1, 100);
	int a[4] = {1,2,3,5};
	vector<int> ce = {1,2,4};
	for(auto i:ce) {
		cout << i << endl;
	}
	int aLen = sizeof(a)/sizeof(int);
	int* b = find(begin(a), end(a), 4);
	int* ec = end(a);
	cout << end(a) << endl;
	cout << *ec << endl;
	cout << *b << endl;*/

	return 0;
}

