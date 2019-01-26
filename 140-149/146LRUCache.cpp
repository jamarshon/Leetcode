/*
146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It
should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists
in the cache, otherwise return -1. put(key, value) - Set or insert the value if
the key is not already present. When the cache reached its capacity, it should
invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

/*
    Submission Date: 2017-07-14
    Runtime: 95 ms
    Difficulty: HARD
*/

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

struct LRUElement {
  int key, value;
  LRUElement(int _key, int _value) : key(_key), value(_value) {}
};

class LRUCache {
  list<LRUElement> linked_list_;  // back is just inserted or used recently
  unordered_map<int, list<LRUElement>::iterator> hash_table_;
  int capacity_;

  void moveToBack(int key) {
    auto it = hash_table_[key];

    LRUElement temp = *it;
    linked_list_.erase(it);
    linked_list_.push_back(temp);

    hash_table_[key] = --linked_list_.end();
  }

 public:
  LRUCache(int capacity) { capacity_ = capacity; }

  int get(int key) {
    if (!hash_table_.count(key)) return -1;

    // update in the linked_list
    moveToBack(key);

    // for(auto e: linked_list_) cout << e.value << endl;
    return linked_list_.back().value;
  }

  void put(int key, int value) {
    if (hash_table_.count(key)) {
      moveToBack(key);
      linked_list_.back().value = value;
    } else {
      if (linked_list_.size() == capacity_) {
        hash_table_.erase(linked_list_.begin()->key);
        linked_list_.erase(linked_list_.begin());
      }
      linked_list_.emplace_back(key, value);
      hash_table_[key] = --linked_list_.end();
    }
  }
};

int main() { return 0; }