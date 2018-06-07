#include <bitset>
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


/*
An integer whose base-ten representation consists only of zero and one is called a  "zero-one".

 

Given an arbitrary integer N, find the string S that represents smallest positive "zero-one"  integer which is a multiple of N.  (It is mathematically guaranteed that every N has at least one S).

 

Input Format
One integer, N.

 

Output Format
Type cast the integer S to a string and return that string.

 

Constraint:
0 < N < 100,000
S should be a zero-one integer as defined above. 
There should not be any leading zeros.

 

Sample Input:
4

Sample Output:
100
 */
typedef long long ll;
string Zero_One(int num) {
    unordered_set<ll> visited;
    queue<pair<string,ll>> q;
    
    q.emplace("1", 1);
    visited.insert(1);
    
    string s;
    ll state;
    while(!q.empty()) {
        tie(s, state) = q.front();
        q.pop();
        
        if(state == 0) return s;
        if(!visited.count((state * 10) % num)) {
            q.emplace(s + "0", (state * 10) % num);
            visited.insert(q.back().second);
        }
        if(!visited.count((state * 10 + 1) % num)) {
            q.emplace(s + "1", (state * 10 + 1) % num);
            visited.insert(q.back().second);
        }
    }
    
    return "";
}

int main() {
    long long x = 111111111111111111111111111111111111111111111;
    cout << x << endl;
    return 0;
}


