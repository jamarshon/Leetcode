/*
582. Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This 
is just like a tree structure. Only one process has PPID that is 0, which means this process 
has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains 
PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list 
of PIDs of processes that will be killed in the end. You should assume that when a process 
is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.
/*
    Submission Date: 2017-05-13
    Runtime: 166 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        int N = pid.size();
        for(int i = 0; i < N; i++) {
            int _ppid = ppid[i];
            int _pid = pid[i];

            if(m.find(_ppid) == m.end()) {
                m[_ppid] = {_pid};
            } else {
                m[_ppid].push_back(_pid);
            }
        }

        vector<int> result{kill};
        int i = 0;
        while(i < result.size()) {
            int current = result[i];
            if(m.find(current) != m.end()) { // non leaf
                vector<int> children = m[current];
                for(auto c: children) {
                    result.push_back(c);
                }
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution s;
    vector<int> pid{1, 3, 10, 5, 4, 1};
	vector<int> ppid{3, 0, 5, 3, 10, 5};
    int kill = 5;
    vector<int> t = s.killProcess(pid, ppid, kill);
	for(auto l: t) cout << l << " ";
	return 0;
}