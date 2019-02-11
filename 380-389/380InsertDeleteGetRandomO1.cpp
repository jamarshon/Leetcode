/*
380. Insert Delete GetRandom O(1)
Design a data structure that supports all following operations in average O(1)
time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element
must have the same probability of being returned.

Example:
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();
/*
  Submission Date: 2019-02-10
  Runtime: 64 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
  /*
  need a vector the random function
  m_ key is the element and the value is its index in v_
  when we remove a kv from m_ in order to keep the rest of the
  values in m_ to point to the right place we have to ensure
  that none of them moves so we swap the last one with the
  one we're removing and then removing the last one.
  this means none of the indicies change besides the last one.
  */
  unordered_map<int, int> m_;
  vector<int> v_;

 public:
  /** Initialize your data structure here. */
  RandomizedSet() {}

  /** Inserts a value to the set. Returns true if the set did not already
   * contain the specified element. */
  bool insert(int val) {
    if (m_.count(val)) return false;
    m_[val] = v_.size();
    v_.push_back(val);
    return true;
  }

  /** Removes a value from the set. Returns true if the set contained the
   * specified element. */
  bool remove(int val) {
    if (!m_.count(val)) return false;
    int ind = m_[val];

    // fix map. erase after in case val is the last element
    m_[v_.back()] = ind;
    m_.erase(val);

    // fix vector
    swap(v_.back(), v_[ind]);
    v_.pop_back();
    return true;
  }

  /** Get a random element from the set. */
  int getRandom() { return v_[rand() % v_.size()]; }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() { return 0; }
