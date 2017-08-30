/*
275. H-Index II
Follow up for H-Index: What if the citations array is sorted in 
ascending order? Could you optimize your algorithm?
/*
    Submission Date: 2017-08-30
    Runtime: 192 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
                i    0, 1, 2, 3, 4
              N - i  5, 4, 3, 2, 1  
    h index is choose index from [0,n] such that
    h elements have citations >= h and N - h have citations < h

    sort and see if citations[i] >= N - i as N - i is the number
    of elements that are greater than or equal to this element
    from [i,N). Since it is sorted, i elements are less than citations[i].
    If citations[i] is greater than N - i, it means
    h = N - i as h elements [i, N) have citations[i] >= h 
    and h elements [0, i) have citations[i] < h
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();
        for(int i = 0; i < N; i++) {
            if(citations[i] >= N - i) {
                return N - i;
            }
        }
        return 0;
    }
};

int main() {
    return 0;
}