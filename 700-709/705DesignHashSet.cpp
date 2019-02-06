/*
705. Design HashSet
Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

  add(value): Insert a value into the HashSet. 
  contains(value) : Return whether the value exists in the HashSet or not.
  remove(value): Remove a value in the HashSet. If the value does not exist in
the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);        
hashSet.add(2);        
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);          
hashSet.contains(2);    // returns true
hashSet.remove(2);          
hashSet.contains(2);    // returns false (already removed)

Note:

  All values will be in the range of [0, 1000000].
  The number of operations will be in the range of [1, 10000].
  Please do not use the built-in HashSet library.
/*
  Submission Date: 2019-02-06
  Runtime: 140 ms
  Difficulty: EASY
*/
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Data {
  hash<int> h;
  int capacity;
  int size = 0;
  vector<list<int>> arr;
  int GetHash(int key) { return h(key) % capacity; }

  Data(int cap) : capacity(cap) { arr.resize(capacity); }
};

class MyHashSet {
  const double load_factor_ = 0.75;
  int capacity_ = 10;
  Data* data_;

  list<int>::iterator Get(int key) {
    auto& l = data_->arr[data_->GetHash(key)];
    for (auto it = l.begin(); it != l.end(); it++) {
      if (*it == key) return it;
    }
    return l.end();
  }

 public:
  /** Initialize your data structure here. */
  MyHashSet() { data_ = new Data(capacity_); }

  void add(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];

    if (it == l.end()) {
      // insert
      l.emplace_back(key);
      data_->size++;

      if (data_->size > load_factor_ * capacity_) {
        Data* old = data_;
        capacity_ *= 2;
        data_ = new Data(capacity_);
        for (const auto& bucket : old->arr) {
          for (const int& k : bucket) {
            add(k);
          }
        }

        delete old;
      }
    }
  }

  void remove(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    if (it != l.end()) {
      l.erase(it);
      data_->size--;
    }
  }

  /** Returns true if this set contains the specified element */
  bool contains(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    return it != l.end();
  }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet obj = new MyHashSet();
 * obj.add(key);
 * obj.remove(key);
 * bool param_3 = obj.contains(key);
 */

int main() {
  return 0;
}
