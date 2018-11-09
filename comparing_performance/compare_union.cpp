#include <bits/stdc++.h>

#include "hash_set.h"
typedef long long ll;
using namespace std;

int main(){
    int first=10000;
    int second=99001;
    vector<int> arr1(first);

    ifstream in1;
    in1.open("test_file1.txt");
    for(int i=0;i<first;i++){
        ll x;
        in1>>x;
        arr1[i]=x;
    }
    //cout<<arr1.size()<<"\n";
    vector<int> arr2(second);

    ifstream in2;
    in2.open("test_file2.txt");
    for(int i=0;i<second;i++){
        ll x;
        in2>>x;
        arr2[i]=x;
    }
// test for time from here
    hash_set<int> st1;
	for(int i=0;i<first;i++){
        st1.insert(arr1[i]);
    }
    //st1.print();
    //cout<<st1.occupied<<"\n";
    hash_set<int> st2;
	for(int i=0;i<second;i++){
        st2.insert(arr2[i]);
    }
    //st2.print();
    //cout<<st2.occupied<<"\n";
    hash_set<int> st3=st1.find_union(st2);
    //cout<<st3.occupied<<"\n";
    st3.print();
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