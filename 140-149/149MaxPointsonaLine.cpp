/*
149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a%b);
    }

    int maxPoints(vector<Point>& points) {
        int N = points.size();

        int max_points = 0;

        for(int i = 0; i < N; i++) {
            int same_count = 0;
            map<tuple<int, int, int>, int> m;

            for(int j = i; j < N; j++) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    same_count++;
                    continue;
                }

                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;

                int gcd_dx_dy = gcd(dx, dy);
                int rem = dx*points[i].y - dy*points[i].x;

                tuple<int, int, int> tp {dx/gcd_dx_dy, dy/gcd_dx_dy, rem/gcd_dx_dy};
                m[tp]++;
            }

            for(auto kv: m) max_points = max(kv.second + same_count, max_points);
            max_points = max(max_points, same_count);
        }

        return max_points;
    }
};

int main() {
    Solution s;
    return 0;
}