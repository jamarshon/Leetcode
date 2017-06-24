/*
68. Text Justification
Given an array of words and a length L, format the text such that each line has exactly L characters and is 
fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. 
Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a 
line do not divide evenly between words, the empty slots on the left will be assigned more spaces than 
the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int len = words.size();
        for(int i = 0; i < len; i++) {
            int temp = i;
            int count = 1;
            int width = words[i].size();
            while(++temp < len) {
                if(width + count - 1 >= maxWidth) break;
                width += words[temp].size();
                count++;
            }

            string line = "";
            // either last line or fits
            if(width + count - 1 <= maxWidth) {
                for(int j = i; j < temp; j++) line += words[j] + ((j == temp - 1) ? "" : " ");
            } else {
                // now below maxWidth and add spacing
                width -= words[--temp].size();
                count--;

                if(count == 1) {
                    line = words[i];
                } else {
                    int num_spaces = (maxWidth - width)/(count - 1);
                    string space = string(num_spaces, ' ');
                    
                    int remainder_space = (maxWidth - width) % (count - 1);
                    
                    for(int j = i; j < temp; j++) {
                        line += words[j];
                        if(j != temp - 1) {
                            line += space + (remainder_space-- > 0 ? " " : "");
                        }
                    }
                }
            }
            
            while(line.size() != maxWidth) line += " ";
            res.push_back(line);
            i = temp - 1;
        }
        return res;
    }
};


int main() {
    return 0;
}