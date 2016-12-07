using namespace std;
#include <iostream>
#include <cmath>

class Solution {
public:
	bool isPalindrome(int x) {
 		if(x < 0){ return false; }
    	int i = floor(log10(x));
    	while(i > 0) {
    		int msn = floor(x / pow(10, i));
    		int lsn = x % 10;
    		if(msn != lsn) {
    			return false;
    		}
    		x %= (int)pow(10, i);
    		x /= 10;
    		i -= 2;
    	}
    	return true;
    }
};

int main() {
	Solution s;
	int input = -2147483648;
	cout << s.isPalindrome(input) << endl;
	return 0;
}