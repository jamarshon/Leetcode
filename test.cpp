using namespace std;
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
	unordered_map <string, vector<int>> hashTable;
	hashTable["jason"].push_back(3);
	hashTable["jason"].push_back(4);
	cout << hashTable["jason"].size() << endl;
	return 0;
}