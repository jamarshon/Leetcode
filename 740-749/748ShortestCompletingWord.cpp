/*
748. Shortest Completing Word
Find the minimum length word from a given dictionary words, which has all the 
letters from the string licensePlate.  Such a word is said to complete the given 
string licensePlate 

Here, for letters we ignore case.  For example, "P" on the licensePlate still 
matches "p" on the word. 

It is guaranteed an answer exists.  If there are multiple answers, return the 
one that occurs first in the array. 

The license plate might have the same letter occurring multiple times.  For 
example, given a licensePlate of "PP", the word "pair" does not complete the 
licensePlate, but the word "supper" does. 


Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S", 
and "T". 
Note that the answer is not "step", because the letter "s" must occur in the 
word twice. 
Also note that we ignored case for the purposes of comparing whether a letter 
exists in the word. 



Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.



Note:

licensePlate will be a string with length in range [1, 7].
licensePlate will contain digits, spaces, or letters (uppercase or lowercase).
words will have a length in the range [10, 1000].
Every words[i] will consist of lowercase letters, and have length in range [1, 
15]. 

/*
    Submission Date: 2018-06-30
    Runtime: 26 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /*
    licensePlate size M, words size N, words[i] size k
    
    generate a frequency of character for licensePlate O(M)
    for each word, loop through character and decrease frequency of character if it exists
    if the frequency is zero, remove it and if the hashmap is empty than all the characters
    are needed in this string so update res if it is shorter O(N*k)
    
    O(N*k + M)
    */
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        unordered_map<char, int> letters;
        for(const auto& c: licensePlate) if(isalpha(c)) letters[tolower(c)]++;
        
        string res = "";
        for(const auto& word: words) {
            unordered_map<char, int> letters_copy = letters;
            for(const auto& c: word) {
                if(letters_copy.count(c)) {
                    letters_copy[c]--;
                    if(letters_copy[c] == 0) {
                        letters_copy.erase(c);
                        if(letters_copy.empty()) break;
                    }
                }
            }
            
            if(letters_copy.empty() && (res.empty() || word.size() < res.size())) {
                res = word;
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}