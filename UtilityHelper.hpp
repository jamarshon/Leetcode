#ifndef UtilityHelper_H
#define UtilityHelper_H

using namespace std;
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <functional>

#include "./Misc/ListNode.cpp"

// Declaration
template <typename T, typename V>
class UtilityHelper {
     public:
          // Prints all the elements of the array
          void printT(vector<T> v);
          void printV(vector<V> v);
          // Does a comparison on the array to see if they are equal
          bool isEqual(vector<T> v1, vector<T> v2);
          // Sorts both arrays first as does not depend on order
          bool isEqualSorted(vector<T> v1, vector<T> v2);
          // Runs the test with inputs and displays it alongside the output after applying a function
          void run(vector<vector<T>> inputs, vector<vector<V>> outputs, 
                  vector<function< vector<V>(vector<T>)> > funcs);
          // Same as above accept the output is not a vector, it's a scalar
          void run(vector<vector<T>> inputs, vector<V> outputs, 
                  vector<function<V(vector<T>)> > funcs);
};

// Definition
template <typename T, typename V>
void UtilityHelper<T, V>::printT(vector<T> v) {
     for(int i = 0, len = v.size(); i < len; i++) {
          cout << v[i];
          cout << " ";
     }
     cout << endl;
}

template <typename T, typename V>
void UtilityHelper<T, V>::printV(vector<V> v) {
     for(int i = 0, len = v.size(); i < len; i++) {
          cout << v[i];
          cout << " ";
     }
     cout << endl;
}

template <typename T, typename V>
bool UtilityHelper<T, V>::isEqual(vector<T> v1, vector<T> v2) {
     int len1 = v1.size(),
          len2 = v2.size();

     if(len1 != len2) { return false; }

     for(int i = 0; i < len1; i++) {
         if(v1[i] != v2[i]) {
          return false;
         }
     }

     return true;
}

template <typename T, typename V>
bool UtilityHelper<T, V>::isEqualSorted(vector<T> v1, vector<T> v2) {
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  return isEqual(v1, v2);
}

template <typename T, typename V>
void UtilityHelper<T, V>::run(vector<vector<T>> inputs, vector<vector<V>> outputs, 
                              vector<function< vector<V>(vector<T>) >> funcs) {
  vector<T> input;
  vector<V> output;
  function< vector<V>(vector<T>) > func;
  vector<V> funcOutput;

  for(int i = 0, len = inputs.size(); i < len; i++) {
      input = inputs[i];
      output = outputs[i];
      func = funcs[i];
      funcOutput = func(input);

      printf("Test Case %d: \n", i);
      cout << "Input: ";
      printT(input);
      cout << "Output: ";
      printV(output);
      cout << "Function Ouput: ";
      printV(funcOutput);
      cout << endl;
   }
}

template <typename T, typename V>
void UtilityHelper<T, V>::run(vector<vector<T>> inputs, vector<V> outputs, 
                              vector<function<V(vector<T>)> > funcs) {
  vector<T> input;
  V output;
  function< V(vector<T>) > func;
  V funcOutput;

  for(int i = 0, len = inputs.size(); i < len; i++) {
      input = inputs[i];
      output = outputs[i];
      func = funcs[i];
      funcOutput = func(input);

      printf("Test Case %d: \n", i);
      cout << "Input: ";
      printT(input);
      cout << "Output: " << output << endl;
      cout << "Function Ouput: " << funcOutput << endl;
   }
}

#endif