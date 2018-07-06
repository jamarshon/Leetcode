
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
825. Friends Of Appropriate Ages
Some people will make friend requests. The list of their ages is given and ages[i] 
is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not 
friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.
/*
    Submission Date: 2018-06-29
    Runtime: 39 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    1 <= ages[i] <= 120
    so have a[i] be the frequency of age i
    for an age i, there should be an age j <= i which can be friends with
    j > 0.5*i + 7     ie. j = 0.5*i + 8
    j must be !(j > 100 && i < 100) note this will never occur as j <= i
    
    so for every person of age i (a[i]) and every person of age j (a[j])
    there can be a[j] * a[i] friend requests made as for a person in j
    can make friend with every person in i (a[i] times) and there are a[j] of these people
    
    if j == i, then it is a[i] * (a[i] - 1) as every person in i 
    can make friends with a[i] - 1 people as they cannot make friends with themself
    */
    int numFriendRequests(vector<int>& ages) {
        vector<int> a(121, 0);
        
        for(const auto& e: ages) a[e]++;
        
        int res = 0;
        for(int i = 1; i < 121; i++) {
            for(int j = 0.5*i + 8; j <= i; j++) res += a[j] * (a[i] - (i == j));
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
830. Positions of Large Groups
In a string S of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

The final answer should be in lexicographic order.

 

Example 1:

Input: "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
Example 2:

Input: "abc"
Output: []
Explanation: We have "a","b" and "c" but no large group.
Example 3:

Input: "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
 

Note:  1 <= S.length <= 1000
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY 
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        vector<vector<int>> res;
        for(int i = 0; i < S.size();) {
            int j = i;
            while(j < S.size() && S[i] == S[j]) j++;
            if(j - i >= 3) {
                res.push_back({i, j-1});
            }
            i = j;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
832. Flipping an Image
Given a binary matrix A, we want to flip the image horizontally, then invert it, and return the resulting image.

To flip an image horizontally means that each row of the image is reversed.  For example, flipping [1, 1, 0] horizontally results in [0, 1, 1].

To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0. For example, inverting [0, 1, 1] results in [1, 0, 0].

Example 1:

Input: [[1,1,0],[1,0,1],[0,0,0]]
Output: [[1,0,0],[0,1,0],[1,1,1]]
Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
Example 2:

Input: [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Notes:

1 <= A.length = A[0].length <= 20
0 <= A[i][j] <= 1
/*
    Submission Date: 2018-05-31
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        for(auto& row: A) {
            reverse(row.begin(), row.end());
            for(auto& el: row) el ^= 1;
        }
        
        return A;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
836. Rectangle Overlap
A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the coordinates of its bottom-left corner, and (x2, y2) are 
the coordinates of its top-right corner.

Two rectangles overlap if the area of their intersection is positive.  To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two rectangles, return whether they overlap.

Example 1:

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
Example 2:

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
Notes:

Both rectangles rec1 and rec2 are lists of 4 integers.
All coordinates in rectangles will be between -10^9 and 10^9.
/*
    Submission Date: 2018-05-24
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool intersects(int a1, int a2, int b1, int b2) {
        return !(b1 >= a2 || a1 >= b2);
    }
    
    // Check if x intervals intersect and y intervals intersect
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return intersects(rec1[0], rec1[2], rec2[0], rec2[2]) && intersects(rec1[1], rec1[3], rec2[1], rec2[3]);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
840. Magic Squares In Grid
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).
Example 1:

Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:
438
951
276

while this one is not:
384
519
762

In total, there is only one magic square inside the given grid.
Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
0 <= grid[i][j] <= 15
/*
    Submission Date: 2018-06-24
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool IsMagicSquare(const vector<vector<int>>& grid, int i, int j) {
        unordered_set<int> st;
        vector<int> row_sum(3, 0), col_sum(3, 0);
        int diag1 = 0, diag2 = 0;
        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                int e = grid[i+y][j+x];
                if(e < 1 || e > 9 || st.count(e)) return false;
                row_sum[y] += e;
                col_sum[x] += e;
                if(y == x) diag1 += e;
                if(x + y == 2) diag2 += e;
            }
        }
        
        for(int x = 1; x < 3; x++) {
            if(row_sum[x] != row_sum[x-1]) return false;
            if(col_sum[x] != col_sum[x-1]) return false;
        }
        
        return diag1 == diag2;
    }
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        int res = 0;
        for(int i = 0; i < N - 2; i++) {
            for(int j = 0; j < M - 2; j++) {
                res += IsMagicSquare(grid, i, j);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
841. Keys and Rooms
There are N rooms and you start in room 0.  Each room has a distinct number in 0, 1, 2, ..., N-1, 
and each room may have some keys to access the next room. 

Formally, each room i has a list of keys rooms[i], and each key rooms[i][j] is an integer in [0, 1, ..., N-1] 
where N = rooms.length.  A key rooms[i][j] = v opens the room with number v.

Initially, all the rooms start locked (except for room 0). 

You can walk back and forth between rooms freely.

Return true if and only if you can enter every room.

Example 1:

Input: [[1],[2],[3],[]]
Output: true
Explanation:  
We start in room 0, and pick up key 1.
We then go to room 1, and pick up key 2.
We then go to room 2, and pick up key 3.
We then go to room 3.  Since we were able to go to every room, we return true.
Example 2:

Input: [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can't enter the room with number 2.
Note:

1 <= rooms.length <= 1000
0 <= rooms[i].length <= 1000
The number of keys in all rooms combined is at most 3000.
/*
    Submission Date: 2018-06-24
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        queue<int> q;
        unordered_set<int> visited;
        
        q.push(0);
        visited.insert(0);
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            for(auto e: rooms[curr]) {
                if(!visited.count(e)) {
                    q.push(e);
                    visited.insert(e);
                }
            }
        }
        
        return visited.size() == rooms.size();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
844. Backspace String Compare
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string eval(string s) {
        string res = "";
        for(const auto& c: s) {
            if(c == '#') {
                if(!res.empty()) res.pop_back();
            } else {
                res.push_back(c);
            }
        }
        return res;
    }
    bool backspaceCompare(string S, string T) {
        return eval(S) == eval(T);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
849. Maximize Distance to Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty. 

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 

Return that maximum distance to closest person.

Example 1:

Input: [1,0,0,0,1,0,1]
Output: 2
Explanation: 
If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
If Alex sits in any other open seat, the closest person has distance 1.
Thus, the maximum distance to the closest person is 2.
Example 2:

Input: [1,0,0,0]
Output: 3
Explanation: 
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Note:

1 <= seats.length <= 20000
seats contains only 0s or 1s, at least one 0, and at least one 1.
/*
    Submission Date: 2018-06-24
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        if(seats.empty()) return INT_MAX;
        
        int N = seats.size();
        // left[i] indicates the distance to the closest 1 to the left 
        vector<int> left(N, INT_MAX);
        for(int i = 0; i < N; i++) {
            if(seats[i] == 1) left[i] = 0;
            else if(i > 0 && left[i-1] < INT_MAX) {
                left[i] = left[i-1] + 1;
            }
        }
        
        int right = INT_MAX;
        int res = INT_MIN;
        /*
        if there is at least one 1 and 0
        left[i] will be INT_MAX until the first 1 then some number after it 
        
        hence if starting from the back, the number will not be INT_MAX so right
        will be correctly minimized.
        */
        for(int i = N-1; i >= 0; i--) {
            if(seats[i] == 1) right = 0;
            else if(right < INT_MAX) right++;
            
            res = max(res, min(left[i], right));
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
852. Peak Index in a Mountain Array
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain, return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
/*
    Submission Date: 2018-06-24
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int low = 0;
        int high = A.size() - 1;
        while(low <= high-2) { // at least 3 elements
            int mid = low + (high-low)/2;
            if(A[mid-1] < A[mid] && A[mid] > A[mid+1]) {
                return mid;
                
            /* 
            a number and the next number has only two conditions < and >
            if < then it is before the peak, so go right
            if > then it is after the peak, so go left
            
            need to include mid in the search as it can be either the left
            or right boundary to the peak
            */
            } if(A[mid-1] < A[mid]) {
                low = mid; 
            } else { // A[mid-1] > A[mid]
                high = mid;
            }
        }
        
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
856. Score of Parentheses
Given a balanced parentheses string S, compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
/*
    Submission Date: 2018-06-29
    Runtime: 4 ms
    Difficulty:MEDIUM 
*/
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string S) {
        // first is the value or -1 if it is a character '(' 
        stack<pair<int, char>> stk;
        for(const auto& e: S) {
            if(e == '(') {
                stk.emplace(-1, '(');
            } else { // e == ')'
                // S is balanced so keep going back until '(' (ie not value)
                // add all the numbers in between and multiply by 2
                int in_between = 0;
                while(stk.top().first != -1) {
                    in_between += stk.top().first;
                    stk.pop();
                }
                
                stk.pop();
                stk.emplace(max(1, 2*in_between), 'r');
            }
        }
        
        int res = 0;
        // since S is balanced then stk must only contain values so add 
        // up and return value
        while(!stk.empty()) {
            res += stk.top().first;
            stk.pop();
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
859. Buddy Strings
Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool buddyStrings(string A, string B) {
        if(A.size() != B.size()) return false;
        
        vector<int> diff;
        for(int i = 0; i < A.size(); i++) {
            if(A[i] != B[i]) {
                diff.push_back(i);
                if(diff.size() > 2) return false;
            }
        }
        
        if(diff.size() == 1) return false;
        if(diff.size() == 0) return unordered_set<char>(A.begin(), A.end()).size() < A.size();
        return A[diff[0]] == B[diff[1]] && A[diff[1]] == B[diff[0]];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
860. Lemonade Change
At a lemonade stand, each lemonade costs $5. 

Customers are standing in a queue to buy from you, and order one at a time 
(in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  
You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.

 

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:

Input: [5,5,10]
Output: true
Example 3:

Input: [10,10]
Output: false
Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can't give change of $15 back because we only have two $10 bills.
Since not every customer received correct change, the answer is false.
 

Note:

0 <= bills.length <= 10000
bills[i] will be either 5, 10, or 20.
/*
    Submission Date: 2018-07-01
    Runtime: 30 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        // change[0] is number of 5's and change[1] is number of 10's.
        // 20's will never be given back so no need to count them.
        vector<int> change(2, 0);
        for(const auto& e: bills) {
            if(e == 5) {
                change[0]++;
            } else if(e == 10) { // can only give a 5 back
                if(change[0] == 0) return false;
                change[0]--;
                change[1]++;
            } else { // e == 20 can give back either 5 and 10 or 3 fives
                if(change[1] > 0 && change[0] > 0) { // try to give back the 10 first as it is less useful
                    change[1]--;
                    change[0]--;
                } else if(change[0] >= 3) {
                    change[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
861. Score After Flipping Matrix
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: 
changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, 
and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
/*
    Submission Date: 2018-07-01
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void FlipRow(vector<vector<int>>& A, int row, int M) {
        for(int j = 0; j < M; j++) A[row][j] ^= 1;
    }
    
    void FlipCol(vector<vector<int>>& A, int col, int N) {
        for(int i = 0; i < N; i++) A[i][col] ^= 1;
    }
    
    /*
    First get all the the elements in A[i][0] to be 1 by toggling rows
    this is because having a 1 in the left most column gives the greatest value 1000 > 0111
    Then for each column, flip the column if it gives a greater amount of 1's in that column
    */
    int matrixScore(vector<vector<int>>& A) {
        if(A.empty()) return 0;
        int N = A.size(), M = A[0].size();
        for(int i = 0; i < N; i++) {
            if(A[i][0] == 0) {
                FlipRow(A, i, M);
            }
        }
        
        for(int j = 0; j < M; j++) {
            int one_count = 0;
            for(int i = 0; i < N; i++) one_count += A[i][j] == 1;
            if(one_count < N - one_count) {
                FlipCol(A, j, N);
            }
        }
        
        int res = 0;
        for(int i = 0; i < N; i++) {
            int temp = 0;
            for(int j = 0; j < M; j++) {
                temp |= A[i][j];
                temp <<= 1;
            }
            res += temp >> 1;
        }
        return res;
    }
};

int main() {
    return 0;
}