/*
274. H-Index
Given an array of citations (each citation is a non-negative integer) 
of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has 
index h if h of his/her N papers have at least h citations each, and 
the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the 
researcher has 5 papers in total and each of them had received 
3, 0, 6, 1, 5 citations respectively. Since the researcher has 
3 papers with at least 3 citations each and the remaining two 
with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one 
is taken as the h-index.
/*
    Submission Date: 2017-08-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
                i    0, 1, 2, 3, 4
              N - i  5, 4, 3, 2, 1  
    h index is choose index from [0,n] such that
    h elements have citations >= h and N - h have citations < h

    Bucket sort
    bucket[i] for i = [0,n) indicates frequency of value i
    in citations. bucket[n] indications frequency of value >= n
    in citations.

    sum[i] shows how many element are greater than or equal to
    i so if sum[i] >= i then h = i as there are sum[i] elements
    greater than or equal to i and N - i elements smaller than
    i.

    3, 0, 6, 1, 5

    buckets
    0 1 2 3 4 5
    1 1 0 1 0 2

    sum   5 4 3 3 2 2  
    index 0 1 2 3 4 5 
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();

        vector<int> bucket(N + 1, 0);
        for(auto c: citations) {
            // if citation greater than N just use N
            // else increase bucket[c]
            bucket[min(c, N)]++; 
        }

        int sum = 0;
        for(int i = N; i >= 0; i--) {
            sum += bucket[i];
            if(sum >= i) return i;
        }

        return 0;
    }
};

int main() {
    Solution s;
    vector<int> v{3, 0, 6, 1, 5};
    cout << s.hIndex(v) << endl;
    return 0;
}