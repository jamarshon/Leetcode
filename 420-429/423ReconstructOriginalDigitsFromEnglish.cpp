/*
423. Reconstruct Original Digits from English
Given a non-empty string containing an out-of-order English representation of 

Note:

Input contains only lowercase English letters.
Input is guaranteed to be valid and can be transformed to its original digits. 
Input length is less than 50,000.



Example 1:
Input: "owoztneoer"

Output: "012"



Example 2:
Input: "fviefuro"

Output: "45"
/*
    Submission Date: 2018-07-13
    Runtime: 28 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution {
    unordered_map<char, string> first_pass { 
        {'z', "zero"}, {'w', "two"}, {'u', "four"}, {'x', "six"}, {'g', "eight"}};
    unordered_map<char, string> second_pass {
        {'o', "one"}, {'h', "three"}, {'f', "five"}, {'s', "seven"}};
    unordered_map<char, string> last_pass {
        {'i', "nine"} };
    
    vector<unordered_map<char, string>> v {
        first_pass, second_pass, last_pass
    };
    
    vector<string> rep{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
public:
    /*
    have 3 passes where an unique number distinguishes between the numbers and only occurs once in that number
    get a frequency map of the string, for each pass see how many times that unique character occurs.
    if it is greater than zero, then it is part of the result so subtract occurence*(occurence in the
    number string) e.g 'h' appeared 3 times in s and 'e' appears 2 times in "three" so subtract 3*2.
    add the integer representation to the result occrence number of times. sort the result and return it.
    
    first unique
    zero => z
    two => w
    four => u
    six => x
    eight => g
    
    second unique
    one => o
    three => h
    five => f
    seven => s
    
    remaining
    nine => i
    */
    
    string originalDigits(string s) {
        unordered_map<string, char> rep_m;
        for(int i = 0; i < 10; i++) rep_m[rep[i]] = i + '0';
        
        unordered_map<char, int> freq;
        for(const auto& c: s) freq[c]++; // o(n)
        
        string res;
        for(const auto& m: v) { // occurs 3 times
            if(freq.empty()) break;
            for(const auto& kv: m) { // occurs max 5 times
                if(freq.empty()) break;
                
                if(freq.count(kv.first)) {
                    int occurences = freq[kv.first];
                    for(int i = 0; i < occurences; i++) res.push_back(rep_m[kv.second]);
                    
                    unordered_map<char, int> distribution;
                    for(const auto& c: kv.second) distribution[c]++; // occurs max 5 time
                    
                    for(const auto& kv2: distribution) { // occurs max 5 time
                        int to_remove = occurences*kv2.second;
                        assert(freq.count(kv2.first));
                        assert(freq[kv2.first] >= to_remove);
                        if(freq[kv2.first] == to_remove) 
                            freq.erase(kv2.first);
                        else
                            freq[kv2.first] -= to_remove;
                    }
                    
                    
                }
            }
        }
        
        sort(res.begin(), res.end());
        return res;        
    }
};

int main() {
    return 0;
}
