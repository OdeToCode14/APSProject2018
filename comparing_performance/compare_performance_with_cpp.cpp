#include <bits/stdc++.h>

#include "hash_set.h"
#include "tree_set.h"

#include <chrono>
typedef long long ll;
using namespace std::chrono; 
using namespace std;
int main(){
	// hash_set<int> te;
	// auto start = high_resolution_clock::now();
	// for(int i=0;i<1000;i++){
	// 	te.insert(i);
	// }
 //    auto stop = high_resolution_clock::now(); 
 //    auto duration = duration_cast<microseconds>(stop - start);
 //    cout << "Time taken by hash_set inserion: "<< duration.count() << " microseconds\n"; 

	
    int first=0;
    
    string file1="test_file1_10^6.txt";
   
   

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


    cout<<"size of file "<<first<<"\n";

  //put numbers in array
    vector<int> arr1(first);

    ifstream in1;
    in1.open(file1);
    for(int i=0;i<first;i++){
        ll x;
        in1>>x;
        arr1[i]=x;
    }

    //C++ unordered_set
    //insert into sets
    auto start = high_resolution_clock::now();
    unordered_set<int> s1;
    for(int i=0;i<first;i++){
        s1.insert(arr1[i]);
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by C++ unordered_set insertion: "<< duration.count() << " microseconds\n";
 


    //insert hash_set
    start = high_resolution_clock::now();
    hash_set<int> hs_st1;
	for(int i=0;i<first;i++){
        hs_st1.insert(arr1[i]);
    }
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by hash_set insertion: "<< duration.count() << " microseconds\n";
    

    //insert into C++ set
    start = high_resolution_clock::now();
    set<int> s2;
    for(int i=0;i<first;i++){
        s2.insert(arr1[i]);
    }
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by C++ set insertion: "<< duration.count() << " microseconds\n";

    //insert into tree_set
    start = high_resolution_clock::now();
    tree_set<int> tr_st1;
	for(int i=0;i<first;i++){
        tr_st1.insert(arr1[i]);
    }
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by tree_set insertion: "<< duration.count() << " microseconds\n";

	return 0;
}