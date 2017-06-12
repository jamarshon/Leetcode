/*
604. Design Compressed String Iterator
Design and implement a data structure for a compressed string iterator. 
It should support the following operations: next and hasNext.

The given compressed string will be in the form of each letter followed 
by a positive integer representing the number of this letter existing in 
the original uncompressed string.

next() - if the original string still has uncompressed characters, return 
the next letter; Otherwise return a white space.
hasNext() - Judge whether there is any letter needs to be uncompressed.

Example:

StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");

iterator.next(); // return 'L'
iterator.next(); // return 'e'
iterator.next(); // return 'e'
iterator.next(); // return 't'
iterator.next(); // return 'C'
iterator.next(); // return 'o'
iterator.next(); // return 'd'
iterator.hasNext(); // return true
iterator.next(); // return 'e'
iterator.hasNext(); // return false
iterator.next(); // return ' '

/*
    Submission Date: 2017-06-11
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

class StringIterator {
vector<pair<char, long long>> v_;
int index_;
public:
    StringIterator(string compressedString) {
        index_ = 0;
        int len = compressedString.size();
        int i = 0;
        while(i < len) {
            char c = compressedString[i];
            i++;
            string rep = "";
            while(i < len && isdigit(compressedString[i])) {
                rep += compressedString[i];
                i++;
            }
            
            long long times = stoll(rep);
            // cout << c << ' ' << times << endl;
            v_.emplace_back(c, times);
        }
    }
    
    char next() {
        if(!hasNext()) return ' ';
        pair<char, long long>& p = v_[index_];
        p.second--;
        if(p.second == 0) index_++;
        return p.first;
    }
    
    bool hasNext() {
        return index_ < v_.size();
    }
};

int main() {
    return 0;
}