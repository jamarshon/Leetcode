/*
535. Encode and Decode TinyURL
TinyURL is a URL shortening service where you enter a URL such as
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as
http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no
restriction on how your encode/decode algorithm should work. You just need to
ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded
to the original URL.
/*
    Submission Date: 2018-06-24
    Runtime: 7 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

/*
A vector and return the encoded as an index to retrieve the original string
The encode called upon the same string should not return the same encoded string
as it would have collision problems so usually a randomizer and a storage of
encoded to original is needed.
*/
class Solution {
 public:
  vector<string> m;
  // Encodes a URL to a shortened URL.
  string encode(string longUrl) {
    m.push_back(longUrl);
    return to_string(m.size());
  }

  // Decodes a shortened URL to its original URL.
  string decode(string shortUrl) { return m[stoi(shortUrl) - 1]; }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

int main() { return 0; }