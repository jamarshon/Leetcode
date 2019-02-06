/*
706. Design HashMap
Design a HashMap without using any built-in hash table libraries.

To be specific, your design should include these functions:

  put(key, value) : Insert a (key, value) pair into the HashMap. If the value
already exists in the HashMap, update the value.
  get(key): Returns the value to which the specified key is mapped, or -1 if
this map contains no mapping for the key. remove(key) : Remove the mapping for
the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);          
hashMap.put(2, 2);        
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found)

Note:

  All keys and values will be in the range of [0, 1000000].
  The number of operations will be in the range of [1, 10000].
  Please do not use the built-in HashMap library.
/*
  Submission Date: 2019-02-06
  Runtime: 160 ms
  Difficulty: EASY
*/
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
struct Data {
  hash<int> h;
  int capacity;
  int size = 0;
  vector<list<pii>> arr;
  int GetHash(int key) { return h(key) % capacity; }

  Data(int cap) : capacity(cap) { arr.resize(capacity); }
};

class MyHashMap {
  const double load_factor_ = 0.75;
  int capacity_ = 10;
  Data* data_;

  list<pii>::iterator Get(int key) {
    auto& l = data_->arr[data_->GetHash(key)];
    for (auto it = l.begin(); it != l.end(); it++) {
      if (it->first == key) return it;
    }
    return l.end();
  }

 public:
  /** Initialize your data structure here. */
  MyHashMap() { data_ = new Data(capacity_); }

  /** value will always be non-negative. */
  void put(int key, int value) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];

    if (it == l.end()) {
      // insert
      l.emplace_back(key, value);
      data_->size++;

      if (data_->size > load_factor_ * capacity_) {
        Data* old = data_;
        capacity_ *= 2;
        data_ = new Data(capacity_);
        for (const auto& bucket : old->arr) {
          for (const pii& p : bucket) {
            put(p.first, p.second);
          }
        }

        delete old;
      }
    } else {
      it->second = value;
    }
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map
   * contains no mapping for the key */
  int get(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    return it == l.end() ? -1 : it->second;
  }

  /** Removes the mapping of the specified value key if this map contains a
   * mapping for the key */
  void remove(int key) {
    auto it = Get(key);
    auto& l = data_->arr[data_->GetHash(key)];
    if (it != l.end()) {
      l.erase(it);
      data_->size--;
    }
  }
};

int main() {
  return 0;
}
