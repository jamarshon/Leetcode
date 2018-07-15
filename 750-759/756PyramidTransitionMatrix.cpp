/*
756. Pyramid Transition Matrix
We are stacking blocks to form a pyramid.  Each block has a color which is a one 
letter string, like `'Z'`. 

For every block of color `C` we place not in the bottom row, we are placing it 
on top of a left block of color `A` and right block of color `B`.  We are 
allowed to place the block there only if `(A, B, C)` is an allowed triple. 

We start with a bottom row of bottom, represented as a single string.  We also 
start with a list of allowed triples allowed.  Each allowed triple is 
represented as a string of length 3. 

Return true if we can build the pyramid all the way to the top, otherwise false.


Example 1:
Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  D   E
 / \ / \
X   Y   Z

This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are 
allowed triples. 



Example 2:
Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.



Note:

bottom will be a string with length in range [2, 8].
allowed will have length in range [0, 200].
Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 
'F', 'G'}. 

/*
    Submission Date: 2018-07-09
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    TrieNode* children[7];
    TrieNode() {
        for(int i = 0; i < 7; i++) {
            children[i] = NULL;
        }
    }
};

class Solution {
public:
    /*
    loop through s from i = [1,N) and seeing if s[i-1] + s[i] exists
    if it does then try all combinations of s[i-1] + s[i] + _ where _ is determined from
    the Trie. base case is when s is just a single letter.
    
    building.size() always == i-1 so if building.size() == N-1 (building row is one less than previous row)
    then i-1 == N-1 or i == N which terminates
    */
    bool f(string s, int i, string building, TrieNode* root) {
        int N = s.size();
        if(N == 1) return true;
        
        if(building.size() == N-1) {
            return f(building, 1, "", root); // swap building and create a new row
        }
        
        // checking trie if AB exists
        TrieNode* curr = root;
        for(int j = 0; j < 2; j++) {
            if(curr->children[s[i - 1 + j] - 'A'] == NULL) return false; 
            curr = curr->children[s[i - 1 +j] - 'A'];
        }
        
        // useing all combinations of AB_ to see if _ can work as the character for the building row
        for(int j = 0; j < 7; j++) {
            if(curr->children[j] == NULL) continue;
            if(f(s, i + 1, building + char('A' + j), root)) return true;
        }
        
        return false;
    }
    
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        TrieNode* root = new TrieNode();
        for(const auto& s: allowed) {
            TrieNode* curr = root;
            for(const auto& c: s) {
                if(curr->children[c - 'A'] == NULL) 
                    curr->children[c - 'A'] = new TrieNode();
                curr = curr->children[c - 'A'];
            }
        }
        
        return f(bottom, 1, "", root);
    }
};

int main() {
    return 0;
}
