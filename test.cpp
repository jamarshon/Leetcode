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

struct Point {
    int x,y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

Point FindMissing(vector<Point> listA, vector<Point> listB) {
    int length = listA.size();
    int low = 0;
    int high = length - 1;
    
    while(low <= high) {
        int mid = low + (high - low)/2;
        if(listA[mid] == listB[mid]) { // [a,..,b, c] [a, ..b, c,d]
            low = mid + 1;
        } else { // [a,...b,c] a, x ... 
            high = mid - 1;
        }
    }

    return listB[low];
}


int main() {
    vector<Point> a{{1,1},{2,2},{3,3},{4,4}},
                b{{1,1},{2,2},{3,3},{4,4},{5,5}};
    Point t = FindMissing(a,b);
    cout << t.x << ' ' << t.y << endl;

    return 0;
}