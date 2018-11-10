#include <bits/stdc++.h>
#include "hash_set.h"
#include "tree_set.h"
#include <chrono>
typedef long long ll;
using namespace std;
using namespace std::chrono;

int main(){
	//hash_set<int> st1;
	//hash_set<int> st2;
	tree_set<int> st1;
	tree_set<int> st2;
	for(int i=0;i<10;i++){
		st1.insert(i);
	}
	for(int i=5;i<100000;i++){
		st2.insert(i);
	}

	auto start = high_resolution_clock::now();

	//hash_set<int> st3=st2.find_intersection(st1);
	tree_set<int> st3=st2.find_intersection(st1);
	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by hash_set find_intersection: "<< duration.count() << " microseconds\n"; 
	st3.print();

	return 0;
}