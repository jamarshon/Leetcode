using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
int toBase(int num, int base) {
    int result = 0;
    int index = 0;
    while(num) {
        result += (num % base)*pow(10, index++);
        num /= base;
    }
    return result;
}

string toBase2(int num, int base) {
    string result;
    while(num) {
        int rem = num % base;
        char c = rem < 10 ? rem + 48 : 65 + rem - 10;
        result = c + result;
        num /= base;
    }
    return result;
}

bool isPalindrome2(string x) {
    int len = x.size();
    for(int i = 0, iLen = len/2; i <= iLen; i++) {
        if(x[i] != x[len - i - 1]) return false;
    }
    return true;
}

bool isPalindrome(int x) {
    int len = floor(log10(x)) + 1;
    int mask = pow(10, len - 1);

    while(x) {
        int rightDigit = x % 10;
        int leftDigit = x / mask;
        if(rightDigit != leftDigit) return false;
        x %= mask;
        x /= 10;
        mask /= 100;
    }

    return true;
};

int main()
{
    cout << toBase(73441, 11) << endl;
    cout << toBase2(73441, 11) << endl;
    cout << isPalindrome2("735637") << endl;
    // cout << fllog2(65) << endl;
    return 0;
}