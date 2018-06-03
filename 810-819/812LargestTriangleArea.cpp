/*
812. Largest Triangle Area
You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.

Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation: 
The five points are show in the figure below. The red triangle is the largest.

Notes:

3 <= points.length <= 50.
No points will be duplicated.
 -50 <= points[i][j] <= 50.
Answers within 10^-6 of the true value will be accepted as correct.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int res = 0;
        int N = points.size();
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                for(int k = j + 1; k < N; k++) {
                    /*
                    given points (a,b), (c,d), (e,f)
                    vector A = (c-a, d-b, 0) and B = (e-a, f-b, 0)
                    cross product of A and B is 
                    ((d-b)*0 - (f-b)*0, -((c-a)*0 - (e-a)*0), (c-a)*(f-b) - (e-a)*(d-b))
                    (0, 0, (c-a)*(f-b) - (e-a)*(d-b))
                    magnitude of A cross B is area of parallelogram so divide by half
                    */
                    int c_minus_a = points[j][0] - points[i][0];
                    int d_minus_b = points[j][1] - points[i][1];
                    int e_minus_a = points[k][0] - points[i][0];
                    int f_minus_b = points[k][1] - points[i][1];
                    
                    res = max(res, abs(c_minus_a*f_minus_b - e_minus_a*d_minus_b));
                }
            }
        }
        return res/2.0;
    }
};

int main() {
    return 0;
}