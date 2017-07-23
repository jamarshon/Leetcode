/*
648. Replace Words
In English, we have a concept called root, which can be followed by some other words to form another 
longer word - let's call this word successor. For example, the root an, followed by other, which can 
form another word another.

Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor 
in the sentence with the root forming it. If a successor has many roots can form it, replace it with the 
root with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
Note:
The input will only have lower-case letters.
1 <= dict words number <= 1000
1 <= sentence words number <= 1000
1 <= root length <= 100
1 <= sentence words length <= 1000

/*
    Submission Date: 2017-07-23
    Runtime: 159 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        unordered_set<string> ds(dict.begin(), dict.end());
        set<int> word_size;
        for(auto ds_e: ds) {
            word_size.insert(ds_e.size());
        }

        stringstream ss(sentence);
        string temp;

        vector<string> res;
        while(getline(ss, temp, ' ')) {
            bool found = false;
            for(auto len: word_size) {
                if(len > temp.size()) {
                    res.push_back(temp);
                    found = true;
                    break;
                } else {
                    if(ds.count(temp.substr(0, len))) {
                        res.push_back(temp.substr(0, len));
                        found = true;
                        break;
                    }
                }
            }

            if(!found) {
                res.push_back(temp);
            }
        }

        return accumulate(res.begin(), res.end(), string(), [](string memo, string a){
            return memo.empty() ? a : memo + " " + a;
        });
    }
};

int main() {
    return 0;
}