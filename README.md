## APSProject2018
Implementation of sets using Hash set as hash table ordered statistics tree implemented as AVL Tree
Hash set is provided as hash_set.h and hash_set.cpp
Tree set is provided as tree_set.h and tree_set.cpp

for using hash_set as header file include it as #include "hash_set.h"

example program:

```
#include <bits/stdc++.h>
#include "hash_set.h"
using namespace std;
int main(){
  hash_set<int> st1;
	hash_set<int> st2;
	for(int i=0;i<10;i++){
		st1.insert(i);
	}
	for(int i=5;i<20;i++){
		st2.insert(i);
	}
  hash_set<int> st3=st1.find_union(st2); // find union of sets 'st1' and 'st2' and put it in set 'st3'
  hash_set<int> st3=st1.find_intersection(st2);
  hash_set<int> st3=st1.find_difference(st2);
  st3.print();
  return 0;
}
```
