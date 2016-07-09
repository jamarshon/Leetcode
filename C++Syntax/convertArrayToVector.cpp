vector<int> myvector (myints, myints + sizeof(myints)/sizeof(int));

vector<int> myvector (begin(myints), end(myints));
vector<int> myvector (myints, end(myints));