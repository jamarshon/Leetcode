/*
858. Mirror Reflection
There is a special square room with mirrors on each of the four walls.  Except
for the southwest corner, there are receptors on each of the remaining corners,
numbered 0, 1, and 2.

The square room has walls of length p, and a laser ray from the southwest
corner first meets the east wall at a distance q from the 0th receptor.

Return the number of the receptor that the ray meets first.  (It is guaranteed
that the ray will meet a receptor eventually.)

Example 1:

Input: p = 2, q = 1
Output: 2
Explanation: The ray meets receptor 2 the first time it gets reflected back to
the left wall.

Note:

  1 <= p <= 1000
  0 <= q <= p
/*
  Submission Date: 2019-02-17
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  expand these pxp blocks so that they form a grid in cartesian
  the line q/p*x must intersect with a point that is (aq, bq)
  where a is the number of qblocks horizontally and b is for vertically

  q/p*(aq) = bq
  aq^2/p = bq
  aq/p = b
  aq = bp

  so find lcm of p and q and this would equal aq and bp
  lcm(c,d) = c*d/gcd(c,d)


  for the qblocks if a is even it means the receptors are in the same place
  else it is flipped horizontally
  if b is odd it is flipped vertically

  a = p/gcd(p,q)
  b = q/gcd(p,q)

  the grid for the qblocks would be (bottom row is a,b = 0,0)
  ...
  [2,1,2,1,2]...
  [0,x,0,x,0]...
  [2,1,2,1,2]...
  [x,0,x,0,x]...

  the guarantee is that the cell will not end on x
  */
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  int mirrorReflection(int p, int q) {
    int g = gcd(p, q);
    int a = p / g;
    int b = q / g;
    if (b % 2 == 0) {
      // not going to be x
      return 0;
    } else {
      return a % 2 == 0 ? 2 : 1;
    }
  }
};

int main() { return 0; }
