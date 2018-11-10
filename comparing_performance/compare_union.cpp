#include <bits/stdc++.h>

#include "hash_set.h"
#include "tree_set.h"

#include <chrono>
typedef long long ll;
using namespace std::chrono; 

int main(){
	hash_set<int> te;
	auto start = high_resolution_clock::now();
	for(int i=0;i<1000;i++){
		te.insert(i);
	}
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by hash_set inserion: "<< duration.count() << " microseconds\n"; 

	/*
    int first=0;
    int second=0;
    string file1="test_file1_10^6.txt";
    string file2="test_file2_10^6.txt";
   

   //calculate first and second sizes
    ifstream in;
    in.open(file1);
    if (!in){
        cout << "\nError opening file.\n";
        return 0;
    }
    //in>>total_num;
    //total_num=0;
    ll dummy;
    while(in>>dummy){
        first++;
    }
    
    in.close();

    in.open(file2);
    if (!in){
        cout << "\nError opening file.\n";
        return 0;
    }
    //in>>total_num;
    //total_num=0;
    while(in>>dummy){
        second++;
    }
    
    in.close();

cout<<"sizes of two files "<<first<<" " << second<<"\n";

  //put numbers in array
    vector<int> arr1(first);

    ifstream in1;
    in1.open(file1);
    for(int i=0;i<first;i++){
        ll x;
        in1>>x;
        arr1[i]=x;
    }
    //cout<<arr1.size()<<"\n";
    vector<int> arr2(second);

    ifstream in2;
    in2.open(file2);
    for(int i=0;i<second;i++){
        ll x;
        in2>>x;
        arr2[i]=x;
    }

// test for time from here

    //insert into sets
    hash_set<int> hs_st1;
	for(int i=0;i<first;i++){
        hs_st1.insert(arr1[i]);
    }
    //st1.print();
    //cout<<st1.occupied<<"\n";
    hash_set<int> hs_st2;
	for(int i=0;i<second;i++){
        hs_st2.insert(arr2[i]);
    }
    //st2.print();
    //cout<<st2.occupied<<"\n";

    tree_set<int> tr_st1;
	for(int i=0;i<first;i++){
        tr_st1.insert(arr1[i]);
    }
    //st1.print();
    //cout<<st1.occupied<<"\n";
    tree_set<int> tr_st2;
	for(int i=0;i<second;i++){
        tr_st2.insert(arr2[i]);
    }

    auto start = high_resolution_clock::now();
    
    hash_set<int> hs_st3=hs_st1.find_union(hs_st2);
    
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by hash_set find_union: "<< duration.count() << " microseconds\n"; 
    //cout<<hs_st3.occupied<<"\n";
    //hs_st3.print();

     start = high_resolution_clock::now();
    tree_set<int> tr_st3=tr_st1.find_union(tr_st2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by tree_set find_union: "<< duration.count() << " microseconds\n";
    */
    //cout<<tr_st3.occupied<<"\n";
    //tr_st3.print();
/*
    int left=1,right=10000;
    int pos=0;
	vector<int> arr1(right-left+1);
	for(int i=left;i<=right;i++){
		arr1[pos++]=i;
	}
	random_shuffle(arr1.begin(),arr1.end());
	

  	left=1000,right=100000;
    vector<int> arr2(right-left+1);
    pos=0;
    for(int i=left;i<=right;i++){
		arr2[pos++]=i;
	}
	random_shuffle(arr2.begin(),arr2.end());
// test for time from here
    hash_set<int> st1;
	for(int i=0;i<arr1.size();i++){
        st1.insert(arr1[i]);
    }
    hash_set<int> st2;
	for(int i=0;i<arr2.size();i++){
        st2.insert(arr2[i]);
    }
    hash_set<int> st3=st1.find_union(st2);
    st3.print();
    //cout<<st3.occupied<<"\n";
*/
	return 0;
}