/*
211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . 
means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.

/*
    Submission Date: 2017-08-03
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool is_word;
    TrieNode() {
        is_word = false;
        for(int i = 0; i < 26; i++) child[i] = NULL;
    }
};

class WordDictionary {
    TrieNode* root_;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root_ = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* curr = root_;
        for(int i = 0, N = word.size(); i < N; i++) {
            char c = word[i];
            if(curr -> child[c - 'a'] == NULL) curr -> child[c - 'a'] = new TrieNode();
            curr = curr -> child[c - 'a'];
        }
        curr -> is_word = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        queue<pair<TrieNode*, int>> q;
        q.emplace(root_, 0);

        TrieNode* curr;
        int index;
        while(!q.empty()) {
            tie(curr, index) = q.front();
            q.pop();

            if(index == word.size()) {
                if(curr -> is_word) return true;
                continue;
            }
            if(word[index] == '.') { // increase index and add all 26 child to the queue
                for(int i = 0; i < 26; i++) {
                    if(curr -> child[i] == NULL) continue;
                    q.emplace(curr -> child[i], index + 1);
                }
            } else {
                // check if current character is valid
                if(curr -> child[word[index] - 'a'] == NULL) continue; 
                q.emplace(curr -> child[word[index] - 'a'], index + 1);
            }
        }
        return false;
    }
};

int main() {
    return 0;
}