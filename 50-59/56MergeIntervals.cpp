/*
56. Merge Intervals
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

/*
    Submission Date: 2017-01-19
    Runtime: 49 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct sortComparison {
    inline bool operator() (const Interval& a, const Interval& b) {
        return a.start < b.start;
    }
};


class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int len = intervals.size();
        if(len == 0) return intervals;

        sort(intervals.begin(), intervals.end(), sortComparison());
        int j = 0;
        vector<Interval> retVec = {intervals[0]};
        for(int i = 1; i < len; i++) {
            if(overlap(intervals[i], retVec[j])) {
                retVec[j].start = min(intervals[i].start, retVec[j].start);
                retVec[j].end = max(intervals[i].end, retVec[j].end);
            } else {
                retVec.push_back(intervals[i]);
                j++;
            }
        }
        
        return retVec;
    }
    bool overlap(Interval a, Interval b) {
        return !(a.end < b.start || a.start > b.end);
    }
};

int main() {
    return 0;
}