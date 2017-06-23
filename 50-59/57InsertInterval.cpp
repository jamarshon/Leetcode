/*
57. Insert Interval
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

/*
    Submission Date: 2017-06-22
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct Compare {
    bool operator() (const Interval& lhs, const Interval& rhs) {
        return lhs.start < rhs.start;
    }
    bool operator() (const Interval& lhs, int start) {
        return lhs.start < start;
    }
    bool operator() (int start, const Interval& rhs) {
        return start < rhs.start;
    }
};

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto it = upper_bound(intervals.begin(), intervals.end(), newInterval.start, Compare());

        auto prev_it = it - 1;
        auto merge_it = prev_it;
        if(it == intervals.begin() || (prev_it -> end) < newInterval.start) {
            // either insert or merge
            if(it == intervals.end() || (it -> start) > newInterval.end) {
                intervals.insert(it, newInterval);
                return intervals;
            } else {
                merge_it = it;
            }
        }

        merge_it -> start = min(merge_it -> start, newInterval.start);

        // find the next disjoint interval, as everything in between is now overlapping
        auto it_large = upper_bound(merge_it, intervals.end(), newInterval.end, Compare());
        int max_end = (it_large - 1) -> end;

        merge_it -> end = max(max(max_end, merge_it -> end), newInterval.end);

        intervals.erase(merge_it + 1, it_large);
        
        return intervals;
    }
};


int main() {
    return 0;
}