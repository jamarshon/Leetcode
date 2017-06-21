/*
30. Substring with Concatenation of All Words
You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in words 
exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int num_words = words.size();
        int K = words.front().size();
        int N = s.size();
        int target_count = words.size();

        unordered_map<string, int> freq;
        map<int, string> m;

        // store frequency of the words
        for(string word: words) {
            freq[word]++;
        }

        // associate substrings with each index
        for(int i = 0; i < N - K + 1; i++) {
            string sub = s.substr(i, K);
            if(freq.count(sub)) {
                m[i] = sub;
            }
        }

        vector<int> res;
        for(int i = 0; i < K; i++) {
            // hop K from i keep track of longest 
            int start = i;
            int curr = i;
            int count = 0;
            unordered_map<string, int> not_seen(freq);

            while(curr < N) {
                // no string from words is at this index
                if(m.find(curr) == m.end()) {
                    not_seen = freq;
                    while(curr < N && m.find(curr) == m.end()) {
                        curr += K;
                    }
                    count = 0;
                    start = curr;
                }
                
                if(curr >= N) break;

                string s = m.find(curr) -> second;

                // the word occured more times than needed so keep removing from start
                while(not_seen[s] == 0 && start < min(N, curr)) {
                    string next = m.find(start) -> second;
                    not_seen[next]++;
                    count--;
                    start += K;
                }

                // increase the longest length if the frequency of the word is greater than zero
                if(not_seen[s] > 0) {
                    not_seen[s]--;
                    count++;
                    if(count == target_count) {
                        res.push_back(start);
                    }
                }

                curr += K;
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}