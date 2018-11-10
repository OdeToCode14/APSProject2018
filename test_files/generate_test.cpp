#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
int main () {
 /* ofstream file;
  file.open ("test_file.txt");
  for(int i=0;i<10;i++){
  	file<<i<<"\n";
  }
  //file << "Please writr this text to a file.\n this text is written using C++\n";
  file.close();
  */
	int left=1,right=100000;
  int pos=0;
	vector<int> arr(right-left+1);
	for(int i=left;i<=right;i++){
		arr[pos++]=i;
	}
	random_shuffle(arr.begin(),arr.end());
	
  ofstream file;
  file.open ("test_file1_10^5.txt");
  for(int i=0;i<arr.size();i++){
	 file<<arr[i]<<"\n";
  }

  //file << "Please writr this text to a file.\n this text is written using C++\n";
  file.close();

  left=50001,right=150000;
  vector<int> arr2(right-left+1);
  pos=0;
  for(int i=left;i<=right;i++){
    arr2[pos++]=i;
  }
  random_shuffle(arr2.begin(),arr2.end());
  
  ofstream file2;
  file2.open ("test_file2_10^5.txt");
  for(int i=0;i<arr2.size();i++){
    file2<<arr2[i]<<"\n";
  }

  //file << "Please writr this text to a file.\n this text is written using C++\n";
  file.close();

  return 0;
}