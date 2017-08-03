/*
218. The Skyline Problem
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city 
when viewed from a distance. Now suppose you are given the locations and height of all the buildings 
as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings 
collectively (Figure B).

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li 
and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its 
height. It is guaranteed that 0 ? Li, Ri ? INT_MAX, 0 < Hi ? INT_MAX, and Ri - Li > 0. You may assume all 
buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: 
[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of 
[ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of 
a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used 
to mark the termination of the skyline, and always has zero height. Also, the ground in between any two 
adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:
[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of 
height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

/*
    Submission Date: 2017-08-02
    Runtime: 29 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

using namespace std;

struct Item {
    int x, y;
    bool is_start;
};

struct SortCompare {
    bool operator()(const Item& lhs, const Item& rhs) {
        if(lhs.x != rhs.x) return lhs.x < rhs.x; // smaller x first
        // if an end and start are the same x, put the start building first
        if(lhs.is_start != rhs.is_start) return lhs.is_start; 
        // both are the same type
        if(lhs.is_start) {
            // both start put higher building first cause it overshadows the smaller ones
            return lhs.y > rhs.y;
        } else {
            // both end put smaller building first as we want to remove all the smaller ones first 
            return lhs.y < rhs.y;
        }
    }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> res;

        map<int, int> m;
        vector<Item> items;
        for(auto building: buildings) {
            items.push_back({building[0], building[2], true});
            items.push_back({building[1], building[2], false});
        }

        sort(items.begin(), items.end(), SortCompare());

        // for(auto item: items) cout << item.x << ' ' << item.y << ' ' << item.is_start << endl;
        for(auto item: items) {
            // we see if adding or removing an item changes the max
            if(item.is_start) {
                // adding this item increases the height so this item is part of output
                bool will_change_max = m.empty() || item.y > (m.rbegin() -> first);
                if(will_change_max) {
                    res.emplace_back(item.x, item.y);
                }
                m[item.y]++;
            } else {
                assert(!m.empty() && m.count(item.y) && m[item.y] > 0);
                if(m[item.y] == 1) {
                    // there is only one item of height item.y and it is the largest
                    // so removing it will change the height meaning the next largest
                    // height (0 if empty) and this current x will be part of output
                    bool will_change_max = item.y == m.rbegin() -> first;
                    m.erase(item.y);

                    if(will_change_max) {
                        pair<int, int> to_insert = {item.x, 0};
                        if(!m.empty()) to_insert.second = m.rbegin() -> first;
                        res.push_back(to_insert);
                    }
                } else {
                    m[item.y]--;
                }
            }
        }
        return res;
    }
};

int main() {
    return 0;
}