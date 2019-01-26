#include <vector>
// initialize without declaring an array and vector
vector<int> v;
vector<int> v(10);
int a[20];

vector<int> first{1, 4, 3};
vector<int> second(4, 100);  // four ints with value 100
vector<int> third(first.begin() + 1,
                  first.end());  // 4 3 as it is copying values from first
vector<int> fourth(third);       // a copy of third

// initialize and declare an array and vector
vector<int> vec = {1, 2, 3};
int arr[10] = {1, 2, 3};

// size of an array and vector
cout << vec.size() << endl;
cout << sizeof(arr) / sizeof(int) << endl;

// convert array to vector
vector<int> vec(begin(arr), end(arr));

// generate elements based on a function (3 is the number of elements it can be
// more than the size of the array)
#include <algorithm>
int current = 0;
function<int(void)> uniqNumber = [&current] { return ++current; };

int arr[5] = {2, 4, 6, 8};
generate_n(arr, 3, uniqNumber);  // 1 2 3 8 0

int arr2[5];
generate_n(arr2 + 1, 2, uniqNumber);  // 8324904 2 3 32766 5767168

vector<int> vec = {2, 4, 6, 8};
generate_n(vec.begin() + 2, 3, uniqNumber);  // 2 4 1 2

// fill elements with a constant (same way as generate_n)
#include <algorithm>
int arr[5] = {2, 4, 6, 8};
fill_n(arr + 1, 3, 100);  // 2 100 100 100 0

vector<int> vec = {2, 4, 6, 8};
fill_n(vec.begin(), 3, 100);