/*
223. Rectangle Area
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as
shown in the figure. Assume that the total area is never beyond the maximum
possible value of int.
    ----- (C,D)
    |   |
    |   |
    -----
(A,B)

    ----- (G,H)
    |   |
    |   |
    -----
(E,F)


/*
    Submission Date: 2017-08-07
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution2 {
 public:
  // A----C and E---G represents intervals say close_x is A---C meaning C <= G
  // if C < E width is 0 as no intersect
  // else width = C - max(A,E)
  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    pair<int, int> close_x{A, C}, far_x{E, G};
    if (C > G) swap(close_x, far_x);
    int width = 0;
    if (far_x.first < close_x.second) {  // check if two intervals intersect
      width = close_x.second - max(close_x.first, far_x.first);
    }

    pair<int, int> close_y{B, D}, far_y{F, H};
    if (D > H) swap(close_y, far_y);
    int height = 0;
    if (far_y.first < close_y.second) {  // check if two intervals intersect
      height = close_y.second - max(close_y.first, far_y.first);
    }

    int intersect_area = height * width;
    int total_area = (C - A) * (D - B) + (G - E) * (H - F);
    return total_area - intersect_area;
  }
};

class Solution {
 public:
  // for A---C and E--G it is just min(C,G) - max(A,E) if this is negative
  // ie no intersection min(C,G) < max(A,E) just make right = left so width is
  // zero
  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int left = max(A, E), right = max(min(C, G), left);
    int bottom = max(B, F), top = max(min(D, H), bottom);

    int intersect_area = (top - bottom) * (right - left);
    int total_area = (C - A) * (D - B) + (G - E) * (H - F);

    return total_area - intersect_area;
  }
};

int main() { return 0; }