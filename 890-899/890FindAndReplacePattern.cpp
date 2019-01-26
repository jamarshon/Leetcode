/*
890. Find and Replace Pattern
You have a list of words and a pattern, and you want to know which words in 
words matches the pattern. 

A word matches the pattern if there exists a permutation of letters p so that 
after replacing every letter x in the pattern with p(x), we get the desired 
word. 

(Recall that a permutation of letters is a bijection from letters to letters: 
every letter maps to another letter, and no two letters map to the same letter.) 

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 


Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b 
-> e, ...}.  
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a 
permutation, 
since a and b map to the same letter.

 

Note:


  1 <= words.length <= 50
  1 <= pattern.length = words[i].length <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for(const auto& w: words) {
            if(w.size() != pattern.size()) continue;
            unordered_map<char, char> p;
            
            unordered_set<char> used;
            bool can_insert = true;
            for(int i = 0; i < w.size(); i++) {
                if(p.count(w[i])) {
                    if(p[w[i]] != pattern[i]) {
                        can_insert = false;
                        break;
                    }
                } else{
                    
                    if(used.count(pattern[i])) {
                        can_insert = false;
                        break;
                    } else {
                        p[w[i]] = pattern[i];
                        used.insert(pattern[i]);                        
                    }
                }
            }
            
            if(can_insert) res.push_back(w);
        }
        
        return res;
    }
};

int main() {
  return 0;
}
