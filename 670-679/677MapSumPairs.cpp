/*
677. Map Sum Pairs
Implement a MapSum class with insert, and sum methods.



For the method insert, you'll be given a pair of (string, integer). The string 
represents the key and the integer represents the value. If the key already 



For the method sum, you'll be given a string representing the prefix, and you 


Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
/*
    Submission Date: 2018-07-02
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

struct TrieNode {
    int sum;
    TrieNode* children[26];
    TrieNode() {
        sum = 0;
        for(int i = 0; i < 26; i++) children[i] = NULL;
    }
};

class MapSum {
    unordered_map<string, int> m;
    TrieNode* root;
public:
    /** Have a trie and unordered_map. the unordered_map keeps track of key and val
     the trie can find prefix easily. each node has sum which is the sum of all...l with each node visited getting the to_add
     added to their sum.
    */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        int to_add = m.count(key) ? val - m[key] : val;
        m[key] = val;
        TrieNode* curr = root;
        curr->sum += to_add;
        
        for(const auto& c: key) {
            if(curr->children[c - 'a'] == NULL) 
                curr->children[c - 'a'] = new TrieNode();
            curr = curr->children[c - 'a'];
            curr->sum += to_add;
        }
    }
    
    int sum(string prefix) {
        TrieNode* curr = root;
        for(const auto& c: prefix) {
            if(curr->children[c - 'a'] == NULL) return 0;
            curr = curr->children[c - 'a'];
        }
        
        return curr->sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */

int main() {
    return 0;
}
