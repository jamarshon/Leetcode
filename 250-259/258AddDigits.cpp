/*
258. Add Digits
Given a non-negative integer num, repeatedly add all its 
digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. 
Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?
/*
    Submission Date: 2017-08-25
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <cmath>

using namespace std;

/*
    digital root problem (single digit) value obtained by an iterative 
    process of summing digits, on each iteration using the result from 
    the previous iteration to compute a digit sum

    cyclic around 9
    ...                 10                  20                  30
    0 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 
    ...             40                  50                  60
    5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 
    ...         70                  80                  90
    1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 
*/
class Solution {
public:
    int addDigits(int num) {
        return 1 + (num - 1) % 9;
    }
};

class Solution2 {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        int num_digits = floor(log10(num)) + 1;
        if(num_digits == 1) return num;
        
        int x = 0;
        while(num) {
            x += num % 10;
            num /= 10;
        }
        
        return addDigits(x);
    }
};

int main() {
    Solution s;
    for(int i = 0; i < 100; i++) {
        cout << i << ' ' << s.addDigits(i) << endl;
    }
    return 0;
}