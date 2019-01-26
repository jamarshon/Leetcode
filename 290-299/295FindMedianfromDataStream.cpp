/*
295. Find Median from Data Stream
Median is the middle value in an ordered integer list. If the size of
the list is even, there is no middle value. So the median is the mean
of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the
data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
/*
    Submission Date: 2017-09-10
    Runtime: 172 ms
    Difficulty: HARD
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
  typedef priority_queue<int, vector<int>, less<int>> MaxHeap;
  typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

  MaxHeap max_heap_;
  MinHeap min_heap_;

 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    if (max_heap_.empty()) {
      max_heap_.push(num);
    } else {
      if (num > max_heap_.top()) {
        min_heap_.push(num);
      } else {
        max_heap_.push(num);
      }

      // Maintain abs(max_heap_.size() - min_heap_.size()) <= 1
      if (max_heap_.size() > min_heap_.size() + 1) {  // max_heap_ too large
        min_heap_.push(max_heap_.top());
        max_heap_.pop();
      } else if (min_heap_.size() >
                 max_heap_.size() + 1) {  // min_heap_ too large
        max_heap_.push(min_heap_.top());
        min_heap_.pop();
      }
    }
  }

  double findMedian() {
    /*
    Three cases: since abs(max_heap_.size() - min_heap_.size()) <= 1
    denote x as min(max_heap_.size() - min_heap_.size())
    1) size x and x means even elements so it just the average of max of first
    heap and min of second heap 2) size x + 1 and x means odd elements so the
    max of the first heap is the median element 3) size x and x + 1 means odd
    elements so the min of the second heap is the median element
    */
    if (max_heap_.size() == min_heap_.size()) {
      return (double)(max_heap_.top() + min_heap_.top()) / 2.0;
    } else if (max_heap_.size() > min_heap_.size()) {
      return max_heap_.top();
    } else {
      return min_heap_.top();
    }
  }
};

int main() { return 0; }