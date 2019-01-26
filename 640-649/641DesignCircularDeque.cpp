/*
641. Design Circular Deque
Design your implementation of the circular double-ended queue (deque).
Your implementation should support following operations:


    MyCircularDeque(k): Constructor, set the size of the deque to be k.
    insertFront(): Adds an item at the front of Deque. Return true if the
operation is successful. insertLast(): Adds an item at the rear of Deque. Return
true if the operation is successful. deleteFront(): Deletes an item from the
front of Deque. Return true if the operation is successful. deleteLast():
Deletes an item from the rear of Deque. Return true if the operation is
successful. getFront(): Gets the front item from the Deque. If the deque is
empty, return -1. getRear(): Gets the last item from Deque. If the deque is
empty, return -1. isEmpty(): Checks whether Deque is empty or not.  isFull():
Checks whether Deque is full or not.


Example:

MyCircularDeque circularDeque = new MycircularDeque(3); // set the size to be 3
circularDeque.insertLast(1);            // return true
circularDeque.insertLast(2);            // return true
circularDeque.insertFront(3);           // return true
circularDeque.insertFront(4);           // return false, the queue is full
circularDeque.getRear();                // return 32
circularDeque.isFull();             // return true
circularDeque.deleteLast();         // return true
circularDeque.insertFront(4);           // return true
circularDeque.getFront();               // return 4
 
 

Note:


    All values will be in the range of [1, 1000].
    The number of operations will be in the range of [1, 1000].
    Please do not use the built-in Deque library.

/*
    Submission Date: 2018-07-12
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class MyCircularDeque {
  int k_;
  int size_;
  int front_;
  int back_;
  vector<int> dq_;

  int mod(int a, int b) { return (b + (a % b)) % b; }

 public:
  /** Initialize your data structure here. Set the size of the deque to be k. */
  MyCircularDeque(int k) {
    k_ = k;
    size_ = 0;
    front_ = 0;
    back_ = k - 1;
    dq_.resize(k);
  }

  /** Adds an item at the front of Deque. Return true if the operation is
   * successful. */
  bool insertFront(int value) {
    if (isFull()) return false;
    front_ = mod(front_ - 1, k_);
    dq_[front_] = value;
    size_++;
    return true;
  }

  /** Adds an item at the rear of Deque. Return true if the operation is
   * successful. */
  bool insertLast(int value) {
    if (isFull()) return false;
    back_ = mod(back_ + 1, k_);
    dq_[back_] = value;
    size_++;
    return true;
  }

  /** Deletes an item from the front of Deque. Return true if the operation is
   * successful. */
  bool deleteFront() {
    if (isEmpty()) return false;
    front_ = mod(front_ + 1, k_);
    size_--;
    return true;
  }

  /** Deletes an item from the rear of Deque. Return true if the operation is
   * successful. */
  bool deleteLast() {
    if (isEmpty()) return false;
    back_ = mod(back_ - 1, k_);
    size_--;
    return true;
  }

  /** Get the front item from the deque. */
  int getFront() {
    if (isEmpty()) return -1;
    return dq_[front_];
  }

  /** Get the last item from the deque. */
  int getRear() {
    if (isEmpty()) return -1;
    return dq_[back_];
  }

  /** Checks whether the circular deque is empty or not. */
  bool isEmpty() { return size_ == 0; }

  /** Checks whether the circular deque is full or not. */
  bool isFull() { return size_ == k_; }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque obj = new MyCircularDeque(k);
 * bool param_1 = obj.insertFront(value);
 * bool param_2 = obj.insertLast(value);
 * bool param_3 = obj.deleteFront();
 * bool param_4 = obj.deleteLast();
 * int param_5 = obj.getFront();
 * int param_6 = obj.getRear();
 * bool param_7 = obj.isEmpty();
 * bool param_8 = obj.isFull();
 */

int main() { return 0; }
