#include <cassert>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
deque (usually pronounced like "deck") is an irregular acronym of double-ended
queue. Double-ended queues are sequence containers with dynamic sizes that can
be expanded or contracted on both ends (either its front or its back).
 
Specific libraries may implement deques in different ways, generally as some
form of dynamic array. But in any case, they allow for the individual elements
to be accessed directly through random access iterators, with storage handled
automatically by expanding and contracting the container as needed.
 
Therefore, they provide a functionality similar to vectors, but with efficient
insertion and deletion of elements also at the beginning of the sequence, and
not only at its end. But, unlike vectors, deques are not guaranteed to store all
its elements in contiguous storage locations: accessing elements in a deque by
offsetting a pointer to another element causes undefined behavior.
 
Both vectors and deques provide a very similar interface and can be used for
similar purposes, but internally both work in quite different ways: While
vectors use a single array that needs to be occasionally reallocated for growth,
the elements of a deque can be scattered in different chunks of storage, with
the container keeping the necessary information internally to provide direct
access to any of its elements in constant time and with a uniform sequential
interface (through iterators). Therefore, deques are a little more complex
internally than vectors, but this allows them to grow more efficiently under
certain circumstances, especially with very long sequences, where reallocations
become more expensive.
 
For operations that involve frequent insertion or removals of elements at
positions other than the beginning or the end, deques perform worse and have
less consistent iterators and references than lists and forward lists.
*/
void DEQUE() {
  deque<int> my_deque;                             // empty deque of ints
  deque<int> first{1, 2, 3, 4};                    // list initialization
  deque<int> second(4, 100);                       // four ints with value 100
  deque<int> third(second.begin(), second.end());  // iterating through second
  deque<int> fourth(third);                        // a copy of third
  deque<int> fifth({6, 7, 8, 9});                  // list initialization

  my_deque.assign(7, 100);  // 7 ints with a value of 100
  my_deque.assign(second.begin() + 1,
                  second.end() - 1);  // copies input iterator first to last

  int a = my_deque.at(1);  // throws exception if out of bounds
  int b = my_deque[1];     // O(1)
  assert(a == b);

  int c = my_deque.back();   // last value in deque
  int d = my_deque.front();  // first value in deque

  // no capacity or max_capacity as not contiguous like vectors
  int e = my_deque.size();  // pushing to my_deque will add val at this index
  int f = my_deque.max_size();

  // iterating forward
  deque<int>::iterator deque_begin_it = my_deque.begin();
  deque<int>::iterator deque_end_it = my_deque.end();

  deque<int>::const_iterator deque_cbegin_it = my_deque.cbegin();
  deque<int>::const_iterator deque_cend_it = my_deque.cend();

  for (; deque_begin_it != deque_end_it; deque_begin_it++) {
    cout << *deque_begin_it << endl;
  }

  // iterating backward
  deque<int>::reverse_iterator deque_rbegin_it = my_deque.rbegin();
  deque<int>::reverse_iterator deque_rend_it = my_deque.rend();

  deque<int>::const_reverse_iterator deque_crbegin_it = my_deque.crbegin();
  deque<int>::const_reverse_iterator deque_crend_it = my_deque.crend();

  for (; deque_rbegin_it != deque_rend_it; deque_rbegin_it++) {
    assert(*deque_rbegin_it == 100);
  }

  // iterator emplace (const_iterator position, Args&&... args);
  // uses args to call constructor and place element constructed at position
  // This effectively increases the container size by one.
  // returns iterator pointed to newly created element
  // If the insertion happens at the beginning or the end of the sequence,
  // all iterators related to this container are invalidated, but pointers and
  // references remain valid, referring to the same elements they were referring
  // to before the call. If the insertion happens anywhere else in the deque,
  // all iterators, pointers and references related to this container are
  // invalidated.
  auto emplace_it = my_deque.emplace(my_deque.begin() + 1, 200);  // O(N)

  assert(*emplace_it == 200);
  assert(emplace_it - my_deque.begin() == 1);

  // insert front and back O(1)
  // void emplace_back (Args&&... args);
  my_deque.emplace_back(300);
  my_deque.emplace_front(0);

  // void push_back (const value_type& val);
  my_deque.push_back(300);
  my_deque.push_front(0);

  // bool empty() const;
  deque<int> empty_deque;
  bool is_empty = empty_deque.empty();

  // erasing elements
  // Removes from the deque container either a single element (position) or a
  // range of elements ([first,last)). Linear on the number of elements erased
  // (destructions). Plus, depending on the particular library implemention, up
  // to an additional linear time on the number of elements between position and
  // one of the ends of the deque. returns an iterator pointing to the new
  // location of the element that followed the last element erased by the
  // function call. This is the container end if the operation erased the last
  // element in the sequence. If the erasure operation includes the last element
  // in the sequence, the end iterator and the iterators, pointers and
  // references referring to the erased elements are invalidated. If the erasure
  // includes the first element but not the last, only those referring to the
  // erased elements are invalidated. If it happens anywhere else in the deque,
  // all iterators, pointers and references related to the container are
  // invalidated.

  // iterator erase (iterator position);
  auto erase_it = my_deque.erase(my_deque.begin() + 1);
  assert(*erase_it == 100);
  assert(erase_it - my_deque.begin() == 1);

  // erase the first 3 elements:
  auto range_erase_it = my_deque.erase(my_deque.begin(), my_deque.begin() + 3);

  // The deque container is extended by inserting new elements before the
  // element at the specified position. Linear on the number of elements
  // inserted (copy/move construction). Plus, depending on the particular
  // library implemention, up to an additional linear in the number of elements
  // between position and one of the ends of the deque. If the insertion happens
  // at the beginning or the end of the sequence, all iterators related to this
  // container are invalidated, but pointers and references remain valid,
  // referring to the same elements they were referring to before the call. If
  // the insertion happens anywhere else in the deque, all iterators, pointers
  // and references related to this container are invalidated. returns an
  // iterator that points to the first of the newly inserted elements. single
  // element (1) iterator insert (iterator position, const value_type& val);
  auto single_insert_it = my_deque.insert(my_deque.begin() + 1, 2);
  assert(*single_insert_it == 2);

  // fill (2) void insert (iterator position, size_type n, const value_type&
  // val);
  auto fill_insert_it = my_deque.insert(my_deque.begin() + 3, 10,
                                        4);  // inserts 4 10 times at index 3
  assert(*fill_insert_it == 4);

  // range (3) template void insert (iterator position, InputIterator first,
  // InputIterator last);
  auto range_insert_it =
      my_deque.insert(my_deque.begin() + 2, second.begin(),
                      second.end());  // copies everything from second to
                                      // my_deque starting at index 2
  assert(*range_insert_it == 100);

  // Assigns new contents to the container, replacing its current contents, and
  // modifying its size accordingly. Copies all the elements from x into the
  // container. O(N) All iterators, references and pointers related to this
  // container before the call are invalidated. In the move assignment,
  // iterators, pointers and references referring to elements in x are also
  // invalidated. copy (1) deque& operator= (const deque& x);
  my_deque = second;

  // pop and push adds element and removes element from front or back in
  // constant time pop reduces size of container by one while push increases it
  // by one

  // The end iterator and any iterator, pointer and reference referring to the
  // removed element are invalidated. Iterators, pointers and references
  // referring to other elements that have not been removed are guaranteed to
  // keep referring to the same elements they were referring to before the call.
  // void pop_back();
  my_deque.pop_back();

  // The iterators, pointers and references referring to the removed element are
  // invalidated. Iterators, pointers and references referring to other elements
  // that have not been removed are guaranteed to keep referring to the same
  // elements they were referring to before the call. void pop_front();
  my_deque.pop_front();

  // All iterators related to this container are invalidated. Pointers and
  // references to elements in the container remain valid, referring to the same
  // elements they were referring to before the call. void push_back (const
  // value_type& val);
  my_deque.push_back(10);
  // void push_front (const value_type& val);
  my_deque.push_front(10);

  // Resizes the container so that it contains n elements.
  // If n is smaller than the current container size, the content is reduced to
  // its first n elements, removing those beyond (and destroying them). If n is
  // greater than the current container size, the content is expanded by
  // inserting at the end as many elements as needed to reach a size of n. If
  // val is specified, the new elements are initialized as copies of val,
  // otherwise, they are value-initialized. Notice that this function changes
  // the actual content of the container by inserting or erasing elements from
  // it. Linear on the number of elements inserted/erased
  // (constructions/destructions). In case the container shrinks, all iterators,
  // pointers and references to elements that have not been removed remain valid
  // after the resize and refer to the same elements they were referring to
  // before the call. If the container expands, all iterators are invalidated,
  // but existing pointers and references remain valid, referring to the same
  // elements they were referring to before. void resize (size_type n,
  // value_type val = value_type());
  my_deque.resize(1);      // now size 1 by only keeping the first element
  my_deque.resize(5, -1);  // no size 5 by adding -1 4 times

  // Shrink to fit
  // Requests the container to reduce its memory usage to fit its size.
  // A deque container may have more memory allocated than needed to hold its
  // current elements: this is because most libraries implement deque as a
  // dynamic array that can keep the allocated space of removed elements or
  // allocate additional capacity in advance to allow for faster insertion
  // operations. This function requests that the memory usage is adapted to the
  // current size of the container, but the request is non-binding, and the
  // container implementation is free to optimize its memory usage otherwise.
  // Note that this function does not change the size of the container (for
  // that, see resize instead). O(N) No changes to iterators
  my_deque.assign(5, 0);
  my_deque.resize(10);
  my_deque.shrink_to_fit();
}

// Lists are sequence containers that allow constant time insert and erase
// operations anywhere within the sequence, and iteration in both directions.
// List containers are implemented as doubly-linked lists; Doubly linked lists
// can store each of the elements they contain in different and unrelated
// storage locations. The ordering is kept internally by the association to each
// element of a link to the element preceding it and a link to the element
// following it. They are very similar to forward_list: The main difference
// being that forward_list objects are single-linked lists, and thus they can
// only be iterated forwards, in exchange for being somewhat smaller and more
// efficient. Compared to other base standard sequence containers (array, vector
// and deque), lists perform generally better in inserting, extracting and
// moving elements in any position within the container for which an iterator
// has already been obtained, and therefore also in algorithms that make
// intensive use of these, like sorting algorithms. The main drawback of lists
// and forward_lists compared to these other sequence containers is that they
// lack direct access to the elements by their position; For example, to access
// the sixth element in a list, one has to iterate from a known position (like
// the beginning or the end) to that position, which takes linear time in the
// distance between these. They also consume some extra memory to keep the
// linking information associated to each element (which may be an important
// factor for large lists of small-sized elements).
void LIST() {
  list<int> my_list{1, 2, 3, 4};
  list<int> first;                                // empty list of ints
  list<int> second(4, 100);                       // four ints with value 100
  list<int> third(second.begin(), second.end());  // iterating through second
  list<int> fourth(third);                        // a copy of third

  first.assign(7, 100);                       // 7 ints with value 100
  second.assign(first.begin(), first.end());  // a copy of first

  int a = my_list.back();
  int b = my_list.front();

  auto begin_it = my_list.begin();
  auto end_it = my_list.end();

  auto cbegin_it = my_list.cbegin();
  auto cend_it = my_list.cend();

  auto rbegin_it = my_list.rbegin();
  auto rend_it = my_list.rend();

  auto crbegin_it = my_list.crbegin();
  auto crend_it = my_list.crend();

  int c = my_list.size();
  bool d = my_list.empty();
  int e = my_list.max_size();
  my_list.clear();

  // iterator emplace (const_iterator position, Args&&... args);
  my_list.emplace(my_list.begin(), 10);  // O(1)
  // void emplace_back (Args&&... args);
  my_list.emplace_back(10);
  // void emplace_front (Args&&... args);
  my_list.emplace_front(10);

  // not valid my_list.begin() + 3 as not random access use next
  auto erase_it = my_list.erase(my_list.begin());  // O(1)
  auto range_erase_it =
      my_list.erase(my_list.begin(), next(my_list.begin(), 1));

  // O(1) returns an iterator that points to the first of the newly inserted
  // elements. iterator insert (iterator position, const value_type& val);
  auto insert_it = my_list.insert(my_list.begin(), 21);
  // void insert (iterator position, size_type n, const value_type& val);
  auto fill_insert_it = my_list.insert(my_list.begin(), 3, 20);
  // void insert (iterator position, InputIterator first, InputIterator last);
  auto range_insert_it =
      my_list.insert(my_list.begin(), second.begin(), second.end());

  // void pop_back();
  my_list.pop_back();
  // void pop_front();
  my_list.pop_front();
  // void push_back (const value_type& val);
  my_list.push_back(10);
  // void push_front (const value_type& val);
  my_list.push_front(10);

  // Removes from the container all the elements that compare equal to val. This
  // calls the destructor of these objects and reduces the container size by the
  // number of elements removed. Linear in container size (comparisons). void
  // remove (const value_type& val);
  my_list.remove(10);
  // Removes from the container all the elements for which Predicate pred
  // returns true. This calls the destructor of these objects and reduces the
  // container size by the number of elements removed. The function calls
  // pred(*i) for each element (where i is an iterator to that element). Any of
  // the elements in the list for which this returns true, are removed from the
  // container. void remove_if (Predicate pred);
  for (auto e : my_list) cout << e << ' ';
  cout << endl;
  my_list.remove_if([](const int& el) { return el % 2 == 0; });
  for (auto e : my_list) cout << e << ' ';
  cout << endl;

  // void resize (size_type n, value_type val = value_type());
  my_list.resize(20, 3);

  // Reverse the order of elements. Reverses the order of the elements in the
  // list container. Linear in list size.
  // Iterator no changes.
  // void reverse();
  my_list.reverse();

  // Sorts the elements in the list, altering their position within the
  // container. The sorting is performed by applying an algorithm that uses
  // either operator< (in version (1)) or comp (in version (2)) to compare
  // elements. This comparison shall produce a strict weak ordering of the
  // elements (i.e., a consistent transitive comparison, without considering its
  // reflexiveness). The resulting order of equivalent elements is stable: i.e.,
  // equivalent elements preserve the relative order they had before the call.
  // The entire operation does not involve the construction, destruction or copy
  // of any element object. Elements are moved within the container. void
  // sort();
  my_list.sort();
  // Binary predicate that, taking two values of the same type of those
  // contained in the list, returns true if the first argument goes before the
  // second argument in the strict weak ordering it defines, and false
  // otherwise. This shall be a function pointer or a function object.
}

void RANDOM() {
  // [a,b]
  int a = 0, b = 10;
  default_random_engine generator;
  uniform_int_distribution<int> dist(a, b);

  cout << dist(generator) << endl;

  // [a,b)
  double c = 0.0, d = 10.0;
  uniform_real_distribution<double> dist2(c, d);
  cout << dist2(generator) << endl;
}
int main() {
  DEQUE();
  LIST();
  RANDOM();
  return 0;
}