## APS Project 2018

Implementation of hash_set using hash table and tree_set using order statistic tree (variant of AVL tree)

1. Hash set is packaged as hash_set.h and hash_set.cpp
2. Tree set is packaged as tree_set.h and tree_set.cpp

for using hash_set as header file include it as #include "hash_set.h"

**example program for hash_set:**

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
  hash_set<int> st3=st1.find_intersection(st2); // find intersection of sets 'st1' and 'st2' and put it in set 'st3'
  hash_set<int> st3=st1.find_difference(st2); // find difference of sets 'st1' and 'st2' (st1-st2) and put it in set 'st3'
  
  st3.print(); // print set elements in sorted order
  
  if(st1.find(5)==true){ // find a key exists in set
  	cout<<"Found\n";
  }else{
  	cout<<"Not Found\n";
  }
  
  st1.erase(4); // deletes an element from the set, if it exists
  
  if(st1.empty()){ // check if set is empty
  	cout<<"Set is empty\n";
  }
  
  return 0;
}
```

**example program for tree_set:**


```
#include <bits/stdc++.h>
#include "tree_set.h"
using namespace std;
int main(){

  tree_set<int> st1;
  tree_set<int> st2;
  
  for(int i=0;i<10;i++){
      st1.insert(i);
   }
   
   for(int i=5;i<20;i++){
	st2.insert(i);
   }
   
  tree_set<int> st3=st1.find_union(st2); // find union of sets 'st1' and 'st2' and put it in set 'st3'
  tree_set<int> st3=st1.find_intersection(st2); // find intersection of sets 'st1' and 'st2' and put it in set 'st3'
  tree_set<int> st3=st1.find_difference(st2); // find difference of sets 'st1' and 'st2' (st1-st2) and put it in set 'st3'
  
  st3.print(); // print set elements in sorted order
  
  if(st1.find(5)==true){ // find a key exists in set
  	cout<<"Found\n";
  }else{
  	cout<<"Not Found\n";
  }
  
  st1.erase(4); // deletes an element from the set, if it exists
  
  if(st1.empty()){ // check if set is empty
  	cout<<"Set is empty\n";
  }
  
  int smallest = st1.find_smallest(); // finds smallest element in the set
  cout<<"Smallest element is: <<smallest<<endl;
  
  st1.remove_smallest(); // removes the smallest element from the set.
  
  return 0;
}
```
