#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

int solution(string &A, string &B) {
    // write your code in C++14 (g++ 6.2.0)
    if(A.find(B) != string::npos) {
        return 1;
    }

     /*
    B should follow the format of suffix A followed by A any number of times
    followed by prefix A
    */

    int res = -1;
    size_t a_ind = B.find(A);
    if(a_ind == string::npos) {
        // B has to be rotated A -> suffix A followed by prefix A
        for(int i = 0; i < B.size(); i++) {
            string rotate_B = B.substr(i) + B.substr(0,i);
            if(rotate_B == A) return 1;
        }
        return -1;
    } else {
        string prefix_B = B.substr(0, a_ind);
        int back = B.size() - prefix_B.size();

        string middle_B = B.substr(a_ind, B.size() - prefix_B.size() - a_ind);
        string suffix_B = B.substr(back);

        string rotate_B = suffix_B + prefix_B + middle_B;

        int i = 0;
        int N = A.size();
        int A_occurences = 0;
        while(i < rotate_B.size()) {
            string chunk = rotate_B.substr(i, N);
            if(chunk != A) return -1;
            A_occurences++;
            i += N;
        }

        return A_occurences + 1;
    }

    return 0;
}

int main() {
    string a, b;
    a = "abcd";
    b = "cdabcdab";
    cout << solution(a, b) << endl;
    // test("abcd");
    return 0;
}