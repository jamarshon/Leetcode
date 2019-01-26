// lambda
// capture-list: variables from the outside of the function that you want
// 				to use inside the function
[capture - list](parameters) -> returnType {}

                                int epsilon = 2;
auto adder = [epsilon](int a) -> bool { return epsilon + a > 0; };

// naming functions where it is: function<return type (parameter type)> function
// name
#include <algorithm>
int epsilon = 2;

function<bool(int)> subtractor = [epsilon](int a) -> bool {
  return epsilon - a > 0;
};

// each

#include <algorithm>
vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

for_each(v.begin(), v.end(), [](int current) { cout << current << endl; });

// print with index
int index = 0;
for_each(v.begin(), v.end(),
         [&index](int current) { cout << current << " " << ++index << endl; });

// map
// map(first, last, beginning of destination range (first or last),
// function(currentElement))
#include <algorithm>
vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

transform(v.begin(), v.end(), v.begin(), [](int i) { return i * 2; });

// map to different type
vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<string> vecStr(v.size());
transform(v.begin(), v.end(), vecStr.begin(),
          [](int i) -> string { return to_string(i * 2) + " word"; });

// fold
// accumulate(first, last, initial, function(memo, currentElement))
// executes in order from left to right
// default is folds left to change it to right use: accumulate(v.rbegin(),
// v.rend(), init, binop)
#include <algorithm>
vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int sum = accumulate(v.begin(), v.end(), 0,
                     [](int memo, int current) { return memo * 2 + current; });

// fold with different type
string str = "";
string finalStr = accumulate(
    v.begin(), v.end(), str,
    [](string memo, int current) { return memo + " " + to_string(current); });
// or use "string finalStr = accumulate(v.begin(), v.end(), string{}, "