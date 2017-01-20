using namespace std;
#include <iostream>
#include <vector>
#include <string>
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
        print(intervals);
        for(int i = 1; i < len; i++) {
            print(retVec);
            if(overlap(intervals[i], retVec[j])) {
                cout << j << endl;
                retVec[j].start = min(intervals[i].start, intervals[j].start);
                retVec[j].end = max(intervals[i].end, intervals[j].end);
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
    void print(vector<Interval> v) {
        for(auto i: v) {
            cout << "[" << i.start << "," << i.end << "],";
        }
        cout << endl;
    }
};
int main() {
    Solution s;
    vector<Interval> v = {{2,3},{2,2},{3,3},{1,3},{5,7},{2,2},{4,6}};
    Interval a = {4, 6};
    Interval b = {5, 7};
    // cout << s.overlap(a, b) << endl;
    vector<Interval> d = s.merge(v);
    s.print(d);
    return 0;
}