/*
709. To Lower Case
Implement function ToLowerCase() that has a string parameter str, and returns 
/*
    Submission Date: 2018-07-12
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string toLowerCase(string str) {
        for(auto& c: str) c = tolower(c);
        return str;
    }
};

int main() {
    return 0;
}
