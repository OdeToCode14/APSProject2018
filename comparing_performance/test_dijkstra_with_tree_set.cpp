#include <bits/stdc++.h>

#include "hash_set.h"
#include "tree_set.h"

#include <chrono>
typedef long long ll;
using namespace std;
using namespace std::chrono; 


typedef pair<int,int> pr;
 
int inf = INT_MAX;

int main(){
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    ifstream in;
    in.open("dijkstra_test_file.txt");


    int n,m;
    in>>n;
    in>>m;
    vector<vector<pair<int,int>>> adj(n);
    vector<int> dist(n,inf);
    vector<bool> done(n,false);
    for(int i=0;i<m;i++){
        int a,b;
        int wt;
        in>>a;
        in>>b;
        in>>wt;
        a--;
        b--;
        adj[a].push_back(make_pair(b,wt));
        //adj[b].push_back(make_pair(a,wt));
    }
    in.close();
     //priority_queue< pr, vector <pr> , greater<pr> > pq;
     tree_set<pr> pq;
     dist[0]=0;
 
     //pq.push(make_pair(0,0));
     auto start = high_resolution_clock::now();
     
     pq.insert(make_pair(0,0));
     while(!pq.empty()){
         pr th=pq.find_smallest();
         pq.remove_smallest();
         int nd=th.first;
         int d=th.second;
 
         if(done[nd] == true){
             continue;
         }
         else{
             //dist[nd]=d;
             done[nd]=true;
         }
         for(int i=0;i<adj[nd].size();i++){
             int neigh=adj[nd][i].first;
             int len=adj[nd][i].second;
             if(dist[nd]+len < dist[neigh]){
                dist[neigh] = dist[nd]+len;
                pq.insert(make_pair(neigh,dist[neigh]));
             }
             //dist[neigh]=min(dist[nd]+len , dist[neigh]);
         }
     }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by tree_set for dijkstra on this file: "<< duration.count() << " microseconds\n";
    
    ofstream out;
    out.open("output_dijkstra_with_tree_set.txt");
     for(int i=1;i<n;i++){
         out<<dist[i]<<" ";
     }
     out<<endl;
     out.close();
     //cout<<n<<" "<<m;
}
/*
int main(){

	
    int first=0;
    int second=0;
    string file1="test_file1_10^4.txt";
    string file2="test_file2_10^4.txt";
   

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
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by hash_set find_union: "<< duration.count() << " microseconds\n"; 
    //cout<<hs_st3.occupied<<"\n";
    //hs_st3.print();

     start = high_resolution_clock::now();
    tree_set<int> tr_st3=tr_st1.find_union(tr_st2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by tree_set find_union: "<< duration.count() << " microseconds\n";
    
 
	return 0;
}
*/